// Options:   --seed 100074 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_074.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int16_t f0;
  int8_t f1;
};

static int16_t g_11 = 0L;
static int32_t g_23 = 0x04DDC877L;
static int32_t g_27 = (-1L);
static volatile int64_t g_41 = 0x5120B879B6842A45LL;
static int32_t *volatile g_42 = &g_23;
static int16_t *g_51 = (void *)0;

static int32_t func_1(void);
static int32_t func_2(uint32_t p_3, union U0 p_4, union U0 p_5, int32_t p_6);

static int32_t func_1(void) {
  uint32_t l_18 = 7UL;
  int32_t l_19 = 0xB0B44CF5L;
  union U0 l_20 = {0x2E77L};
  int32_t *l_24 = &g_23;
  int32_t l_30 = 0x9AA2AAFAL;
  if (((*l_24) = func_2(
           ((safe_rshift_func_uint8_t_u_u(
                ((safe_div_func_uint16_t_u_u(
                     g_11, (safe_mul_func_int16_t_s_s(
                               ((safe_mod_func_int32_t_s_s(
                                    g_11, (safe_mod_func_int32_t_s_s(
                                              (l_18 > l_19), 0x58E92EDAL)))) &&
                                l_19),
                               (-1L))))) &
                 0L),
                l_19)) &
            l_18),
           l_20, l_20, g_11))) {
    int64_t *l_26[2];
    int32_t l_33 = (-1L);
    int16_t *l_34 = &l_20.f0;
    int i;
    for (i = 0; i < 2; i++)
      l_26[i] = (void *)0;
    (*l_24) = (((g_27 = (safe_unary_minus_func_int16_t_s(g_23))) <
                0xA34071E9942C3B03LL) ^
               (safe_mod_func_uint16_t_u_u(
                   (((((((0x4F9AL && 1UL) != g_11) ^ g_11), l_30) != (*l_24)) &&
                     0x92L),
                    g_11),
                   g_11)));
    (*l_24) = (g_11 >= (safe_add_func_int8_t_s_s(
                           (((*l_34) = (0x14L ^ l_33)) ^ (*l_24)), l_33)));
  } else {
    int32_t **l_35 = &l_24;
    int32_t l_40 = 3L;
    int16_t *l_52 = &l_20.f0;
    (*l_35) = &g_23;
    if (((((safe_sub_func_int16_t_s_s(
               ((((((((*l_24) = 3L) <
                     (safe_add_func_int16_t_s_s((0UL < 0xE161E417L), l_40))) &&
                    (**l_35)) ^
                   g_27),
                  1L),
                 g_41) &&
                (**l_35)),
               g_11)),
           (**l_35)) ||
          g_11) == l_40)) {
    lbl_55:
      (*l_24) = 1L;
      g_42 = (void *)0;
    } else {
      for (l_40 = 0; (l_40 <= (-15)); l_40--) {
        int16_t *l_49 = &g_11;
        int16_t **l_50[1];
        int i;
        for (i = 0; i < 1; i++)
          l_50[i] = &l_49;
        (**l_35) = ((((safe_rshift_func_uint16_t_u_s(
                          (safe_rshift_func_uint16_t_u_s(
                              ((g_51 = l_49) == l_52),
                              (safe_mul_func_uint16_t_u_u(g_11, g_23)))),
                          (**l_35))) < (*g_42)) >= 0x6149AF40839CA31BLL) |
                    7UL);
      }
      if (l_19)
        goto lbl_55;
    }
  }
  return (*l_24);
}

static int32_t func_2(uint32_t p_3, union U0 p_4, union U0 p_5, int32_t p_6) {
  uint32_t l_21 = 0x56095DBCL;
  int32_t *l_22 = &g_23;
  (*l_22) |= ((18446744073709551615UL <=
               ((g_11, (p_5.f0 >= 0x255D580090AE7359LL)) < l_21)) ^
              g_11);
  return (*l_22);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11;
  csmith_sink_ = g_23;
  csmith_sink_ = g_27;
  csmith_sink_ = g_41;
  platform_main_end(0, 0);
  return 0;
}
