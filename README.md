# Programowanie-sieciowe
### Repozytorium zawiera rozwiązania zadań z przedmiotu Programowanie Sieciowe prowadzonego na Wydziale Fizyki, Astronomii i Informatyki Stosowanej UJ w roku akademickim 2022-2023.
 

### Zestaw01:

Napisz program w C deklarujący w funkcji main tablicę int liczby[50] i wczytujący do niej z klawiatury kolejne liczby. Wczytywanie należy przerwać gdy użytkownik wpisze zero albo gdy skończy się miejsce w tablicy (tzn. po wczytaniu 50 liczb).

Z main należy następnie wywoływać pomocniczą funkcję drukuj, przekazując jej jako argumenty adres tablicy oraz liczbę wczytanych do niej liczb. Funkcję tę zadeklaruj jako void drukuj(int tablica[], int liczba_elementow). W jej ciele ma być pętla for drukująca te elementy tablicy, które są większe od 10 i mniejsze od 100.

Przypomnij sobie wiadomości o wskaźnikach i arytmetyce wskaźnikowej w C. Napisz alternatywną wersję funkcji drukującej liczby, o sygnaturze void drukuj_alt(int * tablica, int liczba_elementow). Nie używaj w niej indeksowania zmienną całkowitoliczbową (nie może się więc pojawić ani tablica[i], ani *(tablica+i)), zamiast tego użyj wskaźnika przesuwanego z elementu na element przy pomocy ++.

Opracuj funkcję sprawdzającą, czy przekazany jej bufor zawiera tylko i wyłącznie drukowalne znaki ASCII, tzn. bajty o wartościach z przedziału domkniętego [32, 126]. Funkcja ma mieć następującą sygnaturę: bool printable_buf(const void * buf, int len).

Pamiętaj o włączeniu nagłówka <stdbool.h>, bez niego kompilator nie rozpozna ani nazwy typu bool, ani nazw stałych true i false.

Trzeba będzie użyć rzutowania wskaźników, bo typ void * oznacza „adres w pamięci, ale bez informacji o tym co w tym fragmencie pamięci się znajduje”. Na początku ciała funkcji trzeba go zrzutować do typu „adres fragmentu pamięci zawierającego ciąg bajtów”.

A teraz opracuj wersję, która jako argument dostaje łańcuch w sensie języka C, czyli ciąg niezerowych bajtów zakończony bajtem równym zero (ten końcowy bajt nie jest uznawany za należący do łańcucha). Ta wersja funkcji powinna mieć taką sygnaturę: bool printable_str(const char * buf).

W dokumentacji POSIX API znajdź opisy czterech podstawowych funkcji plikowego wejścia-wyjścia, tzn. open, read, write i close. Czy zgadzają się one z tym, co pamiętasz z przedmiotu „Systemy operacyjne”? Jakie znaczenie ma wartość 0 zwrócona jako wynik funkcji read?

Zaimplementuj program kopiujący dane z pliku do pliku przy pomocy powyższych funkcji. Zakładamy, że nazwy plików są podawane przez użytkownika jako argumenty programu (tzn. będą dostępne w tablicy argv). Zwróć szczególną uwagę na obsługę błędów — każde wywołanie funkcji we-wy musi być opatrzone testem sprawdzającym, czy zakończyło się ono sukcesem, czy porażką.

Funkcje POSIX zwracają -1 aby zasygnalizować wystąpienie błędu, i dodatkowo zapisują w globalnej zmiennej errno kod wskazujący przyczynę wystąpienia błędu (na dysku nie ma pliku o takiej nazwie, brak wystarczających praw dostępu, itd.). Polecam Państwa uwadze pomocniczą funkcję perror, która potrafi przetłumaczyć ten kod na zrozumiały dla człowieka komunikat i wypisać go na ekranie.

