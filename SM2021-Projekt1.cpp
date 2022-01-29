#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>


using namespace std;

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;


#define szerokosc 512
#define wysokosc 340

#define tytul "SM2021 - Projekt 1 - Nazwisko Imie"

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);

SDL_Color getPixel(int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);

void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B);

void elipsa(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B);

void ladujBMP(char const *nazwa, int x, int y);

void zapiszBMP(int x, int y, int szer, int wys, char const *nazwa);

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

SDL_Color paletaKolorDedykowana[16];


void wygenerujPalete16Kolorow() {

    int indeks = 0;
    Uint8 R, G, B;

    for (int b = 0; b < 2; b++) {
        for (int g = 0; g < 4; g++) {
            for (int r = 0; r < 2; r++) {
                R = r * 255 / 1;
                G = g * 255 / 3;
                B = b * 255 / 1;

                paleta16[indeks] = {R, G, B};
                // cout<<(int)indeks<<": ["<<(int)R<<", "<<(int)G<<", "<<(int)B<<"]"<<endl;
                indeks++;
            }
        }
    }

}


void wygenerujPalete16Szara() {

    int indeks = 0;
    Uint8 R, G, B;
    Uint8 BW;

    for (BW = 0; BW < 16; BW++) {
        R = BW * 17;
        G = BW * 17;
        B = BW * 17;

        paleta16szara[indeks] = {R, G, B};
        //    cout<<(int)indeks<<": ["<<(int)R<<", "<<(int)G<<", "<<(int)B<<"]"<<endl;
        indeks++;
    }

}


void konwersjaKolorNarzucona4Bit(int rgb_array[szerokosc / 2][wysokosc / 2]) {

    ofstream wyjscie("KonwersjaKolorNarzucona4BitBin.bin",ios::binary);

    char temp;

    SDL_Color kolor;
    Uint8 R, G, B;
    Uint8 RGB;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {

            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            R = (R >> 7);
            G = (G >> 6);
            B = (B >> 7);

            RGB = (B << 3) + (R) + (G << 1);

            for (int i = 0; i < 16; i++)
                if ((int) RGB == i) {
                    setPixel(x + szerokosc / 2, y, paleta16[i].r, paleta16[i].g, paleta16[i].b);

                }

                if(!(x%2)){
                    temp+=(char)RGB&0x0F;
                    wyjscie.write((char*)&temp,sizeof(char));
                    }
                    else{
                temp=(char)RGB<<4;
                }

                rgb_array[x][y] = (int)RGB;
        }
    }

    wyjscie.close();

}


SDL_Color konwersjaKolorNarzucona4Bit(SDL_Color kolor) {

    Uint8 R, G, B;
    Uint8 RGB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    R = (R >> 7);
    G = (G >> 6);
    B = (B >> 7);

    RGB = (B << 3) + (G << 1) + (R);

    return {paleta16[(int) RGB].r, paleta16[(int) RGB].g, paleta16[(int) RGB].b};
}


void konwersjaSzaryNarzucona4Bit(int rgb_array[szerokosc / 2][wysokosc / 2]) {

    ofstream wyjscie("KonwersjaSzaryNarzucona4BitBin.bin",ios::binary);

    char temp;

    SDL_Color kolor;
    Uint8 R, G, B;
    Uint8 RGB;
    Uint8 BW;
    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            BW = 0.299 *R+ 0.587 *G+ 0.114 *B;

            BW=(BW>>4);

            setPixel(x + szerokosc / 2, y, paleta16szara[(int)BW].r, paleta16szara[(int) BW].g,
                     paleta16szara[(int) BW].b);


                     if(!(x%2)){
                    temp+=(char)BW&0x0F;
                    wyjscie.write((char*)&temp,sizeof(char));
                    }
                    else{
                temp=(char)BW<<4;
            }

            rgb_array[x][y] = (int)BW;

        }
    }
    wyjscie.close();
}


SDL_Color konwersjaSzaryNarzucona4Bit(SDL_Color kolor) {

    Uint8 R, G, B;
    Uint8 RGB;
    Uint8 BW;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    BW = 0.299 *R+ 0.587 *G+ 0.114 *B;

    BW=(BW>>4);

    return {paleta16szara[(int) BW].r, paleta16szara[(int) BW].g, paleta16szara[(int) BW].b};
}


