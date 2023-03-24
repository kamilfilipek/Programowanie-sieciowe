#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        perror("Niepoprawna liczba argumentow, poprawne uzycie to: ./zadanie7 numerPortu");
        exit(1);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024];
    char * msg = "Cześć, tu klient!";


    // Tworzenie gniazda
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket()");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Konfiguracja adresu serwera
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // Wysyłanie wiadomości do serwera
    sendto(sockfd, (const char *)msg, strlen(msg),
           0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("(klient): Wysłano wiadomość do serwera.\n");

    // Odbieranie odpowiedzi od serwera
    int len = sizeof(servaddr);
    int n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
                 0, (struct sockaddr *)&servaddr, (socklen_t *)&len);
    buffer[n] = '\0';
    printf("(klient): Odebrano wiadomość od serwera: %s\n", buffer);


    if (close(sockfd) == -1) {
        perror("close");
        return 1;
    }
    return 0;
}



/* gcc -g -std=c99 -pedantic -Wall zadanie9k.c -o zadanie9k
   ./zadanie9k
*/
