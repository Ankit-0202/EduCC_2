// Options:   --seed 300290 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_290.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  int8_t f1;
};

union U2 {
  volatile struct S0 f0;
};

union U3 {
  int8_t f0;
};

static int64_t g_2 = 0xFAB8C3AD3B3152C5LL;
static int32_t g_4 = (-6L);
static volatile uint64_t g_5 = 0UL;
static uint8_t g_21[2] = {0x79L, 0x79L};
static volatile int32_t g_44 = 0L;
static struct S0 g_48 = {0xB818E961L, 0xAEL};
static struct S0 *g_49 = &g_48;
static struct S0 *g_50 = &g_48;
static struct S0 *g_51[2] = {&g_48, &g_48};
static struct S0 **volatile g_52[1][1] = {{(void *)0}};
static struct S0 **volatile g_53 = (void *)0;
static volatile union U2 g_55[1] = {{{4294967295UL, 1L}}};
static uint16_t g_57 = 0x56A9L;
static int32_t g_60 = (-2L);
static int64_t *const volatile g_62 = &g_2;
static int64_t *const volatile *volatile g_61 = &g_62;
static int64_t *volatile g_64[3] = {&g_2, &g_2, &g_2};
static uint64_t g_65[1] = {18446744073709551612UL};
static union U3 g_68 = {0L};

static union U3 func_1(void);
static int32_t func_14(int32_t p_15, int32_t *p_16);
static struct S0 *func_22(int8_t p_23, int32_t p_24);

static union U3 func_1(void) {
  int32_t *l_3[3][2];
  int64_t *l_19 = (void *)0;
  int64_t *l_20 = &g_2;
  int8_t *l_66 = (void *)0;
  int8_t *l_67 = &g_48.f1;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++)
      l_3[i][j] = &g_4;
  }
  --g_5;
  g_44 =
      ((safe_lshift_func_int8_t_s_s(
           (4294967288UL <= (safe_rshift_func_uint8_t_u_s(7UL, 3))),
           ((*l_67) = ((safe_div_func_int64_t_s_s(
                           (func_14((((*l_20) = (safe_rshift_func_int16_t_s_s(
                                          ((g_2 == g_4) < g_2), 9))) >=
                                     18446744073709551615UL),
                                    l_3[2][1]) != 0x8859B346L),
                           g_65[0])) ||
                       g_65[0])))) <= g_65[0]);
  return g_68;
}

static int32_t func_14(int32_t p_15, int32_t *p_16) {
  int64_t l_43 = 1L;
  int64_t *const volatile *volatile l_63 = &g_64[2];
  for (g_4 = 0; (g_4 <= 1); g_4 += 1) {
    uint16_t l_56 = 9UL;
    for (p_15 = 0; (p_15 <= 1); p_15 += 1) {
      int32_t l_45[3];
      struct S0 **l_54 = &g_51[1];
      int32_t *l_58 = &l_45[1];
      int32_t *l_59 = &g_60;
      int i;
      for (i = 0; i < 3; i++)
        l_45[i] = 0L;
      (*l_54) = func_22(
          (safe_add_func_uint8_t_u_u(
              ((safe_add_func_uint64_t_u_u(
                   (255UL |
                    ((safe_rshift_func_int16_t_s_u(
                         (0UL >=
                          ((safe_add_func_int64_t_s_s(
                               (safe_rshift_func_int8_t_s_u(
                                   ((safe_div_func_int32_t_s_s(
                                        (((safe_mod_func_int32_t_s_s(
                                              (safe_rshift_func_uint8_t_u_u(
                                                  (g_21[p_15] &= 255UL), p_15)),
                                              l_43)) == (-3L)),
                                         (*p_16)),
                                        g_44)) > (-1L)),
                                   p_15)),
                               p_15)) > l_45[1])),
                         l_43)) &
                     4294967295UL)),
                   l_45[1])) >= l_43),
              0L)),
          l_43);
      (*l_59) |= ((*l_58) &= (g_55[0], (g_57 = (l_56 = (*p_16)))));
    }
  }
  l_63 = g_61;
  return (*p_16);
}

static struct S0 *func_22(int8_t p_23, int32_t p_24) {
  struct S0 *l_47 = &g_48;
  struct S0 **l_46[3];
  int i;
  for (i = 0; i < 3; i++)
    l_46[i] = &l_47;
  g_51[0] = (g_50 = (g_49 = (void *)0));
  (*l_47) = (*l_47);
  return &g_48;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_21[i];
  }
  csmith_sink_ = g_44;
  csmith_sink_ = g_48.f0;
  csmith_sink_ = g_48.f1;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_57;
  csmith_sink_ = g_60;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_65[i];
  }
  csmith_sink_ = g_68.f0;
  platform_main_end(0, 0);
  return 0;
}
