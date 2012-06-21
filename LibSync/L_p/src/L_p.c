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
#define SAMOLOTY 10
#define N_SAM 10
#define K_SAM 5

semafor_t sem;	//0 - stdout, 1 - dostep, 2 - pas_start, 3 - pas_lad
pamiec_t pam;
pid_t sam[SAMOLOTY];
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
	int i = SAMOLOTY;
	while(i-- > 0)
		kill(sam[i], SIGINT);

	if((i = analizuj_staty(LOG_KAT, LOG_OST)) != SUKCES)
		ERR(error2str(i),1)

	exit(0);
}

void init(void (*clean)(void), void (*interrupt)(int), pamiec_t * pam, staty_t * staty, char * nazwa)
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
	
	if((i = stworz_pamiec(pam, 0, PAMIEC_ID, 1)) != SUKCES)
		ERR(error2str(i),7)
}

void zwolnij_pas(int * tab)
{
	struct sembuf sb;
	int i;
	if(tab[0] < K_SAM)	//priorytet dla ladujacych
	{
		if(tab[2] > 0)
		{
			tab[2]--;
			sb.sem_num = 3;	//pas_lad
			sb.sem_op = 1;
			sb.sem_flg = 0;
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),9)			
		}
		else if(tab[1] > 0)
		{
			tab[1]--;
			sb.sem_num = 2;	//pas_start
			sb.sem_op = 1;
			sb.sem_flg = 0;
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),9)			
		}
		else tab[3] = 1;
	}
	else	//priorytet dla startujacych
	{
		if(tab[1] > 0)	
		{
			tab[1]--;
			sb.sem_num = 2;	//pas_start
			sb.sem_op = 1;
			sb.sem_flg = 0;
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),9)			
		}
		else if(tab[2] > 0 && tab[0] < N_SAM)
		{
			tab[2]--;
			sb.sem_num = 3;	//pas_lad
			sb.sem_op = 1;
			sb.sem_flg = 0;
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),9)			
		}
		else tab[3] = 1;
	}
}

void zmiana(int ind, char * str)
{
	struct sembuf sb;
	int i;
	sb.sem_num = 0;	//semafor na stdout
	sb.sem_op = -1;
	sb.sem_flg = 0;
	if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
		ERR(error2str(i),11)
	
	printf("Samolot nr %d %s", ind, str);
	
	sb.sem_num = 0;	//semafor na stdout
	sb.sem_op = 1;
	sb.sem_flg = 0;
	if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
		ERR(error2str(i),12)

	sleep(1);
}

void samolot(int ind)
{
	init(clean, interrupt, &pam, &statystyki, "SAM");
	
	struct sembuf sb;
	int * tab = (int *)pam.pam_adres;
	int i;
	
	while(1)
	{
		zmiana(ind, "jest na lotniskowcu\n");

		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		sb.sem_num = 1;	//dostep
		sb.sem_op = -1;
		sb.sem_flg = 0;
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),12)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),10)

		if(tab[3])
		{
			tab[3] = 0;

			sb.sem_num = 1;	//dostep
			sb.sem_op = 1;
			sb.sem_flg = 0;
			
			if((i = log_staty(&statystyki,OUT)) != SUKCES)
				ERR(error2str(i),10)
			
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),12)
		}
		else
		{
			tab[1]++;
			sb.sem_num = 1;	//dostep
			sb.sem_op = 1;
			sb.sem_flg = 0;
			
			if((i = log_staty(&statystyki,OUT)) != SUKCES)
				ERR(error2str(i),10)
			
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),12)
			
			sb.sem_num = 2;	//pas_start
			sb.sem_op = -1;
			sb.sem_flg = 0;
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),12)
		}

		zmiana(ind, "startuje\n");

		sb.sem_num = 1;	//dostep
		sb.sem_op = -1;
		sb.sem_flg = 0;
		
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),12)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),10)

		tab[0]--;
		zwolnij_pas(tab);
		
		sb.sem_num = 1;	//dostep
		sb.sem_op = 1;
		sb.sem_flg = 0;
			
		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),10)
			
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),12)

		zmiana(ind, "leci\n");

		sb.sem_num = 1;	//dostep
		sb.sem_op = -1;
		sb.sem_flg = 0;
		
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),12)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),10)

		if(tab[3] && tab[0] < N_SAM)
		{
			tab[3] = 0;

			sb.sem_num = 1;	//dostep
			sb.sem_op = 1;
			sb.sem_flg = 0;
			
			if((i = log_staty(&statystyki,OUT)) != SUKCES)
				ERR(error2str(i),10)
			
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),12)
		}
		else
		{
			tab[2]++;
			sb.sem_num = 1;	//dostep
			sb.sem_op = 1;
			sb.sem_flg = 0;
			
			if((i = log_staty(&statystyki,OUT)) != SUKCES)
				ERR(error2str(i),10)
			
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),12)
			
			sb.sem_num = 3;	//pas_lad
			sb.sem_op = -1;
			sb.sem_flg = 0;
			if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
				ERR(error2str(i),12)
		}

		zmiana(ind, "laduje\n");

		sb.sem_num = 1;	//dostep
		sb.sem_op = -1;
		sb.sem_flg = 0;
		
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)
		
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),12)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),10)

		tab[0]++;
		zwolnij_pas(tab);
		
		sb.sem_num = 1;	//dostep
		sb.sem_op = 1;
		sb.sem_flg = 0;
			
		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),10)
			
		if((i = zmien_semafory(&sem, &sb, 1)) != SUKCES)
			ERR(error2str(i),12)
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
	if((i = stworz_semafory(&sem, 4, SEMAFOR_ID, 2, 1, 1)) != SUKCES)
		ERR(error2str(i),22)	
	
	//0 - stdout, 1 - dostep, 2 - pas_start, 3 - pas_lad
	
	if((i = stworz_pamiec(&pam, 4*sizeof(int), PAMIEC_ID, 1)) != SUKCES)
		ERR(error2str(i),26)

	//0 - na_lotniskowcu, 1 - chce_start, 2 - chce_lad, 3 - wolny_pas
	int * tab = (int *)pam.pam_adres;
	tab[0] = N_SAM/2;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 1;

	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",23)

	i = 0;
	while(i < SAMOLOTY)
		sam[i++] = -1;
	
	i = 0;
	while(i < SAMOLOTY)
	{
		if((sam[i] = fork()) == -1)
			ERR("Blad fork. Konczymy.\n",24)
		else if(sam[i] == 0)
			samolot(i);
		i++;
	}

	sigsuspend(&set);
//interruptAll(0);
	exit(0);
}
