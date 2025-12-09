// Options:   --seed 200199 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_199.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2[3] = {0xE7937D8EL, 0xE7937D8EL, 0xE7937D8EL};
static volatile int8_t g_8 = 0x9DL;
static volatile int8_t *g_7 = &g_8;
static uint32_t g_10 = 4294967286UL;
static int8_t g_14[1][1] = {{1L}};
static int32_t g_16 = 0L;
static int32_t g_32 = 0x021AA291L;
static int8_t g_34 = 0L;
static volatile int8_t g_35[4][2] = {
    {0x0DL, 0x0DL}, {0x0DL, 0x0DL}, {0x0DL, 0x0DL}, {0x0DL, 0x0DL}};
static volatile uint64_t g_36[3] = {
    18446744073709551611UL, 18446744073709551611UL, 18446744073709551611UL};
static float g_45[4] = {0xC.C02768p-85, 0xC.C02768p-85, 0xC.C02768p-85,
                        0xC.C02768p-85};

static int64_t func_1(void);

static int64_t func_1(void) {
  uint32_t l_11 = 0x51554671L;
  int32_t l_26[3];
  int i;
  for (i = 0; i < 3; i++)
    l_26[i] = 0x48ABB75DL;
  for (g_2[1] = (-18); (g_2[1] == 0);
       g_2[1] = safe_add_func_int64_t_s_s(g_2[1], 7)) {
    uint32_t *l_9 = &g_10;
    int8_t *l_12 = (void *)0;
    int8_t *l_13 = &g_14[0][0];
    int32_t l_18 = 0x826A056EL;
    int32_t l_33[4] = {1L, 1L, 1L, 1L};
    int i;
    if ((safe_lshift_func_int8_t_s_s(
            ((*l_13) = ((g_7 != ((g_2[1] && ((*l_9) = 0UL)), &g_8)) | l_11)),
            0))) {
      int32_t *l_15 = &g_16;
      int32_t *l_17 = &g_16;
      int32_t *l_19 = (void *)0;
      int32_t *l_20 = &l_18;
      int32_t *l_21 = &l_18;
      int32_t *l_22 = &g_16;
      int32_t *l_23 = (void *)0;
      int32_t *l_24 = &g_16;
      int32_t *l_25 = &g_16;
      int32_t *l_27 = &g_16;
      int32_t *l_28 = &g_16;
      int32_t *l_29 = &l_26[2];
      int32_t *l_30 = &l_18;
      int32_t *l_31[3][3] = {{&l_26[0], &l_18, &l_26[0]},
                             {&l_26[2], &l_26[2], &l_26[2]},
                             {&l_26[0], &l_18, &l_26[0]}};
      int i, j;
      ++g_36[0];
      if (l_26[0])
        continue;
    } else {
      const float l_39[4] = {0xF.4C9FF7p+88, 0xF.4C9FF7p+88, 0xF.4C9FF7p+88,
                             0xF.4C9FF7p+88};
      int32_t *l_40 = &l_18;
      int32_t *l_41 = (void *)0;
      int32_t *l_42 = &l_18;
      int32_t *l_43 = (void *)0;
      int32_t *l_44[3];
      uint32_t l_46[2];
      int i;
      for (i = 0; i < 3; i++)
        l_44[i] = &l_18;
      for (i = 0; i < 2; i++)
        l_46[i] = 0x3B016FEFL;
      if (g_10)
        break;
      --l_46[0];
    }
  }
  return l_11;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_8;
  csmith_sink_ = g_10;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_14[i][j];
    }
  }
  csmith_sink_ = g_16;
  csmith_sink_ = g_32;
  csmith_sink_ = g_34;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_35[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_36[i];
  }
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_45[i];
  }
  platform_main_end(0, 0);
  return 0;
}
