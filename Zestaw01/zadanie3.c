#include <stdio.h>
#include <stdbool.h>

bool printable_puf(const void * buf, int len)
{
    for(char * pointer = (char *) buf; pointer < (char *) buf + len; pointer++) {
        if(*pointer < 32 || *pointer > 126) 
            return false;
    }

    return true;
}


int main(int argc, char* argv[])
{
    char * test = "abcdefghi";
    char * test2 = "jklmnopr\x14";

    bool output = printable_puf(test, 9);
    printf("%d \n", output);

    output = printable_puf(test2, 9);
    printf("%d \n", output);

    return 0;
}

/* gcc -g -std=c99 -pedantic -Wall zadanie3.c -o zadanie3
   ./zadanie3
*/
