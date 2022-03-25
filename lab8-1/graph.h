#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph {
  short begin;
  short end;
  unsigned weight;
  char used;
} Graph;

int checkInput(int* vertices, int* edges);
int checkEdges(short* begin, short* end, unsigned* weight, const int* vertices);
int createGraph(Graph* graph, const int* edges, const int* vertices);
void printAnswer(Graph* graph, const int* edges);

#endif