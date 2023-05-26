#include "Header.h"

int determineOrientation(�oordinates p, �oordinates q, �oordinates r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;
    else
        return 1;
}

int doLinesIntersect(�oordinates p1, �oordinates q1, �oordinates p2, �oordinates q2) {

    int orientation1 = determineOrientation(p1, q1, p2);
    int orientation2 = determineOrientation(p1, q1, q2);
    int orientation3 = determineOrientation(p2, q2, p1);
    int orientation4 = determineOrientation(p2, q2, q1);

    if (orientation1 != orientation2 && orientation3 != orientation4)
        return 1;

    if (orientation1 == 0 && determineOrientation(p1, p2, q1) == 0 && determineOrientation(q1, q2, p1) == 0)
        return 1;

    return 0;
}

int hasShortCircuit(�oordinates* vertices, int* edges[2], int numEdges) {

    for (int i = 0; i < numEdges; i++) {
        �oordinates p1 = vertices[edges[0][i]];
        �oordinates p2 = vertices[edges[1][i]];
        for (int j = i + 1; j < numEdges; j++) {
            �oordinates q1 = vertices[edges[0][j]];
            �oordinates q2 = vertices[edges[1][j]];
            if (doLinesIntersect(p1, p2, q1, q2))
                return 1;
        }
    }

    return 0;
}
