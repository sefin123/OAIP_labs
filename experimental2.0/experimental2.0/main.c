#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(void)
{
    FILE* file;
    BMPHeader header;
    BMPInfoHeader infoHeader;
    Pixel** pixels = NULL;
    Pixel* pixel = NULL;
    //scanf("%s", &input);
    // открываем BMP-файл на чтение
    file = fopen("input.bmp", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(pixels);
        return 1;
    }

    // считываем заголовок BMP-файла
    fread(&header, sizeof(BMPHeader), 1, file);

    // проверяем, что это BMP-файл
    if (header.type[0] != 'B' || header.type[1] != 'M') {
        printf("Error: Not a BMP file.\n");
        free(pixels);
        fclose(file);
        return 2;
    }

    // считываем заголовок изображения BMP-файла
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // проверяем, что это 24-битное изображение
    if (infoHeader.bpp != 24) {
        printf("Error: Not a 24-bit BMP file.\n");
        free(pixels);
        fclose(file);
        return 3;
    }

    // выделяем память под пиксели
    pixels = (Pixel**)malloc(sizeof(Pixel*) * infoHeader.height);
    if (pixels == NULL) {
        printf("Error: Out of memory.\n");
        fclose(file);
        return 4;
    }
    for (int i = 0; i < infoHeader.height; i++) {
        pixels[i] = (Pixel*)malloc(sizeof(Pixel) * infoHeader.width);
        if (pixels[i] == NULL) {
            printf("Error: Out of memory.\n");
            for (int j = 0; j < i; j++) {
                free(pixels[j]);
            }
            free(pixels);
            fclose(file);
            return 4;
        }
    }
    // считываем пиксели
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];
            fread(pixel, sizeof(Pixel), 1, file);
        }
    }

    // закрываем BMP-файл
    fclose(file);


    //greyFormat(pixels, pixel, header, infoHeader);
    negativeFormat(pixels, pixel, header, infoHeader);
    //gammaCorection(pixels, pixel, header, infoHeader);
    //blur(pixels, pixel, header, infoHeader);

    // открываем BMP-файл на запись
    char* output = malloc(256 * sizeof(char));
    printf("Name of output file: ");
    //scanf_s("%s", output);
    file = fopen("asd.bmp", "wb");
    if (file == NULL) {
        printf("Error creating output file.\n");
        free(pixels);
        fclose(file);
        return 4;
    }

    // записываем заголовок BMP-файла
    fwrite(&header, sizeof(header), 1, file);

    // записываем заголовок изображения BMP-файла
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);

    // записываем пиксели
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];
            fwrite(pixel, sizeof(Pixel), 1, file);
        }
    }

    // закрываем BMP-файл
    fclose(file);

    // освобождаем память, выделенную под пиксели
    for (int i = 0; i < infoHeader.height; i++) {
        free(pixels[i]);
    }
    free(pixels);
    fclose(file);
    printf("DONE\n");
    return 0;
}
