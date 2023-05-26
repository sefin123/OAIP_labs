#include <stdio.h>
#include <stdbool.h>

// ���������� ��������� ������� �����
struct Vertex {
    char name;
    int x;
    int y;
};

// ���������� ��������� ����� �����
struct Edge {
    char start;
    char end;
};

// ������� ������ ������ �����
struct Vertex vertices[] = {
    {'A', 0, 0},
    {'B', 2, 0},
    {'C', 2, 2},
    {'D', 0, 2}
};
int num_vertices = sizeof(vertices) / sizeof(vertices[0]);

// ������� ������ ����� �����
struct Edge edges[] = {
    {'A', 'B'},
    {'B', 'C'},
    {'C', 'D'},
    {'D', 'A'}
};
int num_edges = sizeof(edges) / sizeof(edges[0]);

// ������� ��� �������� ������� ��������� ��������� � �����
bool has_short_circuit() {
    bool visited[num_vertices]; // ������ ���������� ������
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
    }

    char stack[num_vertices]; // ���� ��� ������ �����
    int top = -1;

    // ������� ��� ������ � �������
    bool dfs(char vertex) {
        visited[vertex - 'A'] = true;
        stack[++top] = vertex;

        // �������� ������� �������
        char neighbors[num_vertices];
        int num_neighbors = 0;
        for (int i = 0; i < num_edges; i++) {
            if (edges[i].start == vertex) {
                neighbors[num_neighbors++] = edges[i].end;
            }
        }

        // ������� ���� ������� �������
        for (int i = 0; i < num_neighbors; i++) {
            char neighbor = neighbors[i];
            if (!visited[neighbor - 'A']) {
                if (dfs(neighbor)) {
                    return true;
                }
            }
            else if (neighbor == stack[top]) {
                return true;
            }
        }

        top--;
        return false;
    }

    // ������� ��� ������� �����
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            if (dfs(vertices[i].name)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    // ��������� ������� ��������� ��������� � �����
    if (has_short_circuit()) {
        printf("���� �������� �������� ���������\n");
    }
    else {
        printf("���� �� �������� ��������� ���������\n");
    }

    return 0;
}