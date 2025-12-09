// Options:   --seed 200122 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_122.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int32_t f0;
  int64_t f1;
  const uint16_t f2;
};

static int32_t g_13 = 5L;
static int32_t *g_12[1][4] = {{&g_13, &g_13, &g_13, &g_13}};
static float g_16 = 0x7.383CC4p-48;
static int16_t g_22 = 0x8182L;
static int32_t g_28 = 0xF2AB2BC8L;
static int32_t *volatile g_27 = &g_28;
static float g_31 = 0x0.3p+1;
static int64_t g_32 = 0x96BC712BAD479EA4LL;
static uint8_t g_34 = 252UL;

static int32_t func_1(void);
static int32_t *func_2(uint32_t p_3, int32_t *p_4, uint16_t p_5, int32_t *p_6,
                       int32_t *p_7);

static int32_t func_1(void) {
  struct S0 l_14 = {0x253A34C8L, 0x5B49D585ED065768LL, 0xA5A4L};
  int16_t *l_15[1][2];
  int32_t l_17 = 7L;
  int32_t *l_18 = (void *)0;
  int32_t **l_52 = &g_12[0][0];
  int16_t l_53[4][2] = {
      {(-8L), (-8L)}, {(-8L), (-8L)}, {(-8L), (-8L)}, {(-8L), (-8L)}};
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_15[i][j] = (void *)0;
  }
  (*l_52) = func_2(((safe_add_func_int8_t_s_s(
                        (safe_mul_func_int16_t_s_s(
                            (l_17 = (g_12[0][2] == (l_14, &g_13))), l_14.f1)),
                        l_14.f2)) > g_13),
                   l_18, g_13, l_18, &g_13);
  return l_53[0][0];
}

static int32_t *func_2(uint32_t p_3, int32_t *p_4, uint16_t p_5, int32_t *p_6,
                       int32_t *p_7) {
  int16_t *l_21 = &g_22;
  int32_t l_23 = 0x16EA3DE8L;
  int32_t *l_25 = &g_13;
  uint32_t l_42 = 0xD98A9A26L;
  int32_t **l_45 = (void *)0;
  int32_t l_48[1][3];
  uint64_t l_49 = 1UL;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_48[i][j] = 4L;
  }
  if ((l_23 = (safe_div_func_int16_t_s_s(((void *)0 != l_21), g_22)))) {
    int32_t *l_24 = &l_23;
    int32_t **l_26 = &g_12[0][1];
    (*l_26) = (l_25 = (l_24 = p_6));
    (*g_27) &= (*p_7);
  } else {
    uint8_t *l_33 = &g_34;
    int32_t *l_46 = &l_23;
    int32_t *l_47[2][4] = {{&g_28, &g_28, &g_28, &g_28},
                           {&g_28, &g_28, &g_28, &g_28}};
    int i, j;
    if ((((safe_mul_func_uint16_t_u_u(
              ((((*l_33)++) <= ((safe_rshift_func_uint16_t_u_u(
                                    (safe_add_func_int64_t_s_s(
                                        p_3, (((void *)0 != &p_4) ^ p_3))),
                                    g_28)),
                                p_5)) |
               g_28),
              0x1E1CL)) > (-4L)) <= g_13)) {
      p_6 = p_6;
    } else {
      int32_t *l_41[3];
      int i;
      for (i = 0; i < 3; i++)
        l_41[i] = &g_28;
      --l_42;
      (*g_27) &= ((*p_7) = (&g_12[0][2] != (l_45 = &p_7)));
    }
    --l_49;
  }
  return p_7;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  csmith_sink_ = g_16;
  csmith_sink_ = g_22;
  csmith_sink_ = g_28;
  csmith_sink_ = g_31;
  csmith_sink_ = g_32;
  csmith_sink_ = g_34;
  platform_main_end(0, 0);
  return 0;
}
