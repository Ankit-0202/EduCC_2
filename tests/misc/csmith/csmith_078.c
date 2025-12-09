// Options:   --seed 100078 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_078.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_18 = 4L;
static uint16_t g_20 = 0UL;
static int32_t g_21 = 0L;
static int16_t g_26[2][4] = {{(-1L), (-1L), (-1L), (-1L)},
                             {(-1L), (-1L), (-1L), (-1L)}};
static int32_t g_28 = 0x294B58FEL;
static int32_t *volatile g_27 = &g_28;

static const uint64_t func_1(void);
static int32_t func_2(const int32_t p_3, uint16_t p_4);

static const uint64_t func_1(void) {
  uint8_t l_9 = 1UL;
  uint32_t *l_19[1];
  int32_t l_22 = (-1L);
  int32_t *l_24 = &g_21;
  int16_t *l_25 = &g_26[1][2];
  int i;
  for (i = 0; i < 1; i++)
    l_19[i] = (void *)0;
  (*l_24) = func_2(
      (safe_mod_func_uint64_t_u_u(
          ((safe_sub_func_int32_t_s_s(
               l_9,
               ((((safe_rshift_func_int8_t_s_u(
                      ((g_20 =
                            (l_9 &
                             ((safe_sub_func_uint64_t_u_u(
                                  (safe_rshift_func_uint8_t_u_s(
                                      (((safe_sub_func_int64_t_s_s(
                                            ((l_9 == l_9) | 0x60A22152L), l_9)),
                                        0x348F4A8FE24307A3LL) <= l_9),
                                      2)),
                                  l_9)) <= g_18))) &&
                       0L),
                      l_9)) > l_9) <= g_21) &
                7L))) == 1UL),
          l_22)),
      l_22);
  (*g_27) ^= (((*l_25) = (-1L)), (g_20, g_21));
  return (*l_24);
}

static int32_t func_2(const int32_t p_3, uint16_t p_4) {
  uint32_t l_23 = 0xCDF8ABFFL;
  return l_23;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_18;
  csmith_sink_ = g_20;
  csmith_sink_ = g_21;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_26[i][j];
    }
  }
  csmith_sink_ = g_28;
  platform_main_end(0, 0);
  return 0;
}
