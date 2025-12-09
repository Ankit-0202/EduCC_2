// Options:   --seed 300300 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_300.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  uint8_t f0;
};

static union U1 g_16 = {0UL};
static int32_t g_18 = 2L;
static int32_t *volatile g_17 = &g_18;

static int64_t func_1(void);
static uint8_t func_13(const int16_t p_14, union U1 p_15);

static int64_t func_1(void) {
  uint32_t l_12 = 0xC3938DD4L;
  uint16_t l_19[2];
  int i;
  for (i = 0; i < 2; i++)
    l_19[i] = 0xBC65L;
  (*g_17) ^= (safe_div_func_uint16_t_u_u(
      (safe_mul_func_uint16_t_u_u(
          ((((safe_add_func_int8_t_s_s(
                 (safe_lshift_func_int8_t_s_s(
                     (safe_rshift_func_int16_t_s_u(l_12, 10)), 3)),
                 (func_13(l_12, g_16) != (-4L)))) < l_12) > 0xEF6E229EL) !=
           l_12),
          l_12)),
      6L));
  return l_19[1];
}

static uint8_t func_13(const int16_t p_14, union U1 p_15) { return g_16.f0; }

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_16.f0;
  csmith_sink_ = g_18;
  platform_main_end(0, 0);
  return 0;
}
