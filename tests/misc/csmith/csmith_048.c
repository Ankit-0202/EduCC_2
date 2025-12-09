// Options:   --seed 100048 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_048.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
};

struct S1 {
  int16_t f0;
};

union U3 {
  uint16_t f0;
};

static union U3 g_2[1][2] = {{{0UL}, {0UL}}};
static volatile int32_t g_3 = (-1L);
static int32_t g_4 = 0xC5165352L;
static int64_t g_12 = (-1L);
static uint64_t g_20 = 0x7209C3997B09B37DLL;
static uint64_t g_23[4] = {0xDF8E3BF118C84B7BLL, 0xDF8E3BF118C84B7BLL,
                           0xDF8E3BF118C84B7BLL, 0xDF8E3BF118C84B7BLL};
static struct S1 g_25 = {0x5342L};
static struct S1 g_27 = {1L};
static struct S1 *const **volatile g_30[4] = {(void *)0, (void *)0, (void *)0,
                                              (void *)0};
static int32_t *g_36 = &g_4;
static int32_t **volatile g_35 = &g_36;
static struct S0 g_37 = {0xC4L};

static struct S0 func_1(void);
static uint16_t func_7(int64_t p_8, int8_t p_9, uint8_t p_10);

static struct S0 func_1(void) {
  struct S0 l_38 = {0UL};
  for (g_4 = 0; (g_4 <= 0); g_4 += 1) {
    int64_t *l_11 = &g_12;
    int32_t l_13 = 0x9884CB8FL;
    uint8_t l_14[1];
    struct S1 *const l_29[2] = {&g_25, &g_25};
    struct S1 *const *l_28 = &l_29[0];
    int i;
    for (i = 0; i < 1; i++)
      l_14[i] = 6UL;
    if ((safe_rshift_func_uint16_t_u_u(func_7(((*l_11) = g_3), l_13, l_14[0]),
                                       7))) {
      for (g_27.f0 = 0; (g_27.f0 >= 0); g_27.f0 -= 1) {
        struct S1 *const **l_31 = &l_28;
        (*l_31) = l_28;
      }
    } else {
      for (g_20 = 0; (g_20 <= 0); g_20 += 1) {
        struct S1 *l_32 = &g_25;
        struct S1 **l_33 = &l_32;
        (*l_33) = l_32;
      }
    }
    for (g_27.f0 = 0; (g_27.f0 >= 0); g_27.f0 -= 1) {
      for (g_25.f0 = 0; (g_25.f0 >= 0); g_25.f0 -= 1) {
        (*g_35) = (((*l_11) = (+0x7399D012CD0AB83DLL)), &g_4);
        return g_37;
      }
      for (l_13 = 0; (l_13 <= 0); l_13 += 1) {
        return l_38;
      }
    }
  }
  return l_38;
}

static uint16_t func_7(int64_t p_8, int8_t p_9, uint8_t p_10) {
  int64_t *l_15[2];
  int32_t l_18 = (-9L);
  uint64_t *l_19 = &g_20;
  uint64_t *l_21 = (void *)0;
  uint64_t *l_22[4] = {&g_23[0], &g_23[0], &g_23[0], &g_23[0]};
  int32_t l_24 = 0x511EC1FCL;
  struct S1 *l_26[1];
  int i;
  for (i = 0; i < 2; i++)
    l_15[i] = &g_12;
  for (i = 0; i < 1; i++)
    l_26[i] = &g_25;
  g_27 = (g_25 = ((l_24 ^=
                   ((*l_19) = ((((l_15[0] != (void *)0) ^
                                 (safe_mul_func_uint16_t_u_u(l_18, 0xF18CL))) &&
                                g_12) ||
                               p_8))),
                  g_25));
  return p_10;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_12;
  csmith_sink_ = g_20;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_23[i];
  }
  csmith_sink_ = g_25.f0;
  csmith_sink_ = g_27.f0;
  csmith_sink_ = g_37.f0;
  platform_main_end(0, 0);
  return 0;
}
