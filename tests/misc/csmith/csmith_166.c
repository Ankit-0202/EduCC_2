// Options:   --seed 200166 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_166.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
  volatile uint32_t f1;
};

union U1 {
  uint16_t f0;
  volatile struct S0 f1;
};

union U2 {
  struct S0 f0;
};

static int32_t g_7 = 0x72FA4AD7L;
static union U1 g_13 = {4UL};
static union U1 *const g_16 = &g_13;
static union U1 *const *g_15 = &g_16;
static int32_t g_23 = 0L;
static const int32_t *g_22 = &g_23;
static const int32_t **volatile g_24 = &g_22;
static struct S0 g_25[3] = {
    {8UL, 0xCF456574L}, {8UL, 0xCF456574L}, {8UL, 0xCF456574L}};
static union U2 g_27 = {{0x5EL, 0x7E011B55L}};

static union U2 func_1(void);
static union U1 *func_2(int32_t p_3, const int32_t p_4, const union U1 *p_5,
                        union U1 *p_6);

static union U2 func_1(void) {
  const float l_8 = (-0x8.9p+1);
  const int32_t l_9 = 1L;
  const union U1 *l_10 = (void *)0;
  const union U1 **l_11 = &l_10;
  union U1 *l_12[4] = {(void *)0, (void *)0, (void *)0, (void *)0};
  struct S0 *l_26[3][3] = {{&g_25[2], &g_25[1], &g_25[2]},
                           {&g_25[0], &g_25[0], &g_25[0]},
                           {&g_25[2], &g_25[1], &g_25[2]}};
  int i, j;
  (*l_11) = func_2(g_7, l_9, ((*l_11) = l_10), l_12[3]);
  g_13.f1 = g_25[0];
  return g_27;
}

static union U1 *func_2(int32_t p_3, const int32_t p_4, const union U1 *p_5,
                        union U1 *p_6) {
  uint64_t l_14[4][2];
  union U1 *const **l_17 = (void *)0;
  union U1 *const l_19 = (void *)0;
  union U1 *const *l_18 = &l_19;
  uint64_t *l_20 = &l_14[3][1];
  int32_t l_21[3];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++)
      l_14[i][j] = 8UL;
  }
  for (i = 0; i < 3; i++)
    l_21[i] = 0xE5AB06C0L;
  if ((((*l_20) = (l_14[3][1] & ((l_18 = g_15) == (void *)0))) >= l_21[0])) {
    (*g_24) = g_22;
  } else {
    return p_6;
  }
  return p_6;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_13.f1.f0;
  csmith_sink_ = g_13.f1.f1;
  csmith_sink_ = g_23;
  for (i = 0; i < 3; i++) {
  }
  csmith_sink_ = g_27.f0.f0;
  csmith_sink_ = g_27.f0.f1;
  platform_main_end(0, 0);
  return 0;
}
