#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <Windows.h>

void dodaj_array(int **array, int kolor, int liczba_pixeli){
    int x=0;
    while(array[kolor][x]!=-2){
        ++x;
    }
    if(array[kolor][x]==-2){
        array[kolor][x]=liczba_pixeli;
    }
    else{
        printf("\nERROR\n");
    }
}

//kolejka dla y-ów
typedef struct kol1{
    int liczba;
    struct kol1 *nast;
} kolejka1;

void kol1_wypisz(kolejka1*kol1_glowa){
    printf("Kolejka1:\n");
    for(kolejka1*n=kol1_glowa; n!=NULL; n=n->nast){
        printf("Element %p ma liczbę %d\n", n, n->liczba);
    }
    printf("\n");
}


int kol1_odczyt(kolejka1*n){
    if(n==NULL){
        return -1;
    }
    else {
        while (n->nast != NULL) {
            n = n->nast;
        }
        return n->liczba;
    }
}

void kol1_dodaj(kolejka1**adres_n, int nowa_liczba){
    kolejka1*nowy = malloc(sizeof(kolejka1));
    nowy->liczba = nowa_liczba;
    nowy->nast = NULL;

    if(*adres_n==NULL){ //pusta lista
        *adres_n=nowy;
    }
    else{
        kolejka1*n = *adres_n;

        while(n->nast != NULL){
            n=n->nast;
        }
        n->nast = nowy;
    }
}

int kol1_usun(kolejka1 **glowa) {
    int wartosc;
    kolejka1*obecne, *poprzednie = NULL;

    if (*glowa == NULL) {
        return -1;
    }
    obecne = *glowa;
    while (obecne->nast != NULL) {
        poprzednie = obecne;
        obecne = obecne->nast;
    }
    wartosc = obecne->liczba;
    free(obecne);

    if (poprzednie) {
        poprzednie->nast = NULL;
    }
    else {
        *glowa = NULL;
    }

    return wartosc;
}

//kolejka dla x-ów
typedef struct kol2{
    int liczba;
    struct kol2 *nast;
} kolejka2;

void kol2_wypisz(kolejka2 *kol1_glowa){
    printf("Kolejka:\n");
    for(kolejka2 *n=kol1_glowa; n!=NULL; n=n->nast){
        printf("Element %p ma liczbę %d\n", n, n->liczba);
    }
    printf("\n");
}

int kol2_odczyt(kolejka2 *n){
    if(n==NULL){
        return -1;
    }
    else {
        while (n->nast != NULL) {
            n = n->nast;
        }
        return n->liczba;
    }
}

void kol2_dodaj(kolejka2 **adres_n, int nowa_liczba){
    kolejka2 *nowy = malloc(sizeof(kolejka2));
    kolejka2 *n;
    nowy->liczba = nowa_liczba;
    nowy->nast = NULL;

    if(*adres_n==NULL){
        *adres_n=nowy;
    }
    else{
        n = *adres_n;
        while(n->nast != NULL){
            n=n->nast;
        }
        n->nast = nowy;
    }
}

int kol2_usun(kolejka2 **glowa) {
    int wartosc;
    kolejka2 *obecne;
    kolejka2 *poprzednie = NULL;

    if (*glowa == NULL){
        return -1;
    }
    obecne = *glowa;
    while (obecne->nast != NULL) {
        poprzednie = obecne;
        obecne = obecne->nast;
    }
    wartosc = obecne->liczba;
    free(obecne);

    if (poprzednie) {
        poprzednie->nast = NULL;
    }
    else {
        *glowa = NULL;
    }
    return wartosc;
}


void odczyt(char bf[],int *a1,int *a2){
    int um = 0, i = 0;
    char pomoc[100];
    pomoc[0] = '\0';
    while (bf[i] != '\0') {
        if (um == 0) {
            if (bf[i] == ' ') {
                um = 1;
                ++i;
                *a1 = atoi(pomoc);
                memset(pomoc, 0, sizeof(pomoc));
            }
            else {
                strncat(pomoc, &bf[i], 1);
                ++i;
            }
        }
        else {
            strncat(pomoc, &bf[i], 1);
            ++i;
        }
    }
    *a2 = atoi(pomoc);
}

