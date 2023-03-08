#include <stdio.h>

void drukuj_alt(int * tablica, int liczba_elementow)
{
    printf("Drukuje tablice: \n");

    for(int * pointer = tablica; pointer < tablica + liczba_elementow; pointer++) {
        printf("%d ", *pointer);
    }

    printf("\n");
}


int main()
{
    int liczby[50];
    int liczba_elementow = 0;

    printf("Wpisuj inty: \n");
    do
    {
        scanf("%d", &liczby[liczba_elementow]);
        liczba_elementow++;
    }
    while (liczby[liczba_elementow-1] != 0 && liczba_elementow < 50);
    
    drukuj_alt(liczby, liczba_elementow);

  
    return 0;
}

/* gcc -g -std=c99 -pedantic -Wall zadanie2.c -o zadanie2 
   ./zadanie2
*/
