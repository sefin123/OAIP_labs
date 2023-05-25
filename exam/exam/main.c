#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int x[MAX_VERTICES], y[MAX_VERTICES];

int edgeExists(int u, int v) {
    // проверка наличия ребра между вершинами u и v в графе
    if (graph[u][v] == 1 || graph[v][u] == 1)
        return 1;
    return 0;
}

int intersect(int u1, int v1, int u2, int v2) {
    // проверка пересечения линий между вершинами u1 и v1, и u2 и v2
    if (u1 == u2 || u1 == v2 || v1 == u2 || v1 == v2)
        return 0;
    if ((x[u1] - x[v1]) * (y[u2] - y[v2]) - (x[u2] - x[v2]) * (y[u1] - y[v1]) == 0)
        return 0;
    if ((y[u1] - y[v1]) * (x[u2] - x[v2]) - (x[u1] - x[v1]) * (y[u2] - y[v2]) == 0)
        return 0;
    float ua = ((x[u2] - x[v2]) * (y[u1] - y[u2]) - (y[u2] - y[v2]) * (x[u1] - x[u2])) / ((y[u2] - y[v2]) * (x[u1] - x[v1]) - (x[u2] - x[v2]) * (y[u1] - y[v1]));
    float ub = ((x[u1] - x[v1]) * (y[u1] - y[u2]) - (y[u1] - y[v1]) * (x[u1] - x[u2])) / ((y[u2] - y[v2]) * (x[u1] - x[v1]) - (x[u2] - x[v2]) * (y[u1] - y[v1]));
    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1)
        return 1;
    return 0;
}

void rearrangeGraph()
{
    // перестройка графа, чтобы избежать пересечений линий
    for (int i = 0; i < MAX_VERTICES - 1; i++) {
        for (int j = i + 1; j < MAX_VERTICES; j++) {
            if (x[i] == x[j] && y[i] == y[j])
                continue;
            if (edgeExists(i, j))
                continue;
            int isIntersect = 0;
            for (int k = 0; k < MAX_VERTICES - 1; k++) {
                for (int m = k + 1; m < MAX_VERTICES; m++) {
                    if (edgeExists(k, m))
                        continue;
                    if (intersect(i, j, k, m)) {
                        isIntersect = 1;
                        break;
                    }
                }
                if (isIntersect)
                    break;
            }
            if (!isIntersect)
                continue;
            // перестройка графа
            // ...
            break;
        }
    }
}

void buildPlanarGraph() {
    // построение плоского графа
    // ...
    // после построения графа
        rearrangeGraph();
        // проверка наличия пересечений линий графа, если пересечения есть - перестроение графа, иначе - выход из цикла
}

int main() {
    // чтение входных данных, заполнение матрицы смежности
    // ...
    buildPlanarGraph();
    return 0;
}