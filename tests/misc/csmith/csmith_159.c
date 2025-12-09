// Options:   --seed 200159 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_159.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint64_t f0;
  int32_t f1;
  uint32_t f2;
};

union U1 {
  volatile struct S0 f0;
  const uint32_t f1;
};

static union U1 g_15 = {{0UL, 1L, 0x023DCDF5L}};
static volatile int32_t *volatile g_16 = (void *)0;
static int32_t g_18 = (-9L);
static int32_t *const g_17 = &g_18;
static int32_t *g_21 = (void *)0;
static int32_t **volatile g_20 = &g_21;
static int32_t *g_24 = (void *)0;
static int32_t **volatile g_23 = &g_24;

static const float func_1(void);
static int32_t *func_2(int32_t p_3, uint64_t p_4, int16_t p_5);

static const float func_1(void) {
  uint64_t l_14 = 9UL;
  const int16_t l_19 = (-1L);
  int32_t **l_22 = &g_21;
  (*g_23) =
      ((*l_22) = func_2(
           (((safe_mul_func_uint8_t_u_u(
                 (((~(((safe_unary_minus_func_uint8_t_u(
                           (safe_lshift_func_uint8_t_u_s(
                               (safe_mod_func_uint8_t_u_u(
                                   (l_14 >= ((g_15, g_16) == g_17)), 255UL)),
                               g_18)))) < g_18) ^
                      65535UL)) &&
                   0x7B09L) &
                  0x1571L),
                 g_18)) &&
             l_19),
            (*g_17)),
           l_14, g_18));
  return g_18;
}

static int32_t *func_2(int32_t p_3, uint64_t p_4, int16_t p_5) {
  (*g_20) = &g_18;
  return (*g_20);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_15.f0.f0;
  csmith_sink_ = g_15.f0.f1;
  csmith_sink_ = g_15.f0.f2;
  csmith_sink_ = g_18;
  platform_main_end(0, 0);
  return 0;
}
