// Options:   --seed 100059 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_059.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  const volatile int16_t f1;
  uint32_t f2;
};

static int32_t g_11 = 0x735E4B78L;
static uint16_t g_13 = 0xB2ABL;
static int32_t g_28[1] = {0L};
static int32_t *volatile g_27 = &g_28[0];
static volatile struct S0 g_38 = {0UL, 0xBE4FL, 7UL};
static int64_t g_58 = 0xB361F3D49E3F4D67LL;
static int32_t *volatile g_59 = &g_28[0];

static uint32_t func_1(void);
static int16_t func_6(uint16_t p_7, const int64_t p_8);

static uint32_t func_1(void) {
  uint16_t *l_12 = &g_13;
  int32_t l_16 = 0xEC4F3F7EL;
  int32_t l_17 = 0xD62E6525L;
  if ((l_17 = (safe_rshift_func_int16_t_s_s(
           (safe_add_func_int16_t_s_s(
               func_6(((*l_12) = (safe_lshift_func_int8_t_s_u(g_11, 4))),
                      ((safe_mul_func_int8_t_s_s(
                           ((l_12 == (void *)0) <= 0x451DL), l_16)) <= l_17)),
               0xC6F9L)),
           g_11)))) {
    int8_t l_47 = 6L;
    int32_t l_48 = 0L;
    int32_t l_49[1][3];
    uint64_t l_50[1][3];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_49[i][j] = 6L;
    }
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_50[i][j] = 0x6F1A7E1F4FA7F9CDLL;
    }
    for (l_16 = 0; (l_16 == 1); l_16 = safe_add_func_int8_t_s_s(l_16, 3)) {
      int32_t *l_44 = &g_28[0];
      int32_t l_45 = (-10L);
      int32_t *l_46[3];
      int i;
      for (i = 0; i < 3; i++)
        l_46[i] = (void *)0;
      for (g_11 = 3; (g_11 != (-27));
           g_11 = safe_sub_func_uint64_t_u_u(g_11, 2)) {
        return g_28[0];
      }
      l_50[0][1]++;
    }
  } else {
    int64_t *l_57 = &g_58;
    (*g_59) = (safe_add_func_int8_t_s_s(
        ((safe_rshift_func_uint8_t_u_u(0UL, 1)) <=
         ((*l_57) ^= ((g_28[0] || g_11) && 18446744073709551607UL))),
        0x57L));
  }
  return l_16;
}

static int16_t func_6(uint16_t p_7, const int64_t p_8) {
  uint16_t *l_18[1][1];
  int32_t l_19 = 0L;
  uint64_t l_26[2][1];
  uint8_t l_39 = 1UL;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_18[i][j] = &g_13;
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_26[i][j] = 0x3AC25417612D29EDLL;
  }
  if ((((void *)0 != l_18[0][0]) == ((1UL || l_19) == l_19))) {
    int32_t l_22[3][3];
    uint16_t *l_25[4] = {&g_13, &g_13, &g_13, &g_13};
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++)
        l_22[i][j] = 0L;
    }
    (*g_27) |=
        ((safe_mul_func_int16_t_s_s(
             l_22[0][0],
             (((safe_add_func_int32_t_s_s((l_25[0] != &p_7), l_26[1][0])) ||
               p_7) ||
              l_22[2][0]))) &
         l_26[1][0]);
  } else {
    int32_t *l_30 = &g_28[0];
    int32_t **l_29 = &l_30;
    (*l_29) = (void *)0;
  }
  l_19 = (safe_mul_func_int16_t_s_s(
      (~((p_8 &
          (((safe_mul_func_uint8_t_u_u(
                l_19, (safe_div_func_int16_t_s_s((l_19 <= g_11), 0x9029L)))),
            g_38),
           l_39)) > g_28[0])),
      g_13));
  return g_38.f2;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  csmith_sink_ = g_13;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_28[i];
  }
  csmith_sink_ = g_38.f0;
  csmith_sink_ = g_38.f1;
  csmith_sink_ = g_38.f2;
  csmith_sink_ = g_58;
  platform_main_end(0, 0);
  return 0;
}
