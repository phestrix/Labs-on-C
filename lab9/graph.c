#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int checkInput(int* N, int* M, int* begin, int* end) {
  if (scanf("%d%d%d%d", N, begin, end, M) == 0)
    return 0;
  if ((*N > 5000) || *N < 0) {
    printf("bad number of vertices\n");
    return 0;
  }
  if ((*M < 0) || (*M > (*N * (*N - 1) / 2))) {
    printf("bad number of edges\n");
    return 0;
  }
  if ((*begin < 1 || *begin > *N) || (*end < 1 || *end > *N)) {
    printf("bad vertex\n");
    return 0;
  }
  return 1;
}

int fillMatrix(int* N, int* begin, int* end, unsigned* weight) {
  if (scanf("%d %d %u", begin, end, weight) != 3) {
    printf("bad number of lines\n");
    return 0;
  }
  if ((*begin < 1 || *begin > *N) || (*end < 1 || *end > *N)) {
    printf("bad vertex\n");
    return 0;
  }
  if (*weight > INT_MAX || *weight < 0) {
    printf("bad length\n");
    return 0;
  }
  return 1;
}

unsigned* createGraph(int* N, int* M) {
  unsigned* matrix = malloc(*N * *N * sizeof(unsigned));
  if (!matrix)
    return NULL;
  for (int i = 0; i < *N; ++i) {
    for (int j = 0; j < *N; ++j)
      matrix[i * *N + j] = UINT_MAX;
  }
  for (int i = 0; i < *M; ++i) {
    int begin, end;
    unsigned weight;
    if (!fillMatrix(N, &begin, &end, &weight)) {
      free(matrix);
      return NULL;
    }
    matrix[(begin - 1) * *N + (end - 1)] =
        matrix[(end - 1) * *N + (begin - 1)] = weight;
  }
  return matrix;
}

void checkOut(int* path,
              unsigned* shortestPath,
              unsigned* graph,
              int* begin,
              int* end,
              int* N) {
  for (int i = 0; i < *N; ++i) {
    if (shortestPath[i] == UINT_MAX)
      printf("oo ");
    else if (shortestPath[i] > INT_MAX)
      printf("INT_MAX+ ");
    else
      printf("%u ", shortestPath[i]);
  }
  printf("\n");
  unsigned weight_ofPath = shortestPath[*end - 1];
  int count_ofINT_MAX = 0;
  int weight = *end - 1;
  for (int i = 0; i < *N; ++i) {
    if (graph[(*end - 1) * *N + i] == UINT_MAX)
      continue;
    if ((graph[(*end - 1) * *N + i] + shortestPath[i]) > INT_MAX)
      ++count_ofINT_MAX;
  }
  if ((weight_ofPath > INT_MAX) && (count_ofINT_MAX > 1)) {
    printf("overflow");
    return;
  }
  while (weight != *begin - 1) {
    if (path[weight] == -1) {
      printf("no path");
      return;
    }
    printf("%d ", weight + 1);
    weight = path[weight];
  }
  printf("%d ", *begin);
}

unsigned checkOverflow(unsigned min, unsigned graph) {
  return (UINT_MAX - min >= graph) ? graph + min : UINT_MAX;
}