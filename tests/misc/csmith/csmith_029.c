// Options:   --seed 100029 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_029.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U2 {
  uint32_t f0;
};

static volatile int32_t g_3 = 2L;
static volatile int32_t g_4 = 7L;
static int32_t g_5 = 1L;
static int16_t g_19 = 0xF1FDL;
static union U2 g_21 = {4294967292UL};
static int32_t g_23 = 1L;
static volatile uint32_t g_40 = 0x1E341F56L;
static int32_t *volatile g_43 = &g_23;

static const int64_t func_1(void);
static int32_t func_6(int32_t p_7, const int8_t p_8, int32_t p_9, union U2 p_10,
                      int32_t p_11);

static const int64_t func_1(void) {
  uint64_t l_2[2];
  int i;
  for (i = 0; i < 2; i++)
    l_2[i] = 0UL;
  for (g_5 = 1; (g_5 >= 0); g_5 -= 1) {
    uint64_t l_12 = 0xCFD1F2E96673E7EDLL;
    uint8_t *l_17 = (void *)0;
    uint8_t *l_18[4];
    int i;
    for (i = 0; i < 4; i++)
      l_18[i] = (void *)0;
    if (g_3)
      break;
    if (func_6(l_12,
               ((safe_mul_func_uint16_t_u_u(
                    (safe_div_func_int8_t_s_s(
                        ((g_19 = 255UL) == (((+g_5), g_4) ^ g_5)), g_5)),
                    l_2[0])) &
                0xBD004DDEL),
               g_5, g_21, l_2[0])) {
      (*g_43) = (g_23 || g_3);
    } else {
      int32_t l_48 = 0L;
      if (((void *)0 == &g_5)) {
        (*g_43) = ((void *)0 == &g_5);
      } else {
        return l_12;
      }
      for (g_23 = 1; (g_23 >= 0); g_23 -= 1) {
        int32_t *l_45 = &g_5;
        int32_t **l_44 = &l_45;
        int32_t *l_47[1][3];
        int32_t **l_46 = &l_47[0][0];
        int i, j;
        for (i = 0; i < 1; i++) {
          for (j = 0; j < 3; j++)
            l_47[i][j] = &g_23;
        }
        (*l_46) = ((*l_44) = &g_5);
        if (l_48)
          continue;
      }
    }
  }
  return l_2[1];
}

static int32_t func_6(int32_t p_7, const int8_t p_8, int32_t p_9, union U2 p_10,
                      int32_t p_11) {
  int32_t *l_22 = &g_23;
  int32_t *l_24 = (void *)0;
  int32_t l_25[3];
  int32_t *l_26 = &g_23;
  int32_t *l_27 = (void *)0;
  int32_t *l_28 = &l_25[1];
  int32_t *l_29 = &l_25[1];
  int32_t *l_30 = &l_25[2];
  int32_t *l_31 = &l_25[2];
  int32_t *l_32 = &l_25[2];
  int32_t *l_33 = &g_23;
  int32_t *l_34 = &g_23;
  int32_t *l_35 = &l_25[2];
  int32_t *l_36[4] = {&l_25[0], &l_25[0], &l_25[0], &l_25[0]};
  uint16_t l_37 = 65534UL;
  int i;
  for (i = 0; i < 3; i++)
    l_25[i] = (-5L);
  ++l_37;
  g_40++;
  return g_4;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_19;
  csmith_sink_ = g_21.f0;
  csmith_sink_ = g_23;
  csmith_sink_ = g_40;
  platform_main_end(0, 0);
  return 0;
}