void wymiary(char*arg[], int *w_x, int *w_y, int *max, int *pnum){
    FILE *ptr;
    ptr = fopen(arg[1],"rb");

    int g=0;
    char str_p5[] = "P5";
    char str_p4[] = "P4";
    char wymiary[100];
    char znak;
    char bufor[100];
    bufor[0]='\0';

    do {
        do {
            znak= fgetc(ptr);
            if (znak!= 32 && znak!= 10) {
                strncat(bufor, &znak, 1);
            }
        }
        while (znak!= 32 && znak!= 10);
    }
    while (znak!= 10);
    if (!strcmp(bufor, str_p4)) {
        //printf("\n(P4)\n");
        *pnum=4;
    } else if (!strcmp(bufor, str_p5)) {
        //printf("\n(P5)\n");
        *pnum=5;
    } else {
        printf("\nNIEWŁAŚCIWY FORMAT\n");
        exit(0);
    }
    memset(bufor, 0, sizeof(bufor));

    do {
        do {
            znak= fgetc(ptr);
        }
        while (znak!= 32 && znak!= 10);
    }
    while (znak!= 10);
    ++g;

    do {
        znak= fgetc(ptr);
        if (znak!= 10) {
            strncat(bufor, &znak, 1);
        }
    } while (znak!= 10);

    strcpy(wymiary, bufor);
    memset(bufor, 0, sizeof(bufor));

    odczyt(wymiary,&*w_x,&*w_y);
    if(*pnum==5) {
        do {
            znak = fgetc(ptr);
            if (znak != 10) {
                strncat(bufor, &znak, 1);
            }
        } while (znak != 10);
        *max = atoi(bufor);
        memset(bufor, 0, sizeof(bufor));
    }
    else{
        *max=-1;
    }
    fclose(ptr);
}


void read_file(int wx, int wy, int tab[wy][wx], char*arg[], int *pnum){
    FILE *ptr;
    ptr = fopen(arg[1],"rb");

    if(!ptr){
        printf("\nPlik nie istnieje\n");
        exit(0);
    }

    int g=0;
    int h=4;
    if(*pnum==4){
        h=3;
    }
    char str_hash[] = "#";
    char wymiary[100]; //odczyt
    char max_wart[100]; //atoi?
    char znak;
    char bufor[100];
    bufor[0]='\0';

    while(g<h) {
        switch (g) {
            case 0:
                do {
                    do {
                        znak= fgetc(ptr);
                    } while (znak!= 32 && znak!= 10);
                } while (znak!= 10);
                ++g;
                break;

            case 1:
                znak= fgetc(ptr);
                strncat(bufor, &znak, 1);
                if (!strcmp(bufor, str_hash)) {
                   // printf("\nKOMENTARZ\n");
                }
                memset(bufor, 0, sizeof(bufor));
                do {
                    do {
                        znak= fgetc(ptr);
                    } while (znak!= 32 && znak!= 10);
                }
                while (znak!= 10);
                ++g;
                break;

            case 2:
                do {
                    znak= fgetc(ptr);
                    if (znak!= 10) {
                        strncat(bufor, &znak, 1);
                    }
                } while (znak!= 10);
                strcpy(wymiary, bufor);
                memset(bufor, 0, sizeof(bufor));
                ++g;
                break;

            case 3:
                do {
                    znak= fgetc(ptr);
                    if (znak!= 10) {
                        strncat(bufor, &znak, 1);
                    }
                }
                while (znak!= 10);
                strcpy(max_wart, bufor);
                memset(bufor, 0, sizeof(bufor));
                ++g;
                break;

            default:
                printf("\nerror\n");
                break;
        }
    }

    if(*pnum==4){
        int m;
        for(int i=0;i<wy;i++) {
            m=0;
            for (int j = 0; j < wx/8; j++) {
                unsigned char pixel = fgetc(ptr);
                for (int k = 7; k >= 0; k--) {
                    unsigned char c = pixel >> k & 1;
                    //printf("%d", c);
                    tab[i][m] = c;
                    ++m;
                }
                //printf(" ");
            }
            //printf("\n");
        }
    }
    else if(*pnum==5){
        int pixel;
        for(int i=0;i<wy;i++) {
            for(int j=0;j<wx;j++) {
                pixel = fgetc(ptr);
                tab[i][j] = pixel;
                //printf("[%d] ", tab[i][j]);
            }
            //printf("\n\n");
        }
    }
    else{
        printf("\nerror\n");
    }
    fclose(ptr);
}


