#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pudelko
{
    double x,y,z;
    char *nazwa;
    struct pudelko *wsk;
};

struct para
{
    char znak;
    struct para *wsk;
    struct pudelko *wsk_pudelko1;
    struct pudelko *wsk_pudelko2;
};

char *wczytaj_nazwe()
{
    char bufor[256];
    printf("Podaj nazwe: ");
    scanf("%s",bufor);
    char *nazwa=malloc(sizeof(char)*(strlen(bufor)+1));
    strcpy(nazwa,bufor);
    return nazwa;
}

void dodaj_pudelko(struct pudelko **poczatek)
{
    struct pudelko *nowe_pudelko=malloc(sizeof(struct pudelko));
    nowe_pudelko->nazwa=wczytaj_nazwe();
    printf("Podaj x: ");
    scanf("%lf",&nowe_pudelko->x);
    printf("Podaj y: ");
    scanf("%lf",&nowe_pudelko->y);
    printf("Podaj z: ");
    scanf("%lf",&nowe_pudelko->z);
    if (*poczatek==NULL)
    {
        nowe_pudelko->wsk=*poczatek;
        *poczatek=nowe_pudelko;
    }
    else
    {
        struct pudelko *iterator=*poczatek;
        while(iterator->wsk!=NULL)
        {
            iterator=iterator->wsk;
        }
        nowe_pudelko->wsk=iterator->wsk;
        iterator->wsk=nowe_pudelko;
    }
}

void wypisz(struct para *pierwsza_para)
{
    struct para *iterator_para=pierwsza_para;
    while (iterator_para!=NULL)
    {
        printf("[%s | %s] %c\n",iterator_para->wsk_pudelko1->nazwa,iterator_para->wsk_pudelko2->nazwa,iterator_para->znak);
        iterator_para=iterator_para->wsk;
    }
}

void porownaj(struct pudelko *poczatek,struct para **pierwsza_para)
{
    struct pudelko *iterator_i=poczatek;
    struct pudelko *iterator_j;
    struct para *nowa_para;
    int i,j,k,l,liczba_pudelek;
    liczba_pudelek=0;
    while (iterator_i!=NULL)
    {
        liczba_pudelek++;
        iterator_i=iterator_i->wsk;
    }
    iterator_i=poczatek;
    for(i=1;i<=liczba_pudelek;i++)
    {
        iterator_j=iterator_i->wsk;
        for(j=i+1;j<=liczba_pudelek;j++)
        {
            int max_i,sr_i,min_i;
            int max_j,sr_j,min_j;
            nowa_para=malloc(sizeof(struct para));
            nowa_para->wsk=*pierwsza_para;
            *pierwsza_para=nowa_para;
            nowa_para->wsk_pudelko1=iterator_i;
            nowa_para->wsk_pudelko2=iterator_j;

            double tab[3];

            tab[0]=iterator_i->x;
            tab[1]=iterator_i->y;
            tab[2]=iterator_i->z;

            for(k=0;k<3;k++)
            {
                for(l=k;l<3;l++)
                {
                    if (tab[k]<tab[l])
                    {
                        double tmp=tab[k];
                        tab[k]=tab[l];
                        tab[l]=tmp;
                    }
                }
            }

            min_i=tab[2];
            sr_i=tab[1];
            max_i=tab[0];

            tab[0]=iterator_j->x;
            tab[1]=iterator_j->y;
            tab[2]=iterator_j->z;

            for(k=0;k<3;k++)
            {
                for(l=k;l<3;l++)
                {
                    if (tab[k]<tab[l])
                    {
                        double tmp=tab[k];
                        tab[k]=tab[l];
                        tab[l]=tmp;
                    }
                }
            }

            min_j=tab[2];
            sr_j=tab[1];
            max_j=tab[0];

            if ((max_i>max_j)&&(sr_i>sr_j)&&(min_i>min_j)) nowa_para->znak='>';
            else if ((max_i<max_j)&&(sr_i<sr_j)&&(min_i<min_j)) nowa_para->znak='<';
            else nowa_para->znak='~';

            iterator_j=iterator_j->wsk;
        }
        iterator_i=iterator_i->wsk;
    }

}

int main()
{
    struct pudelko *poczatek=NULL;
    struct para *pierwsza_para=NULL;
    while (1)
    {
        int klawisz;
        int przerwij=0;
        printf("1 - dodaj\n2 - koniec\n");
        scanf("%d",&klawisz);
        getchar();
        switch (klawisz)
        {
            case 1:
            {
                system("clear");
                dodaj_pudelko(&poczatek);
                system("clear");
                break;
            }
            case 2:
            {
                przerwij=1;
                system("clear");
            }
        }
        if (przerwij) break;
    }
    porownaj(poczatek,&pierwsza_para);
    wypisz(pierwsza_para);
    return 0;
}
