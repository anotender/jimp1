#include <stdio.h>
#include <stdlib.h>

#define KOLUMNY 2
#define WIERSZE 3

struct element
{
    int wiersz;
    int kolumna;
    double wartosc;
    struct element *wsk;
};

void dodaj_element(const int i,const int j,const double wartosc,struct element **wsk_poczatek)
{
    if (wartosc!=0)
    {
        struct element *nowy=(struct element*)malloc(sizeof(struct element));
        nowy->kolumna=j+1;
        nowy->wiersz=i+1;
        nowy->wartosc=wartosc;
        if(*wsk_poczatek==NULL)
        {
            nowy->wsk=*wsk_poczatek;
            *wsk_poczatek=nowy;
        }
        else
        {
            struct element *iterator=*wsk_poczatek;
            while(iterator->wsk!=NULL)
            {
                iterator=iterator->wsk;
            }
            nowy->wsk=iterator->wsk;
            iterator->wsk=nowy;
        }
    }
}

void wypisz(struct element *poczatek)
{
    struct element *iterator=poczatek;
    while(iterator!=NULL)
    {
        printf("[wiersz: %d kolumna: %d] wartosc: %.2lf\n",iterator->wiersz,iterator->kolumna,iterator->wartosc);
        iterator=iterator->wsk;
    }
}

void min_max(const struct element *poczatek,double *min,double *max)
{
    struct element *iterator=poczatek;
    double tmp_min,tmp_max;
    tmp_min=poczatek->wartosc;
    tmp_max=poczatek->wartosc;
    while(iterator!=NULL)
    {
        if(iterator->wartosc>tmp_max)
        {
            tmp_max=iterator->wartosc;
        }
        else if(iterator->wartosc<tmp_min)
        {
            tmp_min=iterator->wartosc;
        }

        iterator=iterator->wsk;
    }
    *min=tmp_min;
    *max=tmp_max;
}

int main()
{
    double tablica[WIERSZE][KOLUMNY];
    int i,j;

    for(i=0;i<WIERSZE;i++)
    {
        for(j=0;j<KOLUMNY;j++)
        {
            printf("Podaj wartosc (%d. wiersz %d. kolumna): ",i+1,j+1);
            scanf("%lf",&tablica[i][j]);
            getchar();
        }
    }

    struct element *poczatek=NULL;

    for(i=0;i<WIERSZE;i++)
    {
        for(j=0;j<KOLUMNY;j++)
        {
            dodaj_element(i,j,tablica[i][j],&poczatek);
        }
    }

    wypisz(poczatek);

    double wartosc_najwieksza,wartosc_najmniejsza;

    min_max(poczatek,&wartosc_najmniejsza,&wartosc_najwieksza);

    printf("Wartosc najmniejsza: %.2lf\nWartosc najmniejsza: %.2lf\n",wartosc_najmniejsza,wartosc_najwieksza);

    return 0;
}