void print_tab(int wx, int wy, int tab[wy][wx]){
    for(int u=0;u<wy;u++){
        for(int v=0;v<wx;v++){
            printf("%d ", tab[u][v]);
        }
        printf("\n");
    }
}

void print_check(int wx, int wy, int **check){
    printf("\n");
    for(int m=0;m<wy;m++){
        for(int n=0;n<wx;n++){
            printf("%d ",check[m][n]);
        }
        printf("\n");
    }
    printf("\n");
}

void przeszukiwanie(int wx, int wy, int tab[wy][wx], int **check, int y, int x, kolejka1 **kol1_glowa, kolejka2 **kol2_glowa, int *liczba_pixeli, int *kolor){
    int sw=0;
    int x1,y1;
    int k1=tab[y][x];
    int k2;
    int st=0;
    //printf("\nDane:(%d,%d):%d\n",y,x,tab[y][x]);
    check[y][x]=2;
    ++*liczba_pixeli;
    *kolor = k1;

    switch(sw){
        case 0:
            y1=y-1;
            x1=x;
            k2=tab[y1][x1];
            if(x1>=0 && x1<wx && y1>=0 && y1<wy){
                if(check[y1][x1]==0) {
                    if (k1 == k2) {
                        kol1_dodaj(kol1_glowa,y1);
                        kol2_dodaj(kol2_glowa,x1);
                        check[y1][x1] = 1;
                        ++st;
                    }
                }
            }
            ++sw;
        case 1:
            y1=y;
            x1=x+1;
            k2=tab[y1][x1];
            if(x1>=0 && x1<wx && y1>=0 && y1<wy){
                if(check[y1][x1]==0) {
                    if (k1 == k2) {
                        kol1_dodaj(kol1_glowa,y1);
                        kol2_dodaj(kol2_glowa,x1);
                        check[y1][x1] = 1;
                        ++st;
                    }
                }
            }
            ++sw;
        case 2:
            y1=y+1;
            x1=x;
            k2=tab[y1][x1];
            if(x1>=0 && x1<wx && y1>=0 && y1<wy){
                if(check[y1][x1]==0) {
                    if (k1 == k2) {
                        kol1_dodaj(kol1_glowa,y1);
                        kol2_dodaj(kol2_glowa,x1);
                        check[y1][x1] = 1;
                        ++st;
                    }
                }
            }
            ++sw;
        case 3:
            y1=y;
            x1=x-1;
            k2=tab[y1][x1];
            if((x1>=0 && x1<wx) && (y1>=0 && y1<wy)){
                if(check[y1][x1]==0) {
                    if (k1 == k2) {
                        kol1_dodaj(kol1_glowa,y1);
                        kol2_dodaj(kol2_glowa,x1);
                        check[y1][x1] = 1;
                        ++st;
                    }
                }
            }
            ++sw;
            if(st!=0){
                break;
            }
        case 4:
            break;
        default:
            printf("error\n");
            break;
    }
}

//Znajdowanie niesprawdzonego elemntu
char* poszukiwania(int wx, int wy, int **check){
    static char bufor[100];
    bufor[0] = '\0';
    for(int i=0;i<wy;i++){
        for(int j=0;j<wx;j++){
            if(check[i][j]==0){
                sprintf(bufor,"%d %d",i,j);
                return bufor;
            }
        }
    }
    return 0;
}

