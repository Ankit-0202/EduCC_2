// Options:   --seed 200198 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_198.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_11 = (-1L);
static int8_t g_21[2][3] = {{0xD1L, 0xD1L, 0xD1L}, {0xD1L, 0xD1L, 0xD1L}};
static uint8_t g_23 = 0xABL;
static float g_29[2][2] = {{0x9.Ep-1, 0x9.Ep-1}, {0x9.Ep-1, 0x9.Ep-1}};
static int32_t g_38[4] = {0xC2A4E630L, 0xC2A4E630L, 0xC2A4E630L, 0xC2A4E630L};
static int32_t g_40[2][2] = {{(-1L), (-1L)}, {(-1L), (-1L)}};

static int32_t func_1(void);
static float func_2(int64_t p_3, int8_t p_4, float p_5, uint16_t p_6,
                    uint32_t p_7);

static int32_t func_1(void) {
  const uint16_t l_10 = 9UL;
  float *l_28 = &g_29[1][0];
  int32_t *l_36 = &g_11;
  int32_t *l_37 = &g_38[3];
  int32_t *l_39[3][4];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++)
      l_39[i][j] = &g_40[0][0];
  }
  (*l_28) = func_2(((0x2EDCL == (safe_lshift_func_int8_t_s_s(
                                    0xA9L, ((255UL < l_10) & 4294967291UL)))),
                    l_10),
                   g_11, g_11, l_10, l_10);
  g_40[0][0] =
      ((*l_37) |=
       ((*l_36) = ((safe_rshift_func_uint16_t_u_u(
                       (safe_add_func_int8_t_s_s(
                           (((safe_div_func_int32_t_s_s(l_10, 0xC5C3C3AEL)),
                             (7L | g_23)) &&
                            (-9L)),
                           l_10)),
                       g_21[0][0])) > l_10)));
  return g_38[3];
}

static float func_2(int64_t p_3, int8_t p_4, float p_5, uint16_t p_6,
                    uint32_t p_7) {
  uint64_t l_19 = 1UL;
  int8_t *l_20 = &g_21[0][0];
  uint8_t *l_22 = &g_23;
  int32_t *l_27 = &g_11;
  int32_t **l_26 = &l_27;
  if ((safe_rshift_func_uint16_t_u_u(
          ((safe_lshift_func_uint8_t_u_s(
               (safe_mod_func_int16_t_s_s(
                   (((~((*l_20) = l_19)) ==
                     ((((*l_22) = l_19) >= ((void *)0 != l_22)) ^ 1UL)) > 1L),
                   0x678EL)),
               4)) ^
           p_3),
          11))) {
    for (l_19 = (-24); (l_19 <= 41); ++l_19) {
      return p_7;
    }
  } else {
    return g_11;
  }
  (*l_26) = (void *)0;
  return p_5;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_21[i][j];
    }
  }
  csmith_sink_ = g_23;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_29[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_38[i];
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_40[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
