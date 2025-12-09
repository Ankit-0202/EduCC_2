// Options:   --seed 200187 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_187.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  const int8_t *f0;
};

union U2 {
  volatile float f0;
  volatile uint16_t f1;
};

static int32_t g_2 = (-1L);
static int32_t g_12 = 0x5459EEDAL;
static union U1 g_18[3] = {{0}, {0}, {0}};
static int32_t *g_21 = &g_2;
static int32_t **volatile g_20 = &g_21;
static union U2 g_23 = {0xB.3659EAp+53};
static union U2 *g_27 = &g_23;

static int32_t func_1(void);
static int32_t *func_13(int64_t p_14);

static int32_t func_1(void) {
  uint64_t l_10[2];
  int i;
  for (i = 0; i < 2; i++)
    l_10[i] = 6UL;
  for (g_2 = 0; (g_2 >= 18); g_2 = safe_add_func_uint32_t_u_u(g_2, 9)) {
    int32_t *l_11 = &g_12;
    int64_t l_15 = 0L;
    union U2 *l_22 = &g_23;
    (*l_11) |= (safe_div_func_int8_t_s_s(
        ((safe_mul_func_uint8_t_u_u((~l_10[1]), 0xB7L)) ^ g_2), l_10[0]));
    if (l_10[1]) {
      if (g_12)
        break;
      (*g_20) = func_13(l_15);
    } else {
      union U2 **l_24 = &l_22;
      union U2 *l_26 = &g_23;
      union U2 **l_25 = &l_26;
      (*l_11) &= 0x8F3B8C10L;
      g_27 = ((*l_25) = ((*l_24) = l_22));
    }
  }
  return l_10[0];
}

static int32_t *func_13(int64_t p_14) {
  int32_t *l_19[3][4] = {{&g_12, &g_12, &g_12, &g_12},
                         {&g_12, &g_12, &g_12, &g_12},
                         {&g_12, &g_12, &g_12, &g_12}};
  int i, j;
  for (g_12 = 0; (g_12 > (-5)); g_12 = safe_sub_func_uint32_t_u_u(g_12, 8)) {
    for (p_14 = 2; (p_14 >= 0); p_14 -= 1) {
      if (g_2)
        break;
    }
  }
  return l_19[1][2];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_12;
  csmith_sink_ = g_23.f0;
  csmith_sink_ = g_23.f1;
  platform_main_end(0, 0);
  return 0;
}
