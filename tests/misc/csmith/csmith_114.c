// Options:   --seed 200114 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_114.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  int16_t f0;
};

static int64_t g_9 = 0x3FF82FF40FC0272ALL;
static int32_t g_24 = (-1L);
static int32_t *volatile g_23 = &g_24;
static float *volatile g_28 = (void *)0;
static float g_30 = (-0x1.Dp+1);
static uint8_t g_33 = 0UL;

static int64_t func_1(void);
static uint8_t func_4(int16_t p_5, int32_t p_6, union U1 p_7, uint16_t p_8);

static int64_t func_1(void) {
  int64_t l_20 = 0xD0357257EA0D018DLL;
  int64_t l_21 = 0xC2D621EC2184E5A9LL;
  union U1 l_22 = {0x593CL};
  uint8_t *l_32 = &g_33;
  int32_t l_34 = 9L;
  l_34 &= (safe_rshift_func_uint8_t_u_u(
      ((*l_32) =
           func_4(g_9,
                  (safe_div_func_int16_t_s_s(
                      (g_9 <= ((safe_rshift_func_uint8_t_u_s(
                                   ((safe_mod_func_uint64_t_u_u(
                                        ((((safe_div_func_uint8_t_u_u(
                                               (safe_rshift_func_int16_t_s_u(
                                                   (l_20 >= 9L), g_9)),
                                               l_21)) >= g_9) >= g_9) > g_9),
                                        l_21)),
                                    0xA8L),
                                   2)) ^
                               g_9)),
                      l_20)),
                  l_22, g_9)),
      g_9));
  return l_22.f0;
}

static uint8_t func_4(int16_t p_5, int32_t p_6, union U1 p_7, uint16_t p_8) {
  int32_t *l_27 = &g_24;
  (*g_23) &= g_9;
  for (p_5 = 0; (p_5 > 22); p_5 = safe_add_func_uint32_t_u_u(p_5, 2)) {
    float *l_29 = &g_30;
    int32_t l_31 = 0x91F06E85L;
    (*l_29) = (l_27 != (void *)0);
    if (l_31)
      break;
  }
  return p_5;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_24;
  csmith_sink_ = g_30;
  csmith_sink_ = g_33;
  platform_main_end(0, 0);
  return 0;
}
