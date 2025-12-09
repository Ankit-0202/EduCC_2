// Options:   --seed 100042 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_042.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint8_t f0;
};

static volatile int32_t g_3[3] = {0xBB0CB8CEL, 0xBB0CB8CEL, 0xBB0CB8CEL};
static int32_t g_4[2][3] = {{(-5L), 3L, (-5L)}, {(-5L), 3L, (-5L)}};
static int32_t g_5 = 0L;
static uint8_t g_29[2][3] = {{0UL, 0UL, 0UL}, {255UL, 255UL, 255UL}};
static int32_t g_32[4][3] = {{0x296947A3L, 0L, 0x296947A3L},
                             {(-1L), 0x9AA2AAFAL, (-1L)},
                             {0x296947A3L, 0L, 0x296947A3L},
                             {(-1L), 0x9AA2AAFAL, (-1L)}};
static int32_t *g_31 = &g_32[3][1];
static const struct S1 g_33[4] = {{7UL}, {7UL}, {7UL}, {7UL}};
static struct S1 g_35[2] = {{1UL}, {1UL}};

static uint16_t func_1(void);
static const struct S1 func_21(int64_t p_22, uint32_t p_23, int8_t p_24);

static uint16_t func_1(void) {
  uint64_t l_2[2][4] = {{0xC07E17F759609C3FLL, 18446744073709551615UL,
                         0xC07E17F759609C3FLL, 0xC07E17F759609C3FLL},
                        {18446744073709551615UL, 18446744073709551615UL,
                         18446744073709551612UL, 18446744073709551615UL}};
  int32_t l_6 = (-1L);
  int32_t l_16 = 5L;
  int32_t l_17 = 0x55D58009L;
  int i, j;
  for (g_4[0][1] = 0; (g_4[0][1] <= 1); g_4[0][1] += 1) {
    uint32_t l_18 = 0UL;
    for (g_5 = 1; (g_5 >= 0); g_5 -= 1) {
      int32_t *l_7 = &l_6;
      int32_t *l_8 = &l_6;
      int32_t *l_9 = (void *)0;
      int32_t *l_10 = (void *)0;
      int32_t l_11 = 0xCD49FCFBL;
      int32_t *l_12 = &l_11;
      int32_t *l_13 = &l_11;
      int32_t *l_14 = &l_11;
      int32_t *l_15[1];
      int i;
      for (i = 0; i < 1; i++)
        l_15[i] = &l_11;
      --l_18;
    }
    for (l_17 = 0; (l_17 <= 1); l_17 += 1) {
      for (g_5 = 1; (g_5 >= 0); g_5 -= 1) {
        struct S1 *l_34 = &g_35[0];
        int i, j;
        (*l_34) = func_21(
            ((((l_2[g_5][(l_17 + 2)], &g_3[0]) !=
               ((safe_mul_func_int8_t_s_s(
                    ((safe_add_func_int64_t_s_s(g_4[1][0], l_2[0][0])) >= g_5),
                    0x36L)),
                &l_6)) |
              g_4[1][2]),
             l_2[g_5][(l_17 + 2)]),
            g_29[0][2], g_4[0][1]);
      }
    }
  }
  return l_6;
}

static const struct S1 func_21(int64_t p_22, uint32_t p_23, int8_t p_24) {
  int32_t *l_30 = &g_4[1][2];
  g_31 = l_30;
  return g_33[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_3[i];
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  csmith_sink_ = g_5;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_29[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_32[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
  }
  for (i = 0; i < 2; i++) {
  }
  platform_main_end(0, 0);
  return 0;
}
