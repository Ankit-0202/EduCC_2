// Options:   --seed 200142 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_142.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile uint32_t f0;
  const uint32_t f1;
  volatile int64_t f2;
};

static int32_t g_9 = 0xE05DAE5AL;
static struct S0 g_16 = {4294967291UL, 1UL, 0xFFCF33F23E93D0B5LL};
static int16_t g_19 = 0L;
static volatile uint32_t g_20 = 1UL;

static uint16_t func_1(void);
static int32_t *func_2(int32_t *const p_3, int32_t *p_4, int32_t *p_5,
                       uint64_t p_6, int32_t *p_7);

static uint16_t func_1(void) {
  int32_t *const l_8 = &g_9;
  int32_t **l_10 = (void *)0;
  int32_t *l_11 = &g_9;
  int32_t **l_23 = &l_11;
  (*l_23) = func_2(l_8, (l_11 = &g_9), &g_9, g_9, &g_9);
  return g_20;
}

static int32_t *func_2(int32_t *const p_3, int32_t *p_4, int32_t *p_5,
                       uint64_t p_6, int32_t *p_7) {
  uint8_t l_17 = 0x60L;
  if ((*p_3)) {
    (*p_5) &= 0xBACC5D9BL;
    (*p_4) = (safe_sub_func_int32_t_s_s(
        ((safe_sub_func_uint32_t_u_u((g_16, (p_6, 0x24307A32L)), l_17)) |
         0xA85F88E10E5E5349LL),
        l_17));
  } else {
    int32_t *l_18[1][4];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 4; j++)
        l_18[i][j] = &g_9;
    }
    --g_20;
  }
  return &g_9;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_16.f0;
  csmith_sink_ = g_16.f1;
  csmith_sink_ = g_16.f2;
  csmith_sink_ = g_19;
  csmith_sink_ = g_20;
  platform_main_end(0, 0);
  return 0;
}
