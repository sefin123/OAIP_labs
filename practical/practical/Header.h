#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define scanf scanf_s

typedef struct Ñoordinates {
    int x, y;
}Ñoordinates;

int determineOrientation(Ñoordinates p, Ñoordinates q, Ñoordinates r);

int doLinesIntersect(Ñoordinates p1, Ñoordinates q1, Ñoordinates p2, Ñoordinates q2);

int hasShortCircuit(Ñoordinates* vertices, int* edges[2], int numEdges);