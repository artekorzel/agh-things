#ifndef __SYNC_H__
#define __SYNC_H__

#include<sys/types.h>
#include<sys/sem.h>
#include<sys/resource.h>

/**
	Sta�a zawieraj�ca pocz�tek nazwy ka�dego pliku ze statystukami dotycz�cego pojedynczego w�tku/procesu.
*/
#define LOG_NAZWA "log"

/**
	Sta�a okre�laj�ca maksymalny rozmiar nazw plik�w podawanych jako argumenty wywo�a� funkcji, a tak�e p�l struktur przechowuj�cych takie dane.
*/
#define DL_NAZWY 50

/**
	Sta�a okre�laj�ca maksymaln� d�ugo�� �cie�ki podawan� jako katalog z plikami log�w.
*/
#define DL_SCIEZKI 120

/**
	Sta�a okre�laj�ca rozmiar bufora danych przy operacjach na plikach z logami. 
*/
#define BUFOR 100

/**
	Sta�a tesktowa zawieraj�ca fraz� wstawian� do pliku z logiem przy rozpocz�ciu zapisywania.
*/
#define START "START"

/**
	Sta�a tesktowa zawieraj�ca fraz� wstawian� do pliku z logiem przy pr�bie wej�cia do sekcji krytycznej.
*/
#define TRY "TRY"

/**
	Sta�a tesktowa zawieraj�ca fraz� wstawian� do pliku z logiem po wej�ciu do sekcji krytycznej.
*/
#define IN "IN"

/**
	Sta�a tesktowa zawieraj�ca fraz� wstawian� do pliku z logiem po wyj�ciu z sekcji krytycznej.
*/
#define OUT "OUT"

/**
	Sta�a tesktowa zawieraj�ca fraz� wstawian� do pliku z logiem przy ko�czeniu zapisywania.
*/
#define STOP "STOP"

/**
	Sta�a okre�laj�ca poprawne zako�czenie dzia�ania funkcji.
*/
#define SUKCES 0

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - podano nieprawid�owe argumenty.
*/
#define ARG_ERR 1

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�o si� tworzenie struktury danych. Mo�e by� spowodowany przez pr�b� utworzenia od nowa istniej�cego pliku.
*/
#define TWORZENIE_ERR 2

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�o si� pod��czenie do istniej�cego zasobu.
*/
#define POBRANIE_ERR 3

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�o si� przy��czenie do pami�ci wsp�lnej lub inicjalizacja warto�ci struktury danych.
*/
#define INICJALIZACJA_ERR 4

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�o si� usuni�cie struktury danych.
*/
#define USUNIECIE_ERR 5

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�o si� usuni�cie pliku zwi�zanego ze struktur� danych.
*/
#define USUNIECIE_PLIKU_ERR 6

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�a si� zmiana warto�ci struktury danych lub zawarto�ci pliku z logami.
*/
#define ZMIANA_ERR 7

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�o si� od��czenie od istniej�cej stgruktury danych.
*/
#define ODLACZENIE_ERR 8

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�y si� operacje og�lne na zestawie plik�w z logami, by� mo�e podano nieprawid�owy katalog.
*/
#define LOGI_ERR 9

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�y si� operacje plikowe na konkretnym pliku z logami.
*/
#define LOG_ERR 10

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - plik z logiem zawiera nieprawid�owe dane.
*/
#define ODCZYT_ERR 11

/**
	Sta�a okre�laj�ca b��dne zako�czenie dzia�ania funkcji - nie powiod�y si� operacje zwi�zane z ochron� plik�w z logami pod k�tem zako�czenia dzia�ania programu za pomoc� sygna��w.
*/
#define SYGNALY_ERR 12

/**
	Struktura zawieraj�ca informacje o semaforach komunikacji mi�dzyprocesowej Systemu V. Przechowuje informacje konieczne do dzia�ania funkcji bibliotecznych operuj�cych na zbiorze semafor�w.
*/
typedef struct
{
/**
	Identyfikator zbioru semafor�w w sensie komunikacji mi�dzyprocesowej Systemu V.
*/
	int sem_id;
/**
	Liczba okre�laj�ca liczb� semafor�w w zbiorze semafor�w.
*/
	int ile_sem;
/**
	Nazwa zbioru semafor�w w systemie plik�w w sensie komunikacji mi�dzyprocesowej Systemu V.
*/
	char sem_nazwa[DL_NAZWY];
} semafor_t;

/**
	Struktura danych zawieraj�ca informacje o pami�ci wsp�lnej IPC Systemu V. Zawiera dane potrzebne do dzia�ania funkcji operuj�cych na takiej pami�ci.
*/
typedef struct
{
/**
	Identyfikator pami�ci wsp�lnej - taki jak w IPC Systemu V.
*/
	int pam_id;
/**
	Rozmiar utworzonej/przydzielonej pami�ci wsp�lnej wyra�ony w bajtach.
*/
	int rozmiar_pam;
/**
	Nazwa pami�ci wsp�lnej w systemie plik�w - taka jak w IPC Systemu V.
*/
	char pam_nazwa[DL_NAZWY];
/**
	Wska�nik na pocz�tek utworzonej i przy��czonej pami�ci wsp�lnej.
*/
	void * pam_adres;
} pamiec_t;

/**
	Skr�cona nazwa typu zmiennej warunkowej standardu POSIX.
*/
typedef	pthread_cond_t monitor_t;

/**
	Skr�cona nazwa typu blokad odczytu/zapisu standardu POSIX.
*/
typedef pthread_rwlock_t rwlock_t;

/**
	Skr�cona nazwa typu mutex�w standardu POSIX.
*/
typedef pthread_mutex_t mutex_t;

/**
	Skr�cona nazwa typu odpowiadaj�cego w�tkom standardu POSIX.
*/
typedef pthread_t watek_t;

/**
	Struktura zawieraj�ca informacje potrzebne przy tworzeniu log�w ze statystykami.
*/
typedef struct
{
/**
	Wska�nik na otwarty plik ze statystykami.	
*/
	FILE * log;
/**
	�cie�ka pliku ze statystykami.
*/
	char log_nazwa[DL_SCIEZKI];
/**
	Numer w�tku, w kt�rym prowadzone s� statystyki.
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
