// Options:   --seed 100090 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_090.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0x841B3C69L;
static volatile int32_t g_3 = (-8L);
static int32_t g_4 = (-2L);
static int32_t g_12 = 9L;
static int32_t *volatile g_11 = &g_12;
static int32_t g_22[1] = {0x73468807L};
static uint32_t g_29 = 4294967289UL;
static uint32_t g_31 = 0x20A6FF60L;
static int32_t **volatile g_37 = (void *)0;

static uint64_t func_1(void);
static int32_t *func_15(int32_t p_16, int8_t p_17, uint16_t p_18, uint32_t p_19,
                        int32_t *const p_20);

static uint64_t func_1(void) {
  int32_t l_27 = 0x758E356EL;
  for (g_4 = 22; (g_4 == (-23)); g_4--) {
  }
  return l_27;
}

static int32_t *func_15(int32_t p_16, int8_t p_17, uint16_t p_18, uint32_t p_19,
                        int32_t *const p_20) {
  int32_t *l_35 = &g_4;
  for (p_17 = 0; (p_17 >= 0); p_17 -= 1) {
    int32_t *l_34 = &g_22[p_17];
    int32_t **l_33 = &l_34;
    int i;
    (*l_33) = &g_22[p_17];
    g_3 ^= g_22[p_17];
  }
  return l_35;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_12;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_22[i];
  }
  csmith_sink_ = g_29;
  csmith_sink_ = g_31;
  platform_main_end(0, 0);
  return 0;
}
