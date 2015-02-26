#include <stdio.h>
#include <stdlib.h>

struct liczby
{
    double wartosc;
    struct liczby *wsk;
};

struct ciag
{
    int dlugosc_ciagu;
    struct liczby *wsk_liczby;
    struct ciag *nastepny;
};

struct srednia
{
    double wartosc;
    int dlugosc_ciagu;
};

struct ciag *wczytaj_liczby(const int dlugosc_ciagu)
{
    struct liczby *poczatek=NULL;
    struct liczby *nowy;
    int i;
    for(i=0;i<dlugosc_ciagu;i++)
    {
        nowy=malloc(sizeof(struct liczby));
        nowy->wsk=poczatek;
        poczatek=nowy;
        printf("Podaj wartosc %d. liczby: ",i+1);
        scanf("%lf",&nowy->wartosc);
        getchar();
    }
    return poczatek;
}

void wczytaj_ciag(struct ciag **poczatek,const int dlugosc_ciagu)
{
    struct ciag *nowy=malloc(sizeof(struct ciag));
    struct ciag *iterator=*poczatek;
    nowy->dlugosc_ciagu=dlugosc_ciagu;
    nowy->wsk_liczby=wczytaj_liczby(dlugosc_ciagu);
    if(*poczatek==NULL)
    {
        nowy->nastepny=*poczatek;
        *poczatek=nowy;
    }
    else
    {
        while(iterator->nastepny!=NULL)
        {
            iterator=iterator->nastepny;
        }
        nowy->nastepny=iterator->nastepny;
        iterator->nastepny=nowy;
    }
}

void wypisz(struct ciag *poczatek)
{
    struct ciag *iterator_po_ciagach=poczatek;
    struct liczby *iterator_po_liczbach;
    int licznik_ciagi=1;
    int licznik_liczby;
    while(iterator_po_ciagach!=NULL)
    {
        printf("Ciag %d\n",licznik_ciagi);
        iterator_po_liczbach=iterator_po_ciagach->wsk_liczby;
        licznik_liczby=1;
        while(iterator_po_liczbach!=NULL)
        {
            printf("Liczba %d: %.2lf\n",licznik_liczby,iterator_po_liczbach->wartosc);
            iterator_po_liczbach=iterator_po_liczbach->wsk;
            licznik_liczby++;
        }
        iterator_po_ciagach=iterator_po_ciagach->nastepny;
        licznik_ciagi++;
    }
}

void licz_srednia(struct srednia *srednia_min,struct srednia *srednia_max,struct ciag *poczatek)
{
    struct ciag *iterator_po_ciagach=poczatek;
    struct liczby *iterator_po_liczbach=poczatek->wsk_liczby;
    int dlugosc_ciagu_min_tmp,dlugosc_ciagu_max_tmp;//tu beda przechowywane tymczasowe dlugosci ciagu
    double srednia_min_tmp,srednia_max_tmp,srednia_tmp;//tu beda przechowywane tymczasowe srednie
    srednia_tmp=0;

    //licze srednia dla pierwszego ciagu

    while(iterator_po_liczbach!=NULL)
    {
        srednia_tmp+=iterator_po_liczbach->wartosc;
        iterator_po_liczbach=iterator_po_liczbach->wsk;
    }
    srednia_tmp=srednia_tmp/iterator_po_ciagach->dlugosc_ciagu;
    srednia_min_tmp=srednia_tmp;
    srednia_max_tmp=srednia_tmp;
    dlugosc_ciagu_min_tmp=iterator_po_ciagach->dlugosc_ciagu;
    dlugosc_ciagu_max_tmp=iterator_po_ciagach->dlugosc_ciagu;

    //licze srednia dla reszty

    while(iterator_po_ciagach!=NULL)
    {
        srednia_tmp=0;
        iterator_po_liczbach=iterator_po_ciagach->wsk_liczby;
        while(iterator_po_liczbach!=NULL)
        {
            srednia_tmp+=iterator_po_liczbach->wartosc;
            iterator_po_liczbach=iterator_po_liczbach->wsk;
        }
        srednia_tmp=srednia_tmp/iterator_po_ciagach->dlugosc_ciagu;
        if (srednia_tmp>srednia_max_tmp)
        {
            srednia_max_tmp=srednia_tmp;
            dlugosc_ciagu_max_tmp=iterator_po_ciagach->dlugosc_ciagu;
        }
        else if (srednia_tmp<srednia_min_tmp)
        {
            srednia_min_tmp=srednia_tmp;
            dlugosc_ciagu_min_tmp=iterator_po_ciagach->dlugosc_ciagu;
        }
        iterator_po_ciagach=iterator_po_ciagach->nastepny;
    }

    srednia_min->dlugosc_ciagu=dlugosc_ciagu_min_tmp;
    srednia_min->wartosc=srednia_min_tmp;
    srednia_max->dlugosc_ciagu=dlugosc_ciagu_max_tmp;
    srednia_max->wartosc=srednia_max_tmp;
}

int main()
{
    int dlugosc_ciagu;
    struct srednia srednia_min;
    struct srednia srednia_max;
    struct ciag *poczatek=NULL;

    while(1)
    {
        system("clear");
        printf("Podaj dlugosc ciagu: ");
        scanf("%d",&dlugosc_ciagu);
        getchar();
        if (dlugosc_ciagu==0) break;
        else wczytaj_ciag(&poczatek,dlugosc_ciagu);
    }

    wypisz(poczatek);

    licz_srednia(&srednia_min,&srednia_max,poczatek);

    printf("Srednia max (dlugosc ciagu: %d): %.2lf\n",srednia_max.dlugosc_ciagu,srednia_max.wartosc);
    printf("Srednia min (dlugosc ciagu: %d): %.2lf\n",srednia_min.dlugosc_ciagu,srednia_min.wartosc);

    return 0;
}
