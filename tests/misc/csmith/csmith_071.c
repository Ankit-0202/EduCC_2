// Options:   --seed 100071 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_071.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint8_t f0;
  volatile uint16_t f1;
  const volatile int8_t f2;
};

static uint16_t g_4 = 65535UL;
static volatile struct S1 g_9 = {0x09L, 1UL, 0x67L};
static uint32_t g_13[2] = {3UL, 3UL};
static int32_t g_15 = 0x0E033C22L;
static volatile int32_t g_20 = 0x5DA2CA33L;
static uint16_t g_21[3][4] = {{0x95E0L, 0x95E0L, 0x95E0L, 0x95E0L},
                              {0x95E0L, 0x95E0L, 0x95E0L, 0x95E0L},
                              {0x95E0L, 0x95E0L, 0x95E0L, 0x95E0L}};
static int16_t g_37[4][2] = {{0xB4DBL, 0xB4DBL},
                             {0xB4DBL, 0xB4DBL},
                             {0xB4DBL, 0xB4DBL},
                             {0xB4DBL, 0xB4DBL}};
static int64_t g_41 = 0x330E0E3CEC334572LL;
static uint8_t g_42 = 0x2EL;
static int32_t *g_48 = (void *)0;
static int32_t **volatile g_47 = &g_48;

static const int64_t func_1(void);
static int32_t func_2(int16_t p_3);

static const int64_t func_1(void) {
  uint8_t l_24 = 0xD4L;
  int32_t l_29 = 0x5FE57B6AL;
  int32_t l_30 = (-2L);
  int32_t l_39 = 0x6DE45221L;
  int32_t l_40[3][4];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++)
      l_40[i][j] = 1L;
  }
  if (func_2(g_4)) {
    const uint64_t l_25 = 0x271639956A218F0ELL;
    g_15 &= ((l_24 || l_25) || (safe_div_func_int16_t_s_s(0x452AL, l_24)));
  } else {
    int32_t *l_28[1];
    uint16_t l_31 = 1UL;
    int i;
    for (i = 0; i < 1; i++)
      l_28[i] = &g_15;
    --l_31;
  }
  for (l_29 = 0; (l_29 <= (-28)); l_29--) {
    int32_t *l_36[4][4] = {{&l_30, &l_30, (void *)0, &l_30},
                           {&l_30, &l_30, &l_30, &l_30},
                           {&l_30, &l_30, &l_30, &l_30},
                           {&l_30, &l_30, (void *)0, &l_30}};
    int16_t l_38 = 0x70E9L;
    int i, j;
    g_42--;
    if (g_42) {
      return g_21[2][2];
    } else {
      if ((safe_mul_func_int8_t_s_s(
              ((g_20 && 0xAAL) <=
               ((((void *)0 == &g_13[0]), &g_13[1]) != l_36[2][1])),
              l_40[0][1]))) {
        (*g_47) = &g_15;
        (*g_47) = l_36[3][3];
      } else {
        int64_t l_49 = 2L;
        int32_t l_50[3][2] = {{0L, 0L}, {0L, 0L}, {0L, 0L}};
        int i, j;
        l_50[0][0] = l_49;
      }
    }
  }
  return g_37[2][0];
}

static int32_t func_2(int16_t p_3) {
  uint32_t l_16 = 0x44B0BF24L;
  int32_t l_17 = 0L;
  int32_t l_18 = 0L;
  int32_t l_19 = 0x1AA84CBEL;
  for (g_4 = 0; (g_4 != 52); g_4++) {
    if (p_3)
      break;
  }
  for (g_4 = 0; (g_4 < 20); g_4 = safe_add_func_uint32_t_u_u(g_4, 1)) {
    uint32_t *l_12 = &g_13[0];
    int32_t *l_14[2][2] = {{&g_15, &g_15}, {&g_15, &g_15}};
    int i, j;
    l_16 |= (g_9, (safe_add_func_uint32_t_u_u(p_3, ((*l_12) &= p_3))));
    g_21[2][2]--;
  }
  return l_19;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_9.f0;
  csmith_sink_ = g_9.f1;
  csmith_sink_ = g_9.f2;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_13[i];
  }
  csmith_sink_ = g_15;
  csmith_sink_ = g_20;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_21[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_37[i][j];
    }
  }
  csmith_sink_ = g_41;
  csmith_sink_ = g_42;
  platform_main_end(0, 0);
  return 0;
}
