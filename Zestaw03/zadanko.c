#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 200809L
#define PORT 2020
#define DATA_SIZE 65520

bool doesSocketExist = false;

int main(int argc, char *argv[])
{
    int socketDescriptor, resultCode;
    ssize_t cnt; 

    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor == -1) 
    {
        perror("socket() error");
        exit(1);
    }

    doesSocketExist = true;

    struct sockaddr_in addr = 
    {
        .sin_family = AF_INET,
        .sin_addr = { .s_addr = htonl(INADDR_ANY) },
        .sin_port = htons(PORT)
    };

    resultCode = bind(socketDescriptor, (struct sockaddr *) & addr, sizeof(addr));
    if (resultCode == -1) 
    {
        perror("bind() error");
        exit(1);
    }

    // głowna pętla
    while(true) 
    {
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_len = sizeof(clnt_addr);

        bool isDataRead = false, error = false; 
        char number[DATA_SIZE];
        unsigned char buf[DATA_SIZE + 1];
        int size_of_number = 0; // z ilu cyfr sklada sie liczba
        long int sum = 0;   // suma dzialania
        

        cnt = recvfrom(socketDescriptor, buf, sizeof(buf), 0, (struct sockaddr *) & clnt_addr, & clnt_addr_len);
        if (cnt == -1) 
        {
            perror("recvfrom() error");
            exit(1);
        }

        bool hasSignAppeared = false;
        for (int i = 0, j = 0, previousSignIndex = 0; i < sizeof(buf); i++)
        {
            if(buf[i] == ' ') // jeśli mamy spację, to jest to błąd. 
            {
                error = true;
                break;
            }

            else if(buf[i] == '+' || buf[i] == '-' || buf[i] == 10 || (buf[i] == 13 && buf[i + 1] == 10))
            {
                // Obsługa: pustej wiadomości
                if((buf[i] == '\n' || (buf[i] == '\r' && buf[i + 1] == '\n')) && hasSignAppeared == false && size_of_number == 0)
                {
                    error = true;
                    isDataRead = true;
                    break;
                }

                // Obsługa: wiadomości niepoprawnie zaczynającej się od znaku
                if(size_of_number == 0 && (buf[i] == '+' || buf[i] == '-'))
                {
                    error = true;
                    break;
                }

                // Obsługa: wiadomości zawierającej 2 znaki po sobie 
                if(buf[i - 1] == '+' || buf[i - 1] == '-')
                {
                    error = true;
                    break;
                }
                
                number[j] = '\0';
                long int convertedNumber = atoi(number);

                // Sprawdzanie poprawnosci konwersji
                long int test = convertedNumber;
                for (int k = j - 1; k >= 0; k--)
                {
                    if(number[k] - '0' != test % 10)
                    {
                        error = true;
                        break;
                    }

                    test = test / 10;
                }

                // przepełnienie
                if(sum > sum + convertedNumber || error == true)
                {
                    error = true;
                    break;
                }

                // Sprawdzenie, czy jest to pierwsze wystąpienie znaku działania
                if(hasSignAppeared == false)
                {
                    sum = sum + convertedNumber;
                    hasSignAppeared = true;
                }

                // Działania
                if(buf[previousSignIndex] == '-')
                {
                    sum = sum - convertedNumber;
                }
                if(buf[previousSignIndex] == '+')
                {
                    sum = sum + convertedNumber;

                }
                
                previousSignIndex = i;   // poprzednie wystąpienie znaku działanka
                j = 0;  

                // Sprawdzenie, czy występuje znak końca linii
                if(buf[i] == '\n' || (buf[i] == '\r' && buf[i + 1] == '\n'))
                {
                    isDataRead = true;
                    break;
                } 
            }
            // Sprawdzenie, czy aktualny znak w wiadomości jest cyfrą
            else if(buf[i] >= '0' && buf[i] <= '9')
            {
                number[j] = buf[i];
                size_of_number++;
                j++;
                if(j == 11) // liczba przekracza ulong_max na poziomie odbioru danych
                {
                    error = true;
                    break;
                }
            }
            else // niepoprawny znak ascii
            {
                error = true;
                break;
            }
        } // koniec for


        // działania końcowe.
        if(error)
        {
            cnt = sendto(socketDescriptor, "ERROR", 5, 0, (struct sockaddr *) & clnt_addr, clnt_addr_len);
            if (cnt == -1) 
            {
                perror("sendto() error");
                exit(1);
            }
           
        }
        else
        {
            int out = 0;

            if(isDataRead)
            {
                out = sprintf(number, "%ld\n", sum);
            }
            else
            {
                out = sprintf(number, "%ld", sum);
            }

            cnt = sendto(socketDescriptor, number, out, 0, (struct sockaddr *) & clnt_addr, clnt_addr_len);
            if (cnt == -1) 
            {
                perror("sendto() error");
                exit(1);
            }
        }
    } // koniec while


    // zamykanie gniazdka
    if(doesSocketExist)
    {
        resultCode = close(socketDescriptor);
        if (resultCode == -1) 
        {
            perror("close() error");
            exit(1);
        }
    }
    

    return 0;
}


/* gcc -g -std=c99 -pedantic -Wall zadanko.c -o zadanko
   ./zadanko
*/
