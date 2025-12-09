// Options:   --seed 200102 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_102.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile uint32_t g_11[3] = {0xC08872FAL, 0xC08872FAL, 0xC08872FAL};
static int32_t g_16 = 0xA733E34BL;
static volatile int32_t *g_17 = (void *)0;
static int32_t g_25 = 0xB06C0E26L;
static int16_t g_28 = (-9L);

static uint16_t func_1(void);
static int16_t func_12(uint32_t p_13, uint16_t p_14);

static uint16_t func_1(void) {
  int32_t l_15 = 0xB5F0B101L;
  int16_t *l_26 = (void *)0;
  int16_t *l_27 = &g_28;
  int32_t l_29 = 1L;
  l_29 = (safe_sub_func_uint8_t_u_u(
      ((~(((*l_27) &= (safe_sub_func_uint64_t_u_u(
               (safe_lshift_func_int16_t_s_u((-1L), 10)),
               (safe_lshift_func_uint16_t_u_s(
                   g_11[0], func_12((l_15, g_16), l_15)))))) &&
          l_15)),
       0x50L),
      l_15));
  return l_29;
}

static int16_t func_12(uint32_t p_13, uint16_t p_14) {
  volatile int32_t **l_18 = &g_17;
  float l_21 = 0x0.D3ECF0p-19;
  int32_t *l_22 = (void *)0;
  int32_t *l_23 = (void *)0;
  int32_t *l_24 = &g_25;
  (*l_18) = g_17;
  (*l_24) ^= (safe_sub_func_int32_t_s_s(g_16, 0x92C6EED1L));
  return p_13;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_11[i];
  }
  csmith_sink_ = g_16;
  csmith_sink_ = g_25;
  csmith_sink_ = g_28;
  platform_main_end(0, 0);
  return 0;
}
