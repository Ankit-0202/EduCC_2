// Options:   --seed 200193 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_193.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = (-1L);
static volatile int32_t g_3[4][1] = {{8L}, {8L}, {8L}, {8L}};
static volatile int32_t g_4 = 0x7B1891F7L;
static volatile int32_t g_5 = 0x1836CCB0L;
static volatile int32_t g_6 = 0x9AA810D2L;
static volatile int32_t g_7 = 0xE4B28306L;
static int32_t g_8[1] = {0x3EE32743L};
static float g_19 = (-0x6.9p+1);
static int8_t g_24 = 1L;
static int32_t g_26 = 0xECBE92E3L;
static int32_t *volatile g_25 = &g_26;
static uint32_t g_34 = 0x860BC23CL;

static int16_t func_1(void);
static int32_t func_11(int64_t p_12);

static int16_t func_1(void) {
  uint64_t l_35[1];
  int i;
  for (i = 0; i < 1; i++)
    l_35[i] = 0x7F1BD53D2AE45661LL;
  for (g_8[0] = 7; (g_8[0] < (-9));
       g_8[0] = safe_sub_func_uint16_t_u_u(g_8[0], 7)) {
    (*g_25) = func_11(g_8[0]);
    for (g_24 = 0; (g_24 > (-19)); g_24 = safe_sub_func_uint8_t_u_u(g_24, 1)) {
      uint32_t *l_31 = (void *)0;
      uint32_t *l_32 = (void *)0;
      uint32_t *l_33[3][3] = {{(void *)0, &g_34, (void *)0},
                              {&g_34, &g_34, &g_34},
                              {(void *)0, &g_34, (void *)0}};
      int i, j;
      (*g_25) = ((g_34 = (((255UL <= (safe_add_func_int64_t_s_s(
                                         g_3[0][0], g_8[0]))) == g_26) &&
                          0xB6B7BE2DL)) == g_8[0]);
      if (l_35[0])
        continue;
    }
  }
  return g_24;
}

static int32_t func_11(int64_t p_12) {
  float *l_17 = (void *)0;
  float *l_18 = &g_19;
  float l_22 = (-0x9.Fp+1);
  int32_t l_23 = 0xB6CD3335L;
  g_24 = (safe_sub_func_float_f_f(
      ((safe_mul_func_float_f_f(((((*l_18) = g_8[0]) < p_12) >
                                 (safe_div_func_float_f_f(l_22, p_12))),
                                l_23)) == 0x4.Dp+1),
      g_8[0]));
  return g_3[0][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_8[i];
  }
  csmith_sink_ = g_19;
  csmith_sink_ = g_24;
  csmith_sink_ = g_26;
  csmith_sink_ = g_34;
  platform_main_end(0, 0);
  return 0;
}
