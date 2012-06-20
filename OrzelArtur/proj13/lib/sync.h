#ifndef __SYNC_H__
#define __SYNC_H__

#include<sys/types.h>
#include<sys/sem.h>
#include<sys/resource.h>

/**
	Sta³a zawieraj±ca pocz±tek nazwy ka¿dego pliku ze statystukami dotycz±cego pojedynczego w±tku/procesu.
*/
#define LOG_NAZWA "log"

/**
	Sta³a okre¶laj±ca maksymalny rozmiar nazw plików podawanych jako argumenty wywo³añ funkcji, a tak¿e pól struktur przechowuj±cych takie dane.
*/
#define DL_NAZWY 50

/**
	Sta³a okre¶laj±ca maksymaln± d³ugo¶æ ¶cie¿ki podawan± jako katalog z plikami logów.
*/
#define DL_SCIEZKI 120

/**
	Sta³a okre¶laj±ca rozmiar bufora danych przy operacjach na plikach z logami. 
*/
#define BUFOR 100

/**
	Sta³a tesktowa zawieraj±ca frazê wstawian± do pliku z logiem przy rozpoczêciu zapisywania.
*/
#define START "START"

/**
	Sta³a tesktowa zawieraj±ca frazê wstawian± do pliku z logiem przy próbie wej¶cia do sekcji krytycznej.
*/
#define TRY "TRY"

/**
	Sta³a tesktowa zawieraj±ca frazê wstawian± do pliku z logiem po wej¶ciu do sekcji krytycznej.
*/
#define IN "IN"

/**
	Sta³a tesktowa zawieraj±ca frazê wstawian± do pliku z logiem po wyj¶ciu z sekcji krytycznej.
*/
#define OUT "OUT"

/**
	Sta³a tesktowa zawieraj±ca frazê wstawian± do pliku z logiem przy koñczeniu zapisywania.
*/
#define STOP "STOP"

/**
	Sta³a okre¶laj±ca poprawne zakoñczenie dzia³ania funkcji.
*/
#define SUKCES 0

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - podano nieprawid³owe argumenty.
*/
#define ARG_ERR 1

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³o siê tworzenie struktury danych. Mo¿e byæ spowodowany przez próbê utworzenia od nowa istniej±cego pliku.
*/
#define TWORZENIE_ERR 2

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³o siê pod³±czenie do istniej±cego zasobu.
*/
#define POBRANIE_ERR 3

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³o siê przy³±czenie do pamiêci wspólnej lub inicjalizacja warto¶ci struktury danych.
*/
#define INICJALIZACJA_ERR 4

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³o siê usuniêcie struktury danych.
*/
#define USUNIECIE_ERR 5

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³o siê usuniêcie pliku zwi±zanego ze struktur± danych.
*/
#define USUNIECIE_PLIKU_ERR 6

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³a siê zmiana warto¶ci struktury danych lub zawarto¶ci pliku z logami.
*/
#define ZMIANA_ERR 7

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³o siê od³±czenie od istniej±cej stgruktury danych.
*/
#define ODLACZENIE_ERR 8

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³y siê operacje ogólne na zestawie plików z logami, byæ mo¿e podano nieprawid³owy katalog.
*/
#define LOGI_ERR 9

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³y siê operacje plikowe na konkretnym pliku z logami.
*/
#define LOG_ERR 10

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - plik z logiem zawiera nieprawid³owe dane.
*/
#define ODCZYT_ERR 11

/**
	Sta³a okre¶laj±ca b³êdne zakoñczenie dzia³ania funkcji - nie powiod³y siê operacje zwi±zane z ochron± plików z logami pod k±tem zakoñczenia dzia³ania programu za pomoc± sygna³ów.
*/
#define SYGNALY_ERR 12

/**
	Struktura zawieraj±ca informacje o semaforach komunikacji miêdzyprocesowej Systemu V. Przechowuje informacje konieczne do dzia³ania funkcji bibliotecznych operuj±cych na zbiorze semaforów.
*/
typedef struct
{
/**
	Identyfikator zbioru semaforów w sensie komunikacji miêdzyprocesowej Systemu V.
*/
	int sem_id;
/**
	Liczba okre¶laj±ca liczbê semaforów w zbiorze semaforów.
*/
	int ile_sem;
/**
	Nazwa zbioru semaforów w systemie plików w sensie komunikacji miêdzyprocesowej Systemu V.
*/
	char sem_nazwa[DL_NAZWY];
} semafor_t;

/**
	Struktura danych zawieraj±ca informacje o pamiêci wspólnej IPC Systemu V. Zawiera dane potrzebne do dzia³ania funkcji operuj±cych na takiej pamiêci.
*/
typedef struct
{
/**
	Identyfikator pamiêci wspólnej - taki jak w IPC Systemu V.
*/
	int pam_id;
/**
	Rozmiar utworzonej/przydzielonej pamiêci wspólnej wyra¿ony w bajtach.
*/
	int rozmiar_pam;
/**
	Nazwa pamiêci wspólnej w systemie plików - taka jak w IPC Systemu V.
*/
	char pam_nazwa[DL_NAZWY];
/**
	Wska¼nik na pocz±tek utworzonej i przy³±czonej pamiêci wspólnej.
*/
	void * pam_adres;
} pamiec_t;

/**
	Skrócona nazwa typu zmiennej warunkowej standardu POSIX.
*/
typedef	pthread_cond_t monitor_t;

/**
	Skrócona nazwa typu blokad odczytu/zapisu standardu POSIX.
*/
typedef pthread_rwlock_t rwlock_t;

/**
	Skrócona nazwa typu mutexów standardu POSIX.
*/
typedef pthread_mutex_t mutex_t;

/**
	Skrócona nazwa typu odpowiadaj±cego w±tkom standardu POSIX.
*/
typedef pthread_t watek_t;

/**
	Struktura zawieraj±ca informacje potrzebne przy tworzeniu logów ze statystykami.
*/
typedef struct
{
/**
	Wska¼nik na otwarty plik ze statystykami.	
*/
	FILE * log;
/**
	¦cie¿ka pliku ze statystykami.
*/
	char log_nazwa[DL_SCIEZKI];
/**
	Numer w±tku, w którym prowadzone s± statystyki.
*/
	pid_t tid;
} staty_t;

int stworz_semafory(semafor_t * semafor, int liczba, int ident, 
		int ile_inicjalizowanych, ...);

int zmien_semafory(semafor_t * semafor, struct sembuf * sops, int nsops);

int usun_semafory(semafor_t * semafor);

int stworz_pamiec(pamiec_t * pamiec, int rozmiar, int ident, int czy_podlaczyc);

int zwolnij_pamiec(pamiec_t * pamiec, int czy_usunac);

int stworz_watek(watek_t * watek, int czy_odlaczony, void * (*funkcja) (void *), void * arg);

int stworz_staty(staty_t * staty, char * nazwa, char * katalog);

int log_staty(staty_t * staty, char * opis);

int zakoncz_staty(staty_t * staty);

int analizuj_staty(char * sciezka, char * sciezka_logu_ost);

char * error2str(int error);

#endif
