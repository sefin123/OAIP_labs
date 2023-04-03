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
    // ��������� BMP-���� �� ������
    file = fopen("input.bmp", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(pixels);
        return 1;
    }

    // ��������� ��������� BMP-�����
    fread(&header, sizeof(BMPHeader), 1, file);

    // ���������, ��� ��� BMP-����
    if (header.type[0] != 'B' || header.type[1] != 'M') {
        printf("Error: Not a BMP file.\n");
        free(pixels);
        fclose(file);
        return 2;
    }

    // ��������� ��������� ����������� BMP-�����
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // ���������, ��� ��� 24-������ �����������
    if (infoHeader.bpp != 24) {
        printf("Error: Not a 24-bit BMP file.\n");
        free(pixels);
        fclose(file);
        return 3;
    }

    // �������� ������ ��� �������
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
    // ��������� �������
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];
            fread(pixel, sizeof(Pixel), 1, file);
        }
    }

    // ��������� BMP-����
    fclose(file);


    //greyFormat(pixels, pixel, header, infoHeader);
    negativeFormat(pixels, pixel, header, infoHeader);
    //gammaCorection(pixels, pixel, header, infoHeader);
    //blur(pixels, pixel, header, infoHeader);

    // ��������� BMP-���� �� ������
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

    // ���������� ��������� BMP-�����
    fwrite(&header, sizeof(header), 1, file);

    // ���������� ��������� ����������� BMP-�����
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);

    // ���������� �������
    for (int i = 0; i < infoHeader.height; i++) {
        for (int j = 0; j < infoHeader.width; j++) {
            pixel = &pixels[i][j];
            fwrite(pixel, sizeof(Pixel), 1, file);
        }
    }

    // ��������� BMP-����
    fclose(file);

    // ����������� ������, ���������� ��� �������
    for (int i = 0; i < infoHeader.height; i++) {
        free(pixels[i]);
    }
    free(pixels);
    fclose(file);
    printf("DONE\n");
    return 0;
}
