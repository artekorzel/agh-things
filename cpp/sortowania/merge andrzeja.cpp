#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const int zakres=10000000;
void scal(int *, int* ,int* , int* ,int , int );
void swap (int &war1, int &war2)
{
        int temp;
        temp=war1;
        war1=war2;
        war2=temp;
}
  
void merge(int *tablica,int poczatek, int koniec)
{
        int chaos;//ile elementow mam jeszcze nieposortowanych, czyli ile moge przerzucic
        int lewy,prawy; //jaka jest dlugosc lewego oraz prawego podciagu
        int srodek;                                     
        if (poczatek<koniec)
        {
                srodek=(poczatek+koniec)/2;
                lewy=srodek-poczatek+1; //dlugosc lewego
                prawy=koniec-srodek;    //prawego
                chaos=(zakres-1)-koniec; //ile elementow mam z prawej strony ciagu prawego, czyli ile mam nieposortowancyh
                merge(tablica,poczatek,srodek); //wywoluje rekurencyjnie do chwili az podciagi maja dlugosc rowna 1
                merge(tablica,srodek+1,koniec);
                scal(tablica+poczatek,tablica+poczatek,tablica+srodek,tablica+koniec,prawy,chaos); //procedura scal, wskazniki na poczatek,koniec       
                                                //pierwszego oraz koniec drugiego, przekazuje rowniez dlugosc prawego podciagu oraz ile mam nieposortowanych elem z prawej
        }
}
 
 
void scal(int *tablica, int* Lp,int* Lk, int* Pk,int prawa, int chaos)
{
        int* Pp=Lk+1; //poczatek drugiego
        int* wsk=Pk;    //wskaznik pomocniczy, uzywany przy przesuwaniu
        if (prawa<=chaos)       //czy mamy na tyle miejsca aby przesunac dwa podciagi i zrobic miejsce w lewym koncu tablicy
        {       //na prawy podciag
                while(wsk >= Lp) {swap(*wsk,*(wsk+prawa)); wsk--;} //przesuwam 
                Lp=Lp+prawa;
                Lk=Lk+prawa;
                Pk=Pk+prawa;
                Pp=Pp+prawa;
                while((Lp<=Lk) && (Pp<=Pk)) 
                {if (*Lp<*Pp) 
                        {swap(*tablica,*Lp); tablica++;Lp++;}
                        else {swap(*tablica,*Pp);tablica++;Pp++;}
                }
                while(Lp<=Lk) {swap(*tablica,*Lp); tablica++;Lp++;}     
                while(Pp<=Pk) {swap(*tablica,*Pp);tablica++;Pp++;}      
        }
        else 
        {
                while(prawa>chaos) {Pk--;prawa--;chaos++;}
                if (Pk>=Pp)
                    {
						wsk=Pk;
                        while(wsk >= Lp) {swap(*wsk,*(wsk+prawa)); wsk--;} //przesuwam 
                        Lp=Lp+prawa;
                        Lk=Lk+prawa;
                        Pk=Pk+prawa;
                        Pp=Pp+prawa;
                        while((Lp<=Lk) && (Pp<=Pk)) 
                        {if (*Lp<*Pp) 
                                {swap(*tablica,*Lp); tablica++;Lp++;}
                                else {swap(*tablica,*Pp);tablica++;Pp++;}
                        }
                        while(Lp<=Lk) {swap(*tablica,*Lp); tablica++;Lp++;}     
                        while(Pp<=Pk) {swap(*tablica,*Pp);tablica++;Pp++;}      
                        }
        }
}
 
void sortowanie(int *tablica,int poczatek,int zakres)
{
        int i,j;
        merge(tablica,poczatek,zakres-1);
        for (i=1;(tablica[i-1]<=tablica[i]) && i<zakres;i++);
        if (i < zakres)
                for( ;i<zakres;i++)
                {
                        int temp=tablica[i];
                        for(j=i;(tablica[j-1]>temp) && (j>0);j--) tablica[j]=tablica[j-1];
                        tablica[j]=temp;
                }                
} 
 
int main()
{
        int * tablica = (int *)malloc(zakres*sizeof(int));
        srand((int)time(NULL));
        for(int i=0;i<zakres;i++) {tablica[i]= rand() % 30;}
        
       clock_t start, end;
	start = clock();
	
	sortowanie(tablica,0,zakres);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);
        
        getchar();
}