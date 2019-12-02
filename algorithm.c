//atte tornberg 2019
//tietorakenteet ja algoritmit harjoitustyö c-toteutus

//käytetyt kirjastot

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//struct-rakenne, jossa määritellään solmu

struct solmu {
    char *sana;
    struct solmu *vasen;
    struct solmu *oikea;
};

//funktiot

typedef int (*Vertaa)(const char *, const char *);
void lisaa(char* avain, struct solmu** lehti, Vertaa cmp);
int Vrt_String(const char *a, const char *b);
int haku(char* avain, struct solmu* lehti, Vertaa cmp);

//main, jossa tapahtuu käyttäjältä inputin kysely, puuhun tallennus etc.

int main(int argc, char * argv[]) {
	FILE *tiedosto1, *tiedosto2;
	struct solmu *juuri = NULL;
	char nimi[100];
	char sana[100];
	char a = 1;
	int sanat = 0;

	printf("\nHei Maailma! Tama on yksinkertainen tiedostojen sanojen vertailuohjelma.");
	printf("\nOle hyva ja syota kahden tekstitiedoston nimet, jotka sijaitsevat samassa kansiossa, kuin itse ohjelma.\n");

	do {
	printf("\nSyota ensimmaisen tiedoston nimi (mihin verrataan): ");
	scanf("%s",&nimi);
	tiedosto1=fopen(nimi,"r");

        if(tiedosto1==NULL) {
			printf("\nTiedostoa '%s\' ei loydy!",nimi);
        }else {
            do {
                printf("\nSyota toisen tiedoston nimi (jota verrataan): ");
                scanf("%s",&nimi);
                tiedosto2=fopen(nimi,"r");

            if(tiedosto2==NULL) {
                printf("\nTiedostoa '%s\' ei loydy!",nimi);
            }
            } while(tiedosto2==NULL);
        }
      } while(tiedosto1==NULL);

    while((a = fgetc(tiedosto1)) != EOF) {
        if(a == ' ')
            sanat++;
    }

    rewind(tiedosto1);

    while (!feof(tiedosto1)) { //menee lapi 1. tiedoston sanojen ja laittaa ne puuhun

        fscanf(tiedosto1, "%s", sana);

        strlwr(sana);

        char tempsana[100];
        int i = 0;
        int c = 0;

        for (i = 0; i < strlen(sana); i++) {
            if ((isalpha(sana[i])) || (sana[i] == '\'' || sana[i] == 39)) {
                tempsana[c] = sana[i];
                c++;
            }
        }
        tempsana[c] = '\0';
        lisaa(tempsana, &juuri, (Vertaa)Vrt_String);
    }

    int fclose(FILE *tiedosto1);

    char loydetytSanat[51][24];
    int laskin = 0;

    while (!feof(tiedosto2)) { //menee lapi 2. tiedoston sanojen ja etsii ne puusta, jos ei loydy lisaa loydettyihin sanoihin

        fscanf(tiedosto2, "%s", sana);

        strlwr(sana);

        char tempsana[100];
        int i = 0;
        int c = 0;

        for (i = 0; i < strlen(sana); i++) {
            if ((isalpha(sana[i])) || (sana[i] == '\'' || sana[i] == 39)) {
                tempsana[c] = sana[i];
                c++;
            }
        }
        tempsana[c] = '\0';

        if(haku(tempsana, juuri, (Vertaa)Vrt_String) == 1){
            lisaa(tempsana, &juuri, (Vertaa)Vrt_String);
            strcpy(loydetytSanat[laskin],tempsana);
            laskin++;
        }
        if(laskin==51){
            break;
        }
    }

    int fclose(FILE *tiedosto2);

    //printataan löydetyt sanat

    printf("\nLoydetyt sanat:\n");
    for(int i = 0; i< laskin-1; i++){
        printf("\n%s ", loydetytSanat[i]);
    }
}

//funktio puuhun lisäämiseen

void lisaa(char* avain, struct solmu** lehti, Vertaa cmp) {
    int res;
    if( *lehti == NULL ) {
        *lehti = (struct solmu*) malloc( sizeof( struct solmu ) );
        (*lehti)->sana = malloc( strlen (avain) +1 );
        strcpy ((*lehti)->sana, avain);
        (*lehti)->vasen = NULL;
        (*lehti)->oikea = NULL;

    } else {
        res = cmp (avain, (*lehti)->sana);
        if( res < 0)
            lisaa( avain, &(*lehti)->vasen, cmp);
        else if( res > 0)
            lisaa( avain, &(*lehti)->oikea, cmp);
    }
}

//funktio puusta hakemiseen

int haku(char* avain, struct solmu* lehti, Vertaa cmp) {
    int res;
    if( lehti != NULL ) {
        res = cmp(avain, lehti->sana);
        if( res < 0)
            haku( avain, lehti->vasen, cmp);
        else if( res > 0)
            haku( avain, lehti->oikea, cmp);
        else{
            return 0;
    }}
    else{
        return 1;
    }

}

//funktio stringien vertailuun

int Vrt_String(const char *a, const char *b) {
    return (strcmp (a, b));
}
