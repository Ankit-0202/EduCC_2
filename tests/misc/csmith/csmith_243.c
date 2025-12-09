// Options:   --seed 300243 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_243.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_5 = 0L;
static int32_t g_17[2][2] = {{1L, 1L}, {1L, 1L}};
static uint32_t g_19 = 4UL;
static uint8_t g_25 = 0x68L;
static int32_t *const volatile g_32 = &g_17[0][0];
static int32_t *const volatile g_38 = &g_17[0][1];

static int32_t func_1(void);
static uint64_t func_9(uint32_t p_10, uint32_t p_11, int32_t p_12);
static int32_t func_13(uint8_t p_14);

static int32_t func_1(void) {
  uint32_t l_2 = 4294967294UL;
  uint8_t *l_35[2][3] = {{(void *)0, (void *)0, (void *)0},
                         {&g_25, &g_25, &g_25}};
  int32_t l_39 = 7L;
  int i, j;
  if (l_2) {
    uint32_t *l_18 = &g_19;
    int32_t l_23 = (-1L);
    if ((safe_add_func_int16_t_s_s(g_5, (((*l_18) = (safe_sub_func_int8_t_s_s(
                                              (~func_9(l_2, g_5, l_2)), g_5))),
                                         0xE4BFL)))) {
      uint8_t *l_24[1];
      int32_t *l_26[2][2];
      int i, j;
      for (i = 0; i < 1; i++)
        l_24[i] = &g_25;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
          l_26[i][j] = &l_23;
      }
      g_5 = ((((g_25 = (((safe_add_func_uint16_t_u_u(0x8027L, l_2)) >=
                         ((safe_unary_minus_func_uint16_t_u((l_23 > l_23))) >
                          0x27142B62L)) > g_19)) ||
               g_17[0][0]),
              l_26[1][0]) != (void *)0);
      return g_17[0][1];
    } else {
      const int8_t l_31 = 0x89L;
      (*g_32) |= (safe_rshift_func_uint8_t_u_u(
          (((((safe_lshift_func_uint8_t_u_u(l_31, (l_31, l_31))) > g_25),
             l_31) == l_31) ||
           2UL),
          4));
      return (*g_32);
    }
  } else {
    int32_t l_36 = 0x53403E1FL;
    uint32_t *l_37 = &g_19;
    (*g_38) = (safe_div_func_uint8_t_u_u(
        (((l_35[1][0] == &g_25) >= ((((*l_37) = l_36), g_5) == (-5L))) <= l_2),
        g_17[0][0]));
  }
  return l_39;
}

static uint64_t func_9(uint32_t p_10, uint32_t p_11, int32_t p_12) {
  int32_t *l_16 = &g_17[0][0];
  if (((*l_16) &= func_13(p_10))) {
    (*l_16) = (0x812A3CC92EA21E1DLL >= p_12);
  } else {
    for (p_12 = 0; (p_12 <= 1); p_12 += 1) {
      (*l_16) = 2L;
      if (g_5)
        break;
    }
  }
  return (*l_16);
}

static int32_t func_13(uint8_t p_14) {
  int32_t l_15 = 0xAA96141EL;
  return l_15;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_17[i][j];
    }
  }
  csmith_sink_ = g_19;
  csmith_sink_ = g_25;
  platform_main_end(0, 0);
  return 0;
}
