// Options:   --seed 300246 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_246.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int64_t f0;
  volatile uint16_t f1;
  volatile int8_t f2;
};

static const volatile int8_t g_9 = 1L;
static uint32_t g_12 = 0xD8D38330L;
static int8_t g_15 = 0x2DL;
static uint16_t g_27 = 0x3920L;
static struct S0 g_30 = {1L, 65533UL, 4L};

static uint16_t func_1(void);
static struct S0 func_2(uint32_t p_3, int32_t p_4, uint32_t p_5, uint16_t p_6);
static int32_t func_17(uint64_t p_18, int8_t *p_19);

static uint16_t func_1(void) {
  uint64_t l_13 = 9UL;
  int8_t *l_14 = &g_15;
  int8_t l_16 = 1L;
  struct S0 *l_31 = &g_30;
  (*l_31) = func_2(
      ((((safe_lshift_func_int8_t_s_s(
             0x00L, ((*l_14) |= ((g_9 & (safe_add_func_uint8_t_u_u(
                                            (0xB6BC3EC3L & g_12), g_12))) &
                                 l_13)))) < l_13) < l_13) < l_16),
      l_13, l_13, g_12);
  return g_12;
}

static struct S0 func_2(uint32_t p_3, int32_t p_4, uint32_t p_5, uint16_t p_6) {
  int32_t l_20 = 1L;
  int8_t *l_21 = &g_15;
  int32_t l_23 = 0x3876A47CL;
  int16_t l_24[1];
  int i;
  for (i = 0; i < 1; i++)
    l_24[i] = 1L;
  l_23 |= func_17(l_20, l_21);
  for (p_3 = 0; (p_3 <= 0); p_3 += 1) {
    int32_t *l_25 = &l_23;
    int32_t *l_26[3];
    int i;
    for (i = 0; i < 3; i++)
      l_26[i] = &l_23;
    g_27--;
  }
  return g_30;
}

static int32_t func_17(uint64_t p_18, int8_t *p_19) {
  int64_t l_22[2];
  int i;
  for (i = 0; i < 2; i++)
    l_22[i] = (-3L);
  return l_22[0];
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_12;
  csmith_sink_ = g_15;
  csmith_sink_ = g_27;
  csmith_sink_ = g_30.f0;
  csmith_sink_ = g_30.f1;
  csmith_sink_ = g_30.f2;
  platform_main_end(0, 0);
  return 0;
}
