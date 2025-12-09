// Options:   --seed 100014 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_014.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile uint8_t f0;
  int16_t f1;
};

static int32_t g_3[1] = {(-8L)};
static int8_t g_6 = 0x34L;
static int32_t g_9 = 0x215256EEL;
static int32_t *volatile g_8 = &g_9;
static uint16_t g_23[3][4] = {{65535UL, 0xC658L, 65535UL, 0xC658L},
                              {65535UL, 0xC658L, 65535UL, 0xC658L},
                              {65535UL, 0xC658L, 65535UL, 0xC658L}};
static uint16_t g_26 = 0x03BEL;
static volatile int8_t g_34 = 9L;
static volatile int8_t *g_33 = &g_34;
static volatile int8_t **volatile g_32[1][1] = {{&g_33}};
static uint64_t g_49 = 18446744073709551615UL;
static union U0 g_52 = {0xA3L};
static int64_t g_55 = 0L;
static union U0 *g_62 = &g_52;
static union U0 **volatile g_61 = &g_62;
static int32_t **volatile g_64[2] = {(void *)0, (void *)0};
static uint32_t g_73 = 4UL;
static int32_t *g_80 = &g_3[0];
static int32_t **volatile g_79 = &g_80;
static int32_t **volatile g_107 = (void *)0;
static int32_t **const volatile g_108 = &g_80;

static const uint64_t func_1(void);
static int64_t func_10(const int8_t p_11, int8_t *p_12, uint32_t p_13);

static const uint64_t func_1(void) {
  int64_t l_2[3];
  int32_t l_7[1][4] = {{0xE2949F4FL, 0xE2949F4FL, 0xE2949F4FL, 0xE2949F4FL}};
  int8_t *l_14 = (void *)0;
  int i, j;
  for (i = 0; i < 3; i++)
    l_2[i] = 0x45CDBE8E56F9B2CFLL;
  for (g_3[0] = 2; (g_3[0] >= 0); g_3[0] -= 1) {
    int32_t l_4 = 0xACC5D9B4L;
    int8_t *l_5 = &g_6;
    int i;
    l_4 = (((l_2[g_3[0]] = (-6L)) <=
            ((((*l_5) = l_4), (g_3[0] != l_4)) != l_4)) == l_7[0][2]);
    (*g_8) = l_7[0][3];
  }
  for (g_6 = 2; (g_6 >= 0); g_6 -= 1) {
    int32_t *l_63[1][1];
    int16_t l_74[2];
    int32_t l_75 = 0x7CFDA208L;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_63[i][j] = &l_7[0][2];
    }
    for (i = 0; i < 2; i++)
      l_74[i] = 0L;
    if (((*g_8) = (func_10(l_2[g_6], l_14, (l_2[g_6], l_7[0][0])) < 6UL))) {
      for (g_26 = 0; (g_26 <= 2); g_26 += 1) {
        int32_t **l_65 = &l_63[0][0];
        (*l_65) = &g_3[0];
      }
      for (g_26 = 0; (g_26 <= 2); g_26 += 1) {
        int32_t l_68 = (-3L);
        g_9 |=
            (l_2[0] ||
             (((safe_div_func_uint64_t_u_u((g_6 < (1L > (*g_33))), l_7[0][2])) ^
               0x9BC9383A24CD7C08LL) != 0x6120E7A9L));
        (*g_8) = l_68;
      }
    } else {
      uint32_t l_72 = 0x255F5DB9L;
      uint16_t l_76 = 65529UL;
      g_73 = (l_72 |= ((safe_mod_func_uint16_t_u_u(
                           7UL, (((!l_7[0][2]), g_3[0]) && l_7[0][2]))) &&
                       0x4167AD25L));
      ++l_76;
    }
    for (g_49 = 0; (g_49 <= 0); g_49 += 1) {
      uint64_t l_105 = 0xC356ED06C0765CA4LL;
      uint32_t l_106 = 0x11AB6490L;
      for (l_75 = 2; (l_75 >= 0); l_75 -= 1) {
        uint32_t l_81[3][2] = {{8UL, 8UL}, {8UL, 8UL}, {8UL, 8UL}};
        int i, j;
        (*g_79) = &l_7[g_49][(g_49 + 1)];
        --l_81[0][1];
      }
      if (((((0x5225L &&
              (safe_add_func_uint8_t_u_u(
                  (safe_rshift_func_int8_t_s_s(
                      (~((safe_lshift_func_uint8_t_u_s(
                             (safe_mul_func_uint16_t_u_u(
                                 ((((((safe_sub_func_uint32_t_u_u(
                                          l_7[0][2],
                                          ((safe_rshift_func_int16_t_s_s(
                                               ((safe_rshift_func_uint8_t_u_s(
                                                    ((safe_mul_func_uint16_t_u_u(
                                                         (((*g_8) |=
                                                           (~(safe_lshift_func_int8_t_s_s(
                                                               (+g_23[1][1]),
                                                               0)))) |
                                                          0UL),
                                                         0xB9F2L)),
                                                     0x7CL),
                                                    4)) ^
                                                l_105),
                                               0)) &
                                           65527UL))) == 0xA01F12A7L),
                                     0xB190L) ||
                                    65535UL),
                                   (*g_33)) != g_49),
                                 0x58CDL)),
                             g_23[1][0])) == l_106)),
                      g_6)),
                  g_55))) != 0x996E4E2FL) ^
            g_3[0]) >= 0xBE80L)) {
        if (l_105)
          break;
        (*g_108) = &l_7[0][2];
      } else {
        return l_7[0][1];
      }
    }
  }
  return l_2[1];
}

