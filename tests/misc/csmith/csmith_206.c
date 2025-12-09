// Options:   --seed 300206 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_206.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  uint8_t f0;
};

static uint8_t g_15 = 0x34L;
static int32_t g_19 = 0xA28C7FFFL;
static volatile uint64_t g_22[2] = {18446744073709551613UL,
                                    18446744073709551613UL};
static uint32_t g_41 = 0xB531EAA4L;
static uint32_t g_43 = 0xE197B2C3L;
static int32_t g_54[2][1] = {{(-1L)}, {(-1L)}};
static volatile uint16_t g_91 = 0x4D59L;
static int32_t *g_99 = &g_19;
static int32_t **g_98 = &g_99;
static int32_t ***const volatile g_97[1][3] = {{&g_98, &g_98, &g_98}};
static int32_t ***volatile g_100 = (void *)0;
static uint16_t g_108 = 65530UL;
static int32_t g_114 = 1L;

static const int32_t func_1(void);
static int16_t func_3(int8_t p_4, union U1 p_5, int64_t p_6, int32_t p_7,
                      uint8_t p_8);
static int8_t func_9(uint32_t p_10);

static const int32_t func_1(void) {
  uint32_t l_2 = 4294967295UL;
  union U1 l_73 = {0xE1L};
  int32_t *l_112 = (void *)0;
  int32_t *l_113[3];
  int i;
  for (i = 0; i < 3; i++)
    l_113[i] = &g_114;
  g_114 |=
      (l_2 &
       func_3(
           func_9(((safe_add_func_uint32_t_u_u(
                       (safe_add_func_uint8_t_u_u(
                           (((g_15, (((((((safe_lshift_func_int8_t_s_s(
                                              ((((l_2 == 0UL) && g_15),
                                                0x348F4A8FL) <= 0x307A329EL),
                                              l_2)) == g_15) != l_2) == l_2) |
                                       18446744073709551613UL) <= g_15) ==
                                     g_15)) > 8L) <= g_15),
                           g_15)),
                       0x260389A9L)) |
                   0xFA48A2B8EA2C39D5LL)),
           l_73, g_54[0][0], g_54[1][0], g_54[1][0]));
  return g_108;
}

static int16_t func_3(int8_t p_4, union U1 p_5, int64_t p_6, int32_t p_7,
                      uint8_t p_8) {
  int32_t *l_78 = &g_19;
  int32_t **l_102 = &g_99;
  for (g_19 = (-9); (g_19 >= (-11));
       g_19 = safe_sub_func_int32_t_s_s(g_19, 6)) {
    int32_t *const l_77 = &g_54[1][0];
    if ((((~65529UL), l_77) != l_78)) {
      int32_t *l_79 = &g_54[1][0];
      int32_t *l_80 = &g_54[1][0];
      int32_t *l_81 = &g_54[1][0];
      int32_t *l_82 = &g_54[1][0];
      int32_t *l_83 = &g_54[1][0];
      int32_t *l_84 = &g_54[1][0];
      int32_t *l_85 = &g_54[1][0];
      int32_t *l_86 = (void *)0;
      int32_t *l_87 = (void *)0;
      int32_t l_88 = 0xDA42CED7L;
      int32_t *l_89 = &l_88;
      int32_t l_90 = 0x05CDAFBEL;
      int32_t ***l_94 = (void *)0;
      int32_t **l_96 = &l_86;
      int32_t ***l_95 = &l_96;
      int32_t ***l_101[2];
      int i;
      for (i = 0; i < 2; i++)
        l_101[i] = &g_98;
      ++g_91;
      l_102 = ((*l_95) = &l_78);
    } else {
      uint8_t l_105 = 0UL;
      uint16_t *l_106 = (void *)0;
      uint16_t *l_107 = &g_108;
      g_100 = &l_102;
      (*l_77) = ((safe_add_func_uint16_t_u_u(
                     ((*l_107) = l_105),
                     (safe_unary_minus_func_uint8_t_u(
                         (((safe_mod_func_uint16_t_u_u(g_22[1], (-1L))) &&
                           p_5.f0) == p_6))))),
                 0x8EAE7A24L);
    }
  }
  return g_15;
}

static int8_t func_9(uint32_t p_10) {
  int32_t *l_18 = &g_19;
  int32_t *l_20 = (void *)0;
  int32_t *l_21[2][1];
  uint8_t l_69 = 0xA6L;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_21[i][j] = &g_19;
  }
lbl_72:
  --g_22[1];
  for (g_15 = 14; (g_15 > 38); g_15++) {
    uint64_t l_44[1][2];
    int32_t l_55 = (-5L);
    int16_t l_58 = 9L;
    int32_t l_62 = 0x83A24CD7L;
    int32_t l_63 = 0x2BF48DF1L;
    int32_t l_65 = 3L;
    int32_t l_67 = 0x66912E21L;
    int32_t l_68[1];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_44[i][j] = 0xC5ACC8E11F317735LL;
    }
    for (i = 0; i < 1; i++)
      l_68[i] = (-1L);
    if (((safe_mod_func_uint32_t_u_u(
             (*l_18),
             (safe_mul_func_int8_t_s_s(
                 ((safe_lshift_func_int16_t_s_u(p_10, 15)) || p_10), g_15)))) |
         p_10)) {
      uint32_t *l_39 = (void *)0;
      uint32_t *l_40 = &g_41;
      uint32_t *l_42 = &g_43;
      g_19 =
          ((p_10 == (~p_10)) &&
           ((((((((*l_42) = (((safe_sub_func_uint16_t_u_u(
                                  (!((*l_40) |= ((safe_add_func_uint8_t_u_u(
                                                     0x36L, (-1L))) <= g_15))),
                                  (-1L))) ^
                              0xA7L) ^
                             g_15)) >= p_10),
                0xBDL) < 0UL) <= 1L) &
             0x16L) &&
            l_44[0][1]));
    } else {
      uint64_t *l_46 = &l_44[0][1];
      int32_t l_51 = 0L;
      l_51 ^= ((((*l_46) = (safe_unary_minus_func_int16_t_s(g_41))) != 8UL),
               (safe_sub_func_uint16_t_u_u(
                   (safe_div_func_int64_t_s_s((-7L), g_22[1])), g_41)));
    }
    for (g_19 = 0; (g_19 >= 0); g_19 -= 1) {
      int32_t l_52 = 0L;
      int32_t l_53 = (-4L);
      int32_t l_56 = 0x21FD1B63L;
      int32_t l_57 = (-6L);
      int32_t l_59 = 6L;
      int32_t l_60 = 0x5FD5384EL;
      int32_t l_61 = 0xCB6E384DL;
      int32_t l_64 = 0xF7ADB234L;
      int32_t l_66 = 8L;
      int i, j;
      ++l_69;
      if (l_69)
        goto lbl_72;
    }
  }
  return g_19;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_15;
  csmith_sink_ = g_19;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_22[i];
  }
  csmith_sink_ = g_41;
  csmith_sink_ = g_43;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_54[i][j];
    }
  }
  csmith_sink_ = g_91;
  csmith_sink_ = g_108;
  csmith_sink_ = g_114;
  platform_main_end(0, 0);
  return 0;
}
