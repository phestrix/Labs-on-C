#ifndef HEAPIFY_H
#define HEAPIFY_H
#include "structs.h"

Heap *create_heap();
void heapify(Heap *heap, int i);
q_Node *pop(Heap *heap);
void push(Heap *heap, Node *node);
void free_heap(Heap *heap);
Node *create_node(int count, int chr, Node *left, Node *right);

#endif  // HEAPIFY_H
