// Options:   --seed 100007 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_007.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint16_t f0;
  int16_t f1;
  const int16_t f2;
};

static const volatile uint32_t g_6 = 0x88E1B61BL;
static uint64_t g_19 = 0x65CD3860A421E0BELL;
static int8_t g_21 = 0x51L;
static int32_t g_29 = 0x6A218F0EL;
static int32_t g_37[4][4] = {{(-1L), 8L, 8L, (-1L)},
                             {8L, (-1L), 0x02739425L, (-7L)},
                             {8L, 0x02739425L, 8L, 0x780D7777L},
                             {(-1L), (-7L), 0x780D7777L, 0x780D7777L}};
static volatile uint16_t g_38 = 65527UL;
static struct S0 g_41 = {0UL, 0x7682L, 0x5A4EL};

static struct S0 func_1(void);
static uint16_t func_7(uint32_t p_8);

static struct S0 func_1(void) {
  int64_t l_16 = (-10L);
  int8_t *l_20[3];
  int32_t l_22 = 0x411AA84CL;
  int32_t l_30 = 0xFE35FE57L;
  int32_t *l_31 = &l_30;
  int32_t *l_32 = (void *)0;
  int32_t *l_33 = &l_22;
  int32_t *l_34 = &l_30;
  int32_t *l_35 = (void *)0;
  int32_t *l_36[4];
  int i;
  for (i = 0; i < 3; i++)
    l_20[i] = &g_21;
  for (i = 0; i < 4; i++)
    l_36[i] = &l_22;
  l_30 &= (safe_mod_func_uint64_t_u_u(
      (((safe_mul_func_uint8_t_u_u(
            g_6,
            (func_7((safe_lshift_func_int8_t_s_s(
                 ((safe_lshift_func_uint8_t_u_u(
                      ((l_22 &= (safe_rshift_func_int16_t_s_u(
                            ((+((l_16, (safe_add_func_int8_t_s_s(
                                           (g_19, l_16), 248UL))) <= l_16)) &
                             0x4D39D9827359B504LL),
                            g_19))) &&
                       0xD5L),
                      g_19)) == 0x5DA2CA33L),
                 4))) >= g_19))) &
        g_21),
       0x598737A30B91300DLL),
      g_19));
  ++g_38;
  return g_41;
}

static uint16_t func_7(uint32_t p_8) {
  int8_t *l_25[3];
  int8_t *l_27 = &g_21;
  int8_t **l_26 = &l_27;
  int32_t *l_28[2][3] = {{(void *)0, (void *)0, &g_29},
                         {(void *)0, (void *)0, &g_29}};
  int i, j;
  for (i = 0; i < 3; i++)
    l_25[i] = &g_21;
  g_29 &= (safe_rshift_func_uint8_t_u_s((l_25[0] != ((*l_26) = l_25[0])),
                                        ((p_8 && 6UL) | g_19)));
  return g_29;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  csmith_sink_ = g_19;
  csmith_sink_ = g_21;
  csmith_sink_ = g_29;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_37[i][j];
    }
  }
  csmith_sink_ = g_38;
  csmith_sink_ = g_41.f0;
  csmith_sink_ = g_41.f1;
  csmith_sink_ = g_41.f2;
  platform_main_end(0, 0);
  return 0;
}
