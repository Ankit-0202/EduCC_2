// Options:   --seed 200105 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_105.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint8_t g_5 = 255UL;
static int32_t g_32 = 0x61718BC6L;
static int32_t *g_31 = &g_32;
static int32_t **g_30 = &g_31;
static int32_t ***g_29[1] = {&g_30};
static int32_t ***const *g_28 = &g_29[0];
static int32_t ***const **g_44[4] = {&g_28, &g_28, &g_28, &g_28};

static int16_t func_1(void);
static uint32_t func_9(int64_t p_10, uint32_t p_11, int32_t p_12);

static int16_t func_1(void) {
  float l_4 = 0x1.5A1369p+33;
  int32_t l_8[2][3] = {{(-2L), (-2L), (-2L)}, {(-4L), (-4L), (-4L)}};
  int32_t *l_18 = &l_8[1][2];
  int32_t l_42 = (-6L);
  int i, j;
  if (((safe_rshift_func_uint16_t_u_u(g_5, 5)),
       ((*l_18) = (safe_div_func_int32_t_s_s(
            (l_8[1][2], ((func_9(l_8[1][2], g_5, l_8[0][1]) || g_5) < g_5)),
            g_5))))) {
    const uint32_t l_19 = 4294967286UL;
    int32_t *l_24 = (void *)0;
    int32_t **l_27 = &l_24;
    int32_t ***l_26[3][1];
    int32_t ***const *l_25[1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_26[i][j] = &l_27;
    }
    for (i = 0; i < 1; i++)
      l_25[i] = &l_26[0][0];
    if (l_19) {
      int32_t **l_20 = &l_18;
      int32_t ***l_21 = &l_20;
      (*l_20) = &l_8[1][2];
      (*l_21) = l_20;
    } else {
      (*l_18) |=
          (((safe_add_func_int16_t_s_s(0x0F2DL, (l_24 == l_24))), (-7L)) | g_5);
      g_28 = l_25[0];
    }
  } else {
    int32_t l_41[3];
    int32_t ***const **l_43 = &g_28;
    int i;
    for (i = 0; i < 3; i++)
      l_41[i] = 0x7673ED13L;
    for (g_5 = 0; (g_5 > 9); g_5 = safe_add_func_uint32_t_u_u(g_5, 5)) {
      l_42 ^= ((**g_30) = (((safe_sub_func_uint16_t_u_u(
                                (safe_rshift_func_uint16_t_u_s(
                                    (safe_mul_func_int8_t_s_s(
                                        ((void *)0 == (*g_28)), (*l_18))),
                                    9)),
                                (-1L))) == l_41[0]) >= g_32));
      g_44[1] = l_43;
    }
  }
  return g_5;
}

static uint32_t func_9(int64_t p_10, uint32_t p_11, int32_t p_12) {
  float l_17 = (-0x4.3p+1);
  for (p_10 = (-14); (p_10 == (-17));
       p_10 = safe_sub_func_uint32_t_u_u(p_10, 2)) {
    for (p_12 = 2; (p_12 != (-10)); --p_12) {
      if (p_12)
        break;
    }
  }
  return p_11;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_32;
  platform_main_end(0, 0);
  return 0;
}
