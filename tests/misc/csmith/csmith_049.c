// Options:   --seed 100049 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_049.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int8_t f0;
  uint16_t f1;
  int32_t f2;
};

static int64_t g_8[1][1] = {{0xBA028EA38884515FLL}};
static int32_t g_11 = (-1L);
static int32_t g_13 = 0xBF889E02L;

static int64_t func_1(void);
static uint32_t func_4(struct S0 p_5, uint32_t p_6);

static int64_t func_1(void) {
  struct S0 l_7 = {0x66L, 0xAFCBL, 0x43E95AADL};
  int32_t *l_25[2];
  int i;
  for (i = 0; i < 2; i++)
    l_25[i] = &g_13;
  g_13 =
      (0xAD95E17CL ==
       ((safe_sub_func_uint32_t_u_u(func_4(l_7, (g_8[0][0] || l_7.f2)), g_13)) ^
        l_7.f2));
  return g_8[0][0];
}

static uint32_t func_4(struct S0 p_5, uint32_t p_6) {
  int32_t *l_12 = &g_13;
  int32_t *l_14 = &g_13;
  int32_t *l_15 = &g_13;
  int32_t *l_16 = &g_13;
  int32_t l_17 = 0x703C5764L;
  int32_t *l_18 = &l_17;
  int32_t *l_19 = &g_13;
  int8_t l_20[1][1];
  int32_t *l_21[4][4] = {{&l_17, &l_17, &l_17, &l_17},
                         {&l_17, &l_17, &l_17, &l_17},
                         {&l_17, &l_17, &l_17, &l_17},
                         {&l_17, &l_17, &l_17, &l_17}};
  uint32_t l_22 = 0xF0ADC109L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_20[i][j] = 0x1FL;
  }
  for (p_6 = (-7); (p_6 <= 53); p_6++) {
    g_11 = 0x01B17D72L;
  }
  l_22--;
  return g_11;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  csmith_sink_ = g_11;
  csmith_sink_ = g_13;
  platform_main_end(0, 0);
  return 0;
}
