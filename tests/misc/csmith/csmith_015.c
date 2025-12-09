// Options:   --seed 100015 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_015.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
};

struct S1 {
  volatile int16_t f0;
};

static int32_t g_3 = 0x44182BD7L;
static int32_t **volatile g_4[1][4] = {
    {(void *)0, (void *)0, (void *)0, (void *)0}};
static int32_t *g_6 = &g_3;
static int32_t **const volatile g_5 = &g_6;
static uint64_t g_11 = 0xBC106EC6E54EE87FLL;
static volatile struct S1 g_17 = {0xB91EL};
static uint64_t g_19[2] = {0xD574417F95E19F8CLL, 0xD574417F95E19F8CLL};
static int32_t **volatile g_21 = (void *)0;
static int32_t *g_23 = (void *)0;
static int32_t **volatile g_22 = &g_23;

static uint16_t func_1(void);
static int32_t *func_7(int32_t *p_8, uint64_t p_9, int32_t **p_10);

static uint16_t func_1(void) {
  int32_t *l_2 = &g_3;
  int32_t *l_12 = &g_3;
  int32_t **l_20 = &g_6;
  (*g_5) = l_2;
  (*g_22) = ((*l_20) = func_7((((g_11 = g_3), 0xB807CFAF425F5F99LL), l_12),
                              (*l_12), &g_6));
  return (**l_20);
}

static int32_t *func_7(int32_t *p_8, uint64_t p_9, int32_t **p_10) {
  struct S0 l_15 = {4294967289UL};
  int32_t l_16 = 0xF9481F34L;
  int32_t **l_18[2][2];
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_18[i][j] = (void *)0;
  }
  g_19[0] ^=
      (((safe_rshift_func_uint8_t_u_u(
            ((((((l_15, l_16) <=
                 (((((g_17, l_18[0][0]) != (void *)0) == g_11) || (**g_5)) &
                  g_11)),
                0xEB2DL) <= p_9) > 0x014801465EE6D54ELL),
             p_9),
            g_3)) ||
        0x976B5A7DL),
       0xE65C3421L);
  return (*p_10);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_11;
  csmith_sink_ = g_17.f0;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_19[i];
  }
  platform_main_end(0, 0);
  return 0;
}
