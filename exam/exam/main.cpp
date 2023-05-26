#include <stdio.h>
#include <stdbool.h>

// Определяем структуру вершины графа
struct Vertex {
    char name;
    int x;
    int y;
};

// Определяем структуру ребра графа
struct Edge {
    char start;
    char end;
};

// Создаем массив вершин графа
struct Vertex vertices[] = {
    {'A', 0, 0},
    {'B', 2, 0},
    {'C', 2, 2},
    {'D', 0, 2}
};
int num_vertices = sizeof(vertices) / sizeof(vertices[0]);

// Создаем массив ребер графа
struct Edge edges[] = {
    {'A', 'B'},
    {'B', 'C'},
    {'C', 'D'},
    {'D', 'A'}
};
int num_edges = sizeof(edges) / sizeof(edges[0]);

// Функция для проверки наличия короткого замыкания в графе
bool has_short_circuit() {
    bool visited[num_vertices]; // Массив посещенных вершин
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
    }

    char stack[num_vertices]; // Стек для обхода графа
    int top = -1;

    // Функция для поиска в глубину
    bool dfs(char vertex) {
        visited[vertex - 'A'] = true;
        stack[++top] = vertex;

        // Получаем соседей вершины
        char neighbors[num_vertices];
        int num_neighbors = 0;
        for (int i = 0; i < num_edges; i++) {
            if (edges[i].start == vertex) {
                neighbors[num_neighbors++] = edges[i].end;
            }
        }

        // Обходим всех соседей вершины
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

    // Обходим все вершины графа
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
    // Проверяем наличие короткого замыкания в графе
    if (has_short_circuit()) {
        printf("Граф содержит короткое замыкание\n");
    }
    else {
        printf("Граф не содержит короткого замыкания\n");
    }

    return 0;
}