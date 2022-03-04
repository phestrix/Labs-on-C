#include <limits.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "graph.h"

int main(void) {
  int N, M, begin, end;
  if (checkInput(&N, &M, &begin, &end) == 0)
    return 0;
  int* path = calloc(N, sizeof(int));
  if (!path)
    return 0;
  unsigned* shortestPath = calloc(N, sizeof(unsigned));
  if (!shortestPath) {
    free(path);
    return 0;
  }
  int* used = calloc(N, sizeof(int));
  if (!used) {
    free(path);
    free(shortestPath);
    return 0;
  }
  for (int i = 0; i < N; ++i) {
    shortestPath[i] = UINT_MAX;
    used[i] = -1;
    path[i] = -1;
  }
  dijkstra(&N, &M, &begin, &end, shortestPath, used, path);
  return 0;
}
