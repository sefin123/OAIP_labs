// подключение необходимых заголовочных файлов
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define scanf scanf_s

// определение структуры Vertex, содержащей координаты вершины
struct Vertex {
    int x, y;
};

// функция для определения ориентации тройки точек
int orientation(struct Vertex p, struct Vertex q, struct Vertex r) {
    // вычисление значений для определения ориентации
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    // если значение равно 0, то точки коллинеарны
    if (val == 0)
        return 0;
    // если значение больше 0, то точки образуют левый поворот
    else if (val > 0)
        return 1;
    // если значение меньше 0, то точки образуют правый поворот
    else
        return 2;
}

// функция для проверки пересечения двух отрезков
int doIntersect(struct Vertex p1, struct Vertex q1, struct Vertex p2, struct Vertex q2) {
    // определение ориентации четырех точек
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    // если ориентации разные, то отрезки пересекаются
    if (o1 != o2 && o3 != o4)
        return 1;
    // если точки коллинеарны и лежат на отрезках, то отрезки пересекаются
    if (o1 == 0 && orientation(p1, p2, q1) == 0 && orientation(q1, q2, p1) == 0)
        return 1;
    // в остальных случаях отрезки не пересекаются
    return 0;
}

// функция для проверки наличия короткого замыкания в графе
int hasShortCircuit(struct Vertex* vertices, int numVertices, int* edges[2], int numEdges) {
    // цикл для проверки каждой пары ребер на пересечение
    for (int i = 0; i < numVertices; i++) {
        struct Vertex p1 = vertices[edges[0][i]];
        struct Vertex q1 = vertices[edges[1][i]];
        for (int j = i + 1; j < numEdges; j++) {
            struct Vertex p2 = vertices[edges[0][j]];
            struct Vertex q2 = vertices[edges[1][j]];
            if (doIntersect(p1, q1, p2, q2))
                return 1;
        }
    }
    // если короткое замыкание не найдено, то возвращается 0
    return 0;
}

// Объявление функции main
int main() {
    // Объявление переменных numVertices и numEdges типа int
    int numVertices, numEdges;

    // Вывод на экран запроса на ввод количества вершин
    printf("Enter the number of vertices: ");

    // Считывание введенного пользователем значения и сохранение его в переменную numVertices
    scanf("%d", &numVertices);

    // Выделение памяти под массив вершин размером numVertices и приведение указателя к типу Vertex*
    auto vertices = static_cast<Vertex*>(_malloca(numVertices * sizeof(Vertex)));

    // Проверка, удалось ли выделить память под массив вершин, и завершение программы в случае неудачи
    if (vertices == NULL) abort();

    // Цикл для ввода координат вершин
    for (int i = 0; i < numVertices; i++) {
        // Вывод на экран запроса на ввод координат вершины i
        printf("Enter the x and y coordinates of vertex %d: ", i);

        // Считывание введенных пользователем значений и сохранение их в соответствующие поля структуры Vertex
        scanf("%d", &vertices[i].x);
        scanf("%d", &vertices[i].y);
    }

    // Вывод на экран запроса на ввод количества ребер
    printf("Enter the number of edges: ");

    // Считывание введенного пользователем значения и сохранение его в переменную numEdges
    scanf("%d", &numEdges);

    // Выделение памяти под массив ребер размером numEdges и приведение указателей к типу int*
    int* edges[2] = {
        static_cast<int*>(_malloca(numEdges * sizeof(int))),
        static_cast<int*>(_malloca(numEdges * sizeof(int)))
    };

    // Проверка, удалось ли выделить память под массив ребер, и завершение программы в случае неудачи
    if (edges == NULL) abort();

    // Цикл для ввода ребер
    for (int i = 0; i < numEdges; i++) {
        // Проверка, удалось ли выделить память под массивы вершин для i-го ребра, и завершение программы в случае неудачи
        if (edges[0] == NULL || edges[1] == NULL) abort();

        // Вывод на экран запроса на ввод вершин, образующих i-е ребро
        printf("Enter the two vertices that form edge %d: ", i);

        // Считывание введенных пользователем значений и сохранение их в соответствующие ячейки массивов edges[0] и edges[1]
        scanf("%d", &edges[0][i]);
        scanf("%d", &edges[1][i]);
    }

    /*p>=3 q<=3(p-2)

    */

    // Проверка на наличие короткого замыкания в графе и вывод соответствующего сообщения на экран
    if (hasShortCircuit(vertices, numVertices, edges, numEdges))
        printf("There are short circuits.\n");
    else
        printf("There are no short circuits.\n");

    

    // Возврат значения 0, указывающего на успешное завершение программы
    return 0;
}