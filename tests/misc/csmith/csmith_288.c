// Options:   --seed 300288 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_288.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint16_t g_11 = 65535UL;
static int32_t g_21 = 0xFDDAE974L;
static uint64_t g_23[1][2] = {{0x0412894FF5452FA8LL, 0x0412894FF5452FA8LL}};
static int32_t g_25 = (-7L);
static int32_t *volatile g_24 = &g_25;
static uint64_t *g_30 = &g_23[0][0];

static int8_t func_1(void);
static int32_t func_2(int64_t p_3);
static uint16_t func_7(int32_t p_8, int32_t p_9, uint64_t p_10);

static int8_t func_1(void) {
  int64_t l_4[2];
  int32_t l_37 = 0x93F8DE90L;
  int i;
  for (i = 0; i < 2; i++)
    l_4[i] = (-1L);
  if (func_2(l_4[0])) {
    int32_t *l_20 = &g_21;
    uint64_t *l_22 = &g_23[0][1];
    (*g_24) = (g_21 &= (((*l_22) = ((void *)0 != l_20)) == 1L));
  } else {
    uint64_t *l_31 = &g_23[0][1];
    uint64_t **l_32 = &l_31;
    int32_t l_33[3];
    int32_t *l_34 = &g_21;
    int i;
    for (i = 0; i < 3; i++)
      l_33[i] = 0L;
    (*l_34) |=
        ((safe_sub_func_uint16_t_u_u(
             (2L || (safe_rshift_func_int16_t_s_s(
                        (((g_30 = (void *)0) != ((*l_32) = l_31)) && g_25),
                        g_23[0][0]))),
             0xD2F2L)) &&
         l_33[2]);
  }
  l_37 = (((l_4[0] <= l_4[0]), (safe_sub_func_uint16_t_u_u(3UL, l_4[1]))) |
          l_4[0]);
  return g_21;
}

static int32_t func_2(int64_t p_3) {
  int32_t *l_12[1];
  int32_t l_13 = (-1L);
  int32_t l_14[2];
  int32_t *l_16 = &l_13;
  int i;
  for (i = 0; i < 1; i++)
    l_12[i] = (void *)0;
  for (i = 0; i < 2; i++)
    l_14[i] = 0x4FD9E2A8L;
  (*l_16) = ((safe_mod_func_int8_t_s_s(
                 (func_7(g_11, (l_13 ^= p_3), l_14[1]), g_11), p_3)),
             p_3);
  if (g_11) {
    uint64_t l_19 = 0x3FAA32F3F6085E07LL;
    for (l_13 = (-24); (l_13 != (-24));
         l_13 = safe_add_func_int8_t_s_s(l_13, 8)) {
      return p_3;
    }
    if (g_11) {
      l_19 = g_11;
    } else {
      return p_3;
    }
  } else {
    return g_11;
  }
  return g_11;
}

static uint16_t func_7(int32_t p_8, int32_t p_9, uint64_t p_10) {
  uint16_t l_15 = 65529UL;
  return l_15;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  csmith_sink_ = g_21;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_23[i][j];
    }
  }
  csmith_sink_ = g_25;
  platform_main_end(0, 0);
  return 0;
}
