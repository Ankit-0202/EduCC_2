// Options:   --seed 100010 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_010.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile int32_t f0;
};

union U2 {
  struct S1 f0;
  volatile uint8_t f1;
};

static volatile uint32_t g_2 = 0x7E17F759L;
static int32_t g_4[1][1] = {{0xBB4EBB0CL}};
static const union U2 g_5 = {{-1L}};

static const union U2 func_1(void);

static const union U2 func_1(void) {
  int32_t *l_3 = &g_4[0][0];
  (*l_3) &= g_2;
  return g_5;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  csmith_sink_ = g_5.f0.f0;
  platform_main_end(0, 0);
  return 0;
}
