// Options:   --seed 300240 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_240.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
};

struct S2 {
  uint64_t f0;
  uint16_t f1;
};

static struct S2 g_9 = {18446744073709551611UL, 0UL};
static struct S0 g_11[1][3] = {{{0xB4EF66B1L}, {0xB4EF66B1L}, {0xB4EF66B1L}}};
static int32_t g_14 = 0x7C7AB89BL;

static struct S2 func_1(void);
static int32_t func_2(int16_t p_3, int16_t p_4, const uint64_t p_5);
static uint32_t func_7(struct S2 p_8);

static struct S2 func_1(void) {
  uint64_t l_6 = 18446744073709551613UL;
  int32_t *l_13 = &g_14;
  (*l_13) |= func_2(l_6, (((func_7(g_9), (-8L)) && g_9.f1) <= 1UL), g_9.f0);
  (*l_13) = (*l_13);
  return g_9;
}

static int32_t func_2(int16_t p_3, int16_t p_4, const uint64_t p_5) {
  struct S0 *l_10 = &g_11[0][2];
  struct S0 **l_12 = &l_10;
  (*l_12) = l_10;
  return p_4;
}

static uint32_t func_7(struct S2 p_8) { return g_9.f1; }

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9.f0;
  csmith_sink_ = g_9.f1;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  csmith_sink_ = g_14;
  platform_main_end(0, 0);
  return 0;
}
