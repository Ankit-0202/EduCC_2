// Options:   --seed 200183 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_183.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = (-1L);
static const int32_t *g_19 = &g_2;
static const int32_t **volatile g_18 = &g_19;

static uint16_t func_1(void);
static uint16_t func_5(uint32_t p_6, int64_t p_7, uint32_t p_8, int64_t p_9,
                       int16_t p_10);

static uint16_t func_1(void) {
  int32_t l_14 = (-1L);
  float l_20 = 0x0.2p+1;
  for (g_2 = (-27); (g_2 != 3); g_2 = safe_add_func_uint16_t_u_u(g_2, 6)) {
    int32_t l_13 = 0xB03E3869L;
    if (((func_5(
              (((((safe_sub_func_int16_t_s_s(
                      ((g_2 ^ (l_13 | (0xB00868BB4AAD9DDCLL > g_2))), 0x456EL),
                      g_2)) > l_14) |
                 g_2) == 0x683648BD921B0AE2LL) >= l_14),
              g_2, l_13, g_2, l_13) >= g_2) &&
         l_13)) {
      return g_2;
    } else {
      if (l_13)
        break;
    }
  }
  return g_2;
}

static uint16_t func_5(uint32_t p_6, int64_t p_7, uint32_t p_8, int64_t p_9,
                       int16_t p_10) {
  const int32_t *l_17 = &g_2;
  for (p_9 = (-11); (p_9 < (-30)); p_9 = safe_sub_func_int64_t_s_s(p_9, 8)) {
    (*g_18) = l_17;
  }
  return (*l_17);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  platform_main_end(0, 0);
  return 0;
}
