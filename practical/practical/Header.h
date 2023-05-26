#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define scanf scanf_s

typedef struct �oordinates {
    int x, y;
}�oordinates;

int determineOrientation(�oordinates p, �oordinates q, �oordinates r);

int doLinesIntersect(�oordinates p1, �oordinates q1, �oordinates p2, �oordinates q2);

int hasShortCircuit(�oordinates* vertices, int* edges[2], int numEdges);