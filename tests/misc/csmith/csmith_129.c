// Options:   --seed 200129 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_129.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  const uint32_t f0;
};

static int32_t g_2[1] = {0x891F782AL};
static int32_t g_22 = 0xD4782549L;
static int32_t **g_23 = (void *)0;
static struct S1 g_24 = {9UL};
static volatile int32_t g_27 = 0x818264D9L;
static volatile int32_t g_28[3][3] = {
    {(-1L), (-1L), (-1L)}, {(-1L), (-1L), (-1L)}, {(-1L), (-1L), (-1L)}};
static int32_t g_29 = 0xB8342836L;

static int64_t func_1(void);
static int32_t **func_10(int32_t *p_11, int32_t **p_12, int32_t *p_13,
                         int32_t *p_14, struct S1 p_15);

static int64_t func_1(void) {
  float l_6 = 0x3.9p-1;
  int32_t l_9 = (-1L);
  for (g_2[0] = 0; (g_2[0] > (-14)); --g_2[0]) {
    float l_5 = 0x0.3809D0p-72;
    int32_t l_7 = 1L;
    int32_t *l_8 = &l_7;
    (*l_8) = (((0x2250DB85L && g_2[0]) > g_2[0]) != l_7);
    (*l_8) ^= l_9;
  }
  for (l_9 = 0; (l_9 <= 0); l_9 += 1) {
    int32_t *l_20 = &g_2[0];
    int32_t *l_21 = &g_22;
    g_23 =
        func_10(&l_9,
                ((((*l_21) = (safe_mod_func_int32_t_s_s(
                       (-1L), ((((safe_lshift_func_int16_t_s_s(
                                     ((void *)0 != l_20), 14)) <= 0xE467B47EL) |
                                0xF1EDL) ||
                               g_2[0])))),
                  g_2[0]),
                 g_23),
                l_20, l_20, g_24);
  }
  return l_9;
}

static int32_t **func_10(int32_t *p_11, int32_t **p_12, int32_t *p_13,
                         int32_t *p_14, struct S1 p_15) {
  int32_t *l_32 = &g_2[0];
  for (g_22 = (-23); (g_22 >= 11); g_22++) {
    for (g_29 = 0; (g_29 >= 26); g_29 = safe_add_func_uint64_t_u_u(g_29, 5)) {
      int32_t **l_33 = &l_32;
      (*l_33) = l_32;
    }
  }
  return g_23;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_24.f0;
  csmith_sink_ = g_27;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_28[i][j];
    }
  }
  csmith_sink_ = g_29;
  platform_main_end(0, 0);
  return 0;
}
