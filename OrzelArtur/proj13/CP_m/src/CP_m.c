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
#define CZYT 5
#define PIS 3

rwlock_t czytelnia;
mutex_t print = PTHREAD_MUTEX_INITIALIZER;
watek_t czyt[CZYT];
watek_t pis[PIS];
staty_t statystyki[PIS+CZYT];
pthread_key_t klucz;
void * arg = NULL;

void interrupt(int signo)
{
	zakoncz_staty(pthread_getspecific(klucz));
	pthread_exit(0);
}


void clearAll(void)
{
	pthread_rwlock_destroy(&czytelnia);
	pthread_key_delete(klucz);
	if(arg != NULL)
		free(arg);
}

void interruptAll(int signo)
{
	int i = PIS;
	while(i-- > 0)
		pthread_kill(pis[i], SIGUSR1);
	i = CZYT;
	while(i-- > 0)
		pthread_kill(czyt[i], SIGUSR1);
	
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
	if(pthread_sigmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",6)
}

void * pisarz(void * arg)
{
	double * zadanie = (double*)arg;
	int i, id;

	if((id = (int)syscall(SYS_gettid)) == -1)
		ERR2("Blad syscall.\n",7)

	id %= PIS;
	pthread_setspecific(klucz, &statystyki[id]);

	init(interrupt, &statystyki[id], "PIS");

	while(1)
	{
		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR2(error2str(i),8)
		
		if(pthread_rwlock_wrlock(&czytelnia))
			ERR2("Blad pthread_rwlock_wrlock.\n",9)
 
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR2(error2str(i),10)
		
		*zadanie += 1.2;
		*zadanie *= 2.5;
		*zadanie /= 3.2;
		*zadanie -= 0.2;
		*zadanie *= 1.7;
		*zadanie -= 1.2;
		
		if(pthread_mutex_lock(&print))
			ERR2("Blad pthread_mutex_lock.\n",11)
		
		printf("Zapisano: %lf\n", *zadanie);
		
		if(pthread_mutex_unlock(&print))
			ERR2("Blad pthread_mutex_unlock.\n",12)
		
		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),13)
		
		if(pthread_rwlock_unlock(&czytelnia))
			ERR2("Blad pthread_rwlock_unlock.\n",14)	

		sleep(1);
	}	
}

void * czytelnik(void * arg)
{
	double * zadanie = (double*)arg;
	int i, id;
	
	if((id = (int)syscall(SYS_gettid)) == -1)
		ERR2("Blad syscall.\n",15)

	id %= CZYT;
	id += PIS; 
	
	pthread_setspecific(klucz, &statystyki[id]);
	
	init(interrupt, &statystyki[id], "CZYT");

	while(1)
	{
		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR2(error2str(i),16)
		
		if(pthread_rwlock_rdlock(&czytelnia))
			ERR2("Blad pthread_rwlock_rdlock.\n",17)

		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR2(error2str(i),18)
		
		if(pthread_mutex_lock(&print))
			ERR2("Blad pthread_mutex_lock.\n",19)
		
		printf("Odczytano: %lf\n", *zadanie);
		
		if(pthread_mutex_unlock(&print))
			ERR2("Blad pthread_mutex_unlock.\n",20)
		
		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),21)
		
		if(pthread_rwlock_unlock(&czytelnia))
			ERR2("Blad pthread_rwlock_unlock.\n",22)	

		sleep(1);
	}	
}

int main(void)
{
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",23)
	if(pthread_sigmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",24)
	
	atexit(clearAll);
	
	struct sigaction sa;
	sa.sa_handler = interruptAll;
	sa.sa_flags = 0;
	if(sigaction(SIGINT, &sa, NULL) == -1)
		ERR("Blad sigaction. Konczymy.\n",25)
		
	if(pthread_rwlock_init(&czytelnia, NULL))
		ERR("Blad pthread_rwlock_init.",26)
	
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",27)

   	if((arg = malloc(sizeof(double))) == NULL)
	   ERR("Blad malloc. Konczymy.\n",28)

	*((double *)arg) = 1.0;
	
	if(pthread_key_create(&klucz, NULL))
		ERR("Blad pthread_key_create.\n",29)

	int i = 0;
	int j;
	while(i < PIS)
		if((j = stworz_watek(&pis[i++], 1, pisarz, arg)) != SUKCES)
			ERR(error2str(j),30)

	i = 0;
	while(i < CZYT)
		if((j = stworz_watek(&czyt[i++], 1, czytelnik, arg)) != SUKCES)
			ERR(error2str(j),31)

	sigsuspend(&set);

	exit(0);
}
