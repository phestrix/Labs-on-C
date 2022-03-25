#ifndef TREE_H
#define TREE_H
#include "bits_writing.h"
#include "heapify.h"
#include "structs.h"

Node *build_tree(Heap *heap, int *tab);
void write_tree(Bits_Writer *b_w, Node *root);
void free_tree(Node *root);
void read_tree(Bits_Reader *b_r, Node *root);

#endif  // TREE_H
