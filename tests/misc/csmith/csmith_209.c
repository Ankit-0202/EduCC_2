// Options:   --seed 300209 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_209.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
};

static int32_t g_10 = 0x48B08158L;
static int32_t *const g_9 = &g_10;
static int32_t g_19 = 0xE3E45BBBL;
static int32_t *g_18 = &g_19;
static int32_t **g_22 = &g_18;

static uint32_t func_1(void);
static int32_t *func_2(struct S0 p_3, int32_t *const p_4, int32_t *p_5,
                       int32_t *p_6, int32_t *const p_7);
static int32_t *func_11(uint64_t p_12, int8_t p_13, const int32_t *p_14,
                        int32_t p_15);

static uint32_t func_1(void) {
  struct S0 l_8[1][1] = {{{0x6BAFCB14L}}};
  int32_t *const l_20 = &l_8[0][0].f0;
  int32_t **l_23 = &g_18;
  uint8_t l_24[2];
  int i, j;
  for (i = 0; i < 2; i++)
    l_24[i] = 0x19L;
  (*l_23) =
      func_2(l_8[0][0], g_9,
             func_11((safe_lshift_func_int16_t_s_s(l_8[0][0].f0, l_8[0][0].f0)),
                     l_8[0][0].f0, &g_10, g_10),
             g_18, l_20);
  return l_24[0];
}

static int32_t *func_2(struct S0 p_3, int32_t *const p_4, int32_t *p_5,
                       int32_t *p_6, int32_t *const p_7) {
  int32_t **l_21 = &g_18;
  g_22 = l_21;
  return p_5;
}

static int32_t *func_11(uint64_t p_12, int8_t p_13, const int32_t *p_14,
                        int32_t p_15) {
  (*g_9) = (*p_14);
  return &g_10;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_10;
  csmith_sink_ = g_19;
  platform_main_end(0, 0);
  return 0;
}
