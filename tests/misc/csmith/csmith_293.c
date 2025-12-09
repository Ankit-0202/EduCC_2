// Options:   --seed 300293 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_293.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_8[3] = {0L, 0L, 0L};
static int32_t g_40 = 0L;
static volatile uint32_t g_47 = 4294967295UL;
static uint16_t g_59 = 0x7DFAL;
static int16_t g_70 = 0xFCD5L;
static int32_t *g_76 = &g_8[0];
static int32_t **volatile g_75[1][1] = {{&g_76}};
static int8_t g_82 = 0x37L;
static int64_t g_89 = 0x631D611CF5FC6D38LL;

static int64_t func_1(void);
static int32_t *func_2(int32_t *p_3, int16_t p_4, uint64_t p_5, uint32_t p_6);
static int32_t func_13(int16_t p_14, int64_t p_15, uint16_t p_16, int32_t p_17);

static int64_t func_1(void) {
  int32_t *l_7 = &g_8[0];
  int32_t **l_104[3];
  int32_t *l_105 = &g_8[0];
  uint8_t l_106[2][1];
  int i, j;
  for (i = 0; i < 3; i++)
    l_104[i] = (void *)0;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_106[i][j] = 3UL;
  }
  l_105 = func_2(
      l_7, (*l_7),
      (safe_add_func_int32_t_s_s(
          (safe_mod_func_int8_t_s_s(((func_13((*l_7), g_8[0], (*l_7), g_8[1]) ||
                                      (*l_7)) <= 4294967295UL),
                                    g_8[2])),
          (*g_76))),
      (*l_7));
  return l_106[0][0];
}

static int32_t *func_2(int32_t *p_3, int16_t p_4, uint64_t p_5, uint32_t p_6) {
  int8_t *l_90 = &g_82;
  int32_t l_92[2];
  int i;
  for (i = 0; i < 2; i++)
    l_92[i] = (-1L);
  for (p_4 = 2; (p_4 >= 0); p_4 -= 1) {
    int32_t l_83[2];
    int32_t l_91 = (-8L);
    int i;
    for (i = 0; i < 2; i++)
      l_83[i] = (-10L);
    if (g_8[p_4]) {
      int8_t *l_81[2][2] = {{&g_82, &g_82}, {&g_82, &g_82}};
      int64_t *l_88 = &g_89;
      int32_t *l_93 = &g_40;
      int i, j;
      if ((*g_76))
        break;
      (*l_93) ^= (safe_mul_func_int16_t_s_s(
          (l_92[1] ^= (safe_mul_func_int8_t_s_s(
               (l_83[1] |= ((*p_3) ^ 0x6AC69B76L)),
               ((safe_sub_func_int8_t_s_s(
                    ((((*l_88) = (safe_mod_func_int32_t_s_s((*p_3), g_8[p_4]))),
                      l_90) != (void *)0),
                    g_8[p_4])) <= l_91)))),
          0xD2F7L));
    } else {
      int32_t *l_94 = (void *)0;
      int32_t *l_95 = &g_8[0];
      int32_t *l_96 = &g_8[0];
      int32_t *l_97 = &l_83[1];
      int32_t *l_98 = &g_8[1];
      int32_t *l_99[1];
      int64_t l_100 = 0x3B2A51D28A62AF07LL;
      uint8_t l_101 = 5UL;
      int i;
      for (i = 0; i < 1; i++)
        l_99[i] = &l_83[1];
      l_101++;
    }
  }
  return p_3;
}

static int32_t func_13(int16_t p_14, int64_t p_15, uint16_t p_16,
                       int32_t p_17) {
  int32_t l_24[2][3] = {{(-1L), (-1L), (-1L)}, {0L, 0L, 0L}};
  int32_t *l_29 = &g_8[2];
  int32_t *l_33 = &g_8[2];
  int64_t l_48 = 1L;
  uint32_t l_61 = 4UL;
  int32_t l_63 = 1L;
  int i, j;
  if ((safe_rshift_func_uint16_t_u_s(2UL, 4))) {
    uint32_t l_25 = 0xDDAC0FAAL;
    int32_t l_26[1][1];
    int32_t **l_30 = &l_29;
    int32_t *l_32 = &g_8[0];
    int32_t **l_31 = &l_32;
    int32_t **l_34 = &l_33;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_26[i][j] = 0xC9B780F8L;
    }
    l_26[0][0] = (safe_add_func_int64_t_s_s(
        ((((p_15 != ((safe_mul_func_uint8_t_u_u(l_24[0][2], l_24[0][2])) &
                     0x906D8BC0L)) &&
           l_25) == p_16),
         (-5L)),
        0L));
    if ((g_8[1] <=
         (safe_add_func_int32_t_s_s(
             (((((*l_31) = ((*l_30) = l_29)) != ((*l_34) = l_33)), p_14) ^
              g_8[0]),
             p_16)))) {
      uint32_t *l_39[1];
      int32_t *l_49 = &l_26[0][0];
      int i;
      for (i = 0; i < 1; i++)
        l_39[i] = &l_25;
      (*l_49) ^=
          ((safe_mul_func_int8_t_s_s(
               (safe_sub_func_uint32_t_u_u(
                   ((g_40 = p_14),
                    ((safe_lshift_func_int16_t_s_s(
                         (safe_sub_func_uint64_t_u_u(
                             (((**l_30) &&
                               ((safe_sub_func_uint32_t_u_u(
                                    ((((0x4D8FL ^ 0xAD31L) ^ g_47), p_14) ^
                                     0xCD8AL),
                                    l_48)) |
                                g_40)) &
                              p_15),
                             g_40)),
                         8)),
                     g_40)),
                   4294967290UL)),
               (*l_29))) ||
           g_40);
    } else {
      uint32_t l_50 = 5UL;
      uint64_t l_53 = 1UL;
      --l_50;
      --l_53;
    }
  } else {
    uint16_t *l_58 = &g_59;
    int32_t l_60 = 0x8F60F1B6L;
    int32_t *l_62[2][1];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_62[i][j] = &g_40;
    }
    l_63 |=
        (((((safe_mul_func_uint16_t_u_u(
                ((*l_58) = (((&g_40 == l_29), p_17) > p_16)), l_60)) <= 9UL) &
           l_61) <= l_60),
         p_17);
  }
  if ((+(*l_29))) {
    int16_t *l_69 = &g_70;
    uint32_t l_73 = 0x51DC99B0L;
    int32_t *l_74[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_74[i][j] = &g_40;
    }
    for (p_15 = 0; (p_15 < (-1)); p_15 = safe_sub_func_uint32_t_u_u(p_15, 1)) {
      int64_t l_67 = (-2L);
      l_67 = g_59;
    }
    l_63 ^= (safe_unary_minus_func_uint32_t_u(
        (((*l_69) = 0x3549L) &
         (((safe_add_func_int32_t_s_s(
               (18446744073709551612UL > ((l_73, g_47) || (-10L))),
               0x2CD4B48EL)) < g_59) |
          (*l_29)))));
  } else {
    l_33 = &l_63;
  }
  return (*l_29);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_8[i];
  }
  csmith_sink_ = g_40;
  csmith_sink_ = g_47;
  csmith_sink_ = g_59;
  csmith_sink_ = g_70;
  csmith_sink_ = g_82;
  csmith_sink_ = g_89;
  platform_main_end(0, 0);
  return 0;
}
