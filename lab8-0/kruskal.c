#include "kruskal.h"
#include <stdio.h>
#include <stdlib.h>

static void swap(Graph* a, Graph* b) {
  Graph tmp = *a;
  *a = *b;
  *b = tmp;
}

// func that print mst of graph
static void printAnswer(Graph* graph, const int* edges) {
  for (int i = 0; i < *edges; ++i) {
    if (graph[i].used)
      printf("%hd %hd\n", graph[i].begin, graph[i].end);
  }
}

// quicksort for edges
void sort(Graph* graph, const int first, const int end) {
  if (first < end) {
    int left = first, right = end;

    unsigned center = graph[(left + right) / 2].weight;

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
    sort(graph, left, end);
  }
}

// algo that create graph, find mst in it and then print it
int kruskal(const int* vertices, const int* edges) {
  Graph* graph = malloc(*edges * sizeof(Graph));
  if (!graph)
    return 1;
  if (createGraph(vertices, edges, graph)) {
    free(graph);
    return 1;
  }
  short* parents = malloc(*vertices * sizeof(short));
  if (!parents) {
    free(graph);
    return 1;
  }
  short* rank = malloc(*vertices * sizeof(short));
  if (!rank) {
    free(graph);
    free(parents);
    return 1;
  }

  sort(graph, 0, (*edges) - 1);
  makeSet(vertices, parents, rank);

  int tree = 1;

  for (int i = 0; i < *edges; ++i) {
    graph[i].used = 0;
    short begin = graph[i].begin - 1;
    short end = graph[i].end - 1;
    if (findSet(parents, begin) != findSet(parents, end)) {
      graph[i].used = 1;
      mergeSet(rank, parents, &begin, &end);
      ++tree;
    }
  }

  if (tree != *vertices) {
    free(parents);
    free(rank);
    free(graph);
    printf("no spanning tree\n");
    return 1;
  }

  free(parents);
  free(rank);
  printAnswer(graph, edges);
  free(graph);
  return 0;
}