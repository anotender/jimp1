#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **init(const int liczba_slow)
{
    char **tablica=malloc(sizeof(char*)*liczba_slow);
    return tablica;
}

void wczytaj_wyrazy(char **tablica,const int liczba_slow)
{
    int i;
    for(i=0;i<liczba_slow;i++)
    {
        char bufor[256];
        printf("Podaj %d. wyraz: ",i+1);
        scanf("%s",bufor);
        tablica[i]=malloc((strlen(bufor)+1)*sizeof(char));
        strcpy(tablica[i],bufor);
    }
}

void sort(char **tablica,const int liczba_slow)
{
    int i,j,licznik;
    for(i=0;i<liczba_slow;i++)
    {
        for(j=i;j<liczba_slow;j++)
        {
            if(strcmp(tolower(tablica[i]),tolower(tablica[j]))>0)
            {
                char *tmp=tablica[i];
                tablica[i]=tablica[j];
                tablica[j]=tmp;
            }
        }
    }
}

void wypisz(char **tablica,const int liczba_slow)
{
    sort(tablica,liczba_slow);
    int i;
    for(i=0;i<liczba_slow;i++)
    {
        printf("%d. wyraz: %s\n",i+1,tablica[i]);
    }
}

int main()
{
    printf("Podaj liczbe slow: ");
    int liczba_slow;
    scanf("%d",&liczba_slow);
    char **tablica=init(liczba_slow);
    wczytaj_wyrazy(tablica,liczba_slow);
    wypisz(tablica,liczba_slow);

    return 0;
}
