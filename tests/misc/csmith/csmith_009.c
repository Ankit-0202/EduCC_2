// Options:   --seed 100009 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_009.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint8_t g_10 = 0xA0L;
static int32_t g_13[2] = {1L, 1L};

static int32_t func_1(void);
static int32_t *func_2(int8_t p_3, int32_t *p_4, int32_t *p_5, int32_t *p_6);

static int32_t func_1(void) {
  uint64_t l_9 = 0x47A6DEEC54165132LL;
  int32_t *l_12 = &g_13[1];
  int32_t **l_11 = &l_12;
  const int32_t *l_14 = (void *)0;
  int32_t *l_15 = &g_13[0];
  (*l_11) =
      func_2((safe_lshift_func_uint16_t_u_u(
                 (l_9 >= g_10), ((((*l_11) = (void *)0) == l_14), 65533UL))),
             &g_13[1], l_15, &g_13[1]);
  for (g_10 = 0; (g_10 <= 1); g_10 += 1) {
    int i;
    return g_13[g_10];
  }
  return (**l_11);
}

static int32_t *func_2(int8_t p_3, int32_t *p_4, int32_t *p_5, int32_t *p_6) {
  int32_t *l_16 = &g_13[1];
  int32_t *l_17 = (void *)0;
  int32_t l_18[1][2];
  int32_t *l_19[1];
  int16_t l_20 = 0x3FF6L;
  uint8_t l_21 = 0xB5L;
  int32_t *l_24 = &l_18[0][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_18[i][j] = 0xCB5542AFL;
  }
  for (i = 0; i < 1; i++)
    l_19[i] = &g_13[1];
  l_21--;
  return p_6;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_10;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_13[i];
  }
  platform_main_end(0, 0);
  return 0;
}
