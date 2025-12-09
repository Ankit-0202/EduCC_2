// Options:   --seed 300275 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_275.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int16_t g_2[1] = {0xF606L};
static int32_t g_4 = 0x876E6BACL;
static uint32_t g_6[3][3] = {{0x3292C5EBL, 0x3292C5EBL, 0x87E08A11L},
                             {0x3292C5EBL, 0x3292C5EBL, 0x87E08A11L},
                             {0x3292C5EBL, 0x3292C5EBL, 0x87E08A11L}};

static int32_t func_1(void);

static int32_t func_1(void) {
  int32_t *l_3 = &g_4;
  int32_t *l_5[3];
  int i;
  for (i = 0; i < 3; i++)
    l_5[i] = &g_4;
  ++g_6[1][2];
  return g_2[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_4;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_6[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
