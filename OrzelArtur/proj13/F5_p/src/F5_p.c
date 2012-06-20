#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include"sync.h"

#define ERR(X,Y) {printf("%s",X);exit(Y);}

#define LOG_KAT "./log/"
#define LOG_OST "./log.log"
#define SEMAFOR_ID 1

semafor_t sem;	//0 - 4 widelce oraz 5 - lokaj, 6 - stdout
pid_t fil[5];
staty_t statystyki;

void clean(void)
{
	zakoncz_staty(&statystyki);
}

void interrupt(int signo)
{
	exit(0);
}


void clearAll(void)
{
	usun_semafory(&sem);
}

void interruptAll(int signo)
{
	int i = 5;
	while(i-- > 0)
		kill(fil[i], SIGINT);

	if((i = analizuj_staty(LOG_KAT, LOG_OST)) != SUKCES)
		ERR(error2str(i),1)

	exit(0);
}

void init(void (*clean)(void), void (*interrupt)(int), staty_t * staty, char * nazwa)
{
	atexit(clean);

	int i;
	if((i = stworz_staty(staty, nazwa, LOG_KAT)) != SUKCES)
		ERR(error2str(i),1)
	
	if(signal(SIGINT, interrupt) == SIG_ERR)
		ERR("Blad signal. Konczymy.\n",2)
		
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",3)
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",4)
	if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",5)
}

void filozof(int indeks)
{
	init(clean, interrupt, &statystyki, "FIL");
	
	struct sembuf sb;
	int i;
	
	while(1)
	{
		sb.sem_num = 6;					//stdout
		sb.sem_op = -1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),6)
		
		printf("Filozof nr %d mysli\n", indeks);
		
		sb.sem_num = 6;					//stdout
		sb.sem_op = 1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),7)

		sleep(1);

		sb.sem_num = 5;					//lokaj
		sb.sem_op = -1;
		sb.sem_flg = 0;
		
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)
	
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),9)
		
		sb.sem_num = indeks;			//widelec lewy
		sb.sem_op = -1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),10)
		
		sb.sem_num = (indeks+1) % 5;	//widelec prawy
		sb.sem_op = -1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),11)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),12)

		sb.sem_num = 6;					//stdout
		sb.sem_op = -1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),13)
		
		printf("Filozof nr %d je\n", indeks);
		
		sb.sem_num = 6;					//stdout
		sb.sem_op = 1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),14)
	
		sleep(1);

		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),15)
		
		sb.sem_num = indeks;			//widelec lewy
		sb.sem_op = 1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),16)
		
		sb.sem_num = (indeks+1) % 5;	//widelec prawy
		sb.sem_op = 1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),17)
		
		sb.sem_num = 5;					//lokaj
		sb.sem_op = 1;
		sb.sem_flg = 0;
		
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),18)
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
		
	int i;
	if((i = stworz_semafory(&sem, 7, SEMAFOR_ID, 7, 1, 1, 1, 1, 1, 4, 1)) != SUKCES)
		ERR(error2str(i),22)

	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",23)

	i = 0;
	while(i < 5)
		fil[i++] = -1;
	
	i = 0;
	while(i < 5)
	{
		if((fil[i] = fork()) == -1)
			ERR("Blad fork. Konczymy.\n",24)
		else if(fil[i] == 0)
			filozof(i);
		i++;
	}

	sigsuspend(&set);
//interruptAll(0);
	exit(0);
}
