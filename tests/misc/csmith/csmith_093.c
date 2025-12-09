// Options:   --seed 100093 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_093.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 0x43D837BCL;
static int32_t g_6 = (-1L);
static int32_t g_17[1][2] = {{0x667F5AEEL, 0x667F5AEEL}};
static volatile int32_t g_19[1] = {0x24B969B4L};
static volatile int32_t *g_18 = &g_19[0];
static uint16_t g_26 = 65528UL;
static uint32_t g_29 = 4294967295UL;

static int32_t func_1(void);
static int32_t func_7(int8_t p_8, uint16_t p_9);

static int32_t func_1(void) {
  const uint64_t l_25 = 2UL;
  int32_t l_27 = (-1L);
  int16_t *l_28[3];
  int32_t l_30 = (-9L);
  int32_t l_31 = 0x25A95506L;
  int i;
  for (i = 0; i < 3; i++)
    l_28[i] = (void *)0;
  for (g_2 = (-29); (g_2 > 20); g_2++) {
    int16_t l_10 = 1L;
    if (g_2) {
      int32_t *l_5 = &g_6;
      (*l_5) ^= g_2;
    } else {
      int64_t l_13 = 0xD927F7B6FE6D39C7LL;
      int32_t *l_16 = &g_17[0][1];
      (*l_16) &=
          func_7(((l_10, (((g_2 | (safe_sub_func_int32_t_s_s(
                                      ((l_10 <= g_2) != l_10), l_13))) >= g_6),
                          (void *)0)) == &g_6),
                 g_2);
    }
    (*g_18) = (g_18 == (void *)0);
  }
  (*g_18) =
      ((l_30 =
            (g_29 |=
             ((~(l_27 |= (0UL >= (safe_sub_func_uint8_t_u_u(
                                     ((((safe_mul_func_int16_t_s_s(
                                            g_2, (g_19[0] ^ l_25))) >= l_25) ^
                                       g_26) >= 0xC2A91181L),
                                     l_25))))) ||
              g_17[0][0]))),
       (*g_18));
  return l_31;
}

static int32_t func_7(int8_t p_8, uint16_t p_9) {
  int32_t l_14 = 0x643B8A27L;
  int64_t l_15[2];
  int i;
  for (i = 0; i < 2; i++)
    l_15[i] = (-1L);
  l_14 &= g_2;
  for (p_9 = 0; (p_9 <= 1); p_9 += 1) {
    int i;
    return l_15[p_9];
  }
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
  csmith_sink_ = g_6;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_17[i][j];
    }
  }
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_19[i];
  }
  csmith_sink_ = g_26;
  csmith_sink_ = g_29;
  platform_main_end(0, 0);
  return 0;
}
