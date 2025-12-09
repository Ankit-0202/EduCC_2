// Options:   --seed 300298 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_298.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile uint8_t f0;
  volatile int32_t f1;
};

static int64_t g_9 = 2L;
static volatile struct S0 g_10 = {255UL, -2L};
static volatile struct S0 *volatile g_11 = &g_10;
static struct S0 g_20[1] = {{0xE7L, 0xE815F842L}};
static struct S0 *g_19 = &g_20[0];
static uint8_t g_26 = 0x56L;
static struct S0 **volatile g_27 = &g_19;
static int32_t g_32[1][1] = {{0L}};

static uint64_t func_1(void);
static int32_t func_12(uint8_t p_13, uint16_t p_14);
static int64_t func_15(struct S0 *p_16, uint64_t p_17, uint64_t p_18);

static uint64_t func_1(void) {
  uint16_t l_6 = 0UL;
  uint8_t *l_25 = &g_26;
  int32_t *l_31 = &g_32[0][0];
  (*g_11) =
      ((safe_add_func_uint32_t_u_u(
           0x07E17F75L, (safe_mul_func_uint8_t_u_u(
                            (((((l_6 || (safe_sub_func_int16_t_s_s(l_6, g_9))) &
                                0xC15DL) >= l_6),
                              l_6) < 0xC8L),
                            g_9)))),
       g_10);
  (*l_31) = func_12((func_15(g_19,
                             (safe_rshift_func_uint8_t_u_s(
                                 ((*l_25) = (safe_add_func_int64_t_s_s(
                                      (0x1348L >= (l_6 | 6UL)), g_20[0].f1))),
                                 l_6)),
                             g_9),
                     3UL),
                    l_6);
  return (*l_31);
}

static int32_t func_12(uint8_t p_13, uint16_t p_14) {
  uint16_t l_30 = 65530UL;
  for (p_14 = (-26); (p_14 >= 51); p_14++) {
    for (g_26 = 0; (g_26 <= 0); g_26 += 1) {
      return p_13;
    }
  }
  return l_30;
}

static int64_t func_15(struct S0 *p_16, uint64_t p_17, uint64_t p_18) {
  (*g_27) = &g_20[0];
  return g_20[0].f1;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_10.f0;
  csmith_sink_ = g_10.f1;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_26;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_32[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
