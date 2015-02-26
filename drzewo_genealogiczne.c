#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osoba
{
    char *imie;
    char *nazwisko;
    int wciecie;
    int liczba_dzieci;
    struct osoba *rodzic;
    struct osoba **dziecko;
};

char *przyjmij_wyraz()
{
    char bufor[256];
    char *wyraz;
    scanf("%s",bufor);
    getchar();
    wyraz=malloc(sizeof(char)*(strlen(bufor)+1));
    strcpy(wyraz,bufor);
    return wyraz;
}

struct osoba *dodaj_osobe(struct osoba *glowa,int wciecie)
{
    struct osoba *nowy=malloc(sizeof(struct osoba));
    system("clear");
    if(glowa!=NULL) printf("Rodzic: %s %s\n",glowa->imie,glowa->nazwisko);
    printf("Podaj imie: ");
    nowy->imie=przyjmij_wyraz();
    printf("Podaj nazwisko: ");
    nowy->nazwisko=przyjmij_wyraz();
    printf("Podaj liczbe dzieci: ");
    scanf("%d",&nowy->liczba_dzieci);
    nowy->rodzic=glowa;
    nowy->dziecko=malloc(sizeof(struct osoba)*nowy->liczba_dzieci);
    nowy->wciecie=wciecie+1;
    int i;
    for(i=0; i<nowy->liczba_dzieci; i++)
    {
        nowy->dziecko[i]=dodaj_osobe(nowy,nowy->wciecie);
    }
    return nowy;
}

void wypisz(struct osoba *glowa,FILE *plik)
{
    int i;

    for(i=0;i<glowa->wciecie;i++)
    {
        if (i==0)
        {
            printf("|");
            fprintf(plik,"|");
        }
        else
        {
            printf("  |");
            fprintf(plik,"  |");
        }
    }

    if (glowa->wciecie>0)
    {
        printf("\n|");
        fprintf(plik,"\n|");
    }

    for(i=1;i<glowa->wciecie;i++)
    {
        printf("  |");
        fprintf(plik,"  |");
    }

    if (glowa->wciecie>1)
    {
        printf("--%s %s %d\n",glowa->imie,glowa->nazwisko,glowa->wciecie);
        fprintf(plik,"--%s %s %d\n",glowa->imie,glowa->nazwisko,glowa->wciecie);
    }
    else if (glowa->wciecie>0)
    {
        printf("--%s %s %d\n",glowa->imie,glowa->nazwisko,glowa->wciecie);
        fprintf(plik,"--%s %s %d\n",glowa->imie,glowa->nazwisko,glowa->wciecie);
    }
    else
    {
        printf("%s %s %d\n",glowa->imie,glowa->nazwisko,glowa->wciecie);
        fprintf(plik,"%s %s %d\n",glowa->imie,glowa->nazwisko,glowa->wciecie);
    }

    for(i=0; i<glowa->liczba_dzieci; i++)
    {
        wypisz(glowa->dziecko[i],plik);
    }
}

int main()
{
    struct osoba *glowa=NULL;
    FILE *plik=fopen("drzewo.txt","wt");
    if (!plik)
    {
        printf("Blad z plikiem.");
        return 1;
    }
    glowa=dodaj_osobe(glowa,-1);
    system("clear");
    wypisz(glowa,plik);
    fclose(plik);
    return 0;
}
