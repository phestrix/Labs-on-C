#ifndef GRAPH_H
#define GRAPH_H

unsigned* createGraph(int* N, int* M);
int checkInput(int* N, int* M, int* begin, int* end);
int fillMatrix(int* N, int* begin, int* end, unsigned* weight);
void checkOut(int* path,
              unsigned* shortestPath,
              unsigned* graph,
              int* begin,
              int* end,
              int* N);
unsigned checkOverflow(unsigned min, unsigned graph);

#endif