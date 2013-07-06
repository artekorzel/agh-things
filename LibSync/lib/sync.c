
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/stat.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/times.h>
#include<sys/resource.h>
#include<sys/syscall.h>
#include<signal.h>
#include<errno.h>
#include"sync.h"


/**
	Tworzy zbiór semaforów o wskazanym identyfikatorze.

	@param semafor Wska¼nik na strukturê opisuj±c± zbiór semaforów.
	@param liczba Liczba okre¶laj±ca, ile semaforów ma zaiweraæ zbiór.
	@param ident Identyfikator zbioru semaforów.
	@param ile_inicjalizowanych Liczba okre¶laj±ca, ile semaforów ma zostaæ zainicjalizowanych - po tym argumencie nastêpuje ci±g liczb, które bêd± przypisane do kolejnych semaforów.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int stworz_semafory(semafor_t * semafor, int liczba, int ident, 
		int ile_inicjalizowanych, ...)
{
	if(semafor == NULL || ile_inicjalizowanych > liczba)
		return ARG_ERR;

	semafor->ile_sem = liczba;
	strcpy(semafor->sem_nazwa, "./semafor__");
	sprintf(semafor->sem_nazwa + strlen(semafor->sem_nazwa), 
			"%d", ident % 1000000);

	key_t klucz;

	if(liczba > 0)	//tworzenie
	{
		if(close(open(semafor->sem_nazwa, O_CREAT | O_EXCL, 0666)) == -1)
			return TWORZENIE_ERR;
		if((klucz = ftok(semafor->sem_nazwa, ident)) == -1)
			return TWORZENIE_ERR;
		if((semafor->sem_id = semget(klucz, liczba, IPC_CREAT | IPC_EXCL | 0666)) == -1)
			return TWORZENIE_ERR;
	
		va_list ap;
		va_start(ap,ile_inicjalizowanych);
		int i = 0;
		while(i < ile_inicjalizowanych)
			if(semctl(semafor->sem_id, i++, SETVAL, va_arg(ap, int)) == -1)
				return INICJALIZACJA_ERR;

		va_end(ap);
	}
	else
	{
		if((klucz = ftok(semafor->sem_nazwa, ident)) == -1)
			return POBRANIE_ERR;
		if((semafor->sem_id = semget(klucz, 0, 0)) == -1)
			return POBRANIE_ERR;
	}

	return SUKCES;
}


/**
	Zmienia stan zbioru semaforów.

	@param semafor Wska¼nik na strukturê opisuj±c± zbiór semaforów.
	@param sops Tablica struktur sembuf opisuj±cych zmiany w zbiorze semaforów.
	@param nsops Liczba elementów tablicy sops.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int zmien_semafory(semafor_t * semafor, struct sembuf * sops, int nsops)
{
	if(semafor == NULL || sops == NULL || nsops == 0)
		return ARG_ERR;
	
	if(semop(semafor->sem_id, sops, nsops) == -1)
		return ZMIANA_ERR;

	return SUKCES;
}


/**
	Usuwa zbiór semaforów z pamiêci.

	@param semafor Wska¼nik na strukturê opisuj±c± zbiór semaforów.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int usun_semafory(semafor_t * semafor)
{
	if(semafor == NULL)
		return ARG_ERR;
	if(semctl(semafor->sem_id, 0, IPC_RMID) == -1)
		return USUNIECIE_ERR;
	if(unlink(semafor->sem_nazwa) == -1)
		return USUNIECIE_PLIKU_ERR;
	return SUKCES;
}


/**
	Tworzy now± b±d¼ pod³±cza do istniej±cej pamiêci wspólnej.

	@param pamiec Wska¼nik na strukturê opisuj±c± pamiêæ wspóln±.
	@param rozmiar Rozmiar pamiêci wspólnej, je¶li 0 to znaczy, ¿e pamiêæ ju¿ zosta³a utworzona w systemie i nastêpuje tylko jej pobranie.
	@param ident Identyfikator pamiêci wspólnej.
	@param czy_podlaczyc Je¶li równe 0, to pamiêæ nie zostanie przydzielona, w przeciwnym wypadku - tak.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int stworz_pamiec(pamiec_t * pamiec, int rozmiar, int ident, int czy_podlaczyc)
{
	if(pamiec == NULL)
		return ARG_ERR;

	pamiec->rozmiar_pam = rozmiar;
	strcpy(pamiec->pam_nazwa, "./pamiec__");
	sprintf(pamiec->pam_nazwa + strlen(pamiec->pam_nazwa), 
			"%d", ident % 1000000);

	key_t klucz;

	if(rozmiar > 0)	//tworzenie
	{
		if(close(open(pamiec->pam_nazwa, O_CREAT | O_EXCL, 0666)) == -1)
			return TWORZENIE_ERR;
		if((klucz = ftok(pamiec->pam_nazwa, ident)) == -1)
			return TWORZENIE_ERR;
		if((pamiec->pam_id = shmget(klucz, rozmiar+2000, IPC_CREAT | IPC_EXCL | 0666)) == -1)
			return TWORZENIE_ERR;
	}
	else
	{
		if((klucz = ftok(pamiec->pam_nazwa, ident)) == -1)
			return POBRANIE_ERR;
		if((pamiec->pam_id = shmget(klucz, 0, 0)) == -1)
			return POBRANIE_ERR;
	}

	if(czy_podlaczyc)
	{
		if((pamiec->pam_adres = shmat(pamiec->pam_id, 0, 0)) == (void *)-1)
			return INICJALIZACJA_ERR;
	}
	else pamiec->pam_adres = NULL;

	return SUKCES;	
}


/**
	Zwalnia i ewentualnie usuwa istniej±c± pamiêæ wspóln±.

	@param pamiec Wska¼nik na strukturê opisuj±c± pamiêæ wspóln±.
	@param czy_usunac Je¶li równe 0, to pamiêæ nie zostanie usuniêta, w przeciwnym wypadku - tak.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int zwolnij_pamiec(pamiec_t * pamiec, int czy_usunac)
{
	if(pamiec == NULL)
		return ARG_ERR;

	if(pamiec->pam_adres)
		if(shmdt(pamiec->pam_adres) == -1)
			return ODLACZENIE_ERR;

	if(czy_usunac)
	{
		if(shmctl(pamiec->pam_id, IPC_RMID, NULL) == -1)
			return USUNIECIE_ERR;
		if(remove(pamiec->pam_nazwa) == -1)
			return USUNIECIE_PLIKU_ERR;
	}

	return SUKCES;
}

/**
	Tworzy i uruchamia w±tek.

	@param watek Wskaznik na watek - typu równowa¿nego pthread_t.
	@param czy_odlaczony Je¶li równe 0, to w±tek nie zostanie od³±czony, w przeciwnym wypadku - tak.
	@param funkcja Wska¼nik na funkcjê, która ma byæ wykonywana przez w±tek.
	@param arg Argumenty przekazywane funkcji wykonania w±tku.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int stworz_watek(watek_t * watek, int czy_odlaczony, 
		void * (*funkcja) (void *), void * arg)
{
	if(watek == NULL)
		return ARG_ERR;

	if(czy_odlaczony)
	{
		pthread_attr_t attr;
		if(pthread_attr_init(&attr))
			return TWORZENIE_ERR;

		if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
			return TWORZENIE_ERR;

		if(pthread_create(watek, &attr, funkcja, arg))
			return TWORZENIE_ERR;
	}
	else if(pthread_create(watek, NULL, funkcja, arg))
		return TWORZENIE_ERR;
	return SUKCES;
}


/**
	Tworzy wszelkie potrzebne dane (w tym plik ze statystykami) do logowania danych statystycznych.

	@param staty Wskaznik na strukturê danych z informacjami o pliku statystyk.
	@param nazwa Krótka nazwa okre¶laj±ca rodzaj w±tku/procesu.
	@param katalog ¦cie¿ka katalogu, w którym zapisany zostanie plik ze statystykami.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int stworz_staty(staty_t * staty, char * nazwa, char * katalog)
{
	if(staty == NULL || nazwa == NULL || katalog == NULL)
		return ARG_ERR;

	if((staty->tid = syscall(SYS_gettid)) == -1)
		return TWORZENIE_ERR;

	strcpy(staty->log_nazwa, katalog);
	strcat(staty->log_nazwa, LOG_NAZWA);
	strcat(staty->log_nazwa, "_");
	strcat(staty->log_nazwa, nazwa);
	strcat(staty->log_nazwa, "_");
	int rozmiar = strlen(staty->log_nazwa);
	if(sprintf(staty->log_nazwa + rozmiar, "%d", staty->tid) < 0)
		return TWORZENIE_ERR;

	if((staty->log = fopen(staty->log_nazwa, "w+")) == NULL)
		return TWORZENIE_ERR;

	struct timeval t;
	gettimeofday(&t,NULL);
	double czas = (double)t.tv_sec + (double)t.tv_usec/1000000.0;
	if(fprintf(staty->log, "%lf:%s\n", czas, START) < 0)
		return INICJALIZACJA_ERR;

	return SUKCES;
}


/**
	Zapisuje do pliku ze statystykami aktualny czas i opis sytuacji.

	@param staty Wskaznik na strukturê danych z informacjami o pliku statystyk.
	@param opis Jednolinijkowy opis sytuacji u¿ycia - zalecane jest u¿ywanie w tym celu sta³ych znakowych: TRY, IN, OUT - u¿ycie innych prawdopodobnie spowoduje, ¿e konieczna bêdzie w³asnorêczna implementacja funkcji analizuj±cej statystyki. 

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int log_staty(staty_t * staty, char * opis)
{
	if(staty == NULL || staty->log == NULL || opis == NULL)
		return ARG_ERR;

	sigset_t set, old_set;
	if(sigfillset(&set) == -1)
		return SYGNALY_ERR;
	if(sigprocmask(SIG_SETMASK, &set, &old_set) == -1)
		return SYGNALY_ERR;
	
	struct timeval t;
	gettimeofday(&t,NULL);
	double czas = (double)t.tv_sec + (double)t.tv_usec/1000000.0;
	if(fprintf(staty->log, "%lf:%s\n", czas, opis) < 0)
		return ZMIANA_ERR;

	if(sigprocmask(SIG_SETMASK, &old_set, NULL) == -1)
		return SYGNALY_ERR;
	
	return SUKCES;
}


/**
	Zapisuje do pliku ze statystykami aktualny czas i informacjê o zakoñczeniu statystyk i zamyka plik ze statystykami.

	@param staty Wskaznik na strukturê danych z informacjami o pliku statystyk.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int zakoncz_staty(staty_t * staty)
{
	if(staty == NULL || staty->log == NULL)
		return ARG_ERR;
	
	struct timeval t;
	gettimeofday(&t,NULL);
	double czas = (double)t.tv_sec + (double)t.tv_usec/1000000.0;
	if(fprintf(staty->log, "%lf:%s\n", czas, STOP) < 0)
		return INICJALIZACJA_ERR;
	
	if(fclose(staty->log) == EOF)
		return ODLACZENIE_ERR;

	return SUKCES;
}


/**
	Analizuje pliki ze statystykami. Wypisuje na standardowe wyj¶cie informacje o rodzaju i numerze w±tku/procesu, liczbie prób wej¶cia, wej¶æ i wyj¶æ z sekcji krytycznej, czasach ³±cznych i ¶rednich oczekiwania na wej¶cie i spêdzonych w sekcji krytycznej. Ponadto dane te zapisuje w postaci prostej tabeli w nowym pliku, dziêki czemu mo¿na je wykorzystaæ do tworzenia np. wykresów.

	@param sciezka ¦cie¿ka do katalogu z plikami ze statystykami.
	@param sciezka_logu_ost ¦cie¿ka do nieistniej±cego b±d¼ niepotrzebnego pliku, w którym zostanie umieszczona tabela z wymienionymi informacjami - plik ten NIE MO¯E znajdowaæ siê w katalogu podanym w argumencie sciezka.

	@return W przypadku powodzenia zwracana jest warto¶æ SUKCES, w przeciwnym wypadku - numer b³êdu.
*/
int analizuj_staty(char * sciezka, char * sciezka_logu_ost)
{
	if(sciezka == NULL 
			|| sciezka_logu_ost == NULL 
			|| strstr(sciezka_logu_ost, sciezka) == sciezka_logu_ost)
		return ARG_ERR;

	int dl_sciezki = strlen(sciezka);	
	DIR * dp;
  	struct dirent *ep;
	struct stat statbuf;
 
 	if((dp = opendir(sciezka)) == NULL)
		return LOGI_ERR;

	char nazwa[DL_NAZWY + dl_sciezki + 2];
	strcpy(nazwa, sciezka);
	
	char bufor[BUFOR];
	long ile_try, ile_in, ile_out;
	double t_start, t_try, t_in, t_out, t_stop, t_pracy, t_czekania;
	char * nazwa_watku;
	char * log_w_nazwie;
	long tid; 
	FILE * log, * log_ost;
	
	if((log_ost = fopen(sciezka_logu_ost, "w")) == NULL)
	{
		closedir(dp);
		return LOG_ERR;
	}

	while((ep = readdir(dp)) != NULL)
	{
		strcpy(nazwa + dl_sciezki, ep->d_name);
		if(stat(nazwa, &statbuf) == -1)
		{
			closedir(dp);
			fclose(log_ost);
			return LOG_ERR;
		}
			
		if(S_ISREG(statbuf.st_mode))
		{
			
			log_w_nazwie = strtok(ep->d_name, "_");
			if(strcmp(log_w_nazwie, LOG_NAZWA))
				continue;

			nazwa_watku = strtok(NULL, "_");
			if(nazwa_watku == NULL)
				continue;
			
			tid = strtol(strtok(NULL, "_"), NULL, 10);
			if(errno == ERANGE || errno == EINVAL)
				continue;

			if((log = fopen(nazwa, "r")) == NULL)
			{
				closedir(dp);
				fclose(log_ost);
				return LOG_ERR;
			}

			if(fscanf(log, "%lf:%s", &t_start, bufor) == EOF)
			{
				fclose(log);
				closedir(dp);
				fclose(log_ost);
				return ODCZYT_ERR;
			}
			
			if(strcmp(bufor, START))
			{
				fclose(log);
				closedir(dp);
				fclose(log_ost);
				return LOG_ERR;
			}
			
			ile_try = 0;
			ile_in = 0;
			ile_out = 0;
			t_pracy = 0.0;
			t_czekania = 0.0;

			while(1)
			{
				if(fscanf(log, "%lf:%s", &t_try, bufor) == EOF)
				{
					fclose(log);
					closedir(dp);
					fclose(log_ost);
					return ODCZYT_ERR;
				}

				if(strcmp(bufor, TRY))
				{
					if(strcmp(bufor, STOP) == 0)
					{
						t_stop = t_try;
						break;
					}
					else
					{
						fclose(log);
						closedir(dp);
						fclose(log_ost);
						return LOG_ERR;
					}
				}
				ile_try++;

				if(fscanf(log, "%lf:%s", &t_in, bufor) == EOF)
				{
					fclose(log);
					closedir(dp);
					fclose(log_ost);
					return ODCZYT_ERR;
				}
				
				if(strcmp(bufor, IN))
				{
					if(strcmp(bufor, STOP) == 0)
					{
						t_stop = t_in;
						break;
					}
					else 
					{
						fclose(log);
						closedir(dp);
						fclose(log_ost);
						return LOG_ERR;
					}
				}
				t_czekania += t_in - t_try;
				ile_in++;

				if(fscanf(log, "%lf:%s", &t_out, bufor) == EOF)
				{
					fclose(log);
					closedir(dp);
					fclose(log_ost);
					return ODCZYT_ERR;
				}
				
				if(strcmp(bufor, OUT))
				{
					if(strcmp(bufor, STOP) == 0)
					{
						t_stop = t_out;
						break;
					}
					else 
					{
						fclose(log);
						closedir(dp);
						fclose(log_ost);
						return LOG_ERR;
					}
				}
				t_pracy += t_out - t_in;
				ile_out++;
			}
			if(ferror(log))
			{
				fclose(log);
				closedir(dp);
				fclose(log_ost);
				return ODCZYT_ERR;
			}

			fclose(log);

			fprintf(log_ost, "%s%ld %ld %ld %ld %lf %lf %lf %lf %lf\n",
					nazwa_watku, tid, ile_try, ile_in, ile_out, t_czekania,
				   	t_pracy, t_czekania/ile_in, t_pracy/ile_out, 
					t_stop - t_start);

			printf("Nazwa watku: %s, numer watku: %ld\n", nazwa_watku, tid);
			printf("\tLiczba prob wejscia do sekcji krytycznej: %ld\n", ile_try);
			printf("\tLiczba wejsc do sekcji krytycznej: %ld\n", ile_in);
			printf("\tLiczba wyjsc z sekcji krytycznej: %ld\n", ile_out);
			printf("\tLaczny czas oczekiwania na wejscie: %lf\n", t_czekania);
			printf("\tLaczny czas w sekcji krytycznej: %lf\n", t_pracy);
			printf("\tSredni czas oczekiwania na wejscie: %lf\n", t_czekania/ile_in);
			printf("\tSredni czas w sekcji krytycznej: %lf\n", t_pracy/ile_out);
			printf("\tLaczny czas pracy watku: %lf\n\n", t_stop - t_start);
		}
	}
	closedir(dp);

	fclose(log_ost);

	return SUKCES;
}


