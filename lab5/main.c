#include <stdio.h>

#include "coder.h"

int main() {
  FILE *in = fopen("in.txt", "rb");
  fseek(in, 0L, SEEK_END);
  int par = ftell(in);
  fseek(in, 0L, SEEK_SET);
  if (par < 4) {
    fclose(in);
    return 0;
  }
  int code_or_decode = getc(in);
  getc(in);
  getc(in);
  FILE *out = fopen("out.txt", "wb");
  if (code_or_decode == 'c') {
    code(in, out);
  }
  if (code_or_decode == 'd') {
    decode(in, out);
  }
  fclose(in);
  fclose(out);
  return 0;
}