void ditheringRGB(int rgb_array[szerokosc / 2][wysokosc / 2]) {

ofstream wyjscie("KonwersjaDitheringKolorNarzucona4BitBin.bin",ios::binary);
    char temp;
    Uint8 r,g,b;
    Uint8 rgb;

    SDL_Color kolor;
    SDL_Color nowyKolor;

    float bledyR[(szerokosc / 2) + 2][(wysokosc) + 2];
    float bledyG[(szerokosc / 2) + 2][(wysokosc) + 2];
    float bledyB[(szerokosc / 2) + 2][(wysokosc) + 2];

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

            nowyKolor = konwersjaKolorNarzucona4Bit({static_cast<Uint8>(R), static_cast<Uint8>(G), static_cast<Uint8>(B)});

            int noweR = nowyKolor.r;
            int noweG = nowyKolor.g;
            int noweB = nowyKolor.b;

            setPixel(x + szerokosc / 2, y, noweR, noweG, noweB);

            r=noweR;
            g=noweG;
            b=noweB;
            r = (r >> 7);
            g = (g >> 6);
            b = (b >> 7);

            rgb = (b << 3) + (g << 1) + (r);

             if(!(x%2)){
                    temp+=(char)rgb&0x0F;
                    wyjscie.write((char*)&temp,sizeof(char));
                    }
                    else{
                temp=(char)rgb<<4;
                }

            rgb_array[x][y] = (int)rgb;

            bladR = R - noweR;
            bladG = G - noweG;
            bladB = B - noweB;

            bledyR[x + przesuniecie + 1][y] += (bladR * 7.0 / 16.0);
            bledyR[x + przesuniecie - 1][y + 1] += (bladR * 3.0 / 16.0);
            bledyR[x + przesuniecie][y + 1] += (bladR * 5.0 / 16.0);
            bledyR[x + przesuniecie + 1][y + 1] += (bladR * 1.0 / 16.0);

            bledyG[x + przesuniecie + 1][y] += (bladG * 7.0 / 16.0);
            bledyG[x + przesuniecie - 1][y + 1] += (bladG * 3.0 / 16.0);
            bledyG[x + przesuniecie][y + 1] += (bladG * 5.0 / 16.0);
            bledyG[x + przesuniecie + 1][y + 1] += (bladG * 1.0 / 16.0);

            bledyB[x + przesuniecie + 1][y] += (bladB * 7.0 / 16.0);
            bledyB[x + przesuniecie - 1][y + 1] += (bladB * 3.0 / 16.0);
            bledyB[x + przesuniecie][y + 1] += (bladB * 5.0 / 16.0);
            bledyB[x + przesuniecie + 1][y + 1] += (bladB * 1.0 / 16.0);

        }
    }
    wyjscie.close();
}

