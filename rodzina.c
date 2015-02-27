#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rodzic
{
    char *nazwisko;
    int rok_urodzenia;
    int liczba_dzieci;
    struct dziecko* dzieci;
};

struct dziecko
{
    char *nazwisko;
    int rok_urodzenia;
    struct dziecko *wsk;
};

struct dziecko *wczytaj_dzieci(const char *nazwisko,const int liczba_dzieci)
{
    int i;
    struct dziecko *poczatek=NULL;
    for(i=0;i<liczba_dzieci;i++)
    {
        struct dziecko *nowy=(struct dziecko*)malloc(sizeof(struct dziecko));
        nowy->wsk=poczatek;
        poczatek=nowy;
        nowy->nazwisko=nazwisko;
        printf("Podaj rok urodzenia %d. dziecka: ",i+1);
        scanf("%d",&nowy->rok_urodzenia);
    }
    system("clear");
    return poczatek;
}

char *wczytaj_nazwisko(void)
{
    char bufor[256];
    char *nazwisko;
    printf("Podaj nazwisko: ");
    scanf("%s",bufor);
    nazwisko=(char*)malloc((strlen(bufor)+1)*sizeof(char));
    strcpy(nazwisko,bufor);
    return nazwisko;
}

void wypisz(const struct rodzic *rodzice)
{
    int i;
    for(i=0;i<4;i++)
    {
        printf("Pan %s urodzil sie w %d roku i ma %d dzieci.\n",rodzice[i].nazwisko,rodzice[i].rok_urodzenia,rodzice[i].liczba_dzieci);
        int j=0;
        for(j=0;j<rodzice[i].liczba_dzieci;j++)
        {
            printf("Nazwisko %d. dziecka: %s\n",i+1,rodzice[i].dzieci->nazwisko);
            printf("Rok urodzenia %d. dziecka: %d\n",i+1,rodzice[i].dzieci->rok_urodzenia);
        }
        printf("\n");
    }
}

void czy_ma_dzieci(const struct rodzic *rodzice)
{
    int i,najwiecej,indeks;
    najwiecej=0;
    indeks=0;
    for(i=0;i<4;i++)
    {
        if(rodzice[i].liczba_dzieci==0)
        {
            printf("Pan %s nie ma dzieci.\n",rodzice[i].nazwisko);
            continue;
        }
        if(rodzice[i].liczba_dzieci>najwiecej)
        {
            indeks=i;
            najwiecej=rodzice[i].liczba_dzieci;
        }
    }
    printf("Najwiecej dzieci ma pan %s i ma ich %d.\n",rodzice[indeks].nazwisko,rodzice[indeks].liczba_dzieci);
}

int main()
{
    //inicjalizacja rodzicow
    struct rodzic rodzice[4];
    rodzice[0].nazwisko=wczytaj_nazwisko();
    rodzice[0].rok_urodzenia=1964;
    rodzice[0].liczba_dzieci=2;
    rodzice[0].dzieci=wczytaj_dzieci(rodzice[0].nazwisko,rodzice[0].liczba_dzieci);

    rodzice[1].nazwisko=wczytaj_nazwisko();
    rodzice[1].rok_urodzenia=1953;
    rodzice[1].liczba_dzieci=2;
    rodzice[1].dzieci=wczytaj_dzieci(rodzice[1].nazwisko,rodzice[1].liczba_dzieci);

    rodzice[2].nazwisko=wczytaj_nazwisko();
    rodzice[2].rok_urodzenia=1981;
    rodzice[2].liczba_dzieci=2;
    rodzice[2].dzieci=wczytaj_dzieci(rodzice[2].nazwisko,rodzice[2].liczba_dzieci);

    rodzice[3].nazwisko=wczytaj_nazwisko();
    rodzice[3].rok_urodzenia=1972;
    rodzice[3].liczba_dzieci=0;
    rodzice[3].dzieci=wczytaj_dzieci(rodzice[3].nazwisko,rodzice[3].liczba_dzieci);

    wypisz(rodzice);

    return 0;
}
