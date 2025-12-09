// Options:   --seed 300208 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_208.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_2 = 0xB90DA115L;
static int32_t g_14[3] = {1L, 1L, 1L};
static int32_t *g_18 = (void *)0;
static int32_t **volatile g_17 = &g_18;
static int32_t **volatile g_20[1] = {&g_18};

static uint8_t func_1(void);
static int32_t *func_4(const uint8_t p_5, uint32_t p_6, const int32_t *p_7,
                       int64_t p_8);
static uint8_t func_9(int8_t p_10, int32_t *p_11, int8_t p_12);

static uint8_t func_1(void) {
  uint32_t l_3 = 0x54C3C69AL;
  int32_t *l_23 = &g_14[2];
  if (g_2) {
    uint32_t l_15[1][3];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_15[i][j] = 0x7084BC9CL;
    }
    if (l_3) {
      return l_3;
    } else {
      int32_t *l_13 = &g_14[2];
      (*g_17) =
          (l_3, func_4(func_9(l_3, l_13, l_15[0][1]), l_3, l_13, l_15[0][2]));
    }
  } else {
    uint64_t l_19[2];
    int32_t *l_21 = &g_14[2];
    uint16_t l_25 = 0x5342L;
    int i;
    for (i = 0; i < 2; i++)
      l_19[i] = 0xD7770B168F928D9BLL;
    if (l_19[0]) {
      int32_t l_22 = 0x3997B09BL;
      l_21 = (*g_17);
      l_22 |= 1L;
    } else {
      int32_t **l_24 = &l_21;
      g_20[0] = &g_18;
      (*l_24) = l_23;
    }
    (*l_23) ^= l_25;
  }
  return g_14[2];
}

static int32_t *func_4(const uint8_t p_5, uint32_t p_6, const int32_t *p_7,
                       int64_t p_8) {
  int32_t *l_16 = &g_14[0];
  for (p_6 = 0; (p_6 <= 2); p_6 += 1) {
    if ((*p_7))
      break;
  }
  (*l_16) = 0x2BA7B7E8L;
  return l_16;
}

static uint8_t func_9(int8_t p_10, int32_t *p_11, int8_t p_12) { return p_12; }

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_14[i];
  }
  platform_main_end(0, 0);
  return 0;
}