void ditheringSzary(int rgb_array[szerokosc / 2][wysokosc / 2]) {

    ofstream wyjscie("KonwersjaDitheringSzaryNarzucona4BitBin.bin",ios::binary);

    char temp;
    Uint8 r,g,b;
    Uint8 rgb;

    SDL_Color kolor;
    int BW = 0;
    int BWorg = 0;
    int blad = 0;

    SDL_Color nowyKolor;

    float bledy[(szerokosc / 2 + 2)][wysokosc / 2 + 2]{{}};

    int przesuniecie = 1;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            BWorg = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;

            SDL_Color test = konwersjaSzaryNarzucona4Bit({kolor.r, kolor.b, kolor.g});
            setPixel(x + szerokosc / 2, y, test.r, test.g, test.b);

            BW = BWorg + bledy[x + przesuniecie][y];

            if (BW > 238) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({255, 255, 255});
                blad = BW - 255;
            } else if (BW > 221) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({238, 238, 238});
                blad = BW - 238;
            } else if (BW > 204) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({221, 221, 221});
                blad = BW - 211;
            } else if (BW > 187) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({204, 204, 204});
                blad = BW - 204;
            } else if (BW > 170) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({187, 187, 187});
                blad = BW - 187;
            } else if (BW > 153) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({170, 170, 170});
                blad = BW - 170;
            } else if (BW > 136) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({153, 153, 153});
                blad = BW - 153;
            } else if (BW > 119) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({136, 136, 136});
                blad = BW - 136;
            } else if (BW > 102) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({119, 119, 119});
                blad = BW - 119;
            } else if (BW > 85) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({102, 102, 102});
                blad = BW - 102;
            } else if (BW > 68) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({85, 85, 85});
                blad = BW - 85;
            } else if (BW > 51) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({68, 68, 68});
                blad = BW - 68;
            } else if (BW > 34) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({51, 51, 51});
                blad = BW - 51;
            } else if (BW > 17) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({34, 34, 34});
                blad = BW - 34;
            } else if (BW > 0) {
                nowyKolor = konwersjaSzaryNarzucona4Bit({17, 17, 17});
                blad = BW - 17;
            } else {
                nowyKolor = konwersjaSzaryNarzucona4Bit({0, 0, 0});
                blad = BW;
            }
            setPixel(x, y + wysokosc / 2, nowyKolor.r, nowyKolor.g, nowyKolor.b);

            r=nowyKolor.r;
            g=nowyKolor.g;
            b=nowyKolor.b;
            r = (r >> 7);
            g = (g >> 6);
            b = (b >> 7);

            rgb = (b << 3) + (g << 1) + (r);

            if(!(x%2)){
                    temp+=(char)rgb&0x0F;
                    wyjscie.write((char*)&temp,sizeof(char));
                    }
                    else{
                temp=(char)rgb<<4;
                }

            rgb_array[x][y] = (int)rgb;

            bledy[x + przesuniecie + 1][y] += (blad * 7.0 / 16.0);
            bledy[x + przesuniecie - 1][y + 1] += (blad * 3.0 / 16.0);
            bledy[x + przesuniecie][y + 1] += (blad * 5.0 / 16.0);
            bledy[x + przesuniecie - 1][y + 1] += (blad * 1.0 / 16.0);
        }
    }
    SDL_UpdateWindowSurface(window);
wyjscie.close();
}


struct sort_by_r
{
    inline bool operator() (const SDL_Color& c1, const SDL_Color & c2)
    {
        return (c1.r < c2.r);
    }
};

struct sort_by_g
{
    inline bool operator() (const SDL_Color& c1, const SDL_Color & c2)
    {
        return (c1.g < c2.g);
    }
};

struct sort_by_b
{
    inline bool operator() (const SDL_Color& c1, const SDL_Color & c2)
    {
        return (c1.b < c2.b);
    }
};

struct ColorToBytes {
    SDL_Color color_org;
    SDL_Color color_new;

    ColorToBytes(SDL_Color c1, SDL_Color c2) : color_org(c1), color_new(c2) {}
};


