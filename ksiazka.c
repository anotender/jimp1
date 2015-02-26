#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum napis{autor,tytul};

struct ksiazka
{
	char *autor;
	char *tytul;
	int numer;
	float cena;
	struct ksiazka *wsk;
};
char *wczytaj(enum napis wybor)
{
	switch (wybor)
	{
		case autor:
		{
			char bufor[100];
			char *p_tab;
			printf("Podaj imie i nazwisko autora: ");
			gets(bufor);
			p_tab=malloc((strlen(bufor)+1)*sizeof(char));
			strcpy(p_tab,bufor);
			return p_tab;
		}
		case tytul:
		{
			char bufor[100];
			char *p_tab;
			printf("Podaj tytul: ");
			gets(bufor);
			p_tab=malloc((strlen(bufor)+1)*sizeof(char));
			strcpy(p_tab,bufor);
			return p_tab;
		}
	}
}
void wypisz(struct ksiazka *poczatek,int licznik)
{
	int i;
	struct ksiazka *iterator=poczatek;
	for(i=0;i<licznik;i++)
    {
        printf("%s, %s, cena: %.2f zl, nr katalogowy: %d\n",iterator->autor,iterator->tytul,iterator->cena,iterator->numer);
        iterator=iterator->wsk;
    }
}
struct ksiazka *dodaj(struct ksiazka *poczatek)
{
    struct ksiazka *nowy;
    nowy=malloc(sizeof(struct ksiazka));
    nowy->wsk=poczatek;
    nowy->autor=wczytaj(autor);
    nowy->tytul=wczytaj(tytul);
    printf("Podaj numer katalogowy: ");
    scanf("%d",&nowy->numer);
    printf("Podaj cene: ");
    scanf("%f",&nowy->cena);
    return nowy;
}
int main()
{
	int licznik=0;
	struct ksiazka *poczatek,*koniec;
	poczatek=NULL;
	koniec=NULL;

	while(1)
    {
        int wybor;
        printf("1. Dodaj ksiazke\n2. Pokaz ksiazki\n3. Koniec\nWybor: ");
        scanf("%d",&wybor);getchar();
        system("clear");
        switch (wybor)
        {
            case 1:
                {
                    poczatek=dodaj(poczatek);
                    licznik++;
                    break;
                }
            case 2:
                {
                    wypisz(poczatek,licznik);
                    getchar();
                    break;
                }
            case 3:
                {
                    return 0;
                }
        }
        system("clear");
    }

	return 0;
}
