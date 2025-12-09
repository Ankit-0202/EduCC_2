// Options:   --seed 300238 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_238.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U2 {
  const uint16_t f0;
  uint32_t f1;
};

union U4 {
  volatile uint64_t f0;
};

union U5 {
  uint16_t f0;
  int8_t *volatile f1;
};

static const volatile union U5 g_14 = {1UL};
static int32_t *g_15 = (void *)0;
static int8_t g_21[1] = {0x7FL};
static int8_t *g_23 = (void *)0;
static uint64_t g_30 = 0xDE5A82A6F944DCD6LL;
static int64_t g_37 = 0xCFDEF05DE082ADE8LL;
static int32_t g_40 = 0x473ECFB8L;
static int32_t *volatile g_39 = &g_40;
static const int8_t *g_46[3] = {&g_21[0], &g_21[0], &g_21[0]};
static const int8_t **g_45[2] = {&g_46[1], &g_46[1]};
static const int8_t ***g_44 = &g_45[1];
static int32_t **volatile g_48 = (void *)0;
static const int32_t *g_52[2][3] = {{&g_40, (void *)0, &g_40},
                                    {&g_40, (void *)0, &g_40}};
static const int32_t **volatile g_51 = &g_52[0][1];
static const int32_t **volatile g_53 = &g_52[0][1];
static union U4 g_54 = {0UL};

static union U4 func_1(void);
static const int32_t *func_2(int8_t *p_3, uint16_t p_4);
static int8_t *func_5(union U2 p_6, const int8_t *p_7, uint32_t p_8,
                      int32_t *p_9, int16_t p_10);

static union U4 func_1(void) {
  union U2 l_11 = {65535UL};
  const int8_t *l_12 = (void *)0;
  const int8_t **l_13 = &l_12;
  int8_t **l_22 = (void *)0;
  int8_t *l_25 = &g_21[0];
  int8_t **l_24 = &l_25;
  (*g_51) = func_2(((*l_24) = (g_23 = func_5(l_11, ((*l_13) = l_12),
                                             (((g_14, l_11.f0) & 1L) >=
                                              0x0B5486B6FEB9E9D6LL),
                                             g_15, l_11.f0))),
                   g_21[0]);
  (*g_53) = (*g_51);
  return g_54;
}

static const int32_t *func_2(int8_t *p_3, uint16_t p_4) {
  uint8_t l_28 = 247UL;
  const int32_t *l_50 = &g_40;
  if ((safe_sub_func_uint64_t_u_u(
          (((1L || (p_4 = 65533UL)) == (((void *)0 == &g_23), l_28)) && p_4),
          l_28))) {
    uint64_t l_35 = 0x58A13C444C9CADCDLL;
    const int8_t *l_43[3];
    const int8_t **l_42[2][3];
    const int8_t ***l_41[1];
    int i, j;
    for (i = 0; i < 3; i++)
      l_43[i] = &g_21[0];
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 3; j++)
        l_42[i][j] = &l_43[2];
    }
    for (i = 0; i < 1; i++)
      l_41[i] = &l_42[0][2];
    for (l_28 = 0; (l_28 <= 0); l_28 += 1) {
      uint64_t *l_29 = &g_30;
      int64_t *l_36 = &g_37;
      int32_t *l_38 = (void *)0;
      int i;
      (*g_39) &=
          (((*l_29) = g_21[l_28]) <
           ((*l_36) =
                ((0xB8L || ((safe_lshift_func_uint16_t_u_s(
                                (safe_add_func_int64_t_s_s(
                                    ((0xB0D69B45C761B8CELL >=
                                      0x55D4826422F8DC70LL) < 0xBB9CEC02L),
                                    l_35)),
                                6)) ||
                            p_4)) ||
                 4L)));
    }
    g_44 = (l_41[0] = l_41[0]);
  } else {
    const int32_t *l_47 = &g_40;
    return l_47;
  }
  for (g_30 = 0; (g_30 <= 0); g_30 += 1) {
    int32_t **l_49 = &g_15;
    int i;
    if (g_21[g_30])
      break;
    (*l_49) = &g_40;
  }
  return l_50;
}

static int8_t *func_5(union U2 p_6, const int8_t *p_7, uint32_t p_8,
                      int32_t *p_9, int16_t p_10) {
  int32_t l_19[2];
  int8_t *l_20 = &g_21[0];
  int i;
  for (i = 0; i < 2; i++)
    l_19[i] = 0xFA85F88EL;
  l_19[0] = (safe_mul_func_int8_t_s_s(((+l_19[1]) || 0x3494L), g_14.f0));
  return l_20;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_14.f0;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_21[i];
  }
  csmith_sink_ = g_30;
  csmith_sink_ = g_37;
  csmith_sink_ = g_40;
  csmith_sink_ = g_54.f0;
  platform_main_end(0, 0);
  return 0;
}
