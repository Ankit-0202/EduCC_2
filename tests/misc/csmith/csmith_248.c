// Options:   --seed 300248 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_248.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int16_t f0;
  uint32_t f1;
};

struct S1 {
  int64_t f0;
  int64_t f1;
  volatile struct S0 f2;
};

union U2 {
  volatile struct S1 f0;
  uint8_t f1;
};

static uint32_t g_15 = 5UL;
static int8_t g_23 = 0x75L;
static volatile struct S1 g_31 = {0L, 1L, {0x355CL, 0UL}};
static union U2 *g_48 = (void *)0;
static int32_t g_52 = (-1L);
static volatile uint64_t g_71[2] = {1UL, 1UL};
static int32_t *volatile g_74 = &g_52;
static int32_t g_89[3][2] = {{0x108C6EC2L, 0xE2F9DBC3L},
                             {0x108C6EC2L, 0x108C6EC2L},
                             {0xE2F9DBC3L, 0x108C6EC2L}};
static int8_t g_90 = (-8L);
static volatile int8_t g_91 = 0x58L;

static int8_t func_1(void);
static int32_t func_2(const int32_t p_3, uint64_t p_4, uint8_t p_5,
                      uint64_t p_6, uint16_t p_7);
static uint8_t func_12(int32_t p_13, int8_t p_14);

static int8_t func_1(void) {
  int8_t *l_22 = &g_23;
  int32_t l_24 = 4L;
  int32_t *l_75[1][3];
  int32_t *l_76[2][2];
  int32_t *l_77 = (void *)0;
  int32_t *l_78 = &l_24;
  uint64_t l_92 = 18446744073709551613UL;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_75[i][j] = (void *)0;
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_76[i][j] = &g_52;
  }
  g_90 &=
      (func_2(((*l_78) =
                   ((safe_add_func_int8_t_s_s(
                        ((safe_mul_func_int16_t_s_s(
                             (func_12(
                                  (g_15,
                                   (((((*l_22) &= (safe_add_func_int8_t_s_s(
                                           (safe_mul_func_int8_t_s_s(
                                               g_15,
                                               (safe_rshift_func_uint8_t_u_s(
                                                   (0x5BFB66FEL || 0xB2C41AC3L),
                                                   4)))),
                                           g_15))) == 0xCBL),
                                     0L) >= 0x6CL)),
                                  l_24) > l_24),
                             l_24)) ^
                         0UL),
                        l_24)) &&
                    8UL)),
              g_15, g_15, g_15, g_15),
       (*g_74));
  --l_92;
  return g_89[1][0];
}

static int32_t func_2(const int32_t p_3, uint64_t p_4, uint8_t p_5,
                      uint64_t p_6, uint16_t p_7) {
  int16_t l_86 = 0x797CL;
  int32_t l_87 = (-10L);
  int32_t *l_88[1][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_88[i][j] = &g_89[1][0];
  }
  for (p_5 = 0; (p_5 <= 1); p_5 += 1) {
    int32_t *l_85 = &g_52;
    int i;
    l_87 = ((*l_85) =
                ((safe_rshift_func_uint8_t_u_u(
                     (safe_sub_func_uint64_t_u_u(
                         (safe_sub_func_int8_t_s_s(
                             ((((void *)0 != l_85) || g_71[p_5]) ^ l_86), p_3)),
                         g_52)),
                     7)) == 0x8B8AL));
  }
  g_89[1][0] |= ((p_7 && 1UL) == (((-9L) || l_87) | (*g_74)));
  return p_5;
}

static uint8_t func_12(int32_t p_13, int8_t p_14) {
  uint32_t l_34 = 7UL;
  int8_t l_36[1][3];
  int32_t l_61 = 0x51F4A1ABL;
  int32_t l_64 = 3L;
  int32_t l_67 = 0xF3A6950EL;
  int32_t l_68 = (-1L);
  int32_t l_69 = 0x4C2E3979L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_36[i][j] = 0L;
  }
  if ((safe_lshift_func_int16_t_s_u(
          ((safe_sub_func_int8_t_s_s(
               ((safe_lshift_func_uint8_t_u_u(
                    (((g_31, 4UL) | (safe_div_func_uint64_t_u_u(
                                        1UL, 0x26B5CFDA6C2E3A4CLL))) == 1UL),
                    7)) ||
                g_31.f1),
               g_23)) ||
           l_34),
          l_34))) {
    uint32_t l_35[3][3] = {{4294967290UL, 4294967290UL, 4294967290UL},
                           {0xF402BE2FL, 0xE7EB6652L, 0xF402BE2FL},
                           {4294967290UL, 4294967290UL, 4294967290UL}};
    int i, j;
    for (g_31.f2.f1 = 0; g_31.f2.f1 < 3; g_31.f2.f1 += 1) {
      for (p_14 = 0; p_14 < 3; p_14 += 1) {
        l_35[g_31.f2.f1][p_14] = 0x74F57B17L;
      }
    }
  } else {
    int64_t l_47 = (-7L);
    int32_t l_70 = (-1L);
    for (p_13 = 0; (p_13 >= 0); p_13 -= 1) {
      if (p_14)
        break;
    }
    if ((safe_div_func_uint16_t_u_u(
            ((((g_31.f2.f0 <
                (((safe_mul_func_int16_t_s_s(
                      (safe_sub_func_uint8_t_u_u(
                          (safe_lshift_func_uint8_t_u_s(
                              ((safe_sub_func_uint32_t_u_u(0x10A74126L, p_14)) |
                               0xEC6CL),
                              g_23)),
                          p_14)),
                      0xE219L)) != g_15) <= p_14)) |
               l_47) &
              (-8L)),
             p_13),
            p_13))) {
      union U2 **l_49 = &g_48;
      int32_t *l_51 = &g_52;
      int32_t **l_50 = &l_51;
      (*l_49) = g_48;
      (*l_50) = &p_13;
    } else {
      int32_t *l_54 = &g_52;
      int32_t **l_53 = &l_54;
      int32_t *l_55 = &g_52;
      int32_t *l_56 = &g_52;
      int32_t *l_57 = &g_52;
      int32_t *l_58 = &g_52;
      int32_t l_59[2];
      int32_t *l_60 = &l_59[1];
      int32_t *l_62 = &g_52;
      int32_t *l_63 = &l_61;
      int32_t *l_65 = &l_59[1];
      int32_t *l_66[3][2] = {
          {&l_59[1], &l_64}, {&l_59[1], &l_59[1]}, {&l_64, &l_59[1]}};
      int i, j;
      for (i = 0; i < 2; i++)
        l_59[i] = 0L;
      (*l_53) = &g_52;
      g_71[1]++;
    }
  }
  (*g_74) = (&p_13 != &l_61);
  return l_68;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_15;
  csmith_sink_ = g_23;
  csmith_sink_ = g_31.f0;
  csmith_sink_ = g_31.f1;
  csmith_sink_ = g_31.f2.f0;
  csmith_sink_ = g_31.f2.f1;
  csmith_sink_ = g_52;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_71[i];
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_89[i][j];
    }
  }
  csmith_sink_ = g_90;
  csmith_sink_ = g_91;
  platform_main_end(0, 0);
  return 0;
}
