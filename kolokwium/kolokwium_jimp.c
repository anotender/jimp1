//Nowak wersja B2 wtorek 17

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct sedzia
{
    int identyfikator;
    char *nazwisko;
};

struct wezel
{
    struct sedzia *wsk_sedzia;
    struct wezel *wsk_wezel;
};

struct tablica
{
    int i,j;
    struct tablica *kolejny_mecz;
    struct sedzia *wsk_sedzia[3];
};

char *wczytaj_nazwisko()
{
    char bufor[256];
    char *nazwisko;
    printf("Podaj nazwisko sedziego: ");
    scanf("%s",bufor);
    getchar();
    nazwisko=malloc((strlen(bufor)+1)*sizeof(char));
    strcpy(nazwisko,bufor);
    return nazwisko;
}

void dodaj_wezel(struct sedzia *nowy_sedzia,struct wezel **poczatek)
{
    struct wezel *nowy_wezel=malloc(sizeof(struct wezel));
    nowy_wezel->wsk_sedzia=nowy_sedzia;
    if(*poczatek==NULL)
    {
        nowy_wezel->wsk_wezel=*poczatek;
        *poczatek=nowy_wezel;
    }
    else
    {
        struct wezel *iterator=*poczatek;
        while(iterator->wsk_wezel!=NULL)
        {
            iterator=iterator->wsk_wezel;
        }
        nowy_wezel->wsk_wezel=iterator->wsk_wezel;
        iterator->wsk_wezel=nowy_wezel;
    }
}

int wczytaj_sedziow(struct wezel **poczatek)
{
    srand(time(NULL));
    int id;
    printf("Podaj id sedziego: ");
    scanf("%d",&id);
    if (id)
    {
        struct sedzia *nowy_sedzia=malloc(sizeof(struct sedzia));
        nowy_sedzia->identyfikator=id;
        nowy_sedzia->nazwisko=wczytaj_nazwisko();
        dodaj_wezel(nowy_sedzia,poczatek);
        return 1;
    }
    else
    {
        return 0;
    }
}

struct sedzia *losuj_sedziego(struct wezel *poczatek,const int liczba_sedziow)
{
    int wylosowana_liczba=rand()%liczba_sedziow;
    int i;
    struct wezel *iterator=poczatek;
    for(i=0;i<wylosowana_liczba;i++)
    {
        iterator=iterator->wsk_wezel;
    }
    return iterator->wsk_sedzia;
}

/*do celow testowych
void wypisz(struct wezel *poczatek)
{
    struct wezel *iterator=poczatek;
    while(iterator!=NULL)
    {
        printf("%d. %s\n",iterator->wsk_sedzia->identyfikator,iterator->wsk_sedzia->nazwisko);
        iterator=iterator->wsk_wezel;
    }
}*/

void wypisz_mecze(struct tablica *poczatek)
{
    struct tablica *iterator=poczatek;
    while(iterator!=NULL)
    {
        printf("[%d vs %d] %s %s %s\n",iterator->i,iterator->j,iterator->wsk_sedzia[0]->nazwisko,iterator->wsk_sedzia[1]->nazwisko,iterator->wsk_sedzia[2]->nazwisko);
        iterator=iterator->kolejny_mecz;
    }
}

int main()
{
    int liczba_druzyn,liczba_sedziow,i,j;
    struct wezel *poczatek_wezlow=NULL;
    struct tablica *poczatek_tablicy=NULL;

    liczba_sedziow=0;
    do
    {
        liczba_sedziow++;
        system("clear");
    }while(wczytaj_sedziow(&poczatek_wezlow));

    system("clear");

    liczba_sedziow=liczba_sedziow-1;

    printf("Podaj liczbe druzyn: ");
    scanf("%d",&liczba_druzyn);
    getchar();

    system("clear");

    //wypisz(poczatek_wezlow);
    for(i=1;i<=liczba_druzyn;i++)
    {
        for(j=i+1;j<=liczba_druzyn;j++)
        {
            struct tablica *nowy_mecz=malloc(sizeof(struct tablica));
            nowy_mecz->kolejny_mecz=poczatek_tablicy;
            poczatek_tablicy=nowy_mecz;
            nowy_mecz->i=i;
            nowy_mecz->j=j;
            nowy_mecz->wsk_sedzia[0]=losuj_sedziego(poczatek_wezlow,liczba_sedziow);
            while(1)
            {
                nowy_mecz->wsk_sedzia[1]=losuj_sedziego(poczatek_wezlow,liczba_sedziow);
                if (nowy_mecz->wsk_sedzia[1]!=nowy_mecz->wsk_sedzia[0]) break;
            }
            while(1)
            {
                nowy_mecz->wsk_sedzia[2]=losuj_sedziego(poczatek_wezlow,liczba_sedziow);
                if ((nowy_mecz->wsk_sedzia[2]!=nowy_mecz->wsk_sedzia[0])&&(nowy_mecz->wsk_sedzia[2]!=nowy_mecz->wsk_sedzia[1])) break;
            }
        }
    }

    wypisz_mecze(poczatek_tablicy);


    return 0;
}