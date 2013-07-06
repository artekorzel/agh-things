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

monitor_t widelec[5];
int zajety[5];
monitor_t lokaj = PTHREAD_COND_INITIALIZER;
int dopuszczeni = 0;
mutex_t print = PTHREAD_MUTEX_INITIALIZER;
mutex_t widelce = PTHREAD_MUTEX_INITIALIZER;
watek_t fil[5];
staty_t statystyki[5];
pthread_key_t klucz;

void interrupt(int signo)
{
	zakoncz_staty(pthread_getspecific(klucz));
	pthread_exit(0);
}


void clearAll(void)
{
	int i = 0;
	while(i < 5)
		pthread_cond_destroy(&widelec[i++]);
	pthread_key_delete(klucz);
}

void interruptAll(int signo)
{
	int i = 5;
	while(i-- > 0)
		pthread_kill(fil[i], SIGUSR1);
	
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

void * filozof(void * arg)
{
	int i, id;
	
	if((id = (int)syscall(SYS_gettid)) == -1)
		ERR2("Blad syscall.\n",7)

	id %= 5;
	pthread_setspecific(klucz, &statystyki[id]);
	
	int id_2 = (id + 1) % 5;
	
	init(interrupt, &statystyki[id], "FIL");
		
	while(1)
	{
		if(pthread_mutex_lock(&print))
			ERR2("Blad pthread_mutex_lock.\n",8)
		printf("Filozof nr %d mysli\n", id);
		if(pthread_mutex_unlock(&print))
			ERR2("Blad pthread_mutex_unlock.\n",9)

		sleep(1);

		if(pthread_mutex_lock(&widelce))
			ERR2("Blad pthread_mutex_lock.\n",10)

		if((i = log_staty(&statystyki[id],"TRY")) != SUKCES)
			ERR2(error2str(i),11)
				
		while(dopuszczeni == 4)
			if(pthread_cond_wait(&lokaj, &widelce))
				ERR2("Blad pthread_cond_wait",12)
		dopuszczeni += 1;
		
		if(zajety[id])
			if(pthread_cond_wait(&widelec[id], &widelce))
				ERR2("Blad pthread_cond_wait",13)
		zajety[id] = 1;
		
		if(zajety[id_2])
			if(pthread_cond_wait(&widelec[id_2], &widelce))
				ERR2("Blad pthread_cond_wait",14)
		zajety[id_2] = 1;
		
		if(pthread_mutex_unlock(&widelce))
			ERR2("Blad pthread_mutex_unlock.\n",15)
		
		if((i = log_staty(&statystyki[id],"IN")) != SUKCES)
			ERR2(error2str(i),16)

		if(pthread_mutex_lock(&print))
			ERR2("Blad pthread_mutex_lock.\n",17)
		printf("Filozof nr %d je\n", id);
		if(pthread_mutex_unlock(&print))
			ERR2("Blad pthread_mutex_unlock.\n",18)
		
		sleep(1);
				
		if((i = log_staty(&statystyki[id],"OUT")) != SUKCES)
			ERR2(error2str(i),19)
		
		if(pthread_mutex_lock(&widelce))
			ERR2("Blad pthread_mutex_lock.\n",20)
		
		zajety[id] = 0;
		if(pthread_cond_signal(&widelec[id]))
			ERR2("Blad pthread_cond_signal.\n",21)
		
		zajety[id_2] = 0;
		if(pthread_cond_signal(&widelec[id_2]))
			ERR2("Blad pthread_cond_signal.\n",22)

		dopuszczeni--;
		if(pthread_cond_signal(&lokaj))
			ERR2("Blad pthread_cond_signal.\n",23)

		if(pthread_mutex_unlock(&widelce))
			ERR2("Blad pthread_mutex_unlock.\n",24)
	}	
}

int main(void)
{
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",25)
	if(pthread_sigmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad pthread_sigmask. Konczymy.\n",26)
	
	atexit(clearAll);
	
	struct sigaction sa;
	sa.sa_handler = interruptAll;
	sa.sa_flags = 0;
	if(sigaction(SIGINT, &sa, NULL) == -1)
		ERR("Blad sigaction. Konczymy.\n",27)
		
	int i = 0;
	while(i < 5)
	{
		zajety[i] = 0;
		if(pthread_cond_init(&widelec[i++], NULL))
			ERR("Blad pthread_mutex_init. Konczymy.\n",28)
	}

	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",29)

	if(pthread_key_create(&klucz, NULL))
		ERR("Blad pthread_key_create.\n",30)

	i = 0;
	int j;
	while(i < 5)
		if((j = stworz_watek(&fil[i++], 1, filozof, NULL)) != SUKCES)
			ERR(error2str(j),31)

	sigsuspend(&set);

	exit(0);
}
