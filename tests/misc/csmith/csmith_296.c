// Options:   --seed 300296 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_296.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 1L;
static int64_t g_19 = 7L;
static int32_t g_21[2][1] = {{0x4B2E809BL}, {0x4B2E809BL}};
static volatile int32_t g_22 = 0xDDA8DB88L;
static int32_t g_23 = 0L;
static int16_t g_24[1][1] = {{0x214FL}};
static volatile uint32_t g_25 = 4294967295UL;

static uint16_t func_1(void);

static uint16_t func_1(void) {
  int32_t *l_2 = &g_3;
  int32_t *l_4 = (void *)0;
  int32_t *l_5 = &g_3;
  int32_t l_6 = 0x108F8256L;
  int32_t l_7 = 0xEA6801FCL;
  int32_t *l_8 = (void *)0;
  int32_t *l_9 = &l_7;
  int32_t *l_10 = &l_7;
  int32_t *l_11 = &l_6;
  int32_t *l_12 = &l_7;
  int32_t *l_13 = &l_6;
  int32_t *l_14 = &l_7;
  int32_t *l_15 = (void *)0;
  int32_t *l_16 = (void *)0;
  int32_t *l_17 = &l_7;
  int32_t *l_18[2][3] = {{&l_6, &l_6, &l_6}, {&g_3, &g_3, &g_3}};
  int8_t l_20 = 0xEBL;
  int32_t l_28[3];
  int i, j;
  for (i = 0; i < 3; i++)
    l_28[i] = 0x6A77D77FL;
  --g_25;
  return l_28[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_19;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_21[i][j];
    }
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_23;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_24[i][j];
    }
  }
  csmith_sink_ = g_25;
  platform_main_end(0, 0);
  return 0;
}
