// Options:   --seed 300286 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_286.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint16_t f0;
  const volatile uint32_t f1;
  volatile uint32_t f2;
};

static const int8_t g_12 = 0x44L;
static const int8_t *g_11 = &g_12;
static int8_t *g_13 = (void *)0;
static volatile int32_t g_18 = 1L;
static struct S1 g_21 = {0x8F2BL, 0x167C28CAL, 0UL};
static int32_t g_27[3] = {0x46BD29A2L, 0x46BD29A2L, 0x46BD29A2L};
static int32_t *volatile g_26 = &g_27[2];
static struct S1 *g_32[3][2] = {{&g_21, &g_21}, {&g_21, &g_21}, {&g_21, &g_21}};
static struct S1 *volatile *g_31[2] = {&g_32[1][1], &g_32[1][1]};
static struct S1 *volatile *volatile *volatile g_30 = &g_31[0];

static int8_t func_1(void);
static struct S1 *func_2(const int8_t *p_3, int32_t p_4, uint16_t p_5,
                         struct S1 *const p_6, const int64_t p_7);
static const int8_t *func_8(const int8_t *p_9, uint64_t p_10);

static int8_t func_1(void) {
  int8_t **l_14[3];
  int32_t l_19 = (-5L);
  struct S1 *const l_20 = &g_21;
  struct S1 *l_29 = &g_21;
  struct S1 **l_28 = &l_29;
  int32_t l_34 = (-3L);
  int i;
  for (i = 0; i < 3; i++)
    l_14[i] = &g_13;
  (*l_28) =
      func_2(func_8(g_11, ((g_13 = g_13) != &g_12)), l_19, l_19, l_20, l_19);
  for (l_19 = 2; (l_19 >= 0); l_19 -= 1) {
    for (g_21.f0 = 0; (g_21.f0 <= 2); g_21.f0 += 1) {
      g_30 = (void *)0;
      if ((*g_26))
        continue;
    }
    for (g_21.f0 = 0; (g_21.f0 <= 2); g_21.f0 += 1) {
      struct S1 ***l_33 = &l_28;
      int32_t *l_35 = &g_27[0];
      (*l_35) &= (l_34 = (l_33 != &g_31[1]));
    }
  }
  return (*g_11);
}

static struct S1 *func_2(const int8_t *p_3, int32_t p_4, uint16_t p_5,
                         struct S1 *const p_6, const int64_t p_7) {
  int32_t l_24 = 0xAE8B0121L;
  int32_t l_25 = 0x7BA3F300L;
  (*g_26) = (safe_add_func_uint64_t_u_u(
      (l_24, g_18), ((l_25 = ((g_12, 0x62A04F77722ABAC8LL) >= p_4)) <= l_24)));
  return &g_21;
}

static const int8_t *func_8(const int8_t *p_9, uint64_t p_10) {
  for (p_10 = 2; (p_10 < 16); p_10++) {
    int32_t *l_17[2];
    int i;
    for (i = 0; i < 2; i++)
      l_17[i] = (void *)0;
    g_18 = 7L;
  }
  return &g_12;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_12;
  csmith_sink_ = g_18;
  csmith_sink_ = g_21.f0;
  csmith_sink_ = g_21.f1;
  csmith_sink_ = g_21.f2;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_27[i];
  }
  platform_main_end(0, 0);
  return 0;
}
