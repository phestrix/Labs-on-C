#include <stdlib.h>
#include "graph.h"
#include "kruskal.h"

int main(void) {
  int vertices = 0, edges = 0;
  if (checkInput(&vertices, &edges))
    return 0;

  kruskal(&vertices, &edges);

  return 0;
}
