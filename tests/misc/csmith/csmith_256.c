// Options:   --seed 300256 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_256.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2[1][1] = {{1L}};
static volatile int32_t g_3 = (-4L);
static int32_t g_4 = 5L;
static int32_t g_7 = (-1L);

static int8_t func_1(void);

static int8_t func_1(void) {
  int32_t *l_13 = &g_4;
  int32_t *l_14[2];
  int i;
  for (i = 0; i < 2; i++)
    l_14[i] = &g_7;
  for (g_4 = (-7); (g_4 > (-8)); g_4 = safe_sub_func_uint32_t_u_u(g_4, 6)) {
    for (g_7 = 0; (g_7 <= 0); g_7 += 1) {
      int i, j;
      if (g_2[g_7][g_7])
        break;
    }
    g_7 &= (~(safe_rshift_func_uint16_t_u_s(g_2[0][0], 13)));
  }
  g_7 ^= ((*l_13) = (safe_lshift_func_int16_t_s_s(g_2[0][0], 1)));
  return (*l_13);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_7;
  platform_main_end(0, 0);
  return 0;
}
