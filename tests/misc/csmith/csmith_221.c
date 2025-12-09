// Options:   --seed 300221 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_221.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int16_t f0;
  volatile uint32_t f1;
  uint16_t f2;
};

static int32_t g_13 = (-1L);
static volatile int64_t g_14 = 0L;
static uint32_t g_16 = 1UL;
static uint8_t g_18 = 9UL;
static struct S1 g_21 = {0xEBD0L, 0x4DDE9AB5L, 0UL};

static struct S1 func_1(void);

static struct S1 func_1(void) {
  int16_t *l_12[1][1];
  int32_t l_15 = 0x6D39C7C6L;
  int32_t *l_17 = &l_15;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_12[i][j] = (void *)0;
  }
  (*l_17) =
      ((safe_rshift_func_int8_t_s_u(
           (safe_unary_minus_func_uint8_t_u((safe_div_func_int16_t_s_s(
               (+(safe_div_func_uint16_t_u_u(
                   (safe_rshift_func_int16_t_s_s((g_13 = (-1L)), 11)), g_14))),
               (l_15, 0xDBD0L))))),
           7)) < g_16);
  --g_18;
  return g_21;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  csmith_sink_ = g_14;
  csmith_sink_ = g_16;
  csmith_sink_ = g_18;
  csmith_sink_ = g_21.f0;
  csmith_sink_ = g_21.f1;
  csmith_sink_ = g_21.f2;
  platform_main_end(0, 0);
  return 0;
}
