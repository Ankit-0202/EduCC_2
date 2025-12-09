// Options:   --seed 100095 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_095.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_2 = 18446744073709551607UL;
static int8_t g_15[2] = {0L, 0L};
static uint8_t g_18[1][1] = {{253UL}};
static int32_t g_21[3] = {(-1L), (-1L), (-1L)};
static int32_t *g_23 = &g_21[2];
static int32_t **volatile g_22 = &g_23;
static int32_t *g_24 = &g_21[2];

static int8_t func_1(void);
static int32_t *func_5(uint64_t p_6);

static int8_t func_1(void) {
  int8_t *l_14[1];
  int32_t l_16 = (-10L);
  uint8_t *l_17[4][2] = {{(void *)0, (void *)0},
                         {(void *)0, (void *)0},
                         {(void *)0, (void *)0},
                         {(void *)0, (void *)0}};
  uint16_t l_19[1];
  int32_t **l_25 = &g_23;
  int i, j;
  for (i = 0; i < 1; i++)
    l_14[i] = &g_15[1];
  for (i = 0; i < 1; i++)
    l_19[i] = 0xBE02L;
  g_2++;
  (*l_25) =
      func_5(((safe_rshift_func_int16_t_s_s(
                  g_2, (safe_sub_func_uint32_t_u_u(
                           (safe_div_func_uint8_t_u_u(
                               (safe_unary_minus_func_int8_t_s((l_16 = g_2))),
                               (g_18[0][0] = g_2))),
                           l_19[0])))) &
              l_19[0]));
  return (**l_25);
}

static int32_t *func_5(uint64_t p_6) {
  int32_t *l_20[2][4] = {{&g_21[2], &g_21[2], &g_21[2], &g_21[2]},
                         {&g_21[2], &g_21[2], &g_21[2], &g_21[2]}};
  int i, j;
  (*g_22) = l_20[1][0];
  return g_24;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_15[i];
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_18[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_21[i];
  }
  platform_main_end(0, 0);
  return 0;
}
