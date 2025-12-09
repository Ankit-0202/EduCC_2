// Options:   --seed 300231 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_231.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int16_t g_11 = (-8L);
static volatile int32_t g_17 = 0x3923CCDEL;
static volatile int32_t *volatile g_16[3][1] = {{&g_17}, {&g_17}, {&g_17}};
static int16_t g_20[1][1] = {{0x1E0BL}};
static int32_t g_22 = 0x04DBF0CFL;

static int64_t func_1(void);
static uint8_t func_5(int32_t p_6, uint16_t p_7, uint32_t p_8, uint16_t p_9,
                      uint8_t p_10);

static int64_t func_1(void) {
  uint32_t l_2 = 18446744073709551614UL;
  int16_t *l_19[3];
  int32_t *l_21 = &g_22;
  int i;
  for (i = 0; i < 3; i++)
    l_19[i] = &g_20[0][0];
  if (((*l_21) &=
       (l_2 ==
        (g_20[0][0] &= (safe_lshift_func_uint8_t_u_u(
             func_5(g_11,
                    (safe_mod_func_uint16_t_u_u(
                        ((safe_div_func_int8_t_s_s(7L, 0x2AL)) != 0x43B2B74CL),
                        0x6B0EL)),
                    l_2, l_2, g_11),
             0)))))) {
    int64_t l_23 = 1L;
    return l_23;
  } else {
    uint32_t l_24 = 0UL;
    return l_24;
  }
}

static uint8_t func_5(int32_t p_6, uint16_t p_7, uint32_t p_8, uint16_t p_9,
                      uint8_t p_10) {
  volatile int32_t *volatile *l_18 = &g_16[1][0];
  (*l_18) = g_16[1][0];
  return (**l_18);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  csmith_sink_ = g_17;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_20[i][j];
    }
  }
  csmith_sink_ = g_22;
  platform_main_end(0, 0);
  return 0;
}
