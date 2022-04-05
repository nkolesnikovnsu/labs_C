#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_LENGTH INT_MAX

typedef struct _Edge{
    int first;
    int second;
    int length;
}Edge;

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int find(int s, int* dsu) {
    if (s == dsu[s]) {
        return s;
    }
    return dsu[s] = find(dsu[s], dsu);
}

bool unite(int s1, int s2, int* dsu) {
    s1 = find(s1, dsu);
    s2 = find(s2, dsu);
    if (s1 != s2) {
        if (s2 < s1) {
            swap(&s1, &s2);
        }
        dsu[s2] = s1;
        return true;
    }
    return false;
}

Edge* createArray(int edges) {
    Edge* array = (Edge*)calloc(edges + 1, sizeof(Edge));
    if (!array) {
        return NULL;
    }
    return array;
}

bool checkSpanTree(int vertices, int edges, Edge* arrayOfEdges, int* dsu) {
    if (vertices == 0) {
        return false;
    }
    for (int i = 0; i < edges; i++) {
        if (!unite(arrayOfEdges[i].first, arrayOfEdges[i].second, dsu)) {
            arrayOfEdges[i].first = -1;
        }
    }
    for (int i = 0; i < vertices; i++) {
        find(i, dsu);
        if (dsu[i] != 0) {
            return false;
        }
    }
    return true;
}

int* createDsu(int vertices) {
    int* dsu = (int*)calloc(vertices + 1, sizeof(int));
    if (!dsu) {
        return NULL;
    }
    for (int i = 0; i < vertices; i++) {
        dsu[i] = i;
    }
    return dsu;
}

int compareLengths(const void* first, const void* second) {
    const Edge* firstEdge = (Edge*)first;
    const Edge* secondEdge = (Edge*)second;
    return firstEdge -> length - secondEdge -> length;
}

void freeMemory(Edge* arrEdges, int* dsu) {
    if (arrEdges) {
        free(arrEdges);
    }
    if (dsu) {
        free(dsu);
    }
}

int main() {
    int vertices = 0;
    int edges = 0;
    Edge* arrOfEdges;
    if (scanf("%d%d", &vertices, &edges) < 2) {
        printf("bad input");
        return 0;
    }
    if (vertices < 0 || vertices > 5000) {
        printf("bad number of vertices");
        return 0;
    }
    if (edges < 0 || edges > (vertices) * (vertices - 1) / 2) {
        printf("bad number of edges");
        return 0;
    }

    arrOfEdges = createArray(edges);
    if (!arrOfEdges) {
        printf("no memory");
        return 0;
    }

    for (int i = 0; i < edges; i++) {
        int firstVertice, secondVertice;
        long long length;
        if (scanf("%d%d%lli", &firstVertice, &secondVertice, &length) < 3) {
            printf("bad number of lines");
            freeMemory(arrOfEdges, NULL);
            return 0;
        }
        if ((firstVertice < 1 || firstVertice > vertices) || (secondVertice < 1 || secondVertice > vertices)) {
            printf("bad vertex");
            freeMemory(arrOfEdges, NULL);
            return 0;
        }
        if (length < 0 || length > MAX_LENGTH) {
            printf("bad length");
            freeMemory(arrOfEdges, NULL);
            return 0;
        }
        arrOfEdges[i] = (Edge){firstVertice, secondVertice, (int)length};
    }

    qsort(arrOfEdges, (size_t)edges, sizeof(Edge), compareLengths);

    int* dsu;
    if ((dsu = createDsu(vertices)) == NULL) {
        printf("no memory");
        freeMemory(arrOfEdges, NULL);
        return 0;
    }

    if (!checkSpanTree(vertices, edges, arrOfEdges, dsu)) {
        printf("no spanning tree");
        freeMemory(arrOfEdges, dsu);
        return 0;
    }

    int counterOfEdges = 0;
    for (int i = 0; i < edges; i++) {
        if (arrOfEdges[i].first > 0) {
            printf("%d %d\n", arrOfEdges[i].first, arrOfEdges[i].second);
            counterOfEdges++;
            if (counterOfEdges == vertices - 1) {
                break;
            }
        }
    }

    freeMemory(arrOfEdges, dsu);
    return 0;
}
