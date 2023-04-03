#pragma once
// заголовок BMP-файла

#pragma pack(1) // отключаем выравнивание памяти

typedef struct
{
    unsigned char type[2];
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;
} BMPHeader;

// заголовок изображения BMP-файла
typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int hres;
    unsigned int vres;
    unsigned int colors;
    unsigned int impColors;
} BMPInfoHeader;

// пиксель
typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Pixel;
#pragma pop

void greyFormat(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader);
void negativeFormat(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader);
void gammaCorection(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader);
void blur(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader);
