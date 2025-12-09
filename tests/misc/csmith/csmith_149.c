// Options:   --seed 200149 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_149.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  const int32_t f0;
  int8_t *const volatile f1;
};

union U1 {
  uint8_t f0;
};

union U2 {
  int32_t f0;
  uint8_t f1;
};

static int32_t g_6 = 0x65425A80L;
static float g_13 = 0x0.9p+1;
static int64_t g_15 = (-3L);
static volatile float g_26[4][1] = {
    {0x1.Ep-1}, {0x1.Ep-1}, {0x1.Ep-1}, {0x1.Ep-1}};
static int16_t g_27 = 1L;
static volatile uint32_t g_28[3][1] = {
    {0x35DA2A0CL}, {0x35DA2A0CL}, {0x35DA2A0CL}};
static volatile int32_t g_38 = 0xA7FCC65AL;
static volatile int32_t *g_37 = &g_38;
static volatile int32_t **volatile g_36[3][1] = {{&g_37}, {&g_37}, {&g_37}};
static volatile int32_t **volatile *volatile g_39 = (void *)0;
static volatile int32_t **volatile *volatile g_40 = (void *)0;
static uint32_t g_54[2] = {1UL, 1UL};
static volatile union U0 g_63[2] = {{0xBB416C01L}, {0xBB416C01L}};
static union U1 g_67 = {255UL};
static union U1 *g_66[3][4] = {{&g_67, &g_67, &g_67, &g_67},
                               {&g_67, &g_67, &g_67, &g_67},
                               {&g_67, &g_67, (void *)0, &g_67}};
static union U0 g_70 = {1L};
static union U2 g_72 = {-5L};

static union U2 func_1(void);
static const union U2 *func_31(int32_t *p_32);

static union U2 func_1(void) {
  int32_t *l_2 = (void *)0;
  int32_t *l_3 = (void *)0;
  int32_t *l_4 = (void *)0;
  int32_t *l_5 = &g_6;
  int32_t *l_7 = &g_6;
  int32_t *l_8 = &g_6;
  int32_t *l_9 = &g_6;
  int32_t *l_10 = &g_6;
  int32_t *l_11 = &g_6;
  int32_t *l_12 = &g_6;
  int32_t *l_14 = &g_6;
  int32_t *l_16 = &g_6;
  int32_t l_17 = 0x8B1647C2L;
  int32_t *l_18 = &l_17;
  int32_t l_19 = (-1L);
  int32_t *l_20 = &l_17;
  int32_t *l_21 = &g_6;
  int32_t *l_22 = &g_6;
  int32_t *l_23 = &l_17;
  int32_t *l_24 = &l_17;
  int32_t *l_25[1];
  const union U2 *l_74[1][4] = {{&g_72, &g_72, &g_72, &g_72}};
  const union U2 **l_73 = &l_74[0][3];
  int i, j;
  for (i = 0; i < 1; i++)
    l_25[i] = &g_6;
  g_28[1][0]--;
  (*l_73) = func_31(&g_6);
  return g_72;
}

static const union U2 *func_31(int32_t *p_32) {
  int32_t *l_33 = (void *)0;
  int32_t **l_34 = &l_33;
  volatile int32_t **volatile l_42 = &g_37;
  const union U2 *l_71 = &g_72;
  if (((*p_32), (((*l_34) = l_33) != p_32))) {
    int64_t l_35[3];
    int i;
    for (i = 0; i < 3; i++)
      l_35[i] = 0L;
    if (((&g_6 != ((*l_34) = (void *)0)) >= l_35[2])) {
      volatile int32_t **volatile *l_41[4];
      int i;
      for (i = 0; i < 4; i++)
        l_41[i] = &g_36[2][0];
      l_42 = g_36[0][0];
    } else {
      const uint32_t l_43 = 4UL;
      (*p_32) |= l_43;
    }
  } else {
    int64_t l_46[4][2] = {{0x87B70D8AC507B392LL, 0x87B70D8AC507B392LL},
                          {0x87B70D8AC507B392LL, 0x87B70D8AC507B392LL},
                          {0x87B70D8AC507B392LL, 0x87B70D8AC507B392LL},
                          {0x87B70D8AC507B392LL, 0x87B70D8AC507B392LL}};
    int16_t *l_47 = &g_27;
    uint32_t *l_53 = &g_54[1];
    int16_t l_55 = 0xFC22L;
    int i, j;
    (*l_34) = p_32;
    if ((safe_rshift_func_int16_t_s_s(
            ((((((*l_47) = l_46[3][0]) ||
                ((safe_sub_func_uint32_t_u_u(
                     ((*l_53) = (safe_unary_minus_func_uint8_t_u((
                          ((safe_rshift_func_int16_t_s_u(
                               ((*l_47) = g_6), (0x13309E69L <= g_28[1][0]))) !=
                           (**l_34)) >= 0UL)))),
                     l_55)) &
                 (*p_32))) <= (**l_34)) != (*l_33)) == (*l_33)),
            2))) {
      const int32_t *l_60 = &g_6;
      float *l_64 = (void *)0;
      float *l_65 = &g_13;
      union U1 **l_68 = &g_66[0][3];
      (*l_65) =
          (((safe_sub_func_int16_t_s_s(
                ((*l_47) = (0x8EE72C95L &&
                            (safe_div_func_uint8_t_u_u(
                                ((l_60 !=
                                  ((safe_rshift_func_uint8_t_u_u(
                                       (((g_63[1], g_63[1]), l_55) || (*l_60)),
                                       l_46[3][1])),
                                   (void *)0)) > 0xC84DL),
                                9UL)))),
                0x1580L)) == g_54[0]),
           0xE.91F131p+58);
      (*l_68) = g_66[0][3];
    } else {
      (**l_34) ^= (~((-1L) <= (g_70, g_63[1].f0)));
    }
  }
  (**l_42) &= (*p_32);
  return l_71;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  csmith_sink_ = g_13;
  csmith_sink_ = g_15;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_26[i][j];
    }
  }
  csmith_sink_ = g_27;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_28[i][j];
    }
  }
  csmith_sink_ = g_38;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_54[i];
  }
  for (i = 0; i < 2; i++) {
  }
  csmith_sink_ = g_67.f0;
  csmith_sink_ = g_70.f0;
  csmith_sink_ = g_72.f0;
  csmith_sink_ = g_72.f1;
  platform_main_end(0, 0);
  return 0;
}
