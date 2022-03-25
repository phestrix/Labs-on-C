#include "coder.h"

#include <stdlib.h>
#include <string.h>

int* init_freq(FILE* in) {
  int* tab = calloc(256, sizeof(int));
  int c;
  while ((c = getc(in)) != EOF) {
    tab[c]++;
  }
  return tab;
}

void init_code(Node* root, Code* codes, int* bits, int top) {
  if (root->left) {
    bits[top] = 0;
    init_code(root->left, codes, bits, top + 1);
  }
  if (root->right) {
    bits[top] = 1;
    init_code(root->right, codes, bits, top + 1);
  }
  if (!root->left && !root->right) {
    top = top ? top : 1;
    codes[root->chr].bits = dupli(bits, top);
    codes[root->chr].len = top ? top : 1;
  }
}

int read_code(Bits_Reader* b_r, Node* root) {
  int bit = get_bit(b_r);
  if (!root->left && !root->right) {
    return root->chr;
  }
  if (bit) {
    if (root->right && root->right->chr != 256) return root->right->chr;
    return read_code(b_r, root->right);
  } else {
    if (root->left && root->left->chr != 256) return root->left->chr;
    return read_code(b_r, root->left);
  }
}

void code(FILE* in, FILE* out) {
  size_t inPos = ftell(in);
  Heap* heap = create_heap();
  if (!heap) return;
  int* tab = init_freq(in);
  if (!tab) {
    free(heap);
    return;
  }

  Node* root = build_tree(heap, tab);
  if (!root) {
    free(tab);
    free(heap);
    return;
  }
  int bits[256] = {0}, top = 0;
  Code codes[256];
  init_codes(codes);
  init_code(root, codes, bits, top);
  fseek(in, inPos, SEEK_SET);
  Bits_Writer* bw = creates_bits_writer(out);
  if (!bw) {
    free(tab);
    free(heap);
    free(root);
    return;
  }

  write_tree(bw, root);
  write_code(bw, in, codes);
  int R = (8 - bw->id) % 8;
  while (bw->id % 8) {
    add_bit(bw, 0);
  }
  fputc(R, out);
  free_heap(heap);
  free(tab);
  free_tree(root);
  deinit_code(codes);
  free(bw);
}

void decode(FILE* in, FILE* out) {
  Bits_Reader* b_r = create_bits_reader(in);
  if (!b_r) return;

  fseek(in, 0L, SEEK_END);
  b_r->size = ftell(in) - 3;
  fseek(in, -1L, SEEK_END);
  b_r->byte = getc(in);
  fseek(in, 4L, SEEK_SET);

  Node* root = create_node(0, 256, NULL, NULL);
  if (!root) return;
  read_tree(b_r, root);
  while (b_r->id < (b_r->size * 8) - b_r->byte - 8) {
    int tmp = read_code(b_r, root);
    fputc(tmp, out);
  }
  free(b_r);
  free_tree(root);
}

void init_codes(Code* codes) {
  for (int i = 0; i < 256; i++) {
    codes[i].len = 0;
  }
}

void deinit_code(Code* codes) {
  for (int i = 0; i < 256; i++) {
    if (codes[i].len) {
      free(codes[i].bits);
    }
  }
}

int* dupli(int* src, int len) {
  int* p = malloc(len * sizeof(int));
  memcpy(p, src, len * sizeof(int));
  return p;
}

void write_code(Bits_Writer* b_w, FILE* in, Code* codes) {
  int c;
  while ((c = getc(in)) != EOF) {
    for (int j = 0; j < codes[c].len; j++) {
      add_bit(b_w, codes[c].bits[j]);
    }
  }
}
