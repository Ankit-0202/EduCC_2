// Options:   --seed 200136 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_136.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
  int16_t f1;
};

struct S2 {
  volatile struct S0 f0;
  int8_t f1;
};

struct S3 {
  const struct S0 f0;
  uint16_t f1;
  int16_t f2;
};

static int32_t g_3 = 0xEEE2FDE2L;
static struct S3 g_16[3] = {{{0xDDL, 0x8407L}, 65535UL, 1L},
                            {{0xDDL, 0x8407L}, 65535UL, 1L},
                            {{0xDDL, 0x8407L}, 65535UL, 1L}};
static struct S3 *g_15 = &g_16[2];
static int32_t g_23[3] = {0L, 0L, 0L};
static int32_t *g_22[1] = {&g_23[2]};
static struct S2 g_33 = {{255UL, 8L}, 0x1EL};
static struct S2 g_35 = {{0x67L, 5L}, -10L};
static struct S3 g_39 = {{6UL, 0x0C28L}, 4UL, 0xE7B2L};

static uint8_t func_1(void);
static struct S3 *func_4(int32_t p_5, struct S3 *p_6, struct S3 *p_7,
                         uint32_t p_8, int16_t p_9);

static uint8_t func_1(void) {
  int32_t *l_2[4][3] = {{&g_3, &g_3, &g_3},
                        {&g_3, &g_3, &g_3},
                        {&g_3, &g_3, &g_3},
                        {&g_3, &g_3, &g_3}};
  int64_t l_17[4][3] = {{0L, 0L, 0L}, {0L, 0L, 0L}, {0L, 0L, 0L}, {0L, 0L, 0L}};
  struct S3 **l_37[2];
  struct S3 *l_38 = &g_39;
  int i, j;
  for (i = 0; i < 2; i++)
    l_37[i] = &g_15;
  g_3 = 4L;
  l_38 = func_4(
      (+((((safe_rshift_func_int8_t_s_u(
               (g_3,
                (0L >
                 (((safe_mul_func_uint8_t_u_u((&g_3 != &g_3), 0x31L)) | g_3) ||
                  0x83398963EC58F553LL))),
               4)),
           g_3) <= g_3) ^
         g_3)),
      g_15, &g_16[0], l_17[2][2], g_16[2].f2);
  return g_33.f0.f0;
}

static struct S3 *func_4(int32_t p_5, struct S3 *p_6, struct S3 *p_7,
                         uint32_t p_8, int16_t p_9) {
  int32_t l_27[4][2];
  int32_t l_29 = (-1L);
  struct S3 **l_30 = (void *)0;
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++)
      l_27[i][j] = (-1L);
  }
  for (g_3 = 0; (g_3 != 4); ++g_3) {
    int32_t *l_20 = &g_3;
    int32_t **l_21[4] = {&l_20, &l_20, &l_20, &l_20};
    uint8_t l_26 = 6UL;
    float l_28[2];
    int i;
    for (i = 0; i < 2; i++)
      l_28[i] = (-0x1.Dp-1);
    g_23[0] = ((g_22[0] = l_20) != &g_3);
    if ((l_29 =
             ((9UL == ((safe_div_func_int64_t_s_s(l_26, l_27[0][1])) || p_5)) ^
              l_27[3][1]))) {
      struct S3 ***l_31 = (void *)0;
      struct S3 ***l_32 = (void *)0;
      l_30 = l_30;
    } else {
      struct S2 *l_34[3];
      int32_t *l_36 = (void *)0;
      int i;
      for (i = 0; i < 3; i++)
        l_34[i] = &g_33;
      g_35 = g_33;
      l_36 = &g_3;
    }
  }
  return &g_16[0];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 3; i++) {
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_23[i];
  }
  csmith_sink_ = g_33.f0.f0;
  csmith_sink_ = g_33.f0.f1;
  csmith_sink_ = g_33.f1;
  csmith_sink_ = g_35.f0.f0;
  csmith_sink_ = g_35.f0.f1;
  csmith_sink_ = g_35.f1;
  csmith_sink_ = g_39.f0.f0;
  csmith_sink_ = g_39.f0.f1;
  csmith_sink_ = g_39.f1;
  csmith_sink_ = g_39.f2;
  platform_main_end(0, 0);
  return 0;
}
