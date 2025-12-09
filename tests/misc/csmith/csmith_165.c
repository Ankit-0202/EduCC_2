// Options:   --seed 200165 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_165.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint64_t g_9 = 0xF90EDCAD2086BD08LL;
static int16_t g_19 = 1L;
static uint32_t g_21 = 0UL;
static int32_t g_30 = 0xEC560449L;
static int32_t *volatile g_29 = &g_30;
static int64_t g_38 = 0xEBE1552B9CBADBEFLL;
static volatile uint16_t g_40 = 65528UL;
static int32_t *volatile g_43[1] = {&g_30};
static float g_46[2] = {0x0.CD5C0Fp-34, 0x0.CD5C0Fp-34};

static uint8_t func_1(void);
static uint32_t func_4(float p_5, int16_t p_6, uint64_t p_7, int16_t p_8);

static uint8_t func_1(void) {
  int32_t l_16 = 0x1637C1D6L;
  int16_t *l_17 = (void *)0;
  int16_t *l_18 = &g_19;
  uint32_t *l_20 = &g_21;
  float *l_45[1];
  float l_47[1];
  int i;
  for (i = 0; i < 1; i++)
    l_45[i] = &g_46[0];
  for (i = 0; i < 1; i++)
    l_47[i] = 0x1.Bp+1;
  g_46[0] =
      ((safe_mul_func_float_f_f(
           ((func_4(g_9,
                    (safe_mod_func_uint32_t_u_u(
                        ((*l_20) =
                             (((*l_18) &=
                               (g_9 >
                                ((((safe_mul_func_uint16_t_u_u(
                                       ((safe_lshift_func_uint8_t_u_s(l_16, 3)),
                                        65535UL),
                                       (-9L))) ||
                                   g_9),
                                  g_9) >= 0L))) &&
                              0xA30AL)),
                        l_16)),
                    l_16, g_9) > 0xA1DC7E90L),
            l_16),
           0xA.839BB8p-76)) > g_38);
  return g_30;
}

static uint32_t func_4(float p_5, int16_t p_6, uint64_t p_7, int16_t p_8) {
  uint32_t l_22[4] = {6UL, 6UL, 6UL, 6UL};
  int32_t l_23 = 0x2A284868L;
  int32_t l_39 = 0x426AE69EL;
  int i;
  for (p_6 = 0; (p_6 <= 3); p_6 += 1) {
    int8_t l_28 = 0xFEL;
    int32_t l_37[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_37[i][j] = 0x8D36FBC6L;
    }
    for (g_9 = 0; (g_9 <= 3); g_9 += 1) {
      int32_t *l_24 = &l_23;
      int i;
      l_23 ^= l_22[p_6];
      (*l_24) ^= (-1L);
    }
    if ((+(safe_add_func_int64_t_s_s(l_22[p_6], l_28)))) {
      uint64_t l_31 = 0xD0D42AD015B01D97LL;
      (*g_29) |= p_8;
      return l_31;
    } else {
      int32_t *l_32 = (void *)0;
      int32_t *l_33 = &l_23;
      int32_t *l_34 = &g_30;
      int32_t *l_35 = &g_30;
      int32_t *l_36[4];
      int i;
      for (i = 0; i < 4; i++)
        l_36[i] = &g_30;
      --g_40;
    }
  }
  for (g_9 = 0; (g_9 <= 3); g_9 += 1) {
    int32_t *l_44 = &g_30;
    (*l_44) = (&p_6 == &p_6);
  }
  return l_23;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_19;
  csmith_sink_ = g_21;
  csmith_sink_ = g_30;
  csmith_sink_ = g_38;
  csmith_sink_ = g_40;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_46[i];
  }
  platform_main_end(0, 0);
  return 0;
}
