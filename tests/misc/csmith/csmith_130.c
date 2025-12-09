// Options:   --seed 200130 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_130.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
};

static volatile int32_t g_3 = 0xFAB8C3ADL;
static int32_t g_4[4][1] = {
    {0x152C58FBL}, {0x152C58FBL}, {0x152C58FBL}, {0x152C58FBL}};
static int32_t g_5[3][1] = {{0x58A835A2L}, {0x58A835A2L}, {0x58A835A2L}};
static uint64_t g_14[2] = {0x64D64EA33A4D1B40LL, 0x64D64EA33A4D1B40LL};
static const uint64_t *g_16 = (void *)0;
static int32_t g_22 = 1L;
static int32_t g_24 = 0x1A0197CBL;
static int32_t *volatile g_23[1] = {&g_24};
static int32_t g_27[3] = {(-5L), (-5L), (-5L)};

static int32_t func_1(void);
static int32_t func_6(uint64_t p_7, int64_t p_8, int64_t p_9, uint64_t p_10);

static int32_t func_1(void) {
  struct S0 l_2[2] = {{1L}, {1L}};
  int32_t l_12 = 1L;
  int32_t l_28[3][1];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_28[i][j] = 0xE1289ED5L;
  }
  for (g_4[3][0] = 1; (g_4[3][0] >= 0); g_4[3][0] -= 1) {
    float l_29 = 0x1.7p+1;
    for (g_5[2][0] = 1; (g_5[2][0] >= 0); g_5[2][0] -= 1) {
      uint64_t *l_13 = &g_14[0];
      int32_t *l_26[2];
      uint8_t l_30 = 1UL;
      int i;
      for (i = 0; i < 2; i++)
        l_26[i] = &g_27[2];
      l_28[0][0] &= func_6(
          ((*l_13) = ((!((0xF62858905B8B78ACLL ||
                          (g_4[3][0], ((l_12 == 1UL) && l_12))) != g_4[3][0])),
                      1UL)),
          g_4[3][0], g_4[3][0], g_4[2][0]);
      l_30++;
    }
    for (g_22 = 1; (g_22 >= 0); g_22 -= 1) {
      uint32_t l_33 = 4294967287UL;
      if (l_33)
        break;
    }
  }
  return l_28[0][0];
}

static int32_t func_6(uint64_t p_7, int64_t p_8, int64_t p_9, uint64_t p_10) {
  const uint64_t **l_15[1][3];
  int32_t l_21 = 0xD743CCC0L;
  int32_t *l_25 = &g_24;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_15[i][j] = (void *)0;
  }
  (*l_25) |=
      ((g_16 = &g_14[0]) ==
       ((safe_mod_func_int32_t_s_s(
            ((safe_sub_func_uint16_t_u_u(
                 l_21,
                 (g_22 = ((((p_9, 0xCBEDL) | g_4[0][0]) == 8UL) >= 0x0136L)))) |
             0x50E8F7CFL),
            l_21)),
        (void *)0));
  return p_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_5[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_14[i];
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_24;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_27[i];
  }
  platform_main_end(0, 0);
  return 0;
}
