// ����������� ����������� ������������ ������
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define scanf scanf_s

// ����������� ��������� Vertex, ���������� ���������� �������
struct Vertex {
    int x, y;
};

// ������� ��� ����������� ���������� ������ �����
int orientation(struct Vertex p, struct Vertex q, struct Vertex r) {
    // ���������� �������� ��� ����������� ����������
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    // ���� �������� ����� 0, �� ����� �����������
    if (val == 0)
        return 0;
    // ���� �������� ������ 0, �� ����� �������� ����� �������
    else if (val > 0)
        return 1;
    // ���� �������� ������ 0, �� ����� �������� ������ �������
    else
        return 2;
}

// ������� ��� �������� ����������� ���� ��������
int doIntersect(struct Vertex p1, struct Vertex q1, struct Vertex p2, struct Vertex q2) {
    // ����������� ���������� ������� �����
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    // ���� ���������� ������, �� ������� ������������
    if (o1 != o2 && o3 != o4)
        return 1;
    // ���� ����� ����������� � ����� �� ��������, �� ������� ������������
    if (o1 == 0 && orientation(p1, p2, q1) == 0 && orientation(q1, q2, p1) == 0)
        return 1;
    // � ��������� ������� ������� �� ������������
    return 0;
}

// ������� ��� �������� ������� ��������� ��������� � �����
int hasShortCircuit(struct Vertex* vertices, int numVertices, int* edges[2], int numEdges) {
    // ���� ��� �������� ������ ���� ����� �� �����������
    for (int i = 0; i < numEdges; i++) {
        struct Vertex p1 = vertices[edges[0][i]];
        struct Vertex q1 = vertices[edges[1][i]];
        for (int j = i + 1; j < numEdges; j++) {
            struct Vertex p2 = vertices[edges[0][j]];
            struct Vertex q2 = vertices[edges[1][j]];
            if (doIntersect(p1, q1, p2, q2))
                return 1;
        }
    }
    // ���� �������� ��������� �� �������, �� ������������ 0
    return 0;
}

int main() {
    // ���������� ���������� ����������� ������ � ����������� �����
    int numVertices, numEdges;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    auto vertices = static_cast<Vertex*>(_malloca(numVertices * sizeof(Vertex)));
    if (vertices == NULL) abort();

    for (int i = 0; i < numVertices; i++) {
        printf("Enter the x and y coordinates of vertex %d: ", i);
        scanf("%d", &vertices[i].x);
        scanf("%d", &vertices[i].y);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    int* edges[2] = {
        static_cast<int*>(malloc(numEdges * sizeof(int))),
        static_cast<int*>(malloc(numEdges * sizeof(int)))
    };
    if (edges == NULL) abort();

    for (int i = 0; i < numEdges; i++) {
        if (edges[0] == NULL || edges[1] == NULL) abort();
        printf("Enter the two vertices that form edge %d: ", i);
        scanf("%d", &edges[0][i]);
        scanf("%d", &edges[1][i]);
    }

    // ����� ������� hasShortCircuit � ��������� �� �������� ������ � �����
    if (hasShortCircuit(vertices, numVertices, edges, numEdges))
        printf("There are short circuits.\n");
    else
        printf("There are no short circuits.\n");

    return 0;
}