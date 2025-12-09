// Options:   --seed 200190 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_190.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  float f0;
  uint64_t f1;
};

static int32_t g_2 = 0x04CD4536L;
static int32_t g_11 = (-1L);
static int32_t g_20[2][4] = {{(-4L), (-4L), (-4L), (-4L)},
                             {(-4L), (-4L), (-4L), (-4L)}};
static int32_t g_22 = 0x7C28CAE2L;
static union U0 g_24 = {0xB.C1C234p+65};
static union U0 *g_26[3][3] = {
    {&g_24, &g_24, &g_24}, {&g_24, &g_24, &g_24}, {&g_24, &g_24, &g_24}};
static union U0 **volatile g_25 = &g_26[1][0];
static const int32_t g_31 = 1L;
static const int32_t *g_33 = &g_22;
static const int32_t **const volatile g_32 = &g_33;
static volatile uint32_t g_45 = 0xB1ADF13FL;

static uint64_t func_1(void);
static const int32_t *func_6(const int32_t p_7, int32_t *const p_8,
                             int32_t *p_9);

static uint64_t func_1(void) {
  int32_t *l_34 = &g_20[1][3];
  int32_t *l_35 = &g_20[0][2];
  int32_t *l_36 = &g_22;
  int32_t *l_37 = &g_11;
  int32_t *l_38 = (void *)0;
  int32_t l_39 = 1L;
  int32_t *l_40[1][3];
  float l_41 = 0x7.9p-1;
  int16_t l_42 = 0L;
  int32_t l_43 = 0x1A46C428L;
  int32_t l_44 = 0xFB12B2C9L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_40[i][j] = &g_20[0][2];
  }
  for (g_2 = (-4); (g_2 < 23); g_2++) {
    int64_t l_5 = 0xB659D568D526D2E8LL;
    int32_t *l_10 = (void *)0;
    const int32_t *l_30 = &g_31;
    const int32_t **l_29 = &l_30;
    (*g_32) = (l_5, ((*l_29) = func_6(g_2, &g_2, l_10)));
    return g_31;
  }
  g_45--;
  return g_20[1][3];
}

static const int32_t *func_6(const int32_t p_7, int32_t *const p_8,
                             int32_t *p_9) {
  union U0 *const l_23 = &g_24;
  for (g_11 = 0; (g_11 != 18); ++g_11) {
    union U0 l_18 = {0x1.5p+1};
    if ((*p_8)) {
      int32_t *l_19 = &g_20[0][2];
      int32_t *l_21 = &g_22;
      (*l_21) &= ((*l_19) |= (safe_add_func_int8_t_s_s(
                      p_7, (safe_rshift_func_uint8_t_u_s((l_18, g_2), p_7)))));
      (*g_25) = l_23;
    } else {
      int32_t *l_28[1][4] = {
          {&g_20[0][2], &g_20[0][2], &g_20[0][2], &g_20[0][2]}};
      int32_t **l_27 = &l_28[0][2];
      int i, j;
      (*l_27) = &g_20[1][2];
    }
  }
  return &g_11;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_11;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_20[i][j];
    }
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_24.f0;
  csmith_sink_ = g_31;
  csmith_sink_ = g_45;
  platform_main_end(0, 0);
  return 0;
}
