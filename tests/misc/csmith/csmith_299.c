// Options:   --seed 300299 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_299.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int16_t g_9 = 1L;
static uint32_t g_11 = 4UL;
static uint32_t *g_15 = &g_11;
static int32_t g_34 = 0x70CC321AL;
static uint64_t g_36 = 18446744073709551615UL;
static volatile int32_t g_37 = 1L;
static int32_t g_56 = 0x2EA9177CL;
static int32_t *volatile g_65 = &g_34;
static int32_t *g_68[2][3] = {{&g_56, &g_56, &g_56}, {&g_56, &g_56, &g_56}};
static int32_t **volatile g_67[1][3] = {
    {&g_68[0][1], &g_68[0][1], &g_68[0][1]}};
static int8_t g_79 = (-2L);
static const int32_t *g_86[2][3] = {{(void *)0, (void *)0, (void *)0},
                                    {(void *)0, (void *)0, (void *)0}};
static const int32_t **g_85 = &g_86[1][0];
static int32_t *const volatile g_92[2] = {&g_34, &g_34};
static int32_t *volatile g_99 = &g_34;
static uint32_t **g_103[3][1] = {{&g_15}, {&g_15}, {&g_15}};
static uint32_t **g_106 = &g_15;

static int8_t func_1(void);
static int64_t func_2(int16_t p_3, int32_t p_4, uint32_t p_5, int16_t p_6,
                      int64_t p_7);
static int32_t *func_16(int8_t p_17, uint32_t *const *p_18, uint16_t p_19,
                        uint16_t p_20, int32_t p_21);

static int8_t func_1(void) {
  uint16_t l_8 = 0x2604L;
  uint32_t *l_10 = &g_11;
  int32_t l_71 = 0x6EBB4DFCL;
  int32_t l_72 = (-5L);
  uint64_t *l_94 = &g_36;
  if ((func_2(l_8, g_9, ((*l_10) = l_8), g_9, l_8) ^ l_8)) {
    int16_t l_13 = 0xF885L;
    uint32_t **l_14[3][3] = {{(void *)0, &l_10, &l_10},
                             {(void *)0, &l_10, &l_10},
                             {(void *)0, &l_10, &l_10}};
    int32_t l_73 = 0x1E7D42A8L;
    const uint32_t l_82 = 0x1E78C190L;
    int i, j;
    if (((&g_11 != (g_15 = ((g_11, (0L > l_13)), (void *)0))) < g_11)) {
      int32_t *l_33 = &g_34;
      uint64_t *l_35 = &g_36;
      int32_t **l_69 = &l_33;
      int32_t *l_70[3];
      uint64_t l_74 = 5UL;
      int i;
      for (i = 0; i < 3; i++)
        l_70[i] = (void *)0;
      (*l_69) = func_16(
          ((((l_8 & g_9) |
             ((*l_35) &= ((safe_lshift_func_int16_t_s_u(
                              ((safe_mod_func_int64_t_s_s(
                                   (~(safe_lshift_func_int8_t_s_s(
                                       (((*l_33) = (safe_mod_func_int16_t_s_s(
                                             g_9, g_11))) <= g_9),
                                       6))),
                                   g_9)) ^
                               g_9),
                              8)) > 0UL))) > g_37),
           l_8),
          &g_15, g_9, l_13, l_8);
      l_74++;
    } else {
      int8_t *l_77 = (void *)0;
      int8_t *l_78 = &g_79;
      int32_t *l_83[2];
      uint64_t l_84 = 1UL;
      int i;
      for (i = 0; i < 2; i++)
        l_83[i] = &g_56;
      l_84 &= (((((*l_78) = l_13) && ((*l_78) = l_71)) >
                ((((safe_rshift_func_int16_t_s_u(((7UL < l_82) < g_37), 6)),
                   &g_36) != &g_36) > l_73)) < (-1L));
    }
  } else {
    const int32_t ***l_87 = &g_85;
    int32_t *l_93[1];
    int i;
    for (i = 0; i < 1; i++)
      l_93[i] = &g_56;
    l_72 &= ((((*l_87) = g_85) == &g_86[1][0]) |
             (safe_div_func_uint16_t_u_u(
                 (safe_mod_func_int8_t_s_s((((g_36 | l_71) && l_71) == l_71),
                                           l_71)),
                 0x203DL)));
    (*g_85) = (**l_87);
  }
  if ((((l_94 == &g_36) <= (safe_add_func_int8_t_s_s(l_71, 0x3EL))) != l_72)) {
    uint32_t l_97[3][3] = {{1UL, 1UL, 1UL}, {1UL, 1UL, 1UL}, {1UL, 1UL, 1UL}};
    int32_t *l_98 = (void *)0;
    uint16_t l_100 = 2UL;
    int i, j;
    (*g_99) ^= l_97[0][0];
    l_100 = 0x895DEA71L;
  } else {
    uint32_t **l_101 = (void *)0;
    uint32_t ***l_102 = (void *)0;
    uint32_t ***l_104 = (void *)0;
    uint32_t ***l_105[3];
    int i;
    for (i = 0; i < 3; i++)
      l_105[i] = (void *)0;
    g_106 = (g_103[1][0] = l_101);
  }
  return l_8;
}

static int64_t func_2(int16_t p_3, int32_t p_4, uint32_t p_5, int16_t p_6,
                      int64_t p_7) {
  uint8_t l_12[1][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_12[i][j] = 4UL;
  }
  for (p_6 = 0; p_6 < 1; p_6 += 1) {
    for (g_11 = 0; g_11 < 1; g_11 += 1) {
      l_12[p_6][g_11] = 0UL;
    }
  }
  return l_12[0][0];
}

static int32_t *func_16(int8_t p_17, uint32_t *const *p_18, uint16_t p_19,
                        uint16_t p_20, int32_t p_21) {
  int8_t l_44 = (-1L);
  uint16_t l_45 = 0xDBD8L;
  const uint32_t *l_57 = &g_11;
  uint32_t **l_58 = &g_15;
  int32_t *l_66[1][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_66[i][j] = &g_34;
  }
  if ((safe_lshift_func_int8_t_s_s(
          (safe_rshift_func_int16_t_s_s(
              (safe_mod_func_uint8_t_u_u(0xAFL, l_44)), 4)),
          (((((l_44 <= g_36), p_18) != &g_15) || l_45) != 4L)))) {
    uint64_t l_46 = 18446744073709551615UL;
    l_46--;
  } else {
    for (p_17 = (-30); (p_17 > (-17));
         p_17 = safe_add_func_int64_t_s_s(p_17, 5)) {
      uint16_t *l_52 = (void *)0;
      uint16_t *l_53 = &l_45;
      int32_t *l_54 = &g_34;
      int32_t *l_55 = &g_56;
      if (p_20)
        break;
      (*l_55) = ((!((*l_53) = 65527UL)), ((*l_54) |= g_11));
    }
    if (l_45) {
      return &g_56;
    } else {
      return &g_34;
    }
  }
  (*g_65) =
      ((l_57 != ((*l_58) = &g_11)) ^
       (safe_mul_func_int8_t_s_s(
           ((((safe_lshift_func_int16_t_s_s(
                  (safe_rshift_func_uint8_t_u_s(l_44, 5)), l_44)) < g_56) &
             l_44) ||
            0x65D28285L),
           0x61L)));
  return l_66[0][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_11;
  csmith_sink_ = g_34;
  csmith_sink_ = g_36;
  csmith_sink_ = g_37;
  csmith_sink_ = g_56;
  csmith_sink_ = g_79;
  platform_main_end(0, 0);
  return 0;
}
