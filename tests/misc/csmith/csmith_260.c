// Options:   --seed 300260 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_260.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static const uint64_t g_8 = 0x04EE7D214C405B40LL;
static uint64_t g_17 = 18446744073709551615UL;
static int32_t g_28 = 0L;
static int32_t *g_30 = &g_28;
static int32_t **volatile g_29[2][1] = {{&g_30}, {&g_30}};
static int32_t **volatile g_31 = &g_30;
static int32_t g_34 = 2L;
static uint32_t g_37 = 18446744073709551615UL;

static uint32_t func_1(void);
static int32_t func_2(const int64_t p_3, int32_t p_4, uint32_t p_5,
                      uint32_t p_6, uint16_t p_7);
static int32_t func_13(uint64_t p_14, int32_t p_15);

static uint32_t func_1(void) {
  uint64_t *l_16 = &g_17;
  int32_t l_26 = 0x919ADB82L;
  int8_t l_33 = 0x4DL;
  int32_t *l_36 = &g_28;
  (*l_36) &= func_2(
      g_8,
      (((g_34 = ((((safe_sub_func_int8_t_s_s(
                       (safe_sub_func_int32_t_s_s(
                           func_13(((*l_16)++),
                                   ((safe_add_func_int32_t_s_s(
                                        (safe_mod_func_int16_t_s_s(
                                            (((((safe_sub_func_uint32_t_u_u(
                                                    0UL, (l_16 == &g_8))) |
                                                g_8) < l_26),
                                              l_16) != &g_8),
                                            0xB5AFL)),
                                        g_8)) == g_8)),
                           g_8)),
                       0xE9L)) &&
                   l_33),
                  0L) > l_26)) < 0x41022496L) ^
       g_8),
      l_26, l_33, l_33);
  return g_37;
}

static int32_t func_2(const int64_t p_3, int32_t p_4, uint32_t p_5,
                      uint32_t p_6, uint16_t p_7) {
  int32_t **volatile *l_35 = &g_29[1][0];
  l_35 = &g_31;
  return p_6;
}

static int32_t func_13(uint64_t p_14, int32_t p_15) {
  int32_t *l_27 = &g_28;
  int64_t l_32 = (-1L);
  (*g_31) = l_27;
  return l_32;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_17;
  csmith_sink_ = g_28;
  csmith_sink_ = g_34;
  csmith_sink_ = g_37;
  platform_main_end(0, 0);
  return 0;
}