static int64_t func_10(const int8_t p_11, int8_t *p_12, uint32_t p_13) {
  int8_t *l_18 = &g_6;
  int8_t **l_17 = &l_18;
  uint16_t *l_21 = (void *)0;
  uint16_t *l_22 = &g_23[1][0];
  int32_t l_24 = 0x4DE5A82AL;
  uint16_t *l_25 = &g_26;
  int32_t l_37[4][3];
  uint64_t *l_48[4];
  int8_t **l_53 = (void *)0;
  int64_t *l_54[1];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++)
      l_37[i][j] = (-1L);
  }
  for (i = 0; i < 4; i++)
    l_48[i] = &g_49;
  for (i = 0; i < 1; i++)
    l_54[i] = &g_55;
  if ((((*l_25) =
            ((((*l_22) = ((safe_mul_func_uint8_t_u_u(
                              (((*l_17) = &g_6) == (void *)0),
                              (safe_add_func_uint16_t_u_u(0x2A2EL, g_3[0])))) ==
                          g_3[0])) != l_24) <= l_24)) &
       g_3[0])) {
    uint16_t l_35 = 0xCADCL;
    int32_t *l_36[1];
    int i;
    for (i = 0; i < 1; i++)
      l_36[i] = &g_9;
    g_3[0] ^= (l_37[3][0] =
                   ((((l_24 = (safe_mul_func_int8_t_s_s(
                           ((safe_sub_func_int64_t_s_s(
                                ((safe_unary_minus_func_uint64_t_u(
                                     ((&l_18 == (g_9, g_32[0][0])) < l_24))) ||
                                 l_35),
                                2L)),
                            (-3L)),
                           0xF4L))) ||
                      0xADE89B93L),
                     0xB531EAA473ECFB86LL) <= 18446744073709551609UL));
  } else {
    for (l_24 = (-11); (l_24 <= 6); ++l_24) {
      if (l_37[3][0])
        break;
    }
  }
  if ((safe_mul_func_int16_t_s_s(
          l_37[3][2], ((((l_24 &= (safe_lshift_func_uint16_t_u_u(
                              (safe_lshift_func_int8_t_s_u(
                                  p_11, (safe_sub_func_uint16_t_u_u(
                                            ((((++g_49) ^ ((g_52, 1UL) > p_11)),
                                              &p_12) == l_53),
                                            g_3[0])))),
                              p_13))) > 1UL) >= l_37[1][1]) &
                       p_11)))) {
    int32_t *l_56[1];
    uint16_t l_57 = 0x90EBL;
    int i;
    for (i = 0; i < 1; i++)
      l_56[i] = &g_3[0];
    l_57++;
  } else {
    union U0 *l_60 = &g_52;
    (*g_61) = l_60;
  }
  return p_11;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_3[i];
  }
  csmith_sink_ = g_6;
  csmith_sink_ = g_9;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_23[i][j];
    }
  }
  csmith_sink_ = g_26;
  csmith_sink_ = g_34;
  csmith_sink_ = g_49;
  csmith_sink_ = g_52.f0;
  csmith_sink_ = g_55;
  csmith_sink_ = g_73;
  platform_main_end(0, 0);
  return 0;
}
