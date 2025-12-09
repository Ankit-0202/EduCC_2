// Options:   --seed 100051 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_051.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const uint16_t f0;
  const uint32_t f1;
};

struct S1 {
  struct S0 f0;
};

static int32_t g_3[4][2] = {{0x7161AB6EL, 0x7161AB6EL},
                            {0x7161AB6EL, 0x7161AB6EL},
                            {0x7161AB6EL, 0x7161AB6EL},
                            {0x7161AB6EL, 0x7161AB6EL}};

static struct S1 func_1(void);

static struct S1 func_1(void) {
  int32_t *l_2 = &g_3[3][1];
  int32_t *l_4[4];
  int8_t l_5 = 0xF7L;
  int64_t l_6[3][1];
  uint8_t l_7 = 0x9AL;
  struct S1 l_10[4] = {{{0xD7D9L, 4294967295UL}},
                       {{0xD7D9L, 4294967295UL}},
                       {{0xD7D9L, 4294967295UL}},
                       {{0xD7D9L, 4294967295UL}}};
  int i, j;
  for (i = 0; i < 4; i++)
    l_4[i] = &g_3[3][1];
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_6[i][j] = 0x0CB4E3473EDE5C48LL;
  }
  ++l_7;
  return l_10[2];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
