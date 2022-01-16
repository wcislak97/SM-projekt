#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 512
#define wysokosc 340

#define tytul "SM2021 - Projekt 1 - Nazwisko Imie"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B);
void elipsa(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B);

void ladujBMP(char const* nazwa, int x, int y);
void zapiszBMP(int x, int y, int szer, int wys, char const* nazwa);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

//paleta kolor
//0:  [0, 0, 0]		    //0000
//1:  [255, 0, 0]       //0001
//2:  [0, 85, 0]        //0010
//3:  [255, 85, 0]      //0011
//4:  [0, 170, 0]       //0100
//5:  [255, 170, 0]     //0101
//6:  [0, 255, 0]       //0110
//7:  [255, 255, 0]     //0111
//8:  [0, 0, 255]       //1000
//9:  [255, 0, 255]     //1001
//10: [0, 85, 255]      //1010
//11: [255, 85, 255]	//1011
//12: [0, 170, 255]	    //1100
//13: [255, 170, 255]	//1101
//14: [0, 255, 255]	    //1110
//15: [255, 255, 255]	//1111

//paleta szara
//0: [0, 0, 0]		    //0000
//1: [17, 17, 17]	    //0001
//2: [34, 34, 34]     	//0010
//3: [51, 51, 51]     	//0011
//4: [68, 68, 68]     	//0100
//5: [85, 85, 85]    	//0101
//6: [102, 102, 102]  	//0110
//7: [119, 119, 119]  	//0111
//8: [136, 136, 136]  	//1000
//9: [153, 153, 153]  	//1001
//10: [170, 170, 170] 	//1010
//11: [187, 187, 187] 	//1011
//12: [204, 204, 204] 	//1100
//13: [221, 221, 221] 	//1101
//14: [238, 238, 238] 	//1110
//15: [255, 255, 255] 	//1111

SDL_Color paleta16[16];

SDL_Color paleta16szara[16];


void wygenerujPalete16Kolorow(){

int indeks=0;
Uint8 R,G,B;

for(int b=0;b<2;b++){
    for(int g=0;g<4;g++){
        for(int r=0;r<2;r++){
            R=r*255/1;
            G=g*255/3;
            B=b*255/1;

            paleta16[indeks]={R,G,B};
           // cout<<(int)indeks<<": ["<<(int)R<<", "<<(int)G<<", "<<(int)B<<"]"<<endl;
            indeks++;
        }
    }
}

}

void wygenerujPalete16Szara(){

int indeks=0;
Uint8 R,G,B;
Uint8 BW;

for(BW=0;BW<16;BW++){
            R=BW*17;
            G=BW*17;
            B=BW*17;

            paleta16szara[indeks]={R,G,B};
        //    cout<<(int)indeks<<": ["<<(int)R<<", "<<(int)G<<", "<<(int)B<<"]"<<endl;
            indeks++;
        }

}

void konwersjaKolorNarzucona4Bit(){

SDL_Color kolor;
Uint8 R,G,B;
Uint8 RGB;
for(int y=0;y<wysokosc / 2;y++){
    for (int x=0;x<szerokosc/2;x++){
        kolor=getPixel(x,y);
        R=kolor.r;
        G=kolor.g;
        B=kolor.b;

        R=(R>>7);
        G=(G>>6);
        B=(B>>7);

        RGB=(B<<3)+(R)+(G<<1);

        for(int i=0;i<16;i++)
        if((int)RGB==i){
            setPixel(x+szerokosc/2,y,paleta16[i].r,paleta16[i].g,paleta16[i].b);
        }
    }
}
}

SDL_Color konwersjaKolorNarzucona4Bit(SDL_Color kolor){

    Uint8 R,G,B;
    Uint8 RGB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    R=(R>>7);
    G=(G>>6);
    B=(B>>7);

    RGB=(B<<3)+(G<<1)+(R);

    return { paleta16[(int)RGB].r, paleta16[(int)RGB].g, paleta16[(int)RGB].b };
}

