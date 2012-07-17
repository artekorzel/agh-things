#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<pthread.h>
#include<syscall.h>
#include"sync.h"

#define ERR(X,Y) {printf("%s",X);exit(Y);}
#define ERR2(X,Y) {printf("%s",X);kill(getpid(),SIGINT);}

#define LOG_KAT "./log/"
#define LOG_OST "./log.log"
#define SEMAFOR_ID 1
#define PAMIEC_ID 2
#define PROD 3
#define KONS 5
#define TABLICA 10
#define MAXVAL 100

monitor_t producenci;
monitor_t konsumenci;
mutex_t print = PTHREAD_MUTEX_INITIALIZER;
mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
watek_t prod[PROD];
watek_t kons[KONS];
staty_t statystyki[PROD+KONS];
pthread_key_t klucz;
void * arg = NULL;

void interrupt(int signo)
{
	zakoncz_staty(pthread_getspecific(klucz));
	pthread_exit(0);
}


void clearAll(void)
{
	pthread_cond_destroy(&producenci);
	pthread_cond_destroy(&konsumenci);
	pthread_key_delete(klucz);
	if(arg != NULL)
		free(arg);
}

void interruptAll(int signo)
{
	int i = PROD;
	while(i-- > 0)
		pthread_kill(prod[i], SIGUSR1);
	i = KONS;
	while(i-- > 0)
		pthread_kill(kons[i], SIGUSR1);
	
	if((i = analizuj_staty(LOG_KAT, LOG_OST)) != SUKCES)
		ERR(error2str(i),1)

	exit(0);
}

void init(void (*interrupt)(int), staty_t * staty, char * nazwa)
{
	int i;
	if((i = stworz_staty(staty, nazwa, LOG_KAT)) != SUKCES)
		ERR(error2str(i),2)

	struct sigaction sa;
	sa.sa_handler = interrupt;
	sa.sa_flags = 0;
	if(sigaction(SIGUSR1, &sa, NULL) == -1)
		ERR("Blad sigaction. Konczymy.\n",3)
		
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",4)
	if(sigdelset(&set, SIGUSR1) == -1)
		ERR("Blad sigdelset. Konczymy.\n",5)
	if(pthread_sigmask(SIG_SETMASK, &set, NULL))
		ERR("Blad pthread_sigmask. Konczymy.\n",6)
}

void * producent(void * arg)
{
	double zadanie;
	double * tablica = (double *)arg;
	int * licznik = (int*)(((double *)arg) + TABLICA);
	int * ile = licznik + 2;
	int i, id;
	
	if((id = (int)syscall(SYS_gettid)) == -1)
		ERR2("Blad syscall.\n",7)

	id %= PROD;
	pthread_setspecific(klucz, &statystyki[id]);

	init(interrupt, &statystyki[id], "PROD");
		
	while(1)
	{
		if(pthread_mutex_lock(&mutex))
			ERR2("Blad pthread_mutex_lock.\n",8)

		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR2(error2str(i),9)
				
		while(*ile == TABLICA)
			if(pthread_cond_wait(&producenci, &mutex))
				ERR2("Blad pthread_cond_wait",10)
		
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR2(error2str(i),11)

		zadanie = tablica[*licznik]; 
		zadanie += 1.2;
		zadanie *= 2.5;
		zadanie /= 3.2;
		zadanie -= 0.2;
		zadanie *= 1.7;
		zadanie -= 1.2;
		tablica[*licznik] = zadanie; 
	
		if(pthread_mutex_lock(&print))
			ERR2("Blad pthread_mutex_lock.\n",12)
		printf("Licznik: %d\tWyprodukowano: %lf\n", *licznik, zadanie);
		if(pthread_mutex_unlock(&print))
			ERR2("Blad pthread_mutex_unlock.\n",13)
		
		*licznik = ((*licznik) + 1) % TABLICA;
		*ile = (*ile) +1;

		if(pthread_cond_signal(&konsumenci))
			ERR2("Blad pthread_cond_signal.\n",14)

		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),15)
		
		if(pthread_mutex_unlock(&mutex))
			ERR2("Blad pthread_mutex_unlock.\n",16)

		sleep(1);
	}	
}

