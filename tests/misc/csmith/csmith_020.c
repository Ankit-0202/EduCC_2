// Options:   --seed 100020 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_020.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const volatile int32_t f0;
  int16_t f1;
  int8_t f2;
};

struct S1 {
  volatile uint32_t f0;
  struct S0 f1;
};

static int32_t g_2 = 0xD3C891C5L;
static uint8_t g_14 = 0x95L;
static uint8_t g_19 = 255UL;
static int32_t *g_21 = &g_2;
static int32_t **volatile g_20[4] = {(void *)0, (void *)0, (void *)0,
                                     (void *)0};
static int32_t **volatile g_24[3] = {&g_21, &g_21, &g_21};
static struct S1 g_26 = {0x1DD2E91CL, {1L, 0x2D38L, 0xA8L}};

static struct S1 func_1(void);
static int32_t *const func_5(uint16_t p_6, int32_t *p_7, int32_t *p_8,
                             int32_t *p_9);

static struct S1 func_1(void) {
  int32_t *l_10[3];
  int i;
  for (i = 0; i < 3; i++)
    l_10[i] = &g_2;
  for (g_2 = 0; (g_2 > 17); g_2 = safe_add_func_uint32_t_u_u(g_2, 7)) {
    int32_t **l_22 = (void *)0;
    int32_t **l_23[3];
    int32_t **l_25 = &g_21;
    int i;
    for (i = 0; i < 3; i++)
      l_23[i] = &g_21;
    (*l_25) = (g_2, func_5((4L == g_2), &g_2, l_10[2], &g_2));
  }
  return g_26;
}

static int32_t *const func_5(uint16_t p_6, int32_t *p_7, int32_t *p_8,
                             int32_t *p_9) {
  uint8_t *l_13[1];
  int32_t l_15 = 0xDFAD5BEFL;
  uint8_t l_18 = 0xA6L;
  int i;
  for (i = 0; i < 1; i++)
    l_13[i] = &g_14;
  g_19 = (safe_lshift_func_uint8_t_u_s(
      (((l_15 = g_2) || (safe_sub_func_uint32_t_u_u(
                            9UL, (l_15 = (((void *)0 != l_13[0]) & l_18))))) ==
       g_2),
      p_6));
  return p_9;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_14;
  csmith_sink_ = g_19;
  csmith_sink_ = g_26.f0;
  csmith_sink_ = g_26.f1.f0;
  csmith_sink_ = g_26.f1.f1;
  csmith_sink_ = g_26.f1.f2;
  platform_main_end(0, 0);
  return 0;
}
