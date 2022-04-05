#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool checkInput(int vertices, int edges, int start, int end){
    if (vertices < 0 || vertices > 5000) {
        printf("bad number of vertices");
        return false;
    }
    if (edges < 0 || edges > (vertices) * (vertices - 1) / 2) {
        printf("bad number of edges");
        return false;
    }
    if (start < 1 || end < 1 || start > vertices || end > vertices) {
        printf("bad vertex");
        return false;
    }
    return true;
}

void cleanup(int ** graph, void * parents, void * dist, void * used, int vertices) {
    if (graph) {
        if (vertices != 0) {
            for (int i = 0; i < vertices; i++) {
                if (graph[i]) {
                    free(graph[i]);
                }
            }
        }
        free(graph);
    }

    if (parents) {
        free(parents);
    }

    if (dist) {
        free(dist);
    }

    if (used) {
        free(used);
    }
}

void Dijkstra(int ** graph, int vertices, int start, int end, int * parents, long long * dist, int * used){
    for (int i = 0; i < vertices; i++) {
        if (i != start - 1) {
            dist[i] = LLONG_MAX;
        }
        parents[i] = i;
        used[i] = 0;
    }
    dist[start - 1] = 0;

    int manyPaths = 0;
    int cur = start - 1;
    for (int i = 0; i < vertices; i++) {
        used[cur] = 1;
        for (int j = 0; j < vertices; j++) {
            if (dist[j] >= dist[cur] + graph[cur][j] && graph[cur][j] != 0 && !used[j]) {
                if (dist[j] > INT_MAX && dist[j] != LLONG_MAX && j == end - 1) {
                    manyPaths = 1;
                }

                dist[j] = dist[cur] + graph[cur][j];
                parents[j] = cur;
            }
        }

        int index = 0;
        long long min = LLONG_MAX;
        for (int j = 0; j < vertices; j++) {
            if (dist[j] < min && !used[j]) {
                min = dist[j];
                index = j;
            }
        }
        cur = index;
    }

    for (int i = 0; i < vertices; i++) {
        if (dist[i] <= INT_MAX) {
            printf("%lli ", dist[i]);
        } else if (dist[i] < LLONG_MAX) {
            printf("INT_MAX+ ");
        } else {
            printf("oo ");
        }
    }
    printf("\n");

    if (manyPaths) {
        printf("overflow");
    } else if (dist[end - 1] == LLONG_MAX) {
        printf("no path");
    } else {
        int current = end - 1;
        printf("%d ", current + 1);
        do {
            current = parents[current];
            printf("%d ", current + 1);
        } while (current != parents[current]);
    }
}

int main(){
    int vertices, edges, start, end;
    if (scanf("%d%d%d%d", &vertices, &start, &end, &edges) < 4) {
        printf("bad number of lines");
        return 0;
    }

    bool check = true;
    if((check = checkInput(vertices, edges, start, end)) != true){
        return 0;
    }

    //создадим граф
    int** graph = (int**)calloc(vertices, sizeof(int*));
    if (!graph) {
        printf("out of memory");
        return 0;
    }
    for (int i = 0; i < vertices; i++) {
        graph[i] = (int*)calloc(vertices, sizeof(int));
        if (!graph[i]) {
            cleanup(graph, NULL, NULL, NULL, vertices);
            printf("out of memory");
            return 0;
        }
    }

    //ввод ребер
    for (int i = 0; i < edges; i++) {
        int first, second;
        long long length;
        if (scanf("%d%d%lli", &first, &second, &length) < 3) {
            cleanup(graph, NULL, NULL, NULL, vertices);
            printf("bad number of lines");
            return 0;
        }

        if (first < 1 || second < 1 || first > vertices || second > vertices) {
            cleanup(graph, NULL, NULL, NULL, vertices);
            printf("bad vertex");
            return 0;
        }

        if (length < 0 || length > INT_MAX) {
            cleanup(graph, NULL, NULL, NULL, vertices);
            printf("bad length");
            return 0;
        }

        graph[first - 1][second - 1] = (int)length;
        graph[second - 1][first - 1] = (int)length;
    }

    //создание вспомогательных массивов
    int* parents = (int*)calloc(vertices, sizeof(int));
    if (!parents) {
        cleanup(graph, NULL, NULL, NULL, vertices);
        printf("out of memory");
        return 0;
    }
    long long* dist = (long long*)calloc(vertices, sizeof(long long));
    if (!dist) {
        cleanup(graph, parents, NULL, NULL, vertices);
        printf("out of memory");
        return 0;
    }
    int* used = (int*)calloc(vertices, sizeof(int));
    if (!used) {
        cleanup(graph, parents, dist, NULL, vertices);
        printf("out of memory");
        return 0;
    }

    Dijkstra(graph, vertices, start, end, parents, dist, used);
    cleanup(graph, parents, dist, used, vertices);
    return 0;
}
