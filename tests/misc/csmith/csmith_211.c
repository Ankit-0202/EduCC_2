// Options:   --seed 300211 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_211.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint16_t g_8 = 0x9536L;
static int32_t g_15 = 0xD82C32B9L;
static int32_t *volatile g_14 = &g_15;

static uint16_t func_1(void);
static int32_t func_2(uint32_t p_3, int32_t p_4, int16_t p_5, uint8_t p_6,
                      uint32_t p_7);

static uint16_t func_1(void) {
  const int16_t l_11 = (-8L);
  uint64_t l_12[2];
  int i;
  for (i = 0; i < 2; i++)
    l_12[i] = 0xB01D91E66C619A80LL;
  (*g_14) = func_2(g_8,
                   (((safe_mod_func_uint32_t_u_u((0x79CF1813L >= (-6L)),
                                                 l_11)) < g_8) >= 8UL),
                   l_11, l_11, l_12[1]);
  return g_8;
}

static int32_t func_2(uint32_t p_3, int32_t p_4, int16_t p_5, uint8_t p_6,
                      uint32_t p_7) {
  int16_t l_13[1];
  int i;
  for (i = 0; i < 1; i++)
    l_13[i] = 0x812AL;
  return l_13[0];
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_15;
  platform_main_end(0, 0);
  return 0;
}