void * konsument(void * arg)
{
	double * tablica = (double *)arg;
	int * licznik = (int*)(((double *)arg) + TABLICA) + 1;
	int * ile = licznik + 1;
	double zadanie;
	int i, id;
	
	if((id = (int)syscall(SYS_gettid)) == -1)
		ERR2("Blad syscall.\n",17)

	id %= KONS;
	id += PROD; 
	
	pthread_setspecific(klucz, &statystyki[id]);
	
	init(interrupt, &statystyki[id], "KONS");

	while(1)
	{
		if(pthread_mutex_lock(&mutex))
			ERR2("Blad pthread_mutex_lock.\n",18)
		
		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR2(error2str(i),19)

		while(*ile == 0)
			if(pthread_cond_wait(&konsumenci, &mutex))
				ERR2("Blad pthread_cond_wait",20)
		
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR2(error2str(i),21)	
		
		zadanie = tablica[*licznik]; 
		zadanie += 1.2;
		zadanie /= 1.7;
		zadanie += 0.2;
		zadanie *= 3.2;
		zadanie /= 2.5;
		zadanie -= 1.2;

		if(pthread_mutex_lock(&print))
			ERR2("Blad pthread_mutex_lock. Konczymy.\n",22)
		printf("Licznik: %d\tOdczytano: %lf\t Poprzednia wartosc: %lf\n", 
				*licznik, tablica[*licznik], zadanie);
		if(pthread_mutex_unlock(&print))
			ERR2("Blad pthread_mutex_unlock. Konczymy.\n",23)

		*licznik = ((*licznik) + 1) % TABLICA;
		*ile = (*ile) - 1;

		if(pthread_cond_signal(&producenci))
			ERR2("Blad pthread_cond_signal.\n",24)
		
		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),25)

		if(pthread_mutex_unlock(&mutex))
			ERR2("Blad pthread_mutex_unlock.\n",26)

		sleep(1);
	}	
}

int main(void)
{
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",27)
	if(pthread_sigmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad pthread_sigmask. Konczymy.\n",28)
	
	atexit(clearAll);
	
	struct sigaction sa;
	sa.sa_handler = interruptAll;
	sa.sa_flags = 0;
	if(sigaction(SIGINT, &sa, NULL) == -1)
		ERR("Blad sigaction. Konczymy.\n",29)
		
	int i;
	if(pthread_cond_init(&producenci, NULL))
		ERR("Blad pthread_cond_init.",30)
	if(pthread_cond_init(&konsumenci, NULL))
		ERR("Blad pthread_cond_init.",31)

   	if((arg = malloc(TABLICA*sizeof(double) + 3*sizeof(int))) == NULL)
	   ERR("Blad malloc. Konczymy.\n",32)
	
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",33)

	i = 0;
	while(i < TABLICA)
	{
		*(((double *)arg) + i) = (double)i;
		++i;
	}

	*((int *)(((double *)arg) + TABLICA)) = 0;
	*((int *)(((double *)arg) + TABLICA) + 1) = 0;
	*((int *)(((double *)arg) + TABLICA) + 2) = 0;

	if(pthread_key_create(&klucz, NULL))
		ERR("Blad pthread_key_create.\n",34)

	i = 0;
	int j;
	while(i < PROD)
		if((j = stworz_watek(&prod[i++], 1, producent, arg)) != SUKCES)
			ERR(error2str(j),35)
	i = 0;
	while(i < KONS)
		if((j = stworz_watek(&kons[i++], 1, konsument, arg)) != SUKCES)
			ERR(error2str(j),36)

	sigsuspend(&set);

	exit(0);
}