void generujPaleteDopasowana() {

    int pixels_number = (wysokosc/2) * (szerokosc*2);

    int *r_colors = new int[pixels_number];
    int *g_colors = new int[pixels_number];
    int *b_colors = new int[pixels_number];

    int r_scope = 0, g_scope = 0, b_scope = 0;

    SDL_Color used_colors [pixels_number];
    int used_colors_number = 0;

    SDL_Color all_pixels_colors [pixels_number];
    int all_pixels_colors_number = 0;

    bool found;

    SDL_Color color;

    /**
     * Print all colors - debug function
     */
//    for (int y = 0; y < wysokosc / 2; y++) {
//        for (int x = 0; x < szerokosc / 2; x++) {
//            color = getPixel(x,y);
//            cout << (int) color.r << " " << (int) color.g << " " << (int) color.b << endl;
//        }
//    }


    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            color = getPixel(x,y);

            /**
             * Get scope r, g, b from all colors
             */

            found = false;
            for(int i=0; i < r_scope; i++) if(r_colors[i] == color.r) found = true;
            if (!found) {
                r_colors[r_scope] = color.r;
                r_scope++;
                //cout << "Added R "<< (int) color.r << endl;
            }

            found = false;
            for(int i=0; i < g_scope; i++) if(g_colors[i] == color.g) found = true;
            if (!found) {
                g_colors[g_scope] = color.g;
                g_scope++;
                //cout << "Added G "<< (int) color.g << endl;
            }

            found = false;
            for(int i=0; i < b_scope; i++) if(b_colors[i] == color.b) found = true;
            if (!found) {
                b_colors[b_scope] = color.b;
                b_scope++;
                //cout << "Added B "<< (int) color.b << endl;
            }

            /**
             * Get scope of all colors used in picture
             */
            found = false;
            for(int i=0; i < used_colors_number; i++) if(used_colors[i].r == color.r && used_colors[i].b == color.b && used_colors[i].g == color.g) found = true;
            if (!found) {
                used_colors[used_colors_number] = color;
                used_colors_number++;
               // cout << "Added "<< (int) color.r << " " << (int) color.g << " " << (int) color.b << endl;
            }

            all_pixels_colors[y * (szerokosc/2) + x] = color;
            all_pixels_colors_number++;

        }
    }

    char widest_scope;
    if (r_scope < g_scope) { // g win
        if (b_scope < g_scope) widest_scope = 'g';
        else widest_scope = 'b';
    }
    else { // r win
        if (b_scope < r_scope) widest_scope = 'r';
        else widest_scope = 'b';
    }


    if (widest_scope == 'r') {
        sort(used_colors, used_colors + used_colors_number, sort_by_r());
        sort(all_pixels_colors, all_pixels_colors + all_pixels_colors_number, sort_by_r());
    } else if (widest_scope == 'g') {
        sort(used_colors, used_colors + used_colors_number, sort_by_g());
        sort(all_pixels_colors, all_pixels_colors + all_pixels_colors_number, sort_by_g());
    } else {
        sort(used_colors, used_colors + used_colors_number, sort_by_b());
        sort(all_pixels_colors, all_pixels_colors + all_pixels_colors_number, sort_by_b());
    }


    for(int i=0; i < used_colors_number; i++) {
        color = used_colors[i];
      //  cout << "Sorted by " << widest_scope << ": " << (int) color.r << " " << (int) color.g << " " << (int) color.b << endl;
        paletaKolorDedykowana[i]={color.r,color.g,color.b};
    }
   // std::cout << "Scopes of certain colors: r" << r_scope << " g" << g_scope << " b" << b_scope << std::endl;


    vector <ColorToBytes> vec;
    int a = 16;
    int b;
    int d;
    SDL_Color c;

    for (int i=0; i<used_colors_number; i++) {
      //  cout << "USED COLOR: " << (int) used_colors[i].r << " " << (int) used_colors[i].g << " " << (int) used_colors[i].b << endl;

        if (widest_scope == 'r') {
            b = used_colors[i].r / a;
        } else if (widest_scope == 'g') {
            b = used_colors[i].g / a;
        } else {
            b = used_colors[i].b / a;
        }
        d = b * (float) 16.0/256.0 * used_colors_number;

    //    cout << " - b: " << b << endl;
     //   cout << " - all_pixels_index: " << d << endl;

        c = used_colors[d];


        vec.emplace_back(used_colors[i], c);
       // cout << " - " << (int) used_colors[i].r << " " << (int) used_colors[i].g << " " << (int) used_colors[i].b << " -> " << (int) c.r << " " << (int) c.g << " " << (int) c.b << endl;
    }





    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {

            for (auto color_struc : vec) {
                color = getPixel(x,y);

                if (color.r == color_struc.color_org.r && color.g == color_struc.color_org.g && color.b == color_struc.color_org.b) {
                    setPixel(szerokosc /2 + x, y, color_struc.color_new.r, color_struc.color_new.g, color_struc.color_new.b);
                }
            }
        }
    }
}


