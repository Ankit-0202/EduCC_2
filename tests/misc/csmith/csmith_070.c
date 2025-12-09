// Options:   --seed 100070 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_070.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  int32_t f0;
  int8_t *f1;
};

static volatile int8_t g_9 = 0L;
static union U1 g_11 = {0x8872FA4AL};
static int32_t g_13[3][4] = {
    {0xAE4B9A73L, 0xAE4B9A73L, 0xAE4B9A73L, 0xAE4B9A73L},
    {0xAE4B9A73L, 0xAE4B9A73L, 0xAE4B9A73L, 0xAE4B9A73L},
    {0xAE4B9A73L, 0xAE4B9A73L, 0xAE4B9A73L, 0xAE4B9A73L}};
static int32_t *volatile g_12 = &g_13[0][2];
static int16_t g_21 = 0x4BAEL;
static int32_t *volatile g_22 = (void *)0;
static int32_t *volatile g_23 = (void *)0;
static int32_t *volatile g_24 = &g_13[0][2];

static uint32_t func_1(void);
static int32_t *func_2(int8_t p_3, uint8_t p_4, int16_t p_5, int8_t *p_6);

static uint32_t func_1(void) {
  int8_t l_10 = 0x41L;
  int32_t *l_26 = &g_13[2][2];
  l_26 = func_2((safe_mod_func_int16_t_s_s(g_9, l_10)), (g_11, l_10), g_11.f0,
                &l_10);
  return (*l_26);
}

static int32_t *func_2(int8_t p_3, uint8_t p_4, int16_t p_5, int8_t *p_6) {
  int32_t *l_25 = &g_13[1][1];
  (*g_12) ^= g_11.f0;
  for (p_3 = 0; (p_3 <= 12); p_3++) {
    uint64_t *l_19 = (void *)0;
    uint64_t *l_20 = (void *)0;
    (*g_24) =
        ((~p_3) > (g_21 = (safe_sub_func_int8_t_s_s(g_13[0][1], g_13[0][2]))));
  }
  return l_25;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_11.f0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_13[i][j];
    }
  }
  csmith_sink_ = g_21;
  platform_main_end(0, 0);
  return 0;
}
