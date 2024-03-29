# Programowanie-sieciowe
### Repozytorium zawiera rozwiązania zadań z przedmiotu Programowanie Sieciowe prowadzonego na Wydziale Fizyki, Astronomii i Informatyki Stosowanej UJ w roku akademickim 2022-2023.
 

#### Zestaw 01:

1. Napisz program w C deklarujący w funkcji main tablicę int liczby[50] i wczytujący do niej z klawiatury kolejne liczby. 
     - Wczytywanie należy przerwać gdy użytkownik wpisze zero albo gdy skończy się miejsce w tablicy (tzn. po wczytaniu 50 liczb).

     - Z main należy następnie wywoływać pomocniczą funkcję drukuj, przekazując jej jako argumenty adres tablicy oraz liczbę wczytanych do niej liczb.   
     - Funkcję tę zadeklaruj jako ```void drukuj(int tablica[], int liczba_elementow)```. W jej ciele ma być pętla for drukująca te elementy tablicy, które są większe od 10 i mniejsze od 100.

2. Przypomnij sobie wiadomości o wskaźnikach i arytmetyce wskaźnikowej w C. Napisz alternatywną wersję funkcji drukującej liczby, o sygnaturze void drukuj_alt(int * tablica, int liczba_elementow). 
     - Nie używaj w niej indeksowania zmienną całkowitoliczbową (nie może się więc pojawić ani ```tablica[i]```, ani ```*(tablica+i))```, zamiast tego użyj wskaźnika przesuwanego z elementu na element przy pomocy ++.

3. Opracuj funkcję sprawdzającą, czy przekazany jej bufor zawiera tylko i wyłącznie drukowalne znaki ASCII, tzn. bajty o wartościach z przedziału domkniętego [32, 126]. 
    - Funkcja ma mieć następującą sygnaturę: ```bool printable_buf(const void * buf, int len)```.
    - Pamiętaj o włączeniu nagłówka ```<stdbool.h>```, bez niego kompilator nie rozpozna ani nazwy typu bool, ani nazw stałych true i false.
    - Trzeba będzie użyć rzutowania wskaźników, bo typ void * oznacza „adres w pamięci, ale bez informacji o tym co w tym fragmencie pamięci się znajduje”. Na początku ciała funkcji trzeba go zrzutować do typu „adres fragmentu pamięci zawierającego ciąg bajtów”.

4. A teraz opracuj wersję, która jako argument dostaje łańcuch w sensie języka C, czyli ciąg niezerowych bajtów zakończony bajtem równym zero (ten końcowy bajt nie jest uznawany za należący do łańcucha).
    - Ta wersja funkcji powinna mieć taką sygnaturę: ```bool printable_str(const char * buf)```.

5. W dokumentacji POSIX API znajdź opisy czterech podstawowych funkcji plikowego wejścia-wyjścia, tzn. open, read, write i close.
    - Czy zgadzają się one z tym, co pamiętasz z przedmiotu „Systemy operacyjne”? Jakie znaczenie ma wartość 0 zwrócona jako wynik funkcji read?

6. Zaimplementuj program kopiujący dane z pliku do pliku przy pomocy powyższych funkcji. Zakładamy, że nazwy plików są podawane przez użytkownika jako argumenty programu (tzn. będą dostępne w tablicy ```argv```). 
   - Zwróć szczególną uwagę na obsługę błędów — każde wywołanie funkcji we-wy musi być opatrzone testem sprawdzającym, czy zakończyło się ono sukcesem, czy porażką.
   - Funkcje POSIX zwracają -1 aby zasygnalizować wystąpienie błędu, i dodatkowo zapisują w globalnej zmiennej errno kod wskazujący przyczynę wystąpienia błędu (na dysku nie ma pliku o takiej nazwie, brak wystarczających praw dostępu, itd.). Polecam Państwa uwadze pomocniczą funkcję perror, która potrafi przetłumaczyć ten kod na zrozumiały dla człowieka komunikat i wypisać go na ekranie.
   
   
   

#### Zestaw 02:
1. Linuksowe dystrybucje zazwyczaj zawierają program netcat (może być też dostępny pod nazwą nc) lub jego ulepszoną wersję, ncat. Pozwala on m.in. nawiązać połączenie ze wskazanym serwerem, a następnie wysyłać do niego znaki wpisywane z klawiatury; odpowiedzi zwracane przez serwer są drukowane na ekranie. Pozwala też uruchomić się w trybie serwera czekającego na połączenie na wskazanym numerze portu.

 - Otwórz dwa okna terminalowe, w pierwszym z nich uruchom
ncat -v -l 20123
a w drugim
ncat -v 127.0.0.1 20123


2. Wszystkie wersje netcata domyślnie korzystają z TCP. Trzeba im podać w linii komend opcję -u, aby zamiast gniazdka TCP utworzone zostało gniazdko UDP. Powtórz eksperymenty używając poleceń:

 ncat -v -u -l 20123
 ncat -v -u 127.0.0.1 20123

3. Przejrzyj dokumentację netcata, upewnij się co do znaczenia opcji -v, -l oraz -u. Sprawdź też co robi opcja -C, czyli --crlf. W jakich sytuacjach może ona być potrzebna?


4. (nieobowiązkowe) 

5. Napisz prosty serwer zwracający wizytówkę. Powinien tworzyć gniazdko TCP nasłuchujące na porcie o numerze podanym jako argv[1] (użyj socket, bind i listen), następnie w pętli czekać na przychodzące połączenia (accept), wysyłać ciąg bajtów Hello, world!\r\n jako swoją wizytówkę, zamykać odebrane połączenie i wracać na początek pętli. Pętla ma działać w nieskończoność, aby przerwać działanie programu trzeba będzie użyć Ctrl-C.


6. Przetestuj netcatem powyższy serwer.


7. Napisz prostego klienta, który łączy się (użyj socket i connect) z usługą wskazaną argumentami podanymi w linii komend (adres IPv4 w argv[1], numer portu TCP w argv[2]), drukuje na ekranie wizytówkę zwróconą przez serwer i kończy pracę. Pamiętaj o zasadzie ograniczonego zaufania i przed przesłaniem odebranego bajtu na stdout weryfikuj, czy jest to znak drukowalny lub znak kontrolny używany do zakończenia linii bądź wstawienia odstępu ('\n', '\r' oraz '\t').


8. Sprawdź, czy program-klient poprawnie współdziała z programem-serwerem.

9. Spróbuj napisać podobną parę klient-serwer komunikującą się za pomocą protokołu UDP. Pamiętaj, że UDP nie jest protokołem połączeniowym: wywołanie connect na gniazdku UDP nie powoduje wysłania w sieć żadnych pakietów. Klient musi jako pierwszy wysłać jakiś datagram, a serwer dowiaduje się o istnieniu klienta dopiero gdy ten datagram do niego dotrze. Sprawdź, czy możliwe jest wysyłanie pustych datagramów (tzn. o długości zero bajtów) — jeśli tak, to może niech klient właśnie taki wysyła?
