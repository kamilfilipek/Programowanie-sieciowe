#include <stdio.h>
#include <stdbool.h>

bool printable_str(const char * buf)
{
    unsigned int i = 0;
    while(buf[i] != '\0')
    {   
        if(buf[i] < 32 || buf[i] > 126) 
            return false;
        i++;
    }

    return true;
}


int main(int argc, char* argv[])
{
    char * test = "abcdefghi";
    char * test2 = "jklmnopr\x14";

    bool output = printable_str(test);
    printf("%d \n", output);

    output = printable_str(test2);
    printf("%d \n", output);

    return 0;
}

/* gcc -g -std=c99 -pedantic -Wall zadanie4.c -o zadanie4
   ./zadanie4
*/
