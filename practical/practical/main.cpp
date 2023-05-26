#include "Header.h"

int main() {
        printf("practic\n");

        int numVertices, numEdges;

        printf("Enter the number of vertices: ");
        scanf("%d", &numVertices);

        auto vertices = static_cast<Ñoordinates*>(_malloca(numVertices * sizeof(Ñoordinates)));
        if (vertices == NULL) abort();

        for (int i = 0; i < numVertices; i++) {
            printf("Enter the x coordinates of vertex %d: ", i + 1);
            scanf("%d", &vertices[i].x);
            
            printf("Enter the y coordinates of vertex %d: ", i + 1);
            scanf("%d", &vertices[i].y);
        }

        printf("Enter the number of edges: ");
        scanf("%d", &numEdges);

        int* edges[2] = {
            static_cast<int*>(_malloca(numEdges * sizeof(int))),
            static_cast<int*>(_malloca(numEdges * sizeof(int)))
        };
        if (edges == NULL) abort();

        for (int i = 0; i < numEdges; i++) {
            if (edges[0] == NULL || edges[1] == NULL) abort();

            printf("Enter the two vertices that form edge %d: ", i + 1);

            scanf("%d", &edges[0][i]);
            scanf("%d", &edges[1][i]);
        }

        if (numVertices >= 3 && !(numEdges <= 3 * (numVertices - 2))) {
            printf("This is not a planar graph.\n");

            return 0;
        }

        if (hasShortCircuit(vertices, edges, numEdges))
            printf("There are short circuits.\n");
        else
            printf("There are no short circuits.\n");

        _freea(vertices);
        _freea(edges);
    return 0;
}