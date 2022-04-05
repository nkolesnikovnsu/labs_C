#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
 
#define MAX_LENGTH INT_MAX
 
bool checkInput(int vertices, int edges){
    if (vertices < 0 || vertices > 5000) {
        printf("bad number of vertices");
        return false;
    }
    if (edges < 0 || edges > (vertices) * (vertices + 1) / 2) {
        printf("bad number of edges");
        return false;
    }
    return true;
}
 
bool checkSpanningTree(int vertices, int edges, bool * Edges){
    if (vertices == 0) {
        printf("no spanning tree");
        return false;
    } else if (vertices == 1 && edges == 0) {
        return false;
    }
 
    for (int i = 0; i < vertices; i++) {
        if (!Edges[i]) {
            printf("no spanning tree");
            return false;
        }
    }
    return true;
}
 
void prim(int vertices, long long * priorityQueue, int ** graph, int * vertFrom){
    int current = 0;
    for (int i = 0; i < vertices - 1; i++) {
        for (int j = 0; j < vertices; j++) {
            if (graph[current][j] < priorityQueue[j] && graph[current][j] != 0 && priorityQueue[j] != LLONG_MAX) {
                priorityQueue[j] = graph[current][j];
                vertFrom[j] = current;
            }
        }
 
        int index = -1;
        priorityQueue[current] = LLONG_MAX;
        long long min = priorityQueue[0];
        for (int j = 1; j < vertices; j++) {
            if (priorityQueue[j] < min) {
                min = priorityQueue[j];
                index = j;
            }
        }
 
        current = index;
        printf("%d %d\n", vertFrom[index] + 1, index + 1);
    }
}
 
void cleanup(void * graph, void * pQueue , void * Edges, void * vertFrom ) {
    if (graph)
        free(graph);
 
    if(pQueue)
        free(pQueue);
 
    if(Edges)
        free(Edges);
 
    if(vertFrom)
        free(vertFrom);
}
 
 
int main(){
    int vertices = 0, edges = 0;
    if (scanf("%d%d", &vertices, &edges) < 2) {
        printf("bad input");
        return 0;
    }
 
    bool check = true;
    if((check = checkInput(vertices, edges)) != true){
        return 0;
    }
 
    //создадим двумерный массив динамически
    int** graph = (int**)calloc(vertices, sizeof(int*));
    if (!graph) {
        printf("out of memory");
        return 0;
    }
 
    for (int i = 0; i < vertices; i++) {
        graph[i] = (int*)calloc(vertices, sizeof(int));
        if (!graph[i]) {
            printf("out of memory");
            for (int j = i - 1; j >= 0; j--) {
                free(graph[j]);
            }
            free(graph);
            return 0;
        }
    }
 
    //логический массив для обозначения наличия ребер из вершин
    bool* Edges = (bool*)calloc(vertices, sizeof(bool));
    if (!Edges) {
        printf("out of memory");
        for (int j = 0; j < vertices; j++) {
            free(graph[j]);
        }
        free(graph);
        return 0;
    }
 
    //ввод ребер
    for (int i = 0; i < edges; i++) {
        int first, second;
        long long length;
        if (scanf("%d%d%lli", &first, &second, &length) < 3) {
            printf("bad number of lines");
            for (int j = 0; j < vertices; j++) {
                free(graph[j]);
            }
            cleanup(graph, NULL, Edges, NULL);
            return 0;
        }
        if (first < 1 || second < 1 || first > vertices || second > vertices) {
            printf("bad vertex");
            for (int j = 0; j < vertices; j++) {
                free(graph[j]);
            }
            cleanup(graph, NULL, Edges, NULL);
            return 0;
        }
        if (length < 0 || length > INT_MAX) {
            printf("bad length");
            for (int j = 0; j < vertices; j++) {
                free(graph[j]);
            }
            cleanup(graph, NULL, Edges, NULL);
            return 0;
        }
        graph[first - 1][second - 1] = (int)length;
        graph[second - 1][first - 1] = (int)length;
        Edges[first - 1] = true;
        Edges[second - 1] = true;
    }
 
    //проверка на возможность построить остов
    if((check = checkSpanningTree(vertices, edges, Edges)) != true){
        for (int j = 0; j < vertices; j++) {
            free(graph[j]);
        }
        cleanup(graph, NULL, Edges, NULL);
        return 0;
    }
 
    //зададим priorityQueue массивом
    long long* priorityQueue = (long long*)calloc(vertices, sizeof(long long));
    if (!priorityQueue) {
        printf("out of memory");
        for (int j = 0; j < vertices; j++) {
            free(graph[j]);
        }
        cleanup(graph, NULL, Edges, NULL);
        return 0;
    }
    for (int i = 1; i < vertices; i++) {
        priorityQueue[i] = (long long)INT_MAX + 1;
    }
 
    //зададим вспомогательный массив vertFrom для вершин из которых идем
    int* vertFrom = (int*)calloc(vertices, sizeof(int));
    if (!vertFrom) {
        printf("out of memory");
        for (int j = 0; j < vertices; j++) {
            free(graph[j]);
        }
        cleanup(graph, priorityQueue, Edges, NULL);
        return 0;
    }
 
    prim(vertices, priorityQueue, graph, vertFrom);
 
    for (int j = 0; j < vertices; j++) {
        free(graph[j]);
    }
    cleanup(graph, priorityQueue, Edges, vertFrom);
    return 0;
}
