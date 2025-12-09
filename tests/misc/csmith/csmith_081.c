// Options:   --seed 100081 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_081.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint64_t g_3 = 0x29BF390197F0A290LL;
static int32_t g_7 = 1L;
static int32_t *volatile g_6[3][4] = {{&g_7, &g_7, &g_7, &g_7},
                                      {(void *)0, (void *)0, &g_7, &g_7},
                                      {&g_7, &g_7, &g_7, &g_7}};
static int32_t g_9 = (-3L);

static uint64_t func_1(void);

static uint64_t func_1(void) {
  int32_t l_4 = 0xA1220985L;
  int32_t *l_5 = (void *)0;
  int64_t l_8 = 0xBF9F36173948B081LL;
  l_8 |= ((safe_unary_minus_func_int16_t_s(g_3)), l_4);
  return g_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_7;
  csmith_sink_ = g_9;
  platform_main_end(0, 0);
  return 0;
}
