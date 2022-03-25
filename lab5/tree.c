#include "tree.h"

#include <stdlib.h>

void write_tree(Bits_Writer* b_w, Node* root) {
  if (!root->left && !root->right) {
    add_bit(b_w, 0);
    int d = root->chr;
    for (int i = 0; i < 8; ++i) {
      add_bit(b_w, (d & (1U << 7)) ? 1 : 0);
      d <<= 1;
    }
    return;
  }
  add_bit(b_w, 1);

  write_tree(b_w, root->left);
  write_tree(b_w, root->right);
}
Node* build_tree(Heap* heap, int* tab) {
  for (int i = 0; i < 256; ++i) {
    if (tab[i]) {
      Node* node = create_node(tab[i], i, NULL, NULL);
      push(heap, node);
    }
  }
  if (heap->heap_size == 1) {
    return pop(heap)->data;
  }
  while (heap->heap_size > 1) {
    Node* n1 = pop(heap)->data;
    Node* n2 = pop(heap)->data;
    Node* n = create_node(n1->count + n2->count, 256, n1, n2);
    push(heap, n);
  }
  return pop(heap)->data;
}

void free_tree(Node* root) {
  if (root == NULL) {
    return;
  }
  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

void read_tree(Bits_Reader* b_r, Node* root) {
  int bit = get_bit(b_r);

  if (bit == 0) {
    int byte, bits[8];
    for (int i = 0; i < 8; i++) {
      bits[i] = get_bit(b_r);
    }
    bits_to_byte(&byte, bits);
    root->chr = byte;
    return;
  } else if (bit == 1) {
    root->left = create_node(0, 256, NULL, NULL);
    read_tree(b_r, root->left);

    root->right = create_node(0, 256, NULL, NULL);
    read_tree(b_r, root->right);
  }
}
