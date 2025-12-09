// Options:   --seed 200169 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_169.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
  uint8_t f1;
  volatile int8_t f2;
};

struct S1 {
  volatile int8_t f0;
  uint32_t f1;
};

union U5 {
  const uint32_t f0;
  const volatile int8_t f1;
};

static volatile int32_t g_2[2][4] = {
    {0L, 0xDEEC5416L, 0L, 0L},
    {0xDEEC5416L, 0xDEEC5416L, 0xF6C74AA0L, 0xDEEC5416L}};
static volatile int32_t g_3 = 0x7D0FA516L;
static volatile int32_t g_4 = 9L;
static int32_t g_5 = 0x57B5BF2DL;
static volatile int32_t g_8 = (-10L);
static int32_t g_9[1] = {0x44401D1BL};
static volatile int32_t *volatile g_26 = (void *)0;
static volatile int32_t *volatile g_27 = &g_4;
static volatile int32_t *volatile g_30 = &g_3;
static const union U5 g_32 = {7UL};
static struct S0 g_34 = {0x9EL, 255UL, 0x78L};
static const struct S0 *volatile g_33[4][4] = {{&g_34, &g_34, &g_34, &g_34},
                                               {&g_34, &g_34, &g_34, &g_34},
                                               {&g_34, &g_34, &g_34, &g_34},
                                               {&g_34, &g_34, &g_34, &g_34}};
static struct S0 *g_38[4][4] = {{&g_34, &g_34, &g_34, &g_34},
                                {&g_34, &g_34, &g_34, &g_34},
                                {&g_34, &g_34, &g_34, &g_34},
                                {&g_34, &g_34, &g_34, &g_34}};
static int8_t g_52 = 0xA4L;
static volatile struct S1 g_58 = {1L, 7UL};
static const union U5 g_70[4] = {
    {0x966D8DA3L}, {0x966D8DA3L}, {0x966D8DA3L}, {0x966D8DA3L}};

static const union U5 func_1(void);
static const uint16_t func_14(int32_t p_15, const int16_t p_16, int16_t p_17,
                              uint8_t p_18);

static const union U5 func_1(void) {
  uint8_t l_21 = 0x80L;
  struct S0 *l_39 = &g_34;
  int32_t l_65[4] = {0x5434BB1BL, 0x5434BB1BL, 0x5434BB1BL, 0x5434BB1BL};
  int64_t l_66 = 1L;
  uint32_t l_67 = 18446744073709551609UL;
  int i;
  for (g_5 = (-19); (g_5 > 19); g_5 = safe_add_func_int8_t_s_s(g_5, 9)) {
    int8_t l_12 = 0x0DL;
    for (g_9[0] = 0; (g_9[0] >= 13);
         g_9[0] = safe_add_func_int16_t_s_s(g_9[0], 1)) {
      if (l_12)
        break;
    }
    if ((+func_14(((safe_lshift_func_int8_t_s_s(
                       l_21, ((safe_add_func_uint32_t_u_u(
                                  (safe_lshift_func_int8_t_s_u(g_2[1][2],
                                                               (4L == l_21))),
                                  9UL)) ^
                              0xC6L))),
                   g_2[0][1]),
                  g_5, l_12, g_9[0]))) {
      return g_32;
    } else {
      const struct S0 *volatile *l_35 = &g_33[1][1];
      (*l_35) = g_33[0][3];
    }
  }
  if (l_21) {
    struct S0 *l_36 = (void *)0;
    struct S0 **l_37[2][1];
    uint8_t l_55 = 0UL;
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_37[i][j] = (void *)0;
    }
    if (((g_38[1][1] = l_36) != (l_39 = (void *)0))) {
      uint8_t l_48 = 0xB5L;
      int32_t *l_49 = (void *)0;
      g_5 ^= (g_4 < (safe_lshift_func_uint8_t_u_u(
                        (safe_mul_func_uint16_t_u_u(
                            8UL, (safe_rshift_func_uint16_t_u_s(
                                     (safe_mod_func_int32_t_s_s(l_48, l_21)),
                                     g_32.f0)))),
                        1)));
    } else {
      int32_t *l_50 = &g_9[0];
      int32_t *l_51 = (void *)0;
      int32_t *l_53 = &g_9[0];
      int32_t *l_54 = &g_9[0];
      volatile struct S1 *l_59 = &g_58;
      l_55--;
      (*l_59) = g_58;
    }
  } else {
    int32_t *l_60 = &g_9[0];
    int32_t *l_61 = &g_9[0];
    int32_t *l_62 = (void *)0;
    int32_t *l_63 = &g_5;
    int32_t *l_64[2];
    int i;
    for (i = 0; i < 2; i++)
      l_64[i] = (void *)0;
    l_67++;
  }
  return g_70[1];
}

static const uint16_t func_14(int32_t p_15, const int16_t p_16, int16_t p_17,
                              uint8_t p_18) {
  uint32_t l_28 = 1UL;
  int32_t *l_29 = (void *)0;
  const uint32_t l_31 = 0UL;
  (*g_27) = g_3;
  if ((l_28 > ((l_29 == l_29) & p_18))) {
    return g_2[1][3];
  } else {
    (*g_30) = (*g_27);
  }
  return l_31;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_8;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_9[i];
  }
  csmith_sink_ = g_32.f0;
  csmith_sink_ = g_32.f1;
  csmith_sink_ = g_34.f0;
  csmith_sink_ = g_34.f1;
  csmith_sink_ = g_34.f2;
  csmith_sink_ = g_52;
  csmith_sink_ = g_58.f0;
  csmith_sink_ = g_58.f1;
  for (i = 0; i < 4; i++) {
  }
  platform_main_end(0, 0);
  return 0;
}