void klastrowanie(int wx, int wy,int tab[wy][wx],int **check, int y, int x, kolejka1 **kol1_glowa, kolejka2 **kol2_glowa, int *liczba_pixeli, int *kolor){
    int a1,a2;
    char bf[100];
    bf[0] = '\0';
    przeszukiwanie(wx,wy,tab,&*check,y,x, &*kol1_glowa, &*kol2_glowa, &*liczba_pixeli, &*kolor);

    while(kol1_odczyt(*kol1_glowa)!=-1 && kol2_odczyt(*kol2_glowa)!=-1) {
        a1=kol1_odczyt(*kol1_glowa);
        a2=kol2_odczyt(*kol2_glowa);

        if (check[a1][a2] == 1) {
            kol1_usun(&*kol1_glowa);
            kol2_usun(&*kol2_glowa);
            przeszukiwanie(wx, wy, tab, &*check, a1, a2, &*kol1_glowa, &*kol2_glowa, &*liczba_pixeli, &*kolor);
        }
        else if(check[a1][a2]==2){
            printf("\nerror\n");
        }
        else {
            printf("\nBLAD\n");
        }
    }
}

int main(int n, char*arg[]) {
    //SetConsoleOutputCP(CP_UTF8);
    kolejka1 *kol1_glowa = NULL;
    kolejka2 *kol2_glowa = NULL;
    int w_x,w_y,max;    //wymiary
    int liczba_pixeli=0;
    int kolor=0;
    //int suma=0;
    int pnum, j;

    wymiary(arg, &w_x,&w_y, &max, &pnum);

    int tab[w_y][w_x];
    int **check;    //tablica elementów sprawdzanych i sprawdzonych
    check = malloc(sizeof(*check) * w_y);
    if (check){
        for (int i = 0; i < w_y; i++ ) {
            check[i] = malloc(sizeof(*check[i]) * w_x);
        }
    }
    for(int u=0;u<w_y;u++){
        for(int v=0;v<w_x;v++){
            check[u][v]=0;
        }
    }

    int roz_y,roz_x;
    int rows,cols;
    if (max!=-1) {
        rows = max + 1;
        cols = max / 5;
    }
    else{
        rows=2;
        cols=w_x*w_y;
    }

    int **array;    //tablica liczby pixeli w klastrach
    array = malloc(sizeof(*array) * rows);
    if (array){
        for (int i = 0; i < rows; i++ ) {
            array[i] = malloc(sizeof(*array[i]) * cols);
        }
    }
    for (roz_y = 0; roz_y < rows; roz_y++){
        for (roz_x = 0; roz_x < cols; roz_x++){
            array[roz_y][roz_x]=-2;
        }
    }

    read_file(w_x, w_y, tab, arg, &pnum);
    int a1,a2;
    int liczba=0;

    while(poszukiwania(w_x,w_y,&*check)!=0){
        odczyt(poszukiwania(w_x,w_y,&*check),&a1,&a2);  //wyszukiwanie elementów
        klastrowanie(w_x,w_y,tab,&*check,a1,a2, &kol1_glowa, &kol2_glowa, &liczba_pixeli, &kolor);  //znajdowanie klastrów
        ++liczba;
        //printf("UKONCZONO: klaster %d (%d px)\n", liczba,liczba_pixeli);
        //suma=suma+liczba_pixeli;
        dodaj_array(&*array, kolor, liczba_pixeli);
        liczba_pixeli=0;
    }
    if(pnum==5) {
        kolor = max + 1;
    }
    else if(pnum==4){
        kolor=2;
    }
    //printf("SUMA: %d",suma);
    printf("Kolor : Rozmiary\n");
    for(int i=0;i<kolor;++i){
        j=0;
        if(array[i][0]!=-2){
            printf("%d :",i);
            while(array[i][j]!=-2){
                printf(" %d", array[i][j]);
                ++j;
            }
            printf("\n");
        }
    }
    return 0;
}