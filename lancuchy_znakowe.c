#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *init(const int liczba_slow)
{
    char *tablica=(char*)malloc(sizeof(char*)*liczba_slow);
    return tablica;
}

char *wczytaj_slowo()
{
    char bufor[256];
    scanf("%s",bufor);
    getchar();
    char *slowo=(char*)malloc((strlen(bufor)+1)*sizeof(char));
    strcpy(slowo,bufor);
    return slowo;
}

void wczytaj(char **tablica,const int liczba_slow)
{
    int i;
    for(i=0;i<liczba_slow;i++)
    {
        printf("Podaj %d. wyraz: ",i+1);
        tablica[i]=wczytaj_slowo();
    }
}

/*void sortowanie(char **tablica,const int liczba_slow)
{
    int i,j;
    for(i=0;i<liczba_slow;i++)
    {
        for(j=i;j<liczba_slow;j++)
        {
            if(strcmp(tablica[i],tablica[j])>0)
            {
                char *tmp=tablica[i];
                tablica[i]=tablica[j];
                tablica[j]=tmp;
            }
        }
    }
}*/

void wypisz(char **tablica,const int liczba_slow)
{
    //sortowanie(tablica,liczba_slow);
    int i;
    for(i=0;i<liczba_slow;i++)
    {
        printf("%d. wyraz: %s\n",i+1,tablica[i]);
    }
}

int main()
{
    int liczba_slow;
    printf("Podaj liczbe slow: ");
    scanf("%d",&liczba_slow);
    char *tablica=init(liczba_slow);
    wczytaj(&tablica,liczba_slow);
    wypisz(&tablica,liczba_slow);
    free(tablica);
    return 0;
}
