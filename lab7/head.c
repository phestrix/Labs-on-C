#include "head.h"

#include <stdio.h>
#include <stdlib.h>

// util func for bit writing in matrix
static int powof2(int b) {
  int a = 1;
  for (int i = 0; i < b; i++) a *= 2;
  return a;
}

int input(int* vertices, int* edges) {
  if ((scanf("%d", vertices)) == 1) {
    if (*vertices < 0 || *vertices > 2000) {
      printf("bad number of vertices\n");
      return 1;
    }
  }
  if ((scanf("%d", edges)) == 1) {
    if (*edges < 0 || *edges > (*vertices * (*vertices + 1)) / 2) {
      printf("bad number of edges\n");
      return 1;
    }

  } else {
    printf("bad number of lines\n");
    return 1;
  }
  return 0;
}

int inputEdges(const int* vertices, int* src, int* dst) {
  if (scanf("%d %d", src, dst) != 2) {
    printf("bad number of lines\n");
    return 1;
  }

  if (*src < 1 || *dst < 1 || *src > *vertices || *dst > *vertices) {
    printf("bad vertex\n");
    return 1;
  }

  if (*src == *dst) {
    printf("impossible to sort\n");
    return 1;
  }

  return 0;
}

// func that fill matrix of adjanecy
int createGraph(const int* vertices, const int* edges, char* graph) {
  for (int i = 0; i < *edges; ++i) {
    int src = 0, dst = 0;
    if (inputEdges(vertices, &src, &dst)) {
      return 1;
    }
    graph[(src - 1) * 250 + ((dst - 1) / 8)] += powof2((dst - 1) % 8);
  }

  if (*vertices == 0) {
    printf("impossible to sort\n");
    return 1;
  }
  return 0;
}

void printGraph(short* graph, const int* vertices) {
  for (int i = 0; i < *vertices; ++i) {
    printf("%d ", graph[i] + 1);
  }
}

// func that fill matrix with unmarked flags
void fillRes(short* graph, const int* vertices) {
  for (int i = 0; i < *vertices; ++i) graph[i] = -1;
}

// func that check vertex in matrix
int checkVert(char* matrix, char* extra, const int* count, const int v) {
  if (extra[v]) return 1;

  for (int i = 0; i < *count; i++) {
    if ((matrix[i * 250 + (v / 8)] & (1 << (v % 8))) && !extra[i]) return 1;
  }
  return 0;
}

// dfs implementation
int dfs(char* matrix, short* res, char* extra, int* count, const int* countV) {
  for (int i = 0; i < *countV; ++i) {
    if (!checkVert(matrix, extra, countV, i)) {
      extra[i] = 1;
      res[(*count)++] = i;

      if (*count < *countV) dfs(matrix, res, extra, count, countV);

      (*count)--;
      extra[i] = 0;

      if (res[*countV - 1] != -1) return 1;
    }
  }
  return 0;
}

// Topological sort
int topSort(char* matrix, const int* countV) {
  char* extra = calloc(*countV, sizeof(char));
  short* res = malloc(*countV * sizeof(short));

  fillRes(res, countV);
  int count = 0;
  int check = dfs(matrix, res, extra, &count, countV);
  free(extra);

  if (check)
    printGraph(res, countV);

  else
    printf("impossible to sort\n");

  free(res);
  return 1;
}

// util func for main which allocate memory for matrix's and start Topological
// sort used only in main for more clean code
int doTopSort(int* vertices, int* edges) {
  if (input(vertices, edges)) return 1;

  char* graph = calloc(*vertices * 250, sizeof(char));
  if (!graph) return 1;

  if (createGraph(vertices, edges, graph)) {
    free(graph);
    return 1;
  }

  if (topSort(graph, vertices)) {
    free(graph);
    return 1;
  }

  free(graph);
  return 0;
}