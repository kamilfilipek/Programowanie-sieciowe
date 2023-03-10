// Szkielet serwera TCP/IPv4.
#define _POSIX_C_SOUresult_codeE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>


int main(int argc, char *argv[])
{

    int port = atoi(argv[1]);
    int listening_socket;   // gniazdko nasłuchujące
    int client_socket;  // gniazdko połączone z bieżącym klientem
    int result_code;         // "result_code" to skrót słów "result code"
    ssize_t cnt;    // wyniki zwracane przez read() i write() są tego typu
  
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listening_socket == -1) {
        perror("socket");
        return 1;
    }
    printf("port = %d \n", port);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = { .s_addr = htonl(INADDR_ANY) },
        .sin_port = htons(port)
    };

    
    result_code = bind(listening_socket, (struct sockaddr *) & addr, sizeof(addr));
    if (result_code == -1) {
        perror("bind");
        return 1;
    }

    result_code = listen(listening_socket, 10);
    if (result_code == -1) {
        perror("listen");
        return 1;
    }   
    

    while(true) 
    {
        client_socket = accept(listening_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("accept");
            return 1;
        }
  
        unsigned char buf[16];
        memcpy(buf, "Hello\r\n", 7);

        cnt = write(client_socket, buf, 7);
        if (cnt == -1) {
            perror("write");
            return 1;
        }
        printf("wrote %zi bytes\n", cnt);

        result_code = close(client_socket);
        if (result_code == -1) {
            perror("close");
            return 1;
        }
    }

    result_code = close(listening_socket);
    if (result_code == -1) {
        perror("close");
        return 1;
    }

    return 0;
}

/* gcc -g -std=c99 -pedantic -Wall zadanie5.c -o zadanie5
   ./zadanie5
*/
