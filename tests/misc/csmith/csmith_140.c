// Options:   --seed 200140 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_140.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = (-1L);
static uint32_t g_21 = 0xBAEF6E22L;
static float g_28[3][2] = {{0xC.995F76p+54, 0xC.995F76p+54},
                           {0xC.995F76p+54, 0xC.995F76p+54},
                           {0xC.995F76p+54, 0xC.995F76p+54}};

static uint64_t func_1(void);
static float func_6(int64_t p_7, uint64_t p_8, int8_t p_9, uint16_t p_10,
                    int64_t p_11);

static uint64_t func_1(void) {
  int32_t l_22 = 8L;
  for (g_2 = 24; (g_2 > (-26)); --g_2) {
    int32_t l_19 = 0x74006310L;
    uint32_t *l_20 = &g_21;
    float *l_32 = &g_28[0][0];
    (*l_32) =
        ((!g_2),
         (0x0.Cp+1 !=
          func_6((safe_mod_func_uint32_t_u_u(
                     ((*l_20) |=
                      (~((safe_mul_func_float_f_f(
                             (safe_sub_func_float_f_f(l_19, 0x0.D193E0p+19)),
                             0x7.213EC7p+82)),
                         l_19))),
                     l_22)),
                 g_2, g_2, l_22, g_2)));
    if (l_19)
      continue;
  }
  return g_2;
}

static float func_6(int64_t p_7, uint64_t p_8, int8_t p_9, uint16_t p_10,
                    int64_t p_11) {
  uint8_t l_26[4];
  float *l_27 = &g_28[0][0];
  int32_t l_29 = 0xFBA2522AL;
  int i;
  for (i = 0; i < 4; i++)
    l_26[i] = 0xADL;
  l_29 = (safe_div_func_float_f_f(
      ((*l_27) = (0x1.7p+1 >=
                  ((((-7L) >= ((+g_2) | l_26[3])), g_21) > 0xB.6084EDp-53))),
      g_2));
  for (p_7 = 0; (p_7 > 6); p_7 = safe_add_func_uint64_t_u_u(p_7, 7)) {
    return p_8;
  }
  return g_21;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_21;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_28[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
