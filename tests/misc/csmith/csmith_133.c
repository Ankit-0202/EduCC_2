// Options:   --seed 200133 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_133.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int64_t f0;
  volatile uint64_t f1;
  int64_t f2;
};

static uint32_t g_9 = 4294967295UL;
static uint64_t g_14[3][3] = {
    {0UL, 0UL, 0UL}, {0UL, 0xF17E2F9D44C039ECLL, 0UL}, {0UL, 0UL, 0UL}};
static int32_t g_17 = 0L;
static const int32_t *g_16 = &g_17;
static struct S1 g_23 = {0xFDFE924F63ABEFA0LL, 18446744073709551615UL, -4L};

static int8_t func_1(void);
static int64_t func_2(uint16_t p_3, int16_t p_4, uint32_t p_5);

static int8_t func_1(void) {
  float l_10 = 0x2.9p-1;
  int32_t l_11 = (-7L);
  uint64_t *l_12 = (void *)0;
  uint64_t *l_13[2];
  int8_t l_15 = 1L;
  int i;
  for (i = 0; i < 2; i++)
    l_13[i] = &g_14[0][0];
  if ((func_2((safe_rshift_func_uint16_t_u_u(
                  (!g_9), (l_11 < ((g_14[0][0] |= 0x0315362DAAB72B21LL) &
                                   18446744073709551613UL)))),
              g_9, l_15) |
       g_17)) {
    int32_t l_24[2];
    int32_t *l_25 = &g_17;
    int32_t **l_27 = &l_25;
    int i;
    for (i = 0; i < 2; i++)
      l_24[i] = 0x44ED25E4L;
    if ((g_14[1][0], ((safe_lshift_func_uint8_t_u_u(g_14[0][0], 7)) <=
                      (((safe_mul_func_int8_t_s_s((g_23, 0L), 0xEEL)) |
                        65535UL) == l_24[0])))) {
      return g_23.f1;
    } else {
      int32_t **l_26 = &l_25;
      g_16 = ((*l_26) = l_25);
    }
    (*l_27) = &g_17;
  } else {
    return g_17;
  }
  for (g_17 = 16; (g_17 >= 7); --g_17) {
    for (g_9 = 0; (g_9 <= 2); g_9 += 1) {
      int i, j;
      return g_14[g_9][g_9];
    }
  }
  return l_11;
}

static int64_t func_2(uint16_t p_3, int16_t p_4, uint32_t p_5) {
  const int32_t *l_18[3];
  int i;
  for (i = 0; i < 3; i++)
    l_18[i] = (void *)0;
  l_18[0] = g_16;
  for (g_9 = 0; (g_9 <= 2); g_9 += 1) {
    return g_14[0][1];
  }
  return g_14[2][2];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_14[i][j];
    }
  }
  csmith_sink_ = g_17;
  csmith_sink_ = g_23.f0;
  csmith_sink_ = g_23.f1;
  csmith_sink_ = g_23.f2;
  platform_main_end(0, 0);
  return 0;
}
