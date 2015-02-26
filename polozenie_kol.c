#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct kolo
{
    char *nazwa;
    double x,y,promien;//x,y-wspolrzedne srodka
    int numer;
    struct kolo *wsk;
};

struct tablica
{
    int wiersz;
    int kolumna;
    int czesc_wspolna;
    struct tablica *wsk;
};

char *dodaj_nazwe()
{
    char bufor[256];
    char *nazwa;
    printf("Podaj nazwe kola: ");
    scanf("%s",bufor);
    getchar();
    nazwa=malloc((strlen(bufor)+1)*sizeof(char));
    strcpy(nazwa,bufor);
    return nazwa;
}

void dodaj_kolo(struct kolo **poczatek,int licznik)
{
    struct kolo *nowy=malloc(sizeof(struct kolo));
    nowy->nazwa=dodaj_nazwe();
    printf("Podaj x: ");
    scanf("%lf",&nowy->x);
    getchar();
    printf("Podaj y: ");
    scanf("%lf",&nowy->y);
    getchar();
    printf("Podaj promien: ");
    scanf("%lf",&nowy->promien);
    getchar();
    nowy->numer=licznik;
    if(*poczatek==NULL)
    {
        nowy->wsk=*poczatek;
        *poczatek=nowy;
    }
    else
    {
        struct kolo *iterator=*poczatek;
        while(iterator->wsk!=NULL)
        {
            iterator=iterator->wsk;
        }
        nowy->wsk=iterator->wsk;
        iterator->wsk=nowy;
    }
}

void wypisz(struct kolo *poczatek)
{
    struct kolo *iterator=poczatek;
    while(iterator!=NULL)
    {
        printf("Kolo %s\n",iterator->nazwa);
        printf("X: %.2lf\n",iterator->x);
        printf("Y: %.2lf\n",iterator->y);
        printf("Promien: %.2lf\n",iterator->promien);
        iterator=iterator->wsk;
    }
}

int ile_kol(struct kolo *poczatek)
{
    struct kolo *iterator=poczatek;
    int licznik=0;
    while(iterator!=NULL)
    {
        licznik++;
        iterator=iterator->wsk;
    }
    return licznik;
}

void czesc_wspolna(struct kolo *poczatek,struct tablica **tab)
{
    int i,j;
    struct kolo *iterator_i=poczatek;
    struct kolo *iterator_j;
    int liczba_kol=ile_kol(poczatek);

    for(i=1;i<=liczba_kol;i++)
    {
        iterator_j=iterator_i->wsk;
        for(j=i+1;j<=liczba_kol;j++)
        {
            double odleglosc_miedzy_srodkami;
            struct tablica *nowa_komorka=malloc(sizeof(struct tablica));
            odleglosc_miedzy_srodkami=sqrt(pow(iterator_i->x-iterator_j->x,2)+pow(iterator_i->y-iterator_j->y,2));
            nowa_komorka->wsk=*tab;
            *tab=nowa_komorka;
            nowa_komorka->kolumna=j;
            nowa_komorka->wiersz=i;
            printf("[%d, %d] ",i,j);
            if(odleglosc_miedzy_srodkami>(iterator_i->promien+iterator_j->promien))
            {
                printf("nie\n");
                nowa_komorka->czesc_wspolna=0;
            }
            else
            {
                printf("tak\n");
                nowa_komorka->czesc_wspolna=1;
            }
            iterator_j=iterator_j->wsk;
        }
        iterator_i=iterator_i->wsk;
    }
}

void wypisz_tabele(struct tablica *tab,struct kolo *poczatek)
{
    int i,j;
    struct kolo *iterator_i=poczatek;
    struct kolo *iterator_j;
    struct tablica *iterator_po_tablicy;
    int liczba_kol=ile_kol(poczatek);

    for(i=1;i<=liczba_kol;i++)
    {
        iterator_j=iterator_i->wsk;
        for(j=i+1;j<=liczba_kol;j++)
        {
            iterator_po_tablicy=tab;
            while(1)
            {
                if((iterator_po_tablicy->wiersz==i)&&(iterator_po_tablicy->kolumna==j))break;
                iterator_po_tablicy=iterator_po_tablicy->wsk;
            }
            printf("[%s, %s] ",iterator_i->nazwa,iterator_j->nazwa);
            if(iterator_po_tablicy->czesc_wspolna) printf("tak\n");
            else printf("nie\n");
            iterator_j=iterator_j->wsk;
        }
        iterator_i=iterator_i->wsk;
    }
}

int main()
{
    struct kolo *poczatek=NULL;
    struct tablica *tab=NULL;
    int licznik=0;
    while(1)
    {
        char klawisz;
        printf("p - dodaj kolo\n");
        printf("q - koniec dodawania\n");
        printf("Wybor: ");
        scanf("%c",&klawisz);
        getchar();
        if (klawisz=='p')
        {
            licznik++;
            dodaj_kolo(&poczatek,licznik);
        }
        else if (klawisz=='q')
        {
            break;
        }

        system("clear");
    }
    wypisz(poczatek);
    czesc_wspolna(poczatek,&tab);
    /*int i,j;
    for(i=1;i<=licznik;i++)
    {
        for(j=i+1;j<=licznik;j++)
        {
            printf("[%d, %d] ",i,j);
            struct tablica *iterator=tab;
            while(1)
            {
                if((iterator->wiersz==i)&&(iterator->kolumna==j)) break;
                iterator=iterator->wsk;
            }
            if (iterator->czesc_wspolna) printf("tak\n");
            else printf("nie\n");
        }
    }*/

    wypisz_tabele(tab,poczatek);
    return 0;
}
