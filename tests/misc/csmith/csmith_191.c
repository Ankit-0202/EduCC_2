// Options:   --seed 200191 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_191.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int16_t g_10[3][2] = {
    {0xF0EDL, 0x44ADL}, {0x44ADL, 0xF0EDL}, {0x44ADL, 0x44ADL}};
static uint16_t g_22 = 0x278CL;
static uint8_t g_28 = 248UL;
static int32_t g_30 = 0x89C089CEL;

static const uint32_t func_1(void);
static float func_2(int32_t p_3, int32_t p_4, uint16_t p_5, const float p_6,
                    int32_t p_7);

static const uint32_t func_1(void) {
  uint8_t l_21 = 0x10L;
  int8_t *l_23[3];
  int32_t l_24 = 0x5954E3F1L;
  uint16_t *l_25 = (void *)0;
  uint16_t *l_26 = (void *)0;
  uint16_t *l_27 = &g_22;
  int32_t *l_29 = &g_30;
  int i;
  for (i = 0; i < 3; i++)
    l_23[i] = (void *)0;
  (*l_29) &=
      (((func_2((safe_mul_func_int8_t_s_s(
                    (((g_10[2][0] ||
                       ((*l_27) = (safe_mod_func_int8_t_s_s(
                            (l_24 = (safe_lshift_func_int8_t_s_s(
                                 (safe_rshift_func_uint8_t_u_u(
                                     (safe_sub_func_uint64_t_u_u(
                                         (safe_div_func_uint32_t_u_u(
                                             ((g_10[2][0] | (l_21 != g_22)),
                                              0x7BE02189L),
                                             4294967290UL)),
                                         l_21)),
                                     7)),
                                 5))),
                            249UL)))) > g_28),
                     l_21),
                    g_28)),
                l_21, l_21, g_28, l_21) >= l_21),
        0x7BF199314E764939LL),
       l_24);
  return g_10[2][0];
}

static float func_2(int32_t p_3, int32_t p_4, uint16_t p_5, const float p_6,
                    int32_t p_7) {
  return g_10[2][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_10[i][j];
    }
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_28;
  csmith_sink_ = g_30;
  platform_main_end(0, 0);
  return 0;
}
