#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph {
  short begin;
  short end;
  unsigned weight;
  char used;
} Graph;

int checkInput(int* vertices,int* edges);
int checkEdges(short* begin, short* end, unsigned* weight,const int* vertices);
int createGraph(const int* vertices, const int* edges, Graph* graph);
void makeSet(const int* vertices, short* parents, short* rank);
short findSet(short* parents, short elem);
void mergeSet(short* rank, short* parents, short* begin, short* end);

#endif