#include <stdio.h>
#include <mm_malloc.h>
#include <stdbool.h>



const char* Exceptions[] = {
        "bad number of lines",
        "bad number of vertices",
        "bad vertex",
        "bad number of edges",
        "impossible to sort"
};

typedef enum {
    BAD_LINES,
    BAD_VERTICES,
    BAD_VERTEX,
    BAD_EDGES,
    IMPOSSIBLE_TO_SORT,
    SUCCESS
}ExitCodes;

typedef enum {
    WHITE = 0,
    GREY = 1,
    BLACK = 2
} Colors;
void ADD_NEW_EDGE(int * graph, int x, int y, int numOfVertices) {
    graph[(x) * (numOfVertices) + (y)] = GREY;
}
bool CHECK_EDGE_COLOR(int *graph, int x, int y, int numOfVertices, int color) {
    if(graph[(x) * (numOfVertices) + (y)] == color)
    return(true);
    else
    return(false);
}


ExitCodes ReadAndCheckQuantities(int* n, int* m) {
    if (scanf("%d", n) != 1) {
        return(BAD_LINES);
    }
    if (scanf("%d", m) != 1) {
        return(BAD_LINES);
    }
    if (*n > 1000 || *n < 0) {
        return(BAD_VERTICES);
    }
    if (*m > (*n * (*n - 1) / 2) || *m < 0) {
        return(BAD_EDGES);
    }
    return(SUCCESS);
}

ExitCodes createGraph(int* graph, int n, int m) {
    int x = 0, y = 0;
    for (int i = 0; i < m; i++) {
        if (2 != (scanf("%d %d", &x, &y))) {
            return(BAD_LINES);
        }
        if ((x < 1) || (y < 1) || (x > n) || (y > n)) {
            return(BAD_VERTEX);
        }
        ADD_NEW_EDGE(graph, x - 1, y - 1, n);
    }
    return(SUCCESS);
}

ExitCodes topologicSort(int* graph, int* sortedGraph, int n, int m, int* graphColor, int currentVertex, int* counter) {
    switch (graphColor[currentVertex])
    {
        case BLACK:
            return(SUCCESS);
            break;
        case GREY:
            return(IMPOSSIBLE_TO_SORT);
            break;
        default:
            graphColor[currentVertex] = GREY;
            for (int i = 0; i < n; i++) {
                if (CHECK_EDGE_COLOR(graph, i, currentVertex, n, GREY))
                    if (IMPOSSIBLE_TO_SORT == topologicSort(graph, sortedGraph, n, m, graphColor, i, counter)) {
                        return(IMPOSSIBLE_TO_SORT);
                    }
            }
            graphColor[currentVertex] = BLACK;
            sortedGraph[*counter] = currentVertex + 1;
            (*counter)++;
            return(SUCCESS);
            break;
    }
}

void cleanup(void * graph, void* graphColor, void* sortedGraph) {
    if (graph)
        free(graph);

    if (graphColor)
        free(graphColor);

    if (sortedGraph)
        free(sortedGraph);
}


int main() {
    int n = 0, m = 0;
    ExitCodes rc;
    if (SUCCESS != (rc = ReadAndCheckQuantities(&n, &m))) {
        printf("%s", Exceptions[rc]);
        return(0);
    }

    int* graph = (int*)malloc(n * n * sizeof(int));
    if (SUCCESS != (rc = createGraph(graph, n, m))) {
        printf("%s", Exceptions[rc]);
        cleanup(graph, NULL, NULL);
        return(0);
    }

    int* graphColor = (int*)malloc(n * sizeof(int));
    int* sortedGraph = (int*)malloc(n * sizeof(int));
    if (sortedGraph == NULL) exit(0);

    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (IMPOSSIBLE_TO_SORT == topologicSort(graph, sortedGraph, n, m, graphColor, i, &counter)) {
            printf("%s", Exceptions[IMPOSSIBLE_TO_SORT]);
            cleanup(graph, graphColor, sortedGraph);
            return(0);
        }
    }

    if (sortedGraph == NULL) return(0);
    for (int i = 0; i < n; i++) {
        printf("%d ", sortedGraph[i]);
    }

    cleanup(graph, graphColor, sortedGraph);
    return(0);
}
