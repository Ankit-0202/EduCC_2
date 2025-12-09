// Options:   --seed 300297 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_297.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint8_t f0;
  const int64_t f1;
};

union U1 {
  volatile uint32_t f0;
};

static int32_t *volatile g_5[1][1] = {{(void *)0}};
static int32_t g_7 = 0x6C74AA0DL;
static int32_t *volatile g_6 = &g_7;
static union U1 g_11 = {0x53061ECEL};
static int8_t g_13 = 0xCDL;
static uint64_t g_22[1][3] = {{9UL, 9UL, 9UL}};
static uint8_t g_27 = 0x7BL;
static int32_t *volatile g_29 = &g_7;
static const int32_t *g_34 = &g_7;
static const int32_t **g_33 = &g_34;
static const int32_t ***volatile g_32[2] = {&g_33, &g_33};
static int64_t g_50 = (-1L);
static int32_t *volatile g_52[1][3] = {{(void *)0, (void *)0, (void *)0}};
static int32_t g_77 = (-8L);
static int32_t *volatile g_76 = &g_77;

static uint32_t func_1(void);
static int32_t *func_2(const uint32_t p_3);
static union U1 func_9(int32_t *p_10);

static uint32_t func_1(void) {
  const uint32_t l_4 = 0xCD53BC6EL;
  int32_t *l_79 = &g_77;
  l_79 = func_2(l_4);
  return (*l_79);
}

static int32_t *func_2(const uint32_t p_3) {
  int8_t *l_12[1][3];
  int32_t l_14[3];
  int32_t l_15[2][2] = {{1L, 1L}, {1L, 1L}};
  uint32_t l_28 = 0xA88FF767L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_12[i][j] = &g_13;
  }
  for (i = 0; i < 3; i++)
    l_14[i] = 1L;
  (*g_6) &= p_3;
  if ((((((~(func_9(&g_7), (l_14[1] = 0L))) || l_14[0]) ^ l_15[1][0]) > g_13) >
       0x73D5L)) {
    uint64_t *l_21[2][1];
    int32_t l_23[2];
    uint8_t *l_26 = &g_27;
    const int32_t *l_31 = &l_14[1];
    const int32_t **l_30[1][1];
    const uint16_t l_46[1] = {1UL};
    int64_t l_48 = 0xAE22781501494D85LL;
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_21[i][j] = &g_22[0][0];
    }
    for (i = 0; i < 2; i++)
      l_23[i] = 0xCA4F0670L;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_30[i][j] = &l_31;
    }
    (*g_29) =
        ((((safe_unary_minus_func_int8_t_s(
               ((safe_rshift_func_int16_t_s_s(
                    (((l_23[1] = (safe_rshift_func_int8_t_s_s(0x5EL, p_3))) &&
                      (((*l_26) = (safe_lshift_func_uint8_t_u_u(0x3FL, 2))),
                       p_3)) ||
                     l_14[0]),
                    10)) ^
                g_22[0][0]))) < p_3),
          g_27) < l_28);
    if ((*g_29)) {
      const int32_t ***l_35 = &g_33;
      uint64_t l_47 = 0xE864ADB5D2300B63LL;
      int64_t *l_49 = &g_50;
      int32_t *l_51 = &l_15[1][0];
      (*l_35) = l_30[0][0];
      (*l_51) ^=
          (((*l_49) |=
            ((safe_sub_func_int64_t_s_s(
                 (safe_div_func_uint16_t_u_u(
                     0UL, (safe_rshift_func_int8_t_s_s(
                              (safe_div_func_int64_t_s_s(
                                  (safe_div_func_int64_t_s_s(
                                      (g_22[0][0] &
                                       ((l_46[0] < 0xE2B783560277ED46LL) >=
                                        65527UL)),
                                      g_13)),
                                  l_47)),
                              1)))),
                 p_3)) > l_48)) &&
           18446744073709551607UL);
    } else {
      int32_t *l_53 = &l_23[1];
      int32_t *l_54[1][2];
      uint32_t l_55 = 0x33B15185L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++)
          l_54[i][j] = (void *)0;
      }
      (*l_53) &= (&g_50 == ((0L >= (l_14[2] == 2UL)), &g_50));
      l_55++;
    }
  } else {
    int16_t l_62 = 0x0D4FL;
    uint8_t *l_75 = &g_27;
    if ((safe_mod_func_uint16_t_u_u(
            (safe_rshift_func_int8_t_s_u((l_62 == p_3), p_3)), 65527UL))) {
      union U0 l_67 = {0x73L};
      uint8_t *l_68[1];
      int32_t *l_73 = &g_7;
      int i;
      for (i = 0; i < 1; i++)
        l_68[i] = &g_27;
      (*l_73) |= (safe_sub_func_uint64_t_u_u(
          ((l_14[2] ||
            ((l_67, (g_27++)) !=
             (safe_rshift_func_uint8_t_u_u(
                 (((g_11, g_22[0][0]) != 0xFCL), l_15[1][0]), g_50)))),
           p_3),
          p_3));
      (*g_76) ^=
          (((p_3 == (+(((*l_73), l_75) == (void *)0))) != l_14[1]) && (*l_73));
    } else {
      int32_t *l_78 = &g_77;
      (*g_33) = l_78;
    }
  }
  return &g_7;
}

static union U1 func_9(int32_t *p_10) {
  (*p_10) ^= 0xD1B9849BL;
  return g_11;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_11.f0;
  csmith_sink_ = g_13;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_22[i][j];
    }
  }
  csmith_sink_ = g_27;
  csmith_sink_ = g_50;
  csmith_sink_ = g_77;
  platform_main_end(0, 0);
  return 0;
}
