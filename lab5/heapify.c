#include "heapify.h"

#include <stdlib.h>
#define MAGIC_CONST 1024

static void swap(q_Node **a, q_Node **b) {
  q_Node *tmp = *a;
  *a = *b;
  *b = tmp;
}

Heap *create_heap() {
  Heap *heap = malloc(sizeof(Heap));
  if (!heap) return NULL;
  heap->heap_size = 0;
  heap->arr = malloc(sizeof(q_Node) * MAGIC_CONST);
  return heap;
}

void heapify(Heap *heap, int i) {
  int l = ((2 * i) < MAGIC_CONST) && (i >= 1) ? 2 * i : -1;
  int r = (((2 * i) + 1) < MAGIC_CONST) && (i >= 1) ? (2 * i) + 1 : -1;
  int m = i;
  if ((l <= heap->heap_size) && (l > 0)) {
    if (heap->arr[l]->priority < heap->arr[m]->priority) {
      m = l;
    }
  }
  if ((r <= heap->heap_size && (r > 0))) {
    if (heap->arr[r]->priority < heap->arr[m]->priority) {
      m = r;
    }
  }
  if (m != i) {
    swap(&heap->arr[i], &heap->arr[m]);
    heapify(heap, m);
  }
}

q_Node *pop(Heap *heap) {
  q_Node *m = heap->arr[1];
  heap->arr[1] = heap->arr[heap->heap_size--];
  heapify(heap, 1);
  return m;
}

void push(Heap *heap, Node *node) {
  heap->arr[++heap->heap_size] = malloc(sizeof(q_Node));
  heap->arr[heap->heap_size]->data = node;
  heap->arr[heap->heap_size]->priority = node->count;
  int i = heap->heap_size, p = (i > 1) && (i < MAGIC_CONST) ? i / 2 : -1;
  while ((i > 1) && (heap->arr[p]->priority > heap->arr[i]->priority)) {
    swap(&heap->arr[i], &heap->arr[p]);
    i = p;
    p = (i > 1) && (i < MAGIC_CONST) ? i / 2 : -1;
  }
}

void free_heap(Heap *heap) {
  for (int i = 0; i < heap->heap_size; i++) {
    free(heap->arr[i]);
  }
  free(heap->arr);
  free(heap);
}

Node *create_node(int count, int chr, Node *left, Node *right) {
  Node *ctx = malloc(sizeof(Node));
  ctx->count = count;
  ctx->chr = chr;
  ctx->left = left;
  ctx->right = right;
  return ctx;
}
