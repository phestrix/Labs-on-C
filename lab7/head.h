#ifndef HEAD_H
#define HEAD_H

int input(int* vertices, int* edges);
int inputEdges(const int* vertices, int* src, int* dst);
int createGraph(const int* vertices, const int* edges, char* graph);
void printGraph(short* graph, const int* vertices);
void fillRes(short* graph, const int* vertices);
int checkVert(char* matrix, char* extra, const int* count, const int v);
int dfs(char* matrix, short* res, char* extra, int* count, const int* countV);
int topSort(char* matrix, const int* countV);
int doTopSort(int* vertices, int* edges);

#endif