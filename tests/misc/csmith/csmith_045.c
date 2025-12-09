// Options:   --seed 100045 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_045.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S2 {
  const volatile int16_t f0;
  const uint32_t f1;
};

union U4 {
  uint32_t f0;
};

static volatile int8_t g_12[3][3] = {
    {1L, 0x48L, 1L}, {1L, 0x48L, 1L}, {1L, 0x48L, 1L}};
static struct S2 g_13 = {-5L, 1UL};
static int32_t g_18 = 0L;
static int32_t *g_20 = &g_18;
static int32_t **const volatile g_19 = &g_20;
static int16_t g_24 = 0x6E6CL;

static const int32_t func_1(void);
static int16_t func_6(const uint8_t p_7, const uint32_t p_8, union U4 p_9);

static const int32_t func_1(void) {
  uint64_t l_14 = 0UL;
  const uint16_t l_15 = 0x6E74L;
  union U4 l_16 = {0xCB302AFFL};
  int32_t *l_21 = (void *)0;
  int32_t *l_22[3];
  int16_t l_23 = (-2L);
  int i;
  for (i = 0; i < 3; i++)
    l_22[i] = &g_18;
  g_24 ^=
      (l_23 = (safe_mod_func_uint8_t_u_u(
           252UL, (safe_sub_func_int16_t_s_s(
                      0x164CL,
                      func_6(((((((safe_add_func_uint16_t_u_u(g_12[2][2], 2UL)),
                                  g_12[2][2]),
                                 g_13),
                                l_14) |
                               g_13.f1) |
                              255UL),
                             l_15, l_16))))));
  return g_12[1][0];
}

static int16_t func_6(const uint8_t p_7, const uint32_t p_8, union U4 p_9) {
  int32_t *l_17 = &g_18;
  (*g_19) = l_17;
  return (*l_17);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_12[i][j];
    }
  }
  csmith_sink_ = g_13.f0;
  csmith_sink_ = g_13.f1;
  csmith_sink_ = g_18;
  csmith_sink_ = g_24;
  platform_main_end(0, 0);
  return 0;
}
