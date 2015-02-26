#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *losuj_wyraz(FILE *plik)
{
    int liczba_slow,numer,i;
    char *wyraz=malloc(sizeof(char*));

    liczba_slow=0;
    while (fscanf(plik,"%s",wyraz)!=EOF) liczba_slow++;

    numer=rand()%liczba_slow;

    rewind(plik);

    for(i=0;i<numer;i++)
        fscanf(plik,"%s",wyraz);

    return wyraz;
}

void losuj_slowa(FILE *plik,char *haslo,char **krzyzowka)
{
    int i;
    for(i=0;i<strlen(haslo);i++)
    {
        while(1)
        {
            krzyzowka[i]=losuj_wyraz(plik);
            if(krzyzowka[i][0]==haslo[i]) break;
        }
    }
}

void zapisz(char *haslo,char **krzyzowka)
{
    FILE *plik=fopen("krzyzowka.txt","wt");
    int i;
    for(i=0;i<strlen(haslo);i++)
    {
        int j;
        fprintf(plik,"   ");
        if (i==0)
        {
            for (j=0;j<2*strlen(krzyzowka[i]);j++) fprintf(plik,"-");
        }
        else
        {
            if (strlen(krzyzowka[i])>strlen(krzyzowka[i-1]))
            {
                for (j=0;j<2*strlen(krzyzowka[i]);j++) fprintf(plik,"-");
            }
            else for (j=0;j<2*strlen(krzyzowka[i-1]);j++) fprintf(plik,"-");
        }
        fprintf(plik,"\n");
        fprintf(plik,"%-3d",i+1);
        for(j=0;j<strlen(krzyzowka[i]);j++) fprintf(plik,"%c|",krzyzowka[i][j]);
        fprintf(plik,"\n");
    }
    fprintf(plik,"   ");
    for (i=0;i<2*strlen(krzyzowka[strlen(haslo)-1]);i++) fprintf(plik,"-");
    fclose(plik);
}

int main()
{
    srand(time(NULL));
    FILE *plik=fopen("plik.txt","rt");
    char **krzyzowka;
    char *haslo;
    if(plik==NULL)
    {
        printf("Blad");
        return 1;
    }

    haslo=losuj_wyraz(plik);
    printf("haslo: %s\n",haslo);

    krzyzowka=malloc(sizeof(char*)*strlen(haslo));

    losuj_slowa(plik,haslo,krzyzowka);

    zapisz(haslo,krzyzowka);

    system("gedit krzyzowka.txt");

    return 0;
}
