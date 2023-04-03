#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

void greyFormat(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader)
{
    // преобразуем пиксели в черно-белый формат
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];

            // вычисляем яркость пикселя
            unsigned char gray = (unsigned char)((pixel->r + pixel->g + pixel->b) / 3);
            // устанавливаем значения компонентов RGB в значение яркости
            pixel->r = gray;
            pixel->g = gray;
            pixel->b = gray;
        }
    }
}

void negativeFormat(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader)
{
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];

            // устанавливаем значения компонентов RGB в значение яркости
            pixel->r = 255 - pixel->r;
            pixel->g = 255 - pixel->g;
            pixel->b = 255 - pixel->b;
        }
    }
}

void gammaCorection(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader)
{
    float gamma;
    printf("Offset gamma corection: ");
    scanf_s("%f", &gamma);
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];
            unsigned char r = 255 * pow(pixel->r / 255.0f, gamma);
            unsigned char g = 255 * pow(pixel->g / 255.0f, gamma);
            unsigned char b = 255 * pow(pixel->b / 255.0f, gamma);

            if (r > 255) { r = 255; }
            if (g > 255) { g = 255; }
            if (b > 255) { b = 255; }
            // устанавливаем значения компонентов RGB в значение яркости
            pixel->r = r;
            pixel->g = g;
            pixel->b = b;
        }
    }
}

void blur(Pixel** pixels, Pixel* pixel, BMPHeader header, BMPInfoHeader infoHeader)
{
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];
            float sumRed, sumGreen, sumBlue;
            int counter;
            sumRed = sumGreen = sumBlue = counter = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + k < 0 || i + k > infoHeader.height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > infoHeader.width - 1)
                    {
                        continue;
                    }
                    sumRed += pixels[i + k][j + c].r;
                    sumGreen += pixels[i + k][j + c].g;
                    sumBlue += pixels[i + k][j + c].b;
                    counter++;

                }
            }
            pixel->r = round(sumRed / counter);
            pixel->g = round(sumGreen / counter);
            pixel->b = round(sumBlue / counter);
        }
    }
}