/**
	Zamienia numer b³êdu na jego reprezentacjê w postaci c-stringu.

	@param error Numer b³êdu.

	@return W przypadku powodzenia zwracana jest reprezentacja b³êdu w postaci c-stringu, w przeciwnym wypadku - c-string "NIEZNANY_ERR".
*/
char * error2str(int error)
{
	switch(error)
	{
		case SUKCES: return "SUKCES\n";
		case ARG_ERR: return "ARG_ERR\n";
		case TWORZENIE_ERR: return "TWORZENIE_ERR\n";
		case POBRANIE_ERR: return "POBRANIE_ERR\n";
		case INICJALIZACJA_ERR: return "INICJALIZACJA_ERR\n";
		case USUNIECIE_ERR: return "USUNIECIE_ERR\n";
		case USUNIECIE_PLIKU_ERR: return "USUNIECIE_PLIKU_ERR\n";
		case ZMIANA_ERR: return "ZMIANA_ERR\n";
		case ODLACZENIE_ERR: return "ODLACZENIE_ERR\n";
		case LOGI_ERR: return "LOGI_ERR\n";
		case LOG_ERR: return "LOG_ERR\n";
		case ODCZYT_ERR: return "ODCZYT_ERR\n";
		case SYGNALY_ERR: return "SYGNALY_ERR\n";
		default: return "NIEZNANY_ERR\n";
	}
}