void konwersjaSzaryNarzucona4Bit(){
SDL_Color kolor;
Uint8 R,G,B;
Uint8 RGB;
Uint8 BW;
for(int y=0;y<wysokosc / 2;y++){
    for (int x=0;x<szerokosc/2;x++){
        kolor=getPixel(x,y);
        R=kolor.r;
        G=kolor.g;
        B=kolor.b;

        R=(R>>7);
        G=(G>>6);
        B=(B>>7);

        RGB=(B<<3)+(G<<1)+(R);

        setPixel(x+szerokosc/2,y,paleta16szara[(int)RGB].r, paleta16szara[(int)RGB].g, paleta16szara[(int)RGB].b);
    }
}
}

SDL_Color konwersjaSzaryNarzucona4Bit(SDL_Color kolor){

    Uint8 R,G,B;
    Uint8 RGB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    R=(R>>7);
    G=(G>>6);
    B=(B>>7);

    RGB=(B<<3)+(G<<1)+(R);

    return { paleta16szara[(int)RGB].r, paleta16szara[(int)RGB].g, paleta16szara[(int)RGB].b };
}


void ditheringRGB() {
    SDL_Color kolor;
    SDL_Color nowyKolor;

    float bledyR[(szerokosc/2)+2][(wysokosc) + 2];
    float bledyG[(szerokosc/2)+2][(wysokosc) + 2];
    float bledyB[(szerokosc/2)+2][(wysokosc) + 2];

    memset(bledyR, 0, sizeof(bledyR));
    memset(bledyG, 0, sizeof(bledyG));
    memset(bledyB, 0, sizeof(bledyB));

    int bladR = 0;
    int bladG = 0;
    int bladB = 0;

    int R, G, B;

    int indeks;
    int przesuniecie = 1;

    int test = 8;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);

            R = kolor.r + bledyR[x + przesuniecie][y];
            G = kolor.g + bledyG[x + przesuniecie][y];
            B = kolor.b + bledyB[x + przesuniecie][y];

            if (R > 255) R = 255;
            if (G > 255) G = 255;
            if (B > 255) B = 255;

            if (R < 0) R = 0;
            if (G < 0) G = 0;
            if (B < 0) B = 0;

            nowyKolor = konwersjaKolorNarzucona4Bit({R, G, B});

            int noweR = nowyKolor.r;
            int noweG = nowyKolor.g;
            int noweB = nowyKolor.b;

			setPixel(x + szerokosc / 2, y, noweR, noweG, noweB);

			bladR = R - noweR;
            bladG = G - noweG;
            bladB = B - noweB;

            bledyR[x + przesuniecie + 1][y    ] += (bladR * 7.0 / 16.0);
            bledyR[x + przesuniecie - 1][y + 1] += (bladR * 3.0 / 16.0);
            bledyR[x + przesuniecie    ][y + 1] += (bladR * 5.0 / 16.0);
            bledyR[x + przesuniecie + 1][y + 1] += (bladR * 1.0 / 16.0);

            bledyG[x + przesuniecie + 1][y    ] += (bladG * 7.0 / 16.0);
            bledyG[x + przesuniecie - 1][y + 1] += (bladG * 3.0 / 16.0);
            bledyG[x + przesuniecie    ][y + 1] += (bladG * 5.0 / 16.0);
            bledyG[x + przesuniecie + 1][y + 1] += (bladG * 1.0 / 16.0);

            bledyB[x + przesuniecie + 1][y    ] += (bladB * 7.0 / 16.0);
            bledyB[x + przesuniecie - 1][y + 1] += (bladB * 3.0 / 16.0);
            bledyB[x + przesuniecie    ][y + 1] += (bladB * 5.0 / 16.0);
            bledyB[x + przesuniecie + 1][y + 1] += (bladB * 1.0 / 16.0);

        }
    }

}

