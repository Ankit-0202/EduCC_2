// Options:   --seed 100047 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_047.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 1L;
static int32_t g_3 = 0x5F5C184CL;
static int32_t g_9[2][4] = {
    {0x925EF2C3L, 0xDFCF09CCL, 0x925EF2C3L, 0x925EF2C3L},
    {0xDFCF09CCL, 0xDFCF09CCL, 0xFEF9D786L, 0xDFCF09CCL}};
static int32_t *g_8[1] = {&g_9[0][1]};

static int8_t func_1(void);

static int8_t func_1(void) {
  int32_t *l_6 = (void *)0;
  int32_t l_10 = (-1L);
  int32_t *l_11[2][3];
  int8_t l_12 = 0L;
  uint16_t l_13[3][4] = {{65528UL, 65528UL, 65528UL, 65528UL},
                         {65528UL, 65528UL, 65528UL, 65528UL},
                         {65528UL, 65528UL, 65528UL, 65528UL}};
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++)
      l_11[i][j] = &l_10;
  }
  for (g_3 = 0; (g_3 > 2); ++g_3) {
    int32_t **l_7 = &l_6;
    g_8[0] = ((*l_7) = l_6);
    if (l_10)
      break;
  }
  ++l_13[1][2];
  return g_2;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_9[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
