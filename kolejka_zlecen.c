#include <stdio.h>
#include <stdlib.h>

#define ILE_ZLECEN 10

struct zlecenie
{
    int numer;
    struct zlecenie *wsk;
};

int czy_pusta(const struct zlecenie *poczatek)
{
    if (poczatek==NULL) return 1;
    else return 0;
}

int czy_pelna(const struct zlecenie *poczatek)
{
    if (czy_pusta(poczatek)) return 0;
    else
    {
        struct zlecenie *iterator=poczatek;
        int numer;
        while (iterator!=NULL)
        {
            numer=iterator->numer;
            iterator=iterator->wsk;
        }
        if (numer<ILE_ZLECEN) return 0;
        else return 1;
    }
}

struct zlecenie *dodaj(struct zlecenie *poczatek)
{
    if (czy_pusta(poczatek))
    {
        struct zlecenie *nowy=(struct zlecenie*)malloc(sizeof(struct zlecenie));
        nowy->numer=1;
        nowy->wsk=poczatek;
        poczatek=nowy;
    }
    else
    {
        if (czy_pelna(poczatek))
        {
            system("clear");
            printf("Nie mozesz przyjac nowego zlecenia.");
            getchar();
            return poczatek;
        }
        else
        {
            struct zlecenie *iterator=poczatek;
            struct zlecenie *nowy=(struct zlecenie*)malloc(sizeof(struct zlecenie));
            while(iterator->wsk!=NULL)
            {
                iterator=iterator->wsk;
            }
            nowy->wsk=iterator->wsk;
            nowy->numer=iterator->numer+1;
            iterator->wsk=nowy;
        }
    }
    return poczatek;
}

struct zlecenie *usun(struct zlecenie *poczatek)
{
    if (czy_pusta(poczatek))
    {
        system("clear");
        printf("Kolejka jest pusta.");
        getchar();
        return poczatek;
    }
    else return poczatek->wsk;
}

void wypisz(const struct zlecenie *poczatek)
{
    if (czy_pusta(poczatek))
    {
        int i;
        for(i=0;i<ILE_ZLECEN;i++)
        {
            printf("_ ");
        }
    }
    else
    {
        int i,numer;
        struct zlecenie *iterator=poczatek;
        for(i=0;i<poczatek->numer-1;i++)
        {
            printf("_ ");
        }
        while(iterator!=NULL)
        {
            printf("%d ",iterator->numer);
            numer=iterator->numer;
            iterator=iterator->wsk;
        }
        for(i=numer;i<ILE_ZLECEN;i++)
        {
            printf("_ ");
        }
    }
    printf("\n");
}

int main()
{
    struct zlecenie *poczatek=NULL;
    while(1)
    {
        char klawisz;
        wypisz(poczatek);
        printf("I - przyjecie zlecenia\n");
        printf("O - obsluga zlecenia\n");
        printf("X - wyjscie\n");
        printf("Wybor: ");
        scanf("%c",&klawisz);
        getchar();
        switch (klawisz)
        {
            case 'i':
            {
                poczatek=dodaj(poczatek);
                break;
            }
            case 'o':
            {
                poczatek=usun(poczatek);

                break;
            }
            case 'f':
            {
                system("clear");
                if (czy_pelna(poczatek)) printf("Kolejka jest pelna.");
                else printf("Kolejka nie jest pelna.");
                getchar();
                break;
            }
            case 'e':
            {
                system("clear");
                if (czy_pusta(poczatek)) printf("Kolejka jest pusta.");
                else printf("Kolejka nie jest pusta.");
                getchar();
                break;
            }
            case 'x':
            {
                exit(0);
            }
        }
        system("clear");
    }
    return 0;
}
