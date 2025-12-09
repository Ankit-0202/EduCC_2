// Options:   --seed 100085 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_085.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int8_t g_5 = 1L;
static int32_t g_8 = 0x16DB6D03L;
static volatile int32_t g_11 = (-7L);
static volatile int32_t *volatile g_10[2][4] = {{&g_11, &g_11, &g_11, &g_11},
                                                {&g_11, &g_11, &g_11, &g_11}};
static int32_t g_13 = (-6L);
static int32_t *g_12 = &g_13;
static uint8_t g_24 = 0xAAL;
static uint64_t g_30 = 7UL;
static int32_t g_39 = 0L;
static int32_t **g_43 = &g_12;
static int32_t ***g_42 = &g_43;
static int32_t ****volatile g_44[4][2] = {
    {&g_42, (void *)0}, {&g_42, &g_42}, {(void *)0, &g_42}, {&g_42, (void *)0}};
static int32_t ****volatile g_45 = &g_42;
static uint32_t g_60 = 0xAEF1792FL;
static uint16_t g_62 = 0xB5BCL;
static int32_t **g_68 = &g_12;
static int32_t ***volatile g_67 = &g_68;
static uint32_t g_77 = 8UL;
static int16_t g_79 = 0x959CL;
static int32_t g_80 = 0L;
static const uint64_t g_84 = 0x668E7EE3D9849165LL;

static int32_t func_1(void);
static int32_t ***func_17(uint8_t p_18, uint16_t p_19, int32_t p_20,
                          int32_t *const *p_21, uint64_t p_22);

static int32_t func_1(void) {
  int32_t l_4 = 1L;
  int32_t **l_58[2][3];
  int32_t l_88 = (-1L);
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++)
      l_58[i][j] = (void *)0;
  }
lbl_85:
  if (((((safe_lshift_func_int16_t_s_s(l_4, 11)) | g_5) ^
        ((254UL < 0UL) != g_8)) &
       l_4)) {
    int32_t *l_9 = &l_4;
    int32_t **l_14 = &l_9;
    int32_t l_27 = 1L;
    uint16_t l_57[4][4] = {{0UL, 0UL, 65531UL, 0UL},
                           {0UL, 4UL, 4UL, 0UL},
                           {4UL, 0UL, 4UL, 4UL},
                           {0UL, 0UL, 65531UL, 0UL}};
    uint32_t l_64 = 3UL;
    int i, j;
  lbl_46:
    (*l_9) |= g_5;
    if ((((g_10[1][1] == ((*l_14) = g_12)), 4294967295UL) && (**l_14))) {
      for (g_8 = 0; (g_8 != 26); g_8++) {
        uint8_t *l_23 = &g_24;
        uint64_t *l_28 = (void *)0;
        uint64_t *l_29 = &g_30;
        (*g_45) = func_17(
            g_11, g_13, (((*l_29) ^= (((*l_23)++) == l_27)) >= g_8), &l_9, g_8);
      }
      for (g_39 = 0; (g_39 <= 1); g_39 += 1) {
        if (l_4)
          break;
        if (l_27)
          goto lbl_46;
      }
    } else {
      int8_t l_52[4];
      int32_t **l_59[1][1];
      uint16_t *l_61 = &g_62;
      int32_t l_63 = 9L;
      int i, j;
      for (i = 0; i < 4; i++)
        l_52[i] = 0xD5L;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_59[i][j] = &l_9;
      }
      for (g_30 = (-22); (g_30 >= 2); g_30++) {
        uint16_t l_49 = 0x4584L;
        if (l_49)
          break;
      }
      l_64 ^=
          (l_63 |=
           ((safe_lshift_func_int8_t_s_s(l_52[0], 5)),
            (safe_lshift_func_uint16_t_u_s(
                ((*l_61) &=
                 ((((g_60 &=
                     ((((*g_42) = (*g_42)) ==
                       (l_59[0][0] =
                            ((safe_div_func_uint32_t_u_u(
                                 (((*l_9) | 65532UL) > (**l_14)), l_57[3][0])),
                             l_58[0][0]))) > 0xC4EDD679405A9AD1LL)),
                    (-10L)) ||
                   g_60) <= l_52[0])),
                g_39))));
    }
  } else {
    int32_t l_71 = 0x0043BD3AL;
    int32_t **const *l_74 = &g_43;
    int32_t **const **l_73 = &l_74;
    for (g_62 = 0; (g_62 != 41); g_62++) {
      uint64_t *l_72 = (void *)0;
      int32_t **const ***l_75 = &l_73;
      uint32_t *l_76 = &g_77;
      int16_t *l_78 = &g_79;
      (*g_67) = ((*g_42) = l_58[0][0]);
      if (((safe_mod_func_uint64_t_u_u(
               ((l_71 != ((*l_78) = (((g_30 = l_71),
                                      (((*l_76) = (((((*l_75) = l_73) !=
                                                     &g_67) > 4294967295UL),
                                                   0UL)),
                                       g_5)),
                                     0x2E7CL))) ^
                3L),
               g_39)) == 4UL)) {
        uint64_t l_81 = 8UL;
        (**l_75) = &l_58[0][0];
        (*g_12) = g_84;
      } else {
        if ((*g_12))
          break;
        if (l_4)
          goto lbl_85;
      }
    }
  }
  for (g_62 = 19; (g_62 <= 22); g_62++) {
    if (g_13)
      goto lbl_85;
  }
  return l_88;
}

static int32_t ***func_17(uint8_t p_18, uint16_t p_19, int32_t p_20,
                          int32_t *const *p_21, uint64_t p_22) {
  int32_t *l_37 = (void *)0;
  int32_t *l_38 = &g_39;
  int32_t **l_41[3];
  int32_t ***l_40[4][1] = {{&l_41[0]}, {&l_41[1]}, {&l_41[0]}, {&l_41[1]}};
  int i, j;
  for (i = 0; i < 3; i++)
    l_41[i] = &l_37;
  (*g_12) = (((g_13 == (((*l_38) = ((safe_mul_func_uint8_t_u_u(
                                        (safe_mul_func_uint8_t_u_u(
                                            (p_18 ^= 0x83L),
                                            ((safe_div_func_int16_t_s_s(
                                                 (7L > 2L), 0x366EL)) < 0L))),
                                        0xC6L)),
                                    0L)) ^
                        0x705BE734L)),
              (**p_21)) <= g_24);
  return g_42;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_8;
  csmith_sink_ = g_11;
  csmith_sink_ = g_13;
  csmith_sink_ = g_24;
  csmith_sink_ = g_30;
  csmith_sink_ = g_39;
  csmith_sink_ = g_60;
  csmith_sink_ = g_62;
  csmith_sink_ = g_77;
  csmith_sink_ = g_79;
  csmith_sink_ = g_80;
  csmith_sink_ = g_84;
  platform_main_end(0, 0);
  return 0;
}
