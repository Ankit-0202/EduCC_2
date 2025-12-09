// Options:   --seed 100058 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_058.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
};

struct S1 {
  struct S0 f0;
};

union U3 {
  const int32_t f0;
};

static uint8_t g_9 = 0xC6L;
static const union U3 g_12[2][2] = {{{0x46B6EB6BL}, {0x46B6EB6BL}},
                                    {{0x46B6EB6BL}, {0x46B6EB6BL}}};
static uint8_t g_17 = 0xADL;
static uint8_t *const volatile g_16 = &g_17;
static int64_t g_19 = 3L;
static int8_t g_21[1][1] = {{0x06L}};
static int16_t g_24 = 0x09D7L;

static int32_t func_1(void);
static uint16_t func_4(uint8_t p_5, const union U3 p_6, int8_t p_7);

static int32_t func_1(void) {
  uint8_t *l_8 = &g_9;
  int64_t *l_18[3][3];
  int8_t *l_20 = &g_21[0][0];
  int32_t l_25 = 0L;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      l_18[i][j] = &g_19;
  }
  g_24 |= (safe_mul_func_uint16_t_u_u(
      func_4(((*l_8)++), g_12[0][0],
             ((*l_20) &= ((safe_sub_func_uint8_t_u_u(
                              ((!(g_19 = ((l_8 == g_16) != g_17))) && g_17),
                              g_12[0][0].f0)) == g_17))),
      0x2092L));
  return l_25;
}

static uint16_t func_4(uint8_t p_5, const union U3 p_6, int8_t p_7) {
  struct S1 l_22 = {{-1L}};
  struct S1 *l_23 = &l_22;
  (*l_23) = l_22;
  return l_22.f0.f0;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_17;
  csmith_sink_ = g_19;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_21[i][j];
    }
  }
  csmith_sink_ = g_24;
  platform_main_end(0, 0);
  return 0;
}
