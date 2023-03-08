#include <stdio.h>

void drukuj(int tablica[], int liczba_elementow)
{
    printf("Drukuje tablice: \n");

    for(int i = 0; i < liczba_elementow; i++) {
        printf("%d ", tablica[i]);
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
    
    drukuj(liczby, liczba_elementow);

  
    return 0;
}

/* gcc -g -std=c99 -pedantic -Wall zadanie1.c -o zadanie1 
   ./zadanie1
*/
