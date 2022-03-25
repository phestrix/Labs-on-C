#include "prim.h"
#include <stdio.h>
#include <stdlib.h>

static void swap(Graph* a, Graph* b) {
  Graph tmp = *a;
  *a = *b;
  *b = tmp;
}

void sort(Graph* graph, int first, int last) {
  if (first < last) {
    int left = first, right = last;
    int mid = (left + right) / 2;
    unsigned center = graph[mid].weight;

    while (left <= right) {
      while (graph[left].weight < center)
        ++left;

      while (graph[right].weight > center)
        --right;

      if (left <= right) {
        swap(&graph[left], &graph[right]);
        ++left;
        --right;
      }
    }
    sort(graph, first, right);
    sort(graph, left, last);
  }
}

int prim(Graph* graph, const int* vertices, const int* edges) {
  sort(graph, 0, *edges - 1);
  short* usedVert = calloc(*vertices, sizeof(short));
  if (!usedVert) {
    printf("no spanning tree\n");
    free(graph);
    return 1;
  }
  usedVert[0] = 1;
  for (int i = 0; i < *vertices; ++i) {
    for (int j = 0; j < *edges; ++j) {
      if (usedVert[graph[j].begin - 1] != usedVert[graph[j].end - 1]) {
        usedVert[graph[j].begin - 1] = usedVert[graph[j].end - 1] = 1;
        graph[j].used = 1;
        break;
      }
    }
  }
  for (int i = 0; i < *vertices; ++i) {
    if (!usedVert[i]) {
      free(usedVert);
      free(graph);
      printf("no spanning tree\n");
      return 1;
    }
  }
  free(usedVert);
  return 0;
}

void doPrim(int* vertices, int* edges) {
  if (checkInput(vertices, edges))
    return;
  Graph* graph = malloc(*edges * sizeof(Graph));
  if (createGraph(graph, edges, vertices))
    return;
  if (prim(graph, vertices, edges))
    return;
  printAnswer(graph, edges);
  free(graph);
}