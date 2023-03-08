#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Bledne uzycie programu %s. Podaj 2 pliki rozdzielone spacja.\n", argv[0]);
        exit(1);
    }

    int inputFileDescriptor, outputFileDescriptor;
    char *inputFile = argv[1];
    char *outputFile = argv[2];

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    inputFileDescriptor = open(inputFile, O_RDONLY);
    outputFileDescriptor = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, mode);


    // potencjalne błędy otwierania plikow
    if(inputFileDescriptor == -1)
    {
        perror("Blad otworzenia pliku inputFile.");
        exit(-1);
    }
    if(outputFileDescriptor == -1)
    {
        perror("Blad otworzenia pliku outputFile");
        exit(-1);
    }

  
    char buffer[512];
    size_t nbytes = sizeof(buffer);
    ssize_t bytes_read;
 
    // czytanie pliku
    bytes_read = read(inputFileDescriptor, buffer, nbytes); 
    if(bytes_read == -1)
    {
        perror("Blad czytania pliku inputFile.");
        exit(-1);
    }

    // pisanie do pliku
    nbytes = strlen(buffer);
    ssize_t bytes_written = write(outputFileDescriptor, buffer, nbytes);
    if(bytes_written == -1)
    {
        perror("Blad pisania do pliku outputFile.");
        exit(-1);
    }


    // potencjalne błędy zamykania plikow
    if(close(inputFileDescriptor) == -1)
    {
        perror("inputFileDescriptor close error \n");
        exit(-1);
    }
    if(close(outputFileDescriptor) == -1)
    {
        perror("outputFileDescriptor close error \n");
        exit(-1);
    }

    printf("Sukces.\n");

    return 0;
}


/* gcc -g -std=c99 -pedantic -Wall zadanie6.c -o zadanie6
   ./zadanie6 input.txt output.txt
*/
