// Options:   --seed 100023 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_023.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile uint8_t f0;
  uint64_t f1;
};

struct S1 {
  uint16_t f0;
  volatile struct S0 f1;
  volatile uint32_t f2;
};

static int8_t g_2[1] = {0x34L};
static volatile uint8_t g_3[4][1] = {{0x3DL}, {0x3DL}, {0x3DL}, {0x3DL}};
static uint16_t g_14[1][1] = {{0UL}};
static uint8_t g_24 = 253UL;
static const volatile struct S0 g_27[2][1] = {{{0x2FL, 0UL}}, {{0x2FL, 0UL}}};
static struct S1 g_32 = {0xDA2AL, {4UL, 1UL}, 18446744073709551615UL};
static int32_t g_35[1][2] = {{0xBB650EBFL, 0xBB650EBFL}};
static struct S1 *volatile g_36[2][4] = {{&g_32, &g_32, &g_32, &g_32},
                                         {&g_32, &g_32, &g_32, &g_32}};

static struct S1 func_1(void);
static struct S1 func_6(int16_t p_7, int64_t p_8, uint8_t p_9, int32_t p_10);

static struct S1 func_1(void) {
  uint16_t *l_13 = &g_14[0][0];
  uint16_t l_19 = 0x48BDL;
  uint16_t *const l_22 = &l_19;
  uint8_t *l_23[3][4] = {{(void *)0, (void *)0, (void *)0, (void *)0},
                         {(void *)0, (void *)0, &g_24, (void *)0},
                         {(void *)0, (void *)0, (void *)0, (void *)0}};
  int32_t l_25 = (-1L);
  struct S1 *l_37 = &g_32;
  int i, j;
  --g_3[1][0];
  (*l_37) = func_6(
      (safe_rshift_func_uint16_t_u_s((++(*l_13)), 8)),
      ((safe_lshift_func_uint16_t_u_s(65535UL, 8)), l_19),
      (l_25 = (safe_mod_func_uint8_t_u_u((&l_19 == l_22), g_2[0]))), l_19);
  return (*l_37);
}

static struct S1 func_6(int16_t p_7, int64_t p_8, uint8_t p_9, int32_t p_10) {
  int32_t l_26 = 0xBD4AA41AL;
  int32_t l_33 = (-1L);
  int32_t *l_34 = &g_35[0][1];
  l_26 ^= g_3[1][0];
  (*l_34) &=
      ((p_10, (l_33 = (g_27[0][0], (safe_sub_func_uint64_t_u_u(
                                       (safe_div_func_uint32_t_u_u(
                                           ((g_32, p_8) < l_26), 4294967295UL)),
                                       0x58F87662B0A94FE8LL))))) >= p_10);
  return g_32;
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
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_14[i][j];
    }
  }
  csmith_sink_ = g_24;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
    }
  }
  csmith_sink_ = g_32.f0;
  csmith_sink_ = g_32.f1.f0;
  csmith_sink_ = g_32.f1.f1;
  csmith_sink_ = g_32.f2;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_35[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
