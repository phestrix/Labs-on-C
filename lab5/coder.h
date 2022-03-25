#ifndef CODER_H
#define CODER_H
#include "structs.h"
#include "tree.h"

void init_code(Node *root, Code *codes, int *bits, int top);
int *init_freq(FILE *in);
int read_code(Bits_Reader *b_r, Node *root);
void code(FILE *in, FILE *out);
void decode(FILE *in, FILE *out);
void init_codes(Code *codes);
void deinit_code(Code *codes);
int *dupli(int *src, int len);
void write_code(Bits_Writer *b_w, FILE *in, Code *codes);

#endif  // AB5_FINAL_CODER_H
