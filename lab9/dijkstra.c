#include "dijkstra.h"
#include <stdlib.h>
#include "graph.h"

void dijkstra(int* N,
              int* M,
              int* begin,
              int* end,
              unsigned* shortestPath,
              int* used,
              int* path) {
  unsigned* graph = createGraph(N, M);
  if (!graph) {
    free(path);
    free(used);
    free(shortestPath);
    return;
  }
  shortestPath[*begin - 1] = 0;
  for (int i = 0; i < *N; ++i) {
    unsigned min = UINT_MAX;
    int indexMin = 0;
    for (int j = 0; j < *N; ++j) {
      if (used[j] == 0)
        continue;
      if (shortestPath[j] < min) {
        min = shortestPath[j];
        indexMin = j;
      }
    }
    ++used[indexMin];
    for (int k = 0; k < *N; ++k) {
      if (used[k] == 0)
        continue;
      if (shortestPath[k] <= checkOverflow(min, graph[indexMin * *N + k]))
        continue;
      shortestPath[k] = checkOverflow(min, graph[indexMin * *N + k]);
      path[k] = indexMin;
    }
  }
  checkOut(path, shortestPath, graph, begin, end, N);
  free(used);
  free(path);
  free(graph);
  free(shortestPath);
}