#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int checkInput(int* vertices, int* edges) {
  if (scanf("%d %d", vertices, edges) != 2) {
    printf("bad input\n");
    return 1;
  }
  if (*vertices < 0 || *vertices > 5000) {
    printf("bad number of vertices\n");
    return 1;
  }
  if (*edges < 0 || *edges > (*vertices * (*vertices + 1) / 2)) {
    printf("bad number of edges\n");
    return 1;
  }
  return 0;
}

int checkEdges(short* begin,
               short* end,
               unsigned* weight,
               const int* vertices) {
  if (scanf("%hd %hd %u", begin, end, weight) != 3) {
    printf("bad number of lines\n");
    return 1;
  }
  if (*begin < 0 || *begin > *vertices || *end < 0 || *end > *vertices) {
    printf("bad vertex\n");
    return 1;
  }
  if (*weight > INT_MAX) {
    printf("bad length\n");
    return 1;
  }

  return 0;
}

int createGraph(Graph* graph, const int* edges, const int* vertices) {
  short begin = 0, end = 0;
  unsigned weight = 0;
  for (int i = 0; i < *edges; ++i) {
    if (checkEdges(&begin, &end, &weight, vertices)) {
      free(graph);
      return 1;
    }
    graph[i].begin = begin;
    graph[i].end = end;
    graph[i].weight = weight;
    graph[i].used = 0;
  }
  if (!*vertices) {
    printf("no spanning tree\n");
    free(graph);
    return 1;
  }
  return 0;
}

void printAnswer(Graph* graph, const int* edges) {
  for (int i = 0; i < *edges; ++i) {
    if (graph[i].used)
      printf("%hd %hd\n", graph[i].begin, graph[i].end);
  }
}