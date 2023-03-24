// Szkielet klienta TCP/IPv4.
//
// Po podmienieniu SOCK_STREAM na SOCK_DGRAM staje się on szkieletem klienta
// UDP/IPv4 korzystającego z gniazdka działającego w trybie połączeniowym.
// adres IPv4 w argv[1], numer portu TCP w argv[2]

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        perror("Niepoprawna liczba argumentow, poprawne uzycie to: ./zadanie7 adresIP numerPortu");
        exit(1);
    }

    char * ipv4 = argv[1];
    int port = atoi(argv[2]);
    int sock;
    int rc;         // "rc" to skrót słów "result code"
    ssize_t cnt;    // wyniki zwracane przez read() i write() są tego typu

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = { .s_addr = inet_addr(ipv4) },   // 127.0.0.1
        .sin_port = htons(port)
    };

    //inet_aton(ipv4, &( addr.sin_addr ));

    rc = connect(sock, (struct sockaddr *) & addr, sizeof(addr));
    if (rc == -1) {
        perror("connect");
        return 1;
    }
    
    unsigned char buf[128];

    cnt = read(sock, buf, 128);
    if (cnt == -1) {
        perror("read");
        return 1;
    }

    for(int i = 0; buf[i] != 0; i++) 
    {
        if(buf[i] < 32 || buf[i] > 126)
            printf("?");
        else
            printf("%c", buf[i]);
    }

    printf("\nRead: %zi bytes\n", cnt);
    
    //printf("%s", buf);
    rc = close(sock);
    if (rc == -1) {
        perror("close");
        return 1;
    }

    return 0;
}

/* gcc -g -std=c99 -pedantic -Wall zadanie7.c -o zadanie7
   ./zadanie7
*/
