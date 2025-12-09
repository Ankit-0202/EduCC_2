// Options:   --seed 200107 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_107.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S2 {
  float f0;
  int32_t f1;
};

static int32_t g_6[3] = {0x1C3A23FEL, 0x1C3A23FEL, 0x1C3A23FEL};
static uint16_t g_24 = 65528UL;
static int8_t g_25 = 2L;
static int32_t *g_28 = (void *)0;
static int32_t **volatile g_27 = &g_28;

static float func_1(void);
static int32_t *func_2(struct S2 p_3, int32_t *p_4);

static float func_1(void) {
  int32_t *l_5 = &g_6[1];
  struct S2 l_7 = {-0x8.8p-1, 0x564C7B7FL};
  int32_t **l_26 = (void *)0;
  (*g_27) =
      func_2(((((void *)0 == l_5) != ((*l_5), 0x43AC46DDL)), l_7), &g_6[2]);
  return g_25;
}

static int32_t *func_2(struct S2 p_3, int32_t *p_4) {
  float l_19 = 0x1.Dp+1;
  int32_t l_20 = 6L;
  float *l_21 = &l_19;
  float *l_22 = (void *)0;
  int32_t l_23 = 0xB24ADC9FL;
  g_25 = (safe_div_func_float_f_f(
      (g_24 = (safe_add_func_float_f_f(
           (l_23 = (0x3.4BDAC8p+91 <
                    (+((*l_21) =
                           ((-0x1.3p-1) <
                            ((safe_mul_func_float_f_f(
                                 ((safe_sub_func_float_f_f(
                                      (safe_sub_func_float_f_f(p_3.f0, p_3.f0)),
                                      l_19)) != g_6[1]),
                                 l_20)) >= l_20)))))),
           0x1.65F5C9p+6))),
      g_6[0]));
  return &g_6[1];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_6[i];
  }
  csmith_sink_ = g_24;
  csmith_sink_ = g_25;
  platform_main_end(0, 0);
  return 0;
}