void ditheringSzary() {

    SDL_Color kolor;
    int BW = 0;
    int BWorg = 0;
    int blad = 0;

    SDL_Color nowyKolor;

    float bledy[(szerokosc / 2 + 2)][wysokosc / 2 + 2]{{}};

    int przesuniecie = 1;

    for (int y =0; y < wysokosc / 2 ; y++){
        for (int x =0; x < szerokosc  / 2 ; x++){
            kolor = getPixel(x, y);
            BWorg = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;

            SDL_Color test = konwersjaSzaryNarzucona4Bit({kolor.r, kolor.b, kolor.g});
            setPixel(x + szerokosc / 2, y, test.r, test.g, test.b);

            BW = BWorg + bledy[x+przesuniecie][y];

            if(BW>191){
                nowyKolor = konwersjaSzaryNarzucona4Bit({255, 255, 255});
                setPixel(x , y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);
                //setPixel(x , y + wysokosc / 2, 255,255,255);
                blad = BW - 255;
            } else if (BW > 127) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({191, 191, 191});
                setPixel(x , y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);
                blad = BW - 191;
            } else if (BW > 63) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({127, 127, 127});
                setPixel(x , y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);
                blad = BW - 127;
            } else {
                nowyKolor = konwersjaSzaryNarzucona4Bit({0, 0, 0, 0});
                setPixel(x , y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);
                //setPixel(x, y + wysokosc / 2, 0,0,0);
                blad = BW ;
            }
            bledy[x+przesuniecie + 1][y    ] += (blad * 7.0 / 16.0);
            bledy[x+przesuniecie - 1][y + 1] += (blad * 3.0 / 16.0);
            bledy[x+przesuniecie    ][y + 1] += (blad * 5.0 / 16.0);
            bledy[x+przesuniecie - 1][y + 1] += (blad * 1.0 / 16.0);
        }
    }
    SDL_UpdateWindowSurface(window);

}

void Funkcja1() {

    konwersjaSzaryNarzucona4Bit();
    SDL_UpdateWindowSurface(window);
}



