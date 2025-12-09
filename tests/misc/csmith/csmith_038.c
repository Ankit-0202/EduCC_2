// Options:   --seed 100038 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_038.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  const uint8_t f0;
  const uint32_t f1;
};

static uint8_t g_2[3][4] = {{0x72L, 255UL, 0x72L, 0x72L},
                            {255UL, 255UL, 0x14L, 255UL},
                            {255UL, 0x72L, 0x72L, 255UL}};
static volatile int32_t g_3 = 0x55B7CEFAL;
static volatile int32_t g_4 = 0x9AC196A1L;
static int32_t g_5 = 0x9CC14173L;
static int16_t g_19 = (-1L);
static int32_t g_31 = (-1L);
static uint32_t g_32 = 18446744073709551614UL;
static int16_t *volatile g_39 = (void *)0;
static int32_t *volatile g_43 = &g_31;
static int8_t g_57 = 0x95L;

static uint8_t func_1(void);
static int32_t func_6(uint16_t p_7, union U0 p_8, uint16_t p_9, uint16_t p_10);

static uint8_t func_1(void) {
  uint64_t l_17[1][3];
  int16_t l_22[4][2] = {
      {(-9L), 0x5DCEL}, {0x5DCEL, (-9L)}, {0x5DCEL, 0x5DCEL}, {(-9L), 0x5DCEL}};
  union U0 l_23 = {3UL};
  int32_t *l_37[4];
  uint32_t l_44 = 0x3F116E8CL;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_17[i][j] = 3UL;
  }
  for (i = 0; i < 4; i++)
    l_37[i] = (void *)0;
  for (g_5 = 0; (g_5 <= 2); g_5 += 1) {
    int16_t *l_18 = &g_19;
    uint64_t *l_20 = &l_17[0][2];
    int32_t l_21[4][1];
    int32_t l_68[1];
    int32_t l_78[1][2];
    uint32_t l_79 = 0x50740728L;
    int i, j;
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 1; j++)
        l_21[i][j] = 0L;
    }
    for (i = 0; i < 1; i++)
      l_68[i] = (-8L);
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_78[i][j] = 0x441872AFL;
    }
  }
  return g_3;
}

static int32_t func_6(uint16_t p_7, union U0 p_8, uint16_t p_9, uint16_t p_10) {
  volatile int32_t **l_24 = (void *)0;
  volatile int32_t *l_25 = &g_3;
  l_25 = &g_3;
  for (p_10 = 1; (p_10 < 3); p_10++) {
    int32_t *l_28 = (void *)0;
    int32_t *l_29 = (void *)0;
    int32_t *l_30[3];
    int i;
    for (i = 0; i < 3; i++)
      l_30[i] = &g_31;
    g_32++;
  }
  return g_5;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_19;
  csmith_sink_ = g_31;
  csmith_sink_ = g_32;
  csmith_sink_ = g_57;
  platform_main_end(0, 0);
  return 0;
}
