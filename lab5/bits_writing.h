#ifndef BITS_WRITER_H
#define BITS_WRITER_H
#include "structs.h"

Bits_Writer *creates_bits_writer(FILE *file);
void add_bit(Bits_Writer *bw, int bit);
void write_bits(Bits_Writer *b_w);
void read_bits(Bits_Reader *b_r);
int get_bit(Bits_Reader *b_r);
Bits_Reader *create_bits_reader(FILE *file);
void byte_to_bits(int b, int *bits);
void bits_to_byte(int *b, int const *bits);

#endif  // AB5_FINAL_BITS_WRITER_H
