#include <stdbool.h>
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
    if (argc != 2)
    {
        perror("Niepoprawna liczba argumentow, poprawne uzycie to: ./zadanie5 numerPortu");
        exit(1);
    }

    int port = atoi(argv[1]);
    int listeningSocket, len, n;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    char *msg = "Cześć, tu serwer!";

    // Tworzenie gniazda
    listeningSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (listeningSocket == -1) {
        perror("socket()");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Konfiguracja adresu serwera
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // Przypisanie adresu serwera do gniazda
    if (bind(listeningSocket, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Nieudane przypisanie adresu serwera do gniazda");
        exit(1);
    }

    printf("Serwer uruchomiony i nasłuchuje na porcie %d\n", port);

    len = sizeof(cliaddr);

    // Nieskończona pętla odbierająca i wysyłająca wiadomości
    while(true) {
        n = recvfrom(listeningSocket, (char *)buffer, sizeof(buffer),
                     0, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
        buffer[n] = '\0';
        printf("(serwer): Odebrano wiadomość od klienta: %s\n", buffer);

        sendto(listeningSocket, (const char *)msg, strlen(msg),
               0, (const struct sockaddr *)&cliaddr, len);
        printf("(serwer): Wysłano wiadomość do klienta.\n");

        
    }

  
    if (close(listeningSocket) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}




/* gcc -g -std=c99 -pedantic -Wall zadanie9s.c -o zadanie9s
   ./zadanie9s
*/

