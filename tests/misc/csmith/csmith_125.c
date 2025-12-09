// Options:   --seed 200125 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_125.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
};

struct S1 {
  uint8_t f0;
  const int64_t f1;
};

static volatile struct S1 g_4 = {1UL, 0L};
static int32_t g_7 = 7L;
static float g_11 = 0xC.29478Cp+65;
static uint64_t g_13 = 18446744073709551611UL;
static float g_17[1] = {0x6.7AB6CEp-47};
static const uint32_t g_19[2] = {0xD9532955L, 0xD9532955L};
static int32_t g_21 = 0x3C47AA29L;

static uint32_t func_1(void);
static struct S1 func_2(struct S0 p_3);

static uint32_t func_1(void) {
  struct S0 l_5 = {0x95L};
  const uint32_t l_18[2][1] = {{1UL}, {1UL}};
  int32_t *l_20 = &g_21;
  int i, j;
  (*l_20) ^= (((func_2((g_4, l_5)), g_4.f1) ^ l_18[0][0]) < g_19[1]);
  for (g_13 = 0; (g_13 < 53); ++g_13) {
    uint32_t l_25[2];
    int i;
    for (i = 0; i < 2; i++)
      l_25[i] = 8UL;
    for (g_7 = 0; (g_7 >= 0); g_7 -= 1) {
      (*l_20) &= (0x10L && (safe_unary_minus_func_uint32_t_u(0x826243A5L)));
      l_25[1]--;
    }
  }
  return g_4.f1;
}

static struct S1 func_2(struct S0 p_3) {
  uint32_t l_6[4] = {0x60EC01E6L, 0x60EC01E6L, 0x60EC01E6L, 0x60EC01E6L};
  float l_10[3];
  int32_t l_12[3][3] = {{(-1L), 0x68CB667FL, (-1L)},
                        {(-1L), 0x68CB667FL, (-1L)},
                        {(-1L), 0x68CB667FL, (-1L)}};
  struct S1 l_16 = {0x06L, -10L};
  int i, j;
  for (i = 0; i < 3; i++)
    l_10[i] = 0x1.Bp+1;
  for (p_3.f0 = 0; (p_3.f0 <= 3); p_3.f0 += 1) {
    int32_t *l_8 = &g_7;
    int32_t *l_9[2];
    int i;
    for (i = 0; i < 2; i++)
      l_9[i] = &g_7;
    for (g_7 = 0; (g_7 <= 3); g_7 += 1) {
      return g_4;
    }
    g_13++;
  }
  return l_16;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4.f0;
  csmith_sink_ = g_4.f1;
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  csmith_sink_ = g_13;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_17[i];
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_19[i];
  }
  csmith_sink_ = g_21;
  platform_main_end(0, 0);
  return 0;
}