void kompresjaByteRun(int wejscie[], int dlugosc, vector<int>& wyjscie) {
    int i = 0;
    while (i < dlugosc) {
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])) {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + j + 1]) && (j < 127)) {
                j++;
            }
            //cout << -j << ", " << wejscie[i + j] << ", ";
            wyjscie.push_back(-j);
            wyjscie.push_back(wejscie[i + j]);
            i += (j + 1);
        } else {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] != wejscie[i + j + 1]) && (j < 127)) {
                j++;
            }
            if ((i + j == dlugosc - 1) && (j < 127)) {
                j++;
            }
            //cout << (j - 1) << ", ";
            wyjscie.push_back(j - 1);
            for (int k = 0; k < j; k++) {
                //cout << wejscie[i + k] << ", ";
                wyjscie.push_back(wejscie[i + k]);
            }
            i += j;
        }
        //cout << wyjscie[i] << endl;
    }
}

void dekompresjaByteRun(int wejscie[], int dlugosc) {
    int i = 0;
    while (i < dlugosc) {
        if (wejscie[i] == -128) {
            i++;
        } else if (wejscie[i] < 0) {
            for (int j = 0; j < -(wejscie[i] - 1); j++) {
                cout << wejscie[i + 1] << ", ";
            }
            i += 2;
        } else {
            for (int j = 0; j < (wejscie[i] + 1); j++) {
                cout << wejscie[i + 1 + j] << ", ";
            }
            i += wejscie[i] + 2;
        }
    }
}

void kompresjaRLE(int wejscie[], int dlugosc, vector<int>& wyjscie) {
    int i = 0;

    while (i < dlugosc) {
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])) {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + j + 1]) && (j < 254)) {
                j++;
            }
            //cout << j + 1 << ", " << wejscie[i + j] << ", ";
            wyjscie.push_back(wejscie[j + 1]);
            wyjscie.push_back(wejscie[i + j]);
            i += (j + 1);
        } else {
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] != wejscie[i + j + 1]) && (j < 254)) {
                j++;
            }
            if ((i + j == dlugosc - 1) && (j < 254)) {
                j++;
            }
            //cout << (int) 0 << ", " << j << ", ";
            wyjscie.push_back(0);
            wyjscie.push_back(j);
            for (int k = 0; k < j; k++) {
                //cout << wejscie[i + k] << ", ";
                wyjscie.push_back(wejscie[i + k]);
            }
            if (j % 2 != 0) {
                //cout << (int) 0 << ", ";
                wyjscie.push_back(0);
            }
            i += j;
        }
    }
}

void dekompresjaRLE(int wejscie[], int dlugosc) {
    int i = 0;
    int ile = 0;

    while (i < dlugosc) {
        if (wejscie[i] > 0) {
            for (int j = 0; j < wejscie[i]; j++) {
                cout << wejscie[i + 1] << ", ";
            }
            i += 2;
        } else {
            ile = wejscie[i + 1];
            for (int j = 0; j < ile; j++) {
                cout << wejscie[i + 1 + j + 1] << ", ";
            }
            i += ile + 2;
            if (ile % 2 != 0) {
                i++;
            }
        }
    }
}

int rozmiar(vector<vector<int>>& dane) {
    int sizeV = dane.size();
    for(int i = 0; i < dane.size(); i++) {
        sizeV += dane[i].size();
    }
    cout << sizeV << endl;
}

void zapisz(string nazwa, vector<vector<int>>& dane) {
    ofstream wyjscie(nazwa + ".bin",ios::binary);
    char temp;
    for (int i = 0; i < dane.size(); i++) {
        for (int j = 0; j < dane[i].size(); j++) {
            if(!(j%2)){
                    temp+=(char)dane[i][j]&0x0F;
                    wyjscie.write((char*)&temp,sizeof(char));
                    }
                    else{
                temp=(char)dane[i][j]<<4;
                }
        }
    }
    wyjscie.close();
}

void Funkcja1() {

    auto rgb_array = new int[szerokosc / 2][wysokosc / 2];
    konwersjaSzaryNarzucona4Bit(rgb_array);
    vector<vector<int>> byte_run;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaByteRun(rgb_array[i], wysokosc / 2, row);
        byte_run.push_back(row);
    }
    vector<vector<int>> rle;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaRLE(rgb_array[i], wysokosc / 2, row);
        rle.push_back(row);
    }
    int rozmiar_byte_run = rozmiar(byte_run);
    int rozmiar_rle= rozmiar(rle);

    if (rozmiar_byte_run > rozmiar_rle) {
        zapisz("KonwersjaSzaryNarzucona4Bit_rle", rle);
    } else {
        zapisz("KonwersjaSzaryNarzucona4Bit_byterun", byte_run);
    }

    zapiszBMP(szerokosc,0,szerokosc,wysokosc,"KonwersjaSzaryNarzucona4Bit.bmp");

    SDL_UpdateWindowSurface(window);
}