void Funkcja2() {

    konwersjaKolorNarzucona4Bit();

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    ditheringSzary();

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    ditheringRGB();

    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {



    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {



    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    //...

    SDL_UpdateWindowSurface(window);
}

void kompresjaByteRun(int wejscie[], int dlugosc) {
    int i = 0;
    while (i < dlugosc) {
        if ( (i < dlugosc-1) && (wejscie[i] == wejscie[i + 1]) ) {
            int j = 0;
            while ( (i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i+j+1]) && (j < 127) ) {
                j++;
            }
            cout << -j << ", " << wejscie[i+j] << ", ";
            i += (j+1);
        } else {
            int j = 0;
            while ( (i+j < dlugosc-1) && (wejscie[i + j] != wejscie[i+j+1]) && (j < 127) ) {
                j++;
            }
            if ( (i+j == dlugosc-1) && (j < 127) ) {
                j++;
            }
            cout << (j - 1) << ", ";
            for(int k = 0; k < j; k++) {
                cout << wejscie[i + k] << ", ";
            }
            i += j;
        }
    }
}

void dekompresjaByteRun(int wejscie[], int dlugosc) {
    int i = 0;
    while(i < dlugosc) {
        if (wejscie[i] == -128) {
            i++;
        } else if (wejscie[i] < 0) {
            for (int j = 0; j <-(wejscie[i]-1); j++) {
                cout << wejscie[i+1] << ", ";
            }
            i += 2;
        } else {
            for (int j = 0; j < (wejscie[i] + 1); j++) {
                cout << wejscie[i + 1 + j] << ", ";
            }
            i += wejscie[i] +2;
        }
    }
}

void kompresjaRLE(int wejscie[], int dlugosc) {
    int i = 0;

    while (i < dlugosc) {
        if ( (i < dlugosc - 1) && (wejscie[i] == wejscie[i+1]) ) {
            int j = 0;
            while ( (i+j < dlugosc - 1) && (wejscie[i+j] == wejscie[i+j+1]) && (j < 254) ) {
                j++;
            }
            cout << j + 1 << ", " << wejscie[i + j] << ", ";
            i += (j+1);
        } else {
            int j = 0;
            while ( (i+j < dlugosc - 1) && (wejscie[i+j] != wejscie[i+j+1]) && (j < 254) ) {
                j++;
            }
            if( (i+j == dlugosc-1) && (j < 254) ) {
                j++;
            }
            cout << (int)0 << ", " << j << ", ";
            for (int k = 0; k < j; k++) {
                cout << wejscie[i+k] << ", ";
            }
            if(j % 2 != 0) {
                cout << (int)0 << ", ";
            }
            i += j;
        }
    }
}

void dekompresjaRLE(int wejscie[], int dlugosc) {
    int i = 0;
    int ile = 0;

    while(i < dlugosc) {
        if(wejscie[i] > 0) {
            for (int j = 0; j < wejscie[i]; j++) {
                cout << wejscie[i+1] << ", ";
            }
            i += 2;
        } else {
            ile = wejscie[i+1];
            for (int j=0; j < ile; j++) {
                cout << wejscie[i+1+j+1] << ", ";
            }
            i += ile + 2;
            if (ile % 2 != 0) {
                i++;
            }
        }
    }
}

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void zapiszBMP(int x, int y, int szer, int wys, char const* nazwa)
{
    SDL_Surface* bmp = SDL_CreateRGBSurface(SDL_SWSURFACE, szer, wys, 32, 0, 0, 0, 0);
    if (bmp==NULL) {
        printf("Unable to save bitmap: %s\n", SDL_GetError());
        }
    else
    {
        SDL_Rect fragment;
        fragment.x = x;
        fragment.y = y;
        fragment.w = szer;
        fragment.h = wys;
        SDL_BlitSurface(screen, &fragment, bmp, 0);
        SDL_LockSurface(bmp);

        SDL_SaveBMP(bmp, nazwa);
        SDL_UnlockSurface(bmp);
    }
}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    return 0;
    }
    SDL_UpdateWindowSurface(window);

    wygenerujPalete16Kolorow();
    wygenerujPalete16Szara();
    cout<<"Wcisnij przycisk 'a' aby wczytac obraz z pliku"<<endl;
    cout<<"Wcisnij przycisk '1' aby przekonwerowac obraz na obraz 4-bitowy z szara paleta narzucona bez ditheringu."<<endl;
    cout<<"Wcisnij przycisk '2' aby przekonwerowac obraz na obraz 4-bitowy z kolorowa paleta narzucona bez ditheringu."<<endl;
    cout<<"Wcisnij przycisk '3' aby przekonwerowac obraz na obraz 4-bitowy z szara paleta narzucona z ditheringiem."<<endl;
    cout<<"Wcisnij przycisk '4' aby przekonwerowac obraz na obraz 4-bitowy z kolorow paleta narzucona z ditheringiem."<<endl;



    bool done = false;
    SDL_Event event;
    // główna pętla programu
    while (SDL_WaitEvent(&event)) {
        // sprawdzamy czy pojawiło się zdarzenie
        switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;

            // sprawdzamy czy został wciśnięty klawisz
            case SDL_KEYDOWN: {
                // wychodzimy, gdy wciśnięto ESC
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                if (event.key.keysym.sym == SDLK_1)
                    Funkcja1();
                if (event.key.keysym.sym == SDLK_2)
                    Funkcja2();
                if (event.key.keysym.sym == SDLK_3)
                    Funkcja3();
                if (event.key.keysym.sym == SDLK_4)
                    Funkcja4();
                if (event.key.keysym.sym == SDLK_5)
                    Funkcja5();
                if (event.key.keysym.sym == SDLK_6)
                    Funkcja6();
                if (event.key.keysym.sym == SDLK_7)
                    Funkcja7();
                if (event.key.keysym.sym == SDLK_8)
                    Funkcja8();
                if (event.key.keysym.sym == SDLK_9)
                    Funkcja9();
                if (event.key.keysym.sym == SDLK_a)
                    ladujBMP("obrazek1.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_s)
                    ladujBMP("obrazek2.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_d)
                    ladujBMP("obrazek3.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_f)
                    ladujBMP("obrazek4.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_g)
                    ladujBMP("obrazek5.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_h)
                    ladujBMP("obrazek6.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_j)
                    ladujBMP("obrazek7.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_k)
                    ladujBMP("obrazek8.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_b)
                    czyscEkran(0, 0, 10);
                else
                    break;
               }
        }
        if (done) break;
    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
    return 0;
}
