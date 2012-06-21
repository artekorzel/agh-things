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
#define SAMOLOTY 10
#define N_SAM 10
#define K_SAM 5

monitor_t start = PTHREAD_COND_INITIALIZER;
monitor_t ladowanie = PTHREAD_COND_INITIALIZER;
mutex_t print = PTHREAD_MUTEX_INITIALIZER;
mutex_t lotniskowiec = PTHREAD_MUTEX_INITIALIZER;
watek_t sam[SAMOLOTY];
staty_t statystyki[SAMOLOTY];
pthread_key_t klucz;
int na_lotniskowcu = 0;
int wolny = 1;
int do_startu = 0;
int do_ladowania = 0;

void interrupt(int signo)
{
	zakoncz_staty(pthread_getspecific(klucz));
	pthread_exit(0);
}

void clearAll(void)
{
	pthread_key_delete(klucz);
}

void interruptAll(int signo)
{
	int i = SAMOLOTY;
	while(i-- > 0)
		pthread_kill(sam[i], SIGUSR1);

	if((i = analizuj_staty(LOG_KAT, LOG_OST)) != SUKCES)
		ERR(error2str(i),1)

	exit(0);
}

void init(void (*interrupt)(int), staty_t * staty, char * nazwa)
{
	int i;
	if((i = stworz_staty(staty, nazwa, LOG_KAT)) != SUKCES)
		ERR(error2str(i),1)
	
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

void zwolnij_pas()
{
	if(na_lotniskowcu < K_SAM)	//priorytet dla ladujacych
	{
		if(do_ladowania > 0)
		{
			do_ladowania--;
			if(pthread_cond_signal(&ladowanie))
				ERR2("Blad pthread_cond_signal.\n",21)
		}
		else
		{
			if(do_startu > 0) 
				do_startu--;
			if(pthread_cond_signal(&start))
				ERR2("Blad pthread_cond_signal.\n",21)
		}
	}
	else	//priorytet dla startujacych
	{
		if(do_startu > 0)
		{
			do_startu--;
			if(pthread_cond_signal(&start))
				ERR2("Blad pthread_cond_signal.\n",21)
		}
		else if(na_lotniskowcu < N_SAM)
		{
			if(do_ladowania > 0)
				do_ladowania--;
			if(pthread_cond_signal(&ladowanie))
				ERR2("Blad pthread_cond_signal.\n",21)
		}
	}
}

void zmiana(int ind, char * str)
{
	if(pthread_mutex_lock(&print))
		ERR2("Blad pthread_mutex_lock.\n",17)
	printf("Samolot nr %d %s", ind, str);
	if(pthread_mutex_unlock(&print))
		ERR2("Blad pthread_mutex_unlock.\n",18)

	sleep(1);
}

void * samolot(void * arg)
{
	int i, id;
	
	if((id = (int)syscall(SYS_gettid)) == -1)
		ERR2("Blad syscall.\n",7)

	id %= SAMOLOTY;
	pthread_setspecific(klucz, &statystyki[id]);
	init(interrupt, &statystyki[id], "SAM");
	
	while(1)
	{
		zmiana(id, "jest na lotniskowcu\n");

		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if(pthread_mutex_lock(&lotniskowiec))
			ERR2("Blad pthread_mutex_lock.\n",17)
		
		if(!wolny)
			if(pthread_cond_wait(&start, &lotniskowiec))
				ERR2("Blad pthread_cond_wait",12)
		
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR2(error2str(i),10)

		wolny = 0;
		do_startu++;

		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),10)
		
		if(pthread_mutex_unlock(&lotniskowiec))
			ERR2("Blad pthread_mutex_unlock.\n",17)
			
		zmiana(id, "startuje\n");

		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if(pthread_mutex_lock(&lotniskowiec))
			ERR2("Blad pthread_mutex_lock.\n",17)
		
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR(error2str(i),10)

		na_lotniskowcu--;
		wolny = 1;
		zwolnij_pas();
		
		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),10)
		
		if(pthread_mutex_unlock(&lotniskowiec))
			ERR2("Blad pthread_mutex_unlock.\n",17)

		zmiana(id, "leci\n");

		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if(pthread_mutex_lock(&lotniskowiec))
			ERR2("Blad pthread_mutex_lock.\n",17)
		
		if(!wolny || na_lotniskowcu == N_SAM)
			if(pthread_cond_wait(&ladowanie, &lotniskowiec))
				ERR2("Blad pthread_cond_wait",12)
		
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR(error2str(i),10)

		wolny = 0;
		do_ladowania++;
		
		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),10)
		
		if(pthread_mutex_unlock(&lotniskowiec))
			ERR2("Blad pthread_mutex_unlock.\n",17)
		
		zmiana(id, "laduje\n");

		if((i = log_staty(&statystyki[id],TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if(pthread_mutex_lock(&lotniskowiec))
			ERR2("Blad pthread_mutex_lock.\n",17)
		
		if((i = log_staty(&statystyki[id],IN)) != SUKCES)
			ERR(error2str(i),10)

		na_lotniskowcu++;
		wolny = 1;
		zwolnij_pas();
		
		if((i = log_staty(&statystyki[id],OUT)) != SUKCES)
			ERR2(error2str(i),10)
		
		if(pthread_mutex_unlock(&lotniskowiec))
			ERR2("Blad pthread_mutex_unlock.\n",17)
	}	
}

int main(void)
{
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",19)
	if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",20)
	
	atexit(clearAll);
	
	if(signal(SIGINT, interruptAll) == SIG_ERR)
		ERR("Blad signal. Konczymy.\n",21)
		
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",23)

	int i = 0;
	if(pthread_key_create(&klucz, NULL))
		ERR("Blad pthread_key_create.\n",30)
	
	i = 0;
	int j;
	while(i < SAMOLOTY)
		if((j = stworz_watek(&sam[i++], 1, samolot, NULL)) != SUKCES)
			ERR(error2str(j),31)
	
	sigsuspend(&set);
//interruptAll(0);
	exit(0);
}