void Funkcja2() {

    auto rgb_array = new int[szerokosc / 2][wysokosc / 2];
    konwersjaKolorNarzucona4Bit(rgb_array);
    vector<vector<int>> byte_run;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaByteRun(rgb_array[i], wysokosc / 2, row);
        byte_run.push_back(row);
    }
    vector<vector<int>> rle;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaRLE(rgb_array[i], wysokosc / 2, row);
        rle.push_back(row);
    }
    int rozmiar_byte_run = rozmiar(byte_run);
    int rozmiar_rle= rozmiar(rle);

    if (rozmiar_byte_run > rozmiar_rle) {
        zapisz("KonwersjaKolorNarzucona4Bit_rle", rle);
    } else {
        zapisz("KonwersjaKolorNarzucona4Bit_byterun", byte_run);
    }

    zapiszBMP(szerokosc,0,szerokosc,wysokosc,"KonwersjaKolorNarzucona4Bit.bmp");

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    auto rgb_array = new int[szerokosc / 2][wysokosc / 2];
    ditheringSzary(rgb_array);
    vector<vector<int>> byte_run;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaByteRun(rgb_array[i], wysokosc / 2, row);
        byte_run.push_back(row);
    }
    vector<vector<int>> rle;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaRLE(rgb_array[i], wysokosc / 2, row);
        rle.push_back(row);
    }
    int rozmiar_byte_run = rozmiar(byte_run);
    int rozmiar_rle= rozmiar(rle);

    if (rozmiar_byte_run > rozmiar_rle) {
        zapisz("KonwersjaDitheringSzaryNarzucona4Bbit_rle", rle);
    } else {
        zapisz("KonwersjaDitheringSzaryNarzucona4Bbit_byterun", byte_run);
    }

    zapiszBMP(0,wysokosc,szerokosc,wysokosc,"KonwersjaDitheringSzaryNarzucona4Bbit.bmp");

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    auto rgb_array = new int[szerokosc / 2][wysokosc / 2];
    ditheringRGB(rgb_array);
    vector<vector<int>> byte_run;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaByteRun(rgb_array[i], wysokosc / 2, row);
        byte_run.push_back(row);
    }
    vector<vector<int>> rle;
    for (int i = 0; i < szerokosc / 2; i++) {
        vector<int> row;
        kompresjaRLE(rgb_array[i], wysokosc / 2, row);
        rle.push_back(row);
    }
    int rozmiar_byte_run = rozmiar(byte_run);
    int rozmiar_rle= rozmiar(rle);


    if (rozmiar_byte_run > rozmiar_rle) {
        zapisz("KonwersjaDitheringKolorNarzucona4Bbit_rle", rle);
    } else {
        zapisz("KonwersjaDitheringKolorNarzucona4Bbit_byterun", byte_run);
    }
    zapiszBMP(szerokosc,0,szerokosc,wysokosc,"KonwersjaDitheringKolorNarzucona4Bbit.bmp");

    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {


    generujPaleteDopasowana();
    zapiszBMP(szerokosc,0,szerokosc,wysokosc,"KonwersjaKolorDopasowana4Bbit.bmp");


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

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B) {
    if ((x >= 0) && (x < szerokosc) && (y >= 0) && (y < wysokosc)) {
        /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

        /* Pobieramy informację ile bajtów zajmuje jeden piksel */
        int bpp = screen->format->BytesPerPixel;

        /* Obliczamy adres piksela */
        Uint8 *p1 = (Uint8 *) screen->pixels + (y * 2) * screen->pitch + (x * 2) * bpp;
        Uint8 *p2 = (Uint8 *) screen->pixels + (y * 2 + 1) * screen->pitch + (x * 2) * bpp;
        Uint8 *p3 = (Uint8 *) screen->pixels + (y * 2) * screen->pitch + (x * 2 + 1) * bpp;
        Uint8 *p4 = (Uint8 *) screen->pixels + (y * 2 + 1) * screen->pitch + (x * 2 + 1) * bpp;

        /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
        switch (bpp) {
            case 1: //8-bit
                *p1 = pixel;
                *p2 = pixel;
                *p3 = pixel;
                *p4 = pixel;
                break;

            case 2: //16-bit
                *(Uint16 *) p1 = pixel;
                *(Uint16 *) p2 = pixel;
                *(Uint16 *) p3 = pixel;
                *(Uint16 *) p4 = pixel;
                break;

            case 3: //24-bit
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
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
                *(Uint32 *) p1 = pixel;
                *(Uint32 *) p2 = pixel;
                *(Uint32 *) p3 = pixel;
                *(Uint32 *) p4 = pixel;
                break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B) {
    if ((x >= 0) && (x < szerokosc * 2) && (y >= 0) && (y < wysokosc * 2)) {
        /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

        /* Pobieramy informację ile bajtów zajmuje jeden piksel */
        int bpp = screen->format->BytesPerPixel;

        /* Obliczamy adres piksela */
        Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

        /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
        switch (bpp) {
            case 1: //8-bit
                *p = pixel;
                break;

            case 2: //16-bit
                *(Uint16 *) p = pixel;
                break;

            case 3: //24-bit
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
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
                *(Uint32 *) p = pixel;
                break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color;
    Uint32 col = 0;
    if ((x >= 0) && (x < szerokosc) && (y >= 0) && (y < wysokosc)) {
        //określamy pozycję
        char *pPosition = (char *) screen->pixels;

        //przesunięcie względem y
        pPosition += (screen->pitch * y * 2);

        //przesunięcie względem x
        pPosition += (screen->format->BytesPerPixel * x * 2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return (color);
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color;
    Uint32 col = 0;
    if ((x >= 0) && (x < szerokosc) && (y >= 0) && (y < wysokosc)) {
        //określamy pozycję
        char *pPosition = (char *) surface->pixels;

        //przesunięcie względem y
        pPosition += (surface->pitch * y);

        //przesunięcie względem x
        pPosition += (surface->format->BytesPerPixel * x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return (color);
}


void ladujBMP(char const *nazwa, int x, int y) {
    SDL_Surface *bmp = SDL_LoadBMP(nazwa);
    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    } else {
        SDL_Color kolor;
        for (int yy = 0; yy < bmp->h; yy++) {
            for (int xx = 0; xx < bmp->w; xx++) {
                kolor = getPixelSurface(xx, yy, bmp);
                setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
            }
        }
        SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}

void zapiszBMP(int x, int y, int szer, int wys, char const *nazwa) {

    SDL_Surface *bmp = SDL_CreateRGBSurface(SDL_SWSURFACE, szer, wys, 32, 0, 0, 0, 0);
    if (bmp == NULL) {
        printf("Unable to save bitmap: %s\n", SDL_GetError());
    } else {
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


void czyscEkran(Uint8 R, Uint8 G, Uint8 B) {
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}


int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc * 2, wysokosc * 2,
                              SDL_WINDOW_SHOWN);

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
    cout << "Wcisnij przycisk 'a' aby wczytac obraz z pliku" << endl;
    cout << "Wcisnij przycisk '1' aby przekonwerowac obraz na obraz 4-bitowy z szara paleta narzucona bez ditheringu."
         << endl;
    cout
            << "Wcisnij przycisk '2' aby przekonwerowac obraz na obraz 4-bitowy z kolorowa paleta narzucona bez ditheringu."
            << endl;
    cout << "Wcisnij przycisk '3' aby przekonwerowac obraz na obraz 4-bitowy z szara paleta narzucona z ditheringiem."
         << endl;
    cout << "Wcisnij przycisk '4' aby przekonwerowac obraz na obraz 4-bitowy z kolorow paleta narzucona z ditheringiem."
         << endl;
     cout << "Wcisnij przycisk '5' aby przekonwerowac obraz na obraz 4-bitowy z kolorow paleta dedykowaną."
         << endl;

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
