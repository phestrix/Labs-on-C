#pragma once
#include <stdio.h>

typedef struct Node {
  int count;
  int chr;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct q_Node {
  Node *data;
  int priority;
} q_Node;

typedef struct Heap {
  q_Node **arr;
  int heap_size;
} Heap;

typedef struct Code {
  int *bits;
  int len;
} Code;

typedef struct Bits_Writer {
  FILE *file;
  int buff[8];
  int id;
} Bits_Writer;

typedef struct Bits_Reader {
  FILE *file;
  int buff[8];
  int id;
  int size;
  int byte;
} Bits_Reader;
