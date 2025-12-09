// Options:   --seed 100032 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_032.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile uint16_t f0;
  int32_t f1;
  volatile uint64_t f2;
};

static volatile int32_t g_3 = 0xE1265AB3L;
static volatile int32_t g_4 = 0xA624CDB8L;
static int32_t g_5 = (-1L);
static uint8_t g_13 = 0UL;
static uint8_t g_32 = 0xB2L;
static uint8_t g_34 = 252UL;
static uint8_t g_37[1][2] = {{0xFBL, 0xFBL}};
static volatile int32_t *volatile g_38 = &g_3;
static int16_t g_43[1][3] = {{0x347AL, 0x347AL, 0x347AL}};
static volatile uint8_t g_52 = 0UL;
static volatile struct S0 g_55 = {65535UL, 0xBE340CFCL, 1UL};
static uint32_t g_67 = 0x70D6E0D2L;
static int32_t g_70 = 0xC75621C9L;
static int32_t *volatile g_69 = &g_70;

static const uint32_t func_1(void);
static int32_t func_6(const int8_t p_7);

static const uint32_t func_1(void) {
  int32_t l_2[3][1];
  int32_t l_51 = 3L;
  int64_t l_65 = 3L;
  int32_t l_66 = (-10L);
  int8_t l_68 = 0L;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_2[i][j] = 5L;
  }
  for (g_5 = 0; (g_5 <= 0); g_5 += 1) {
    uint8_t *l_12 = &g_13;
    int32_t l_14 = 0x132D7AF2L;
    int32_t *l_50 = &l_14;
    if (func_6(
            (g_5 >
             (((safe_mod_func_int64_t_s_s(
                   (((safe_add_func_uint64_t_u_u(
                         (l_2[2][0] > ((((*l_12) = 0x30L), g_5) != l_2[2][0])),
                         g_4)) == 0x10DDL) <= g_5),
                   g_5)) <= 65533UL) >= l_14)))) {
      for (g_13 = 0; (g_13 <= 0); g_13 += 1) {
        int32_t *l_49 = &g_5;
        int32_t **l_48[4][2] = {
            {&l_49, &l_49}, {&l_49, &l_49}, {&l_49, &l_49}, {&l_49, &l_49}};
        int i, j;
        l_50 = ((&l_2[g_13][g_5] != &g_3), &l_2[0][0]);
        g_52--;
      }
    } else {
      if ((*g_38))
        break;
    }
    for (g_13 = 0; (g_13 <= 0); g_13 += 1) {
      volatile struct S0 *l_56 = &g_55;
      (*l_56) = g_55;
    }
  }
  (*g_69) =
      (g_5 = (safe_rshift_func_int8_t_s_u(
           ((((0L >= (safe_mod_func_int16_t_s_s(
                         ((g_67 = ((safe_mul_func_uint8_t_u_u(
                                       ((safe_sub_func_int16_t_s_s(
                                            (l_2[2][0] |= (l_65 & g_55.f0)),
                                            l_65)) != 0xEFL),
                                       l_65)) &&
                                   l_66)) <= g_37[0][0]),
                         g_37[0][0]))) &
              0L) != l_68) &
            g_43[0][1]),
           g_37[0][0])));
  return g_43[0][1];
}

static int32_t func_6(const int8_t p_7) {
  uint32_t l_15[4] = {0UL, 0UL, 0UL, 0UL};
  int32_t l_42 = (-7L);
  int i;
  for (g_13 = 0; (g_13 <= 3); g_13 += 1) {
    uint16_t l_30 = 0x46F2L;
    uint8_t *l_31 = &g_32;
    uint8_t *l_33 = &g_34;
    uint32_t l_35 = 0xE905F4D0L;
    uint8_t *l_36 = &g_37[0][0];
    int32_t l_40 = 0xA4122E7DL;
    int32_t l_41 = 9L;
    int32_t l_44 = (-1L);
    uint16_t l_45 = 65530UL;
    int i;
    if ((l_15[g_13] <=
         ((safe_add_func_int32_t_s_s(
              ((((safe_rshift_func_uint16_t_u_s(
                     (((*l_36) ^=
                       ((safe_lshift_func_uint8_t_u_u(
                            (1UL <=
                             (safe_mul_func_uint8_t_u_u(
                                 ((*l_33) |=
                                  ((*l_31) =
                                       ((safe_div_func_int8_t_s_s(
                                            (safe_sub_func_uint16_t_u_u(
                                                (((safe_mul_func_int16_t_s_s(
                                                      ((-3L) <= 0xAAL), g_4)) <
                                                  l_30),
                                                 0xBF5BL),
                                                p_7)),
                                            g_13)) != 0L))),
                                 l_35))),
                            6)) ^
                        7UL)) ^
                      l_15[g_13]),
                     l_15[1])) &&
                 l_15[3]) >= (-6L)) &&
               0xC8F9491450187E52LL),
              0x54EB856AL)) ^
          g_13))) {
      (*g_38) = g_3;
      if (p_7)
        continue;
    } else {
      int32_t *l_39[1];
      int i;
      for (i = 0; i < 1; i++)
        l_39[i] = (void *)0;
      l_45--;
    }
  }
  return (*g_38);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_13;
  csmith_sink_ = g_32;
  csmith_sink_ = g_34;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_37[i][j];
    }
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_43[i][j];
    }
  }
  csmith_sink_ = g_52;
  csmith_sink_ = g_55.f0;
  csmith_sink_ = g_55.f1;
  csmith_sink_ = g_55.f2;
  csmith_sink_ = g_67;
  csmith_sink_ = g_70;
  platform_main_end(0, 0);
  return 0;
}
