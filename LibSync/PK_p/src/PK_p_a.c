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
#define PROD 3
#define KONS 5
#define TABLICA 10
#define MAXVAL 100

semafor_t sem;
pamiec_t pam;
pid_t prod[PROD];
pid_t kons[KONS];
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
	int i = PROD;
	while(i-- > 0)
		kill(prod[i], SIGINT);
	i = KONS;
	while(i-- > 0)
		kill(kons[i], SIGINT);

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

void producent()
{
	init(clean, interrupt, &pam, &statystyki, "PROD");
	
	struct sembuf sb[2];

	double zadanie;
	int * licznik = (int*)(((double*)pam.pam_adres) + TABLICA);
	int i;
	
	while(1)
	{
		sb[0].sem_num = 0;	//wolne
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 2;	//ochrona licznika dla producentow
		sb[1].sem_op = -1;
		sb[1].sem_flg = 0;
		
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),8)
	
		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),9)
		
		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),10)

		zadanie = *(((double*)pam.pam_adres)+(*licznik)); 
		zadanie += 1.2;
		zadanie *= 2.5;
		zadanie /= 3.2;
		zadanie -= 0.2;
		zadanie *= 1.7;
		zadanie -= 1.2;
		*(((double*)pam.pam_adres)+(*licznik)) = zadanie; 
		
		sb[0].sem_num = 4;	//semafor na stdout
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),11)
		
		printf("Licznik: %d\tWyprodukowano: %lf\n", *licznik, zadanie);
		
		sb[0].sem_num = 4;	//semafor na stdout
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),12)
		
		*licznik = ((*licznik) + 1) % TABLICA;

		sb[0].sem_num = 1;	//pelne
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 2;	//ochrona licznika dla producentow
		sb[1].sem_op = 1;
		sb[1].sem_flg = 0;
		
		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),13)

		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),14)

		sleep(1);
	}	
}

void konsument()
{
	init(clean, interrupt, &pam, &statystyki, "KONS");

	struct sembuf sb[2];
	
	int i;
	int * licznik = (int*)(((double*)pam.pam_adres) + TABLICA) + 1;
	double zadanie;

	while(1)
	{
		sb[0].sem_num = 1;	//pelne
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 3;	//ochrona licznika dla konsumentow
		sb[1].sem_op = -1;
		sb[1].sem_flg = 0;
		
		if((i = log_staty(&statystyki,TRY)) != SUKCES)
			ERR(error2str(i),15)

		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),16)

		if((i = log_staty(&statystyki,IN)) != SUKCES)
			ERR(error2str(i),17)	

		zadanie = *(((double*)pam.pam_adres)+(*licznik)); 
		zadanie += 1.2;
		zadanie /= 1.7;
		zadanie += 0.2;
		zadanie *= 3.2;
		zadanie /= 2.5;
		zadanie -= 1.2;

		sb[0].sem_num = 4;	//semafor na stdout
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),18)
		
		printf("Licznik: %d\tOdczytano: %lf\t Poprzednia wartosc: %lf\n", 
				*licznik, *(((double*)pam.pam_adres)+(*licznik)), zadanie);
		
		sb[0].sem_num = 4;	//semafor na stdout
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		if((i = zmien_semafory(&sem, sb, 1)) != SUKCES)
			ERR(error2str(i),19)

		*licznik = ((*licznik) + 1) % TABLICA;

		sb[0].sem_num = 0;	//wolne
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		sb[1].sem_num = 3;	//ochrona licznika dla konsumentow
		sb[1].sem_op = 1;
		sb[1].sem_flg = 0;	
		
		if((i = log_staty(&statystyki,OUT)) != SUKCES)
			ERR(error2str(i),20)
		
		if((i = zmien_semafory(&sem, sb, 2)) != SUKCES)
			ERR(error2str(i),21)

		sleep(1);
	}	
}

int main(void)
{
	sigset_t set;
	if(sigfillset(&set) == -1)
		ERR("Blad sigfillset. Konczymy.\n",22)
	if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
		ERR("Blad sigprocmask. Konczymy.\n",23)
	
	atexit(clearAll);
	
	if(signal(SIGINT, interruptAll) == SIG_ERR)
		ERR("Blad signal. Konczymy.\n",24)
		
	int i;
	if((i = stworz_semafory(&sem, 5, SEMAFOR_ID, 5, TABLICA, 0, 1, 1, 1)) != SUKCES)
		ERR(error2str(i),25)

	if((i = stworz_pamiec(&pam, TABLICA*sizeof(double) + 2*sizeof(int), PAMIEC_ID, 1)) != SUKCES)
		ERR(error2str(i),26)
	
	if(sigdelset(&set, SIGINT) == -1)
		ERR("Blad sigdelset. Konczymy.\n",27)

	i = 0;
	while(i < TABLICA)
	{
		*(((double *)pam.pam_adres) + i) = (double)i;
		++i;
	}

	i = 0;
	while(i < PROD)
		prod[i++] = -1;
	
	i = 0;
	while(i < KONS)
		kons[i++] = -1;

	i = 0;
	while(i < PROD)
	{
		if((prod[i] = fork()) == -1)
			ERR("Blad fork. Konczymy.\n",28)
		else if(prod[i] == 0)
			producent();
		i++;
	}

	i = 0;
	while(i < KONS)
	{
		if((kons[i] = fork()) == -1)
			ERR("Blad fork. Konczymy.\n",29)
		else if(kons[i] == 0)
			konsument();
		i++;
	}		

	sigsuspend(&set);
//interruptAll(0);
	exit(0);
}
