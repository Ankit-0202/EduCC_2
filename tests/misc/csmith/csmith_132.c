// Options:   --seed 200132 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_132.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint64_t g_2 = 0UL;
static int32_t g_9 = 0L;
static const int32_t *g_16 = (void *)0;
static int32_t g_19[4] = {0x41CE3CB5L, 0x41CE3CB5L, 0x41CE3CB5L, 0x41CE3CB5L};
static int32_t *const volatile g_18 = &g_19[0];
static uint32_t g_22 = 0xE26595ADL;
static uint8_t g_26 = 1UL;
static const uint32_t g_37[2] = {0x8CDC14C3L, 0x8CDC14C3L};
static uint32_t g_39 = 6UL;
static int16_t g_41 = (-1L);
static uint32_t g_43[4] = {0x593C394AL, 0x593C394AL, 0x593C394AL, 0x593C394AL};
static int32_t g_48[1][1] = {{0x8E972CE3L}};

static int8_t func_1(void);
static uint32_t func_3(const uint32_t p_4, const int64_t p_5);

static int8_t func_1(void) {
  int32_t l_7 = 0x214C405BL;
  int32_t *l_45 = &g_19[0];
  int32_t *l_46 = (void *)0;
  int32_t *l_47 = &g_48[0][0];
  (*l_47) &=
      ((*l_45) =
           ((g_2, func_3((safe_unary_minus_func_int8_t_s(l_7)), l_7)) & l_7));
  return (*l_45);
}

static uint32_t func_3(const uint32_t p_4, const int64_t p_5) {
  int32_t *l_8[4];
  int i;
  for (i = 0; i < 4; i++)
    l_8[i] = &g_9;
  g_9 |= 2L;
  for (g_9 = 21; (g_9 <= (-24)); g_9--) {
    const int32_t *l_14[2][3] = {{&g_9, &g_9, &g_9}, {&g_9, &g_9, &g_9}};
    const int32_t **l_15[2][1];
    int32_t **l_17 = &l_8[1];
    uint32_t *l_21 = &g_22;
    uint8_t *l_25 = &g_26;
    const uint32_t *l_36 = &g_37[1];
    const uint32_t **l_35 = &l_36;
    uint32_t *l_38 = &g_39;
    int16_t *l_40 = &g_41;
    uint32_t *l_42 = &g_43[1];
    int32_t l_44[1][2];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_15[i][j] = (void *)0;
    }
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_44[i][j] = 0xF6657EEFL;
    }
    (*g_18) &= (safe_div_func_int64_t_s_s(
        ((g_16 = l_14[0][2]) == ((*l_17) = l_8[1])), g_2));
    l_44[0][1] =
        ((((*l_42) ^=
           ((*l_38) =
                ((+(((*l_21) = ((void *)0 != &l_8[1])) >
                    ((((safe_mul_func_uint16_t_u_u(
                           (((*l_25)--) &
                            (safe_div_func_int32_t_s_s(
                                (((safe_rshift_func_int16_t_s_u(
                                      ((*l_40) = (safe_add_func_uint8_t_u_u(
                                           (((*l_35) = l_21) == l_38), p_5))),
                                      15)) ^
                                  1UL) < (**l_17)),
                                g_2))),
                           0x3B19L)) |
                       0x1359A703L) ||
                      0UL) ||
                     0x07DFL))),
                 g_37[0]))),
          g_19[2]) >= p_5);
  }
  return g_37[1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_9;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_19[i];
  }
  csmith_sink_ = g_22;
  csmith_sink_ = g_26;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_37[i];
  }
  csmith_sink_ = g_39;
  csmith_sink_ = g_41;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_43[i];
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_48[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
