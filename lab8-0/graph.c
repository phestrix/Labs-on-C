#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

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
  if (*begin < 1 || *begin > *vertices || *end < 1 || *end > *vertices) {
    printf("bad vertex\n");
    return 1;
  }
  if (*weight > INT_MAX) {
    printf("bad length\n");
    return 1;
  }
  return 0;
}

// util func which fill graph
int createGraph(const int* vertices, const int* edges, Graph* graph) {
  for (int i = 0; i < *edges; ++i) {
    unsigned weight = 0;
    short begin = 0, end = 0;
    if (checkEdges(&begin, &end, &weight, vertices))
      return 1;
    graph[i].begin = begin;
    graph[i].end = end;
    graph[i].weight = weight;
  }
  return 0;
}

// make dsu set
void makeSet(const int* vertices, short* parents, short* rank) {
  for (int i = 0; i < *vertices; ++i) {
    parents[i] = i;
    rank[i] = 0;
  }
}

// find set in dsu
short findSet(short* parents, short elem) {
  if (parents[elem] == elem)
    return elem;
  parents[elem] = findSet(parents, parents[elem]);
  return parents[elem];
}

// merge two sets in dsu in one
void mergeSet(short* rank, short* parents, short* begin, short* end) {
  *begin = findSet(parents, *begin);
  *end = findSet(parents, *end);
  parents[*begin] = *begin;
  parents[*end] = *end;
  if (rank[*begin] > rank[*end]) {
    parents[*end] = *begin;
    return;
  }
  parents[*begin] = *end;
  if (rank[*begin] == rank[*end])
    rank[*end] += 1;
}
