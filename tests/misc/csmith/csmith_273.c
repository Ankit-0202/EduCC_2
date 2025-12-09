// Options:   --seed 300273 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_273.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4 = 0x0985A957L;
static volatile uint32_t g_5[2] = {0xAAD8530DL, 0xAAD8530DL};
static volatile int32_t g_10 = 0xA028EA38L;
static volatile int32_t g_11 = 0x515FDC8DL;
static int32_t g_12 = (-1L);
static uint16_t g_17 = 65528UL;

static const int32_t func_1(void);

static const int32_t func_1(void) {
  int32_t l_2[2][3] = {{1L, 1L, 1L}, {0xF0A290BEL, 0xF0A290BEL, 0xF0A290BEL}};
  int32_t *l_3[2];
  int i, j;
  for (i = 0; i < 2; i++)
    l_3[i] = &g_4;
  g_5[1]++;
  for (g_4 = 0; (g_4 != 23); g_4++) {
    int64_t l_15[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_15[i][j] = 0xF889E022A5BC4220LL;
    }
    for (g_12 = 0; (g_12 != (-21)); g_12--) {
      uint16_t *l_16 = &g_17;
      int32_t l_18 = 0xB0A6D081L;
      int32_t l_21 = 0x94D0E834L;
      l_18 ^= (0x753EL == (((-1L) <= ((*l_16) &= l_15[2][0])) > 0x1A6BL));
      l_21 ^=
          ((safe_div_func_int16_t_s_s(((void *)0 == &g_12),
                                      ((l_18 = 0x56L) & l_15[2][0]))) != g_17);
    }
  }
  return g_10;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_5[i];
  }
  csmith_sink_ = g_10;
  csmith_sink_ = g_11;
  csmith_sink_ = g_12;
  csmith_sink_ = g_17;
  platform_main_end(0, 0);
  return 0;
}
