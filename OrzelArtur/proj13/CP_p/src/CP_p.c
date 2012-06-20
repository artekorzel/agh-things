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
#define PAMIEC_ID 2
#define CZYT 5
#define PIS 3

semafor_t sem;
//0 - wolne
//1 - przedsionek
//2 - pisarze
//3 - printf

pamiec_t pam;
pid_t czyt[CZYT];
pid_t pis[PIS];
staty_t statystyki;

void clean(void)
{
	zakoncz_staty(&statystyki);
	zwolnij_pamiec(&pam, 0);
}

void interrupt(int signo)
{
	exit(0);
}


void clearAll(void)
{
	usun_semafory(&sem);
	zwolnij_pamiec(&pam, 1);
}

void interruptAll(int signo)
{
	int i = CZYT;
	while(i-- > 0)
		kill(czyt[i], SIGINT);
	i = PIS;
	while(i-- > 0)
		kill(pis[i], SIGINT);

	if((i = analizuj_staty(LOG_KAT, LOG_OST)) != SUKCES)
		ERR(error2str(i),1)
	
	exit(0);
}

void init(void (*clean)(void), void (*interrupt)(int), pamiec_t * pam, staty_t * staty, char * nazwa)
{
	atexit(clean);
	
	int i;
	if((i = stworz_staty(staty, nazwa, LOG_KAT)) != SUKCES)
		ERR(error2str(i),2)
	
	if(signal(SIGINT, interrupt) == SIG_ERR)
		ERR("Blad signal. Konczymy.\n",3)
		
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",4)
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",5)
	if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",6)

	if((i = stworz_pamiec(pam, 0, PAMIEC_ID, 1)) != SUKCES)
		ERR(error2str(i),7)
}

void pisarz()
{
	init(clean, interrupt, &pam, &statystyki, "PIS");
	
	struct sembuf sb[2];

	double zadanie;
	int i;
	
	while(1)
	{
		sb[0].sem_num = 1;	//przedsionek
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 2;	//pisarze
		sb[1].sem_op = -1;
		sb[1].sem_flg = 0;
	
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)

		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),9)

		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),10)

		sb[0].sem_num = 0;	//wolne
		sb[0].sem_op = -CZYT;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 1;	//przedsionek
		sb[1].sem_op = -1;
		sb[1].sem_flg = 0;
	
		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),11)

		zadanie = *((double*)pam.pam_adres); 
		zadanie += 1.2;
		zadanie *= 2.5;
		zadanie /= 3.2;
		zadanie -= 0.2;
		zadanie *= 1.7;
		zadanie -= 1.2;
		*((double*)pam.pam_adres) = zadanie; 
		
		sb[0].sem_num = 3;	//semafor na stdout
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),12)
		
		printf("Zapisano: %lf\n", zadanie);
		
		sb[0].sem_num = 3;	//semafor na stdout
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),13)

		sb[0].sem_num = 0;	//wolne
		sb[0].sem_op = CZYT;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 2;	//pisarze
		sb[1].sem_op = 1;
		sb[1].sem_flg = 0;
		
		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),14)

		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),15)

		sleep(1);
	}	
}

void czytelnik()
{
	init(clean, interrupt, &pam, &statystyki, "CZYT");

	struct sembuf sb[2];
	
	int i;
	double zadanie;

	while(1)
	{
		sb[0].sem_num = 0;	//wolne
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 1;	//przedsionek
		sb[1].sem_op = 0;
		sb[1].sem_flg = 0;

		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),16)

		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),17)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),18)

		zadanie = *((double*)pam.pam_adres); 

		sb[0].sem_num = 3;	//semafor na stdout
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),19)
		
		printf("Odczytano: %lf\n", zadanie);
		
		sb[0].sem_num = 3;	//semafor na stdout
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),20)

		sb[0].sem_num = 0;	//wolne
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;	
		
		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),21)

		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),22)

		sleep(1);
	}	
}

int main(void)
{
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",23)
	if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",24)
	
	atexit(clearAll);
	
	if(signal(SIGINT, interruptAll) == SIG_ERR)
		ERR("Blad signal. Konczymy.\n",25)
		
	int i;
	if((i = stworz_semafory(&sem, 4, SEMAFOR_ID, 4, CZYT, 0, 1, 1)) != SUKCES)
		ERR(error2str(i),26)

	if((i = stworz_pamiec(&pam, sizeof(double), PAMIEC_ID, 1)) != SUKCES)
		ERR(error2str(i),27)
	
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",28)

	*((double *)pam.pam_adres) = 1.0;

	i = 0;
	while(i < CZYT)
		czyt[i++] = -1;
	
	i = 0;
	while(i < PIS)
		pis[i++] = -1;

	i = 0;
	while(i < CZYT)
	{
		if((czyt[i] = fork()) == -1)
			ERR("Blad fork. Konczymy.\n",29)
		else if(czyt[i] == 0)
			czytelnik();
		i++;
	}

	i = 0;
	while(i < PIS)
	{
		if((pis[i] = fork()) == -1)
			ERR("Blad fork. Konczymy.\n",30)
		else if(pis[i] == 0)
			pisarz();
		i++;
	}		

	sigsuspend(&set);

	exit(0);
}
