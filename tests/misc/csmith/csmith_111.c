// Options:   --seed 200111 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_111.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
  const volatile int32_t f1;
  int8_t f2;
};

union U3 {
  volatile struct S0 f0;
};

union U6 {
  volatile int32_t f0;
  int8_t *f1;
};

static volatile float g_2 = 0x3.6544D1p+60;
static uint8_t g_4 = 253UL;
static uint64_t g_6[1] = {18446744073709551615UL};
static int8_t g_15[3] = {0x4EL, 0x4EL, 0x4EL};
static int8_t *g_14 = &g_15[2];
static volatile uint64_t g_17 = 0x3CA955A63A74ADF2LL;
static volatile uint64_t *const volatile g_16 = &g_17;
static uint64_t g_19 = 7UL;
static float g_23 = 0xC.9D8D92p+4;
static float *volatile g_22 = &g_23;
static union U3 g_29 = {{1L, 9L, -1L}};
static union U6 g_35[4][3] = {{{-9L}, {-9L}, {-9L}},
                              {{-9L}, {-9L}, {-9L}},
                              {{-9L}, {-9L}, {-9L}},
                              {{-9L}, {-9L}, {-9L}}};
static uint32_t g_39 = 0xBFEFA2E5L;

static int32_t func_1(void);
static union U6 func_11(int8_t *p_12, uint8_t p_13);

static int32_t func_1(void) {
  int32_t l_3 = 0x6EC6E54EL;
  uint64_t *l_5 = &g_6[0];
  uint64_t l_36 = 0xE29AC92D14B4322ELL;
  uint64_t l_37 = 0x9063446B7D869E77LL;
  int32_t *l_38 = (void *)0;
  g_39 = (l_3 > ((((*l_5) = g_4) >
                  ((safe_rshift_func_int16_t_s_s(
                       (safe_lshift_func_int16_t_s_u(
                           (func_11(g_14, g_15[2]), g_29.f0.f2), g_15[2])),
                       3)),
                   l_36)),
                 l_37));
  return l_36;
}

static union U6 func_11(int8_t *p_12, uint8_t p_13) {
  uint64_t *l_18 = &g_19;
  int32_t l_20 = 0xB8CEFFB9L;
  float *l_21 = (void *)0;
  (*g_22) = (g_15[0], ((g_16 != l_18) <= l_20));
  for (l_20 = 0; (l_20 >= 25); l_20 = safe_add_func_int8_t_s_s(l_20, 5)) {
    union U3 *l_28 = &g_29;
    float *l_34 = &g_23;
    for (g_19 = 13; (g_19 <= 19); g_19 = safe_add_func_uint16_t_u_u(g_19, 6)) {
      l_28 = l_28;
    }
    (*l_34) = (safe_add_func_float_f_f(
        (0xA.D7BA96p-69 >= p_13),
        ((safe_mod_func_int8_t_s_s(((l_20 > g_29.f0.f0) & 65535UL), p_13)),
         p_13)));
  }
  return g_35[2][0];
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
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_6[i];
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_15[i];
  }
  csmith_sink_ = g_17;
  csmith_sink_ = g_19;
  csmith_sink_ = g_23;
  csmith_sink_ = g_29.f0.f0;
  csmith_sink_ = g_29.f0.f1;
  csmith_sink_ = g_29.f0.f2;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  csmith_sink_ = g_39;
  platform_main_end(0, 0);
  return 0;
}
