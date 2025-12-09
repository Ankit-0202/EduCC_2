// Options:   --seed 100016 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_016.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_6 = 0x65E08CCCL;
static int32_t *g_11 = &g_6;
static int32_t **const volatile g_10 = &g_11;

static const int64_t func_1(void);
static int32_t *func_2(uint32_t p_3);

static const int64_t func_1(void) {
  const int32_t l_12 = 1L;
  (*g_10) = func_2((0xED23B618L != 1UL));
  return l_12;
}

static int32_t *func_2(uint32_t p_3) {
  uint8_t l_4 = 1UL;
  int32_t *l_9 = &g_6;
  if (l_4) {
    int32_t *l_5 = &g_6;
    return l_5;
  } else {
    int32_t *l_7 = &g_6;
    int32_t **l_8 = &l_7;
    (*l_8) = l_7;
    return l_9;
  }
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  platform_main_end(0, 0);
  return 0;
}
