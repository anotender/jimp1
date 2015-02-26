#include <stdio.h>
#include <stdlib.h>

struct diamenty
{
    int cena,numer;
    struct diamenty *wsk;
};

struct para
{
    int cena,i,j;//i-wiersz;j-kolumna
    struct para *wsk;
};

struct diamenty *wczytaj()//funkcja sluzy do wczytywania liczby i ceny kolejnych diamentow, zwraca adres pierwszego diamentu
{
    struct diamenty *poczatek=NULL;
    int i,liczba;
    printf("Podaj liczbe diamentow: ");
    scanf("%d",&liczba);
    for(i=liczba;i>0;i--)
    {
        struct diamenty *nowy;
        nowy=(struct diamenty*)malloc(sizeof(struct diamenty));
        nowy->wsk=poczatek;
        poczatek=nowy;
        nowy->numer=i;
        printf("Podaj cene %d. diamentu: ",i);
        scanf("%d",&nowy->cena);
    }
    return poczatek;
}

struct para *policz(struct diamenty *poczatek)//funkcja liczy sume kazdej pary diamentow, przyjmuje adres pierwszego diamentu i zwraca adres pierwszej pary
{
    struct para *pierwsza_para=NULL;
    int i,j;
    int liczba=0;
    struct diamenty *iterator=poczatek;
    iterator=poczatek;
    while(iterator!=NULL)
    {
        liczba++;
        iterator=iterator->wsk;
    }
    for(i=1;i<=liczba;i++)
    {
        for(j=i+1;j<=liczba;j++)
        {
            struct para *nowy;
            nowy=(struct para*)malloc(sizeof(struct para));
            nowy->wsk=pierwsza_para;
            pierwsza_para=nowy;
            nowy->i=i;
            nowy->j=j;
            iterator=poczatek;
            while(iterator->numer!=i)
            {
                iterator=iterator->wsk;
            }
            nowy->cena=iterator->cena;
            iterator=poczatek;
            while(iterator->numer!=j)
            {
                iterator=iterator->wsk;
            }
            nowy->cena+=iterator->cena;
        }
    }
    return pierwsza_para;
}

void wypisz_wszystkie_ceny(struct diamenty *poczatek)//funkcja sluzy do wypisywania ceny kazdego diamentu, jako argument przyjmuje wskaznik na pierwszy diament
{
    struct diamenty *iterator=poczatek;
    int i=1;
    while(iterator!=NULL)
    {
        printf("Cena %d. diamentu: %d\n",i,iterator->cena);
        iterator=iterator->wsk;
        i++;
    }
}

void wypisz_sume(struct para *poczatek)//funkcja sluzy do wypisania sumy zadanej pary diamentow, jako argument przyjmuje adres pierwszej pary
{
    int i,j;
    while(1)
    {
        printf("Podaj numer pierwszego diamentu: ");
        scanf("%d",&i);
        printf("Podaj numer drugiego diamentu: ");
        scanf("%d",&j);
        if(j!=i)break;
        printf("Nie mozesz policzyc wziac dwoch tych samych diamentow.");
        system("clear");
    }
    if(j<i)
    {
        int tmp=i;
        i=j;
        j=tmp;
    }
    struct para *iterator=poczatek;
    while(1)
    {
        if((iterator->i==i)&&(iterator->j==j))break;
        iterator=iterator->wsk;
    }
    printf("Cena: %d",iterator->cena);
}

int main()
{
    struct diamenty *poczatek_diamentow;
    struct para *pierwsza_para;
    poczatek_diamentow=wczytaj(poczatek_diamentow);
    wypisz_wszystkie_ceny(poczatek_diamentow);
    pierwsza_para=policz(poczatek_diamentow);
    wypisz_sume(pierwsza_para);
    return 0;
}
