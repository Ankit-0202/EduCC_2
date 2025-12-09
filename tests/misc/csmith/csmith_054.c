// Options:   --seed 100054 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_054.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U4 {
  const int64_t f0;
};

static int32_t *volatile g_2 = (void *)0;
static int32_t *volatile *volatile g_3 = &g_2;
static int32_t *g_10 = (void *)0;
static int32_t **g_9 = &g_10;
static int16_t g_18[4][2] = {{0L, 0L}, {0L, 0L}, {0L, 0L}, {0L, 0L}};
static int32_t g_20[3][1] = {{0x86AEBA4DL}, {0x86AEBA4DL}, {0x86AEBA4DL}};
static union U4 g_22 = {-9L};
static union U4 *g_24 = &g_22;
static union U4 **volatile g_23 = &g_24;

static int16_t func_1(void);
static union U4 *const func_4(int32_t **p_5, uint64_t p_6, uint32_t p_7,
                              const int16_t p_8);

static int16_t func_1(void) {
  uint8_t l_17 = 1UL;
  (*g_3) = g_2;
  (*g_23) =
      func_4(g_9,
             ((safe_add_func_int64_t_s_s(
                  (safe_div_func_uint64_t_u_u(
                      (safe_add_func_int8_t_s_s(l_17, g_18[3][1])), l_17)),
                  (-4L))) >= g_18[3][1]),
             l_17, g_18[3][0]);
  return g_18[3][1];
}

static union U4 *const func_4(int32_t **p_5, uint64_t p_6, uint32_t p_7,
                              const int16_t p_8) {
  int32_t *l_19 = &g_20[1][0];
  union U4 *const l_21 = &g_22;
  (*g_9) = l_19;
  return l_21;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_18[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_20[i][j];
    }
  }
  csmith_sink_ = g_22.f0;
  platform_main_end(0, 0);
  return 0;
}
