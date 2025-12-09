// Options:   --seed 100099 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_099.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_9 = 0L;
static int16_t g_11 = 0xBA1AL;
static int64_t g_13 = 0L;
static int32_t *g_14 = (void *)0;
static volatile uint64_t g_15 = 0x94A61BF0796840EBLL;
static int32_t g_17[3][1] = {{1L}, {1L}, {1L}};

static int32_t func_1(void);
static const int32_t *func_2(int16_t p_3, int32_t *p_4);

static int32_t func_1(void) {
  uint8_t *l_12[3][1];
  const int32_t *l_19 = (void *)0;
  const int32_t **l_18 = &l_19;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_12[i][j] = (void *)0;
  }
  (*l_18) =
      func_2((safe_rshift_func_uint8_t_u_u(
                 (safe_sub_func_uint8_t_u_u(
                     g_9, (!(g_13 = ((5L & 0x7909B7928FBC781CLL) & g_11))))),
                 0)),
             g_14);
  return g_9;
}

static const int32_t *func_2(int16_t p_3, int32_t *p_4) {
  const int32_t *l_16[2];
  int i;
  for (i = 0; i < 2; i++)
    l_16[i] = &g_17[1][0];
  g_15 = g_9;
  return l_16[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_11;
  csmith_sink_ = g_13;
  csmith_sink_ = g_15;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_17[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
