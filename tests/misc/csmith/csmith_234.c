// Options:   --seed 300234 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_234.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int8_t f0;
  uint32_t f1;
  volatile uint64_t f2;
};

union U1 {
  const volatile int32_t f0;
  int64_t f1;
};

union U2 {
  int16_t f0;
  int8_t *volatile f1;
};

static int8_t g_11 = 0x27L;
static int8_t *g_10 = &g_11;
static int8_t g_32 = 7L;
static int32_t g_35 = (-1L);
static union U1 g_42[3][1] = {
    {{0x14A12652L}}, {{0x14A12652L}}, {{0x14A12652L}}};
static union U2 g_48 = {0x4956L};
static struct S0 g_54 = {2L, 0xEEDA7DA9L, 0xC5C2DA50E28AB82ALL};
static int8_t g_55[3] = {0x99L, 0x99L, 0x99L};
static int16_t g_57 = 0x12CBL;

static int32_t func_1(void);
static struct S0 func_7(int8_t *p_8, uint32_t p_9);
static union U1 *func_15(uint8_t p_16);

static int32_t func_1(void) {
  uint32_t l_12[3][3] = {{0UL, 0UL, 0UL},
                         {0x501874DAL, 0x501874DAL, 0x501874DAL},
                         {0UL, 0UL, 0UL}};
  int32_t *l_56[3];
  int i, j;
  for (i = 0; i < 3; i++)
    l_56[i] = &g_35;
  g_57 = ((safe_add_func_uint16_t_u_u(
              (g_55[0] &=
               (((!((safe_mul_func_int16_t_s_s(
                        (func_7(g_10, l_12[2][0]), g_54.f2), l_12[2][0])) &&
                    g_54.f0)) == 0xB037L) <= 0xDB28543BL)),
              l_12[2][0])) &
          l_12[2][0]);
  return g_35;
}

static struct S0 func_7(int8_t *p_8, uint32_t p_9) {
  for (p_9 = 0; (p_9 <= 55); p_9++) {
    int8_t *l_17 = &g_11;
    int32_t l_22 = 0xA41B8700L;
    int16_t l_23 = 0xA3BDL;
    union U1 *l_53 = &g_42[0][0];
    union U1 **l_52 = &l_53;
    (*l_52) = func_15(
        (((((void *)0 == l_17) &&
           (safe_add_func_int8_t_s_s(
               (safe_rshift_func_uint16_t_u_s(((void *)0 != l_17), p_9)),
               (-1L)))) &&
          l_22) |
         l_23));
  }
  return g_54;
}

static union U1 *func_15(uint8_t p_16) {
  uint32_t l_33[1][3];
  union U1 *const l_41 = &g_42[0][0];
  union U1 *const *l_40 = &l_41;
  int32_t *l_49 = (void *)0;
  int32_t **l_50 = &l_49;
  union U1 *l_51 = &g_42[2][0];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_33[i][j] = 0x2C80F3BBL;
  }
  for (g_11 = 0; (g_11 <= 27); g_11++) {
    int8_t *l_31[3][1];
    int32_t *l_34 = &g_35;
    int32_t l_39 = 1L;
    union U1 *l_44 = &g_42[1][0];
    union U1 *const *l_43 = &l_44;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_31[i][j] = &g_32;
    }
    (*l_34) |= ((l_33[0][0] = (safe_div_func_uint64_t_u_u(
                     (safe_add_func_uint8_t_u_u(((~4294967295UL) <= p_16),
                                                (0x9E4A0435L != g_11))),
                     0xFF846C8C5CECCE00LL))) ^
                p_16);
    if ((safe_sub_func_int8_t_s_s(p_16, (+l_39)))) {
      int16_t l_47 = (-8L);
      l_43 = l_40;
      (*l_34) = (safe_div_func_uint16_t_u_u((*l_34), l_47));
    } else {
      (*l_34) = (g_48, 0x847726B4L);
      if ((*l_34))
        break;
    }
  }
  (*l_50) = l_49;
  return l_51;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  csmith_sink_ = g_32;
  csmith_sink_ = g_35;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
    }
  }
  csmith_sink_ = g_48.f0;
  csmith_sink_ = g_54.f0;
  csmith_sink_ = g_54.f1;
  csmith_sink_ = g_54.f2;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_55[i];
  }
  csmith_sink_ = g_57;
  platform_main_end(0, 0);
  return 0;
}
