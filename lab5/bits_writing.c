#include "bits_writing.h"

#include <stdlib.h>
#include <string.h>

Bits_Writer *creates_bits_writer(FILE *file) {
  Bits_Writer *bw = malloc(sizeof(Bits_Writer));
  bw->file = file;
  bw->id = 0;
  return bw;
}

void add_bit(Bits_Writer *bw, int bit) {
  bw->buff[bw->id++] = bit;
  if (bw->id == 8) {
    write_bits(bw);
    bw->id = 0;
  }
}

void write_bits(Bits_Writer *b_w) {
  int byte = 0;
  for (int i = 0; i < 8; i++) {
    byte <<= 1;
    byte += b_w->buff[i];
  }

  fputc(byte, b_w->file);
  memset(b_w->buff, 0, sizeof(b_w->buff));
}

void read_bits(Bits_Reader *b_r) {
  memset(b_r->buff, 0, sizeof(b_r->buff));
  int c;
  if ((c = getc(b_r->file)) == EOF) return;
  byte_to_bits(c, b_r->buff);
}

int get_bit(Bits_Reader *b_r) {
  int bit = b_r->buff[(b_r->id++) % 8];
  if (!(b_r->id % 8)) {
    read_bits(b_r);
  }
  return bit;
}

Bits_Reader *create_bits_reader(FILE *file) {
  Bits_Reader *br = malloc(sizeof(Bits_Reader));
  br->file = file;
  br->id = 0;
  read_bits(br);
  return br;
}
void byte_to_bits(int b, int *bits) {
  for (int i = 0; i < 8; i++) {
    bits[i] = (b & (1 << 7)) ? 1 : 0;
    b <<= 1;
  }
}

void bits_to_byte(int *b, const int *bits) {
  *b = 0;
  for (int i = 0; i < 8; i++) {
    *b <<= 1;
    *b += bits[i];
  }
}
