// Options:   --seed 100061 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_061.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 0L;
static int32_t g_4[1][3] = {{(-4L), (-4L), (-4L)}};
static int32_t g_5[2] = {0x9869EC42L, 0x9869EC42L};
static int8_t g_24 = 0x47L;
static int64_t g_35 = 0xCE094BF7D69FDB81LL;
static int16_t g_48 = 0x0821L;
static const int32_t g_53 = 0xF140B356L;
static int8_t g_71 = 0L;
static uint8_t g_73 = 0xA1L;
static int32_t *g_82[4][2] = {{(void *)0, (void *)0},
                              {(void *)0, (void *)0},
                              {(void *)0, (void *)0},
                              {(void *)0, (void *)0}};
static int32_t **volatile g_81 = &g_82[3][0];

static int64_t func_1(void);
static const int32_t *func_8(uint32_t p_9);

static int64_t func_1(void) {
  int16_t l_2[2][4] = {{0x6240L, 0x6240L, 0x2C70L, 0x6240L},
                       {0x6240L, 1L, 1L, 0x6240L}};
  int i, j;
  for (g_3 = 0; (g_3 <= 1); g_3 += 1) {
    int32_t *l_57 = &g_4[0][0];
    int32_t **l_56 = &l_57;
    uint32_t l_66 = 0x0765A3FFL;
    uint64_t l_74 = 0x1E6FA5B36276A268LL;
    for (g_4[0][0] = 1; (g_4[0][0] >= 0); g_4[0][0] -= 1) {
      const int32_t *l_52 = &g_53;
      const int32_t **l_51 = &l_52;
      const int32_t *l_55 = &g_5[0];
      const int32_t **l_54 = &l_55;
      int i, j;
      for (g_5[0] = 0; (g_5[0] <= 1); g_5[0] += 1) {
        int32_t *l_6[1];
        int32_t **l_7 = &l_6[0];
        int i, j;
        for (i = 0; i < 1; i++)
          l_6[i] = (void *)0;
        (*l_7) = l_6[0];
        if (l_2[g_3][g_3])
          continue;
      }
      (*l_54) = ((*l_51) = func_8(l_2[g_4[0][0]][g_4[0][0]]));
    }
    (*l_56) = (void *)0;
    for (g_24 = 1; (g_24 >= 0); g_24 -= 1) {
      int32_t *l_58 = &g_4[0][0];
      int32_t *l_59 = (void *)0;
      int32_t *l_60 = &g_5[0];
      int32_t *l_61 = &g_5[0];
      int32_t *l_62 = &g_5[0];
      int32_t *l_63 = &g_5[0];
      int32_t *l_64 = &g_4[0][0];
      int32_t *l_65[4][3] = {{&g_4[0][2], &g_4[0][2], &g_4[0][2]},
                             {&g_5[0], &g_5[0], &g_5[0]},
                             {&g_4[0][2], &g_4[0][2], &g_4[0][2]},
                             {&g_5[0], &g_5[0], &g_5[0]}};
      int8_t *l_70 = &g_71;
      uint8_t *l_72[2];
      int i, j;
      for (i = 0; i < 2; i++)
        l_72[i] = &g_73;
      l_66--;
      if ((safe_unary_minus_func_uint8_t_u(
              (((((*l_70) &= 8L) >= (++l_74)), l_2[g_3][(g_24 + 2)]),
               (safe_lshift_func_int8_t_s_u(l_2[g_3][g_24], 4)))))) {
        (*l_58) ^= g_5[0];
        (*l_58) |=
            (~((g_3 != (((((void *)0 != &g_71) <= 6UL) <= 0x1AACL) > g_5[0])),
               0UL));
      } else {
        if (g_73)
          break;
      }
    }
  }
  for (g_73 = 0; (g_73 <= 1); g_73 += 1) {
    int32_t **l_80 = (void *)0;
    int64_t l_83[3];
    int i;
    for (i = 0; i < 3; i++)
      l_83[i] = 0L;
    (*g_81) = &g_5[0];
    if (l_83[2])
      break;
    for (g_71 = 0; (g_71 <= 1); g_71 += 1) {
      int32_t *l_84 = &g_3;
      int32_t **l_85 = &l_84;
      (*l_85) = l_84;
    }
  }
  return l_2[0][3];
}

static const int32_t *func_8(uint32_t p_9) {
  uint64_t l_18[2];
  int8_t *l_22 = (void *)0;
  int8_t *l_23 = &g_24;
  int32_t l_37 = 0L;
  int i;
  for (i = 0; i < 2; i++)
    l_18[i] = 18446744073709551614UL;
  if (((((*l_23) =
             (((safe_unary_minus_func_int16_t_s(
                   ((((safe_div_func_uint16_t_u_u(
                          ((((!(safe_sub_func_int8_t_s_s(
                                 ((safe_mod_func_uint8_t_u_u(
                                      ((l_18[1] ^ (!g_5[0])) >=
                                       (safe_rshift_func_uint8_t_u_u(
                                           ((l_18[1], p_9) | p_9), g_4[0][1]))),
                                      1UL)) |
                                  65531UL),
                                 g_5[1]))) != l_18[1]) < g_4[0][0]) |
                           g_3),
                          l_18[1])),
                      0L) <= p_9),
                    g_5[0]))) == g_4[0][0]) > g_3)) ||
        0x84L) != g_4[0][1])) {
    for (p_9 = 0; (p_9 <= 1); p_9 += 1) {
      for (g_24 = 1; (g_24 >= 0); g_24 -= 1) {
        int i;
        if (g_5[p_9])
          break;
        if (g_5[g_24])
          break;
      }
    }
  } else {
    uint64_t l_33 = 0UL;
    int64_t *l_34 = &g_35;
    int32_t *l_36[1][4];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 4; j++)
        l_36[i][j] = &g_5[0];
    }
    l_37 = (safe_add_func_int64_t_s_s(
        ((*l_34) &= (safe_sub_func_int32_t_s_s(
             (safe_sub_func_uint16_t_u_u(
                 (g_5[0], 0UL), (safe_mod_func_uint64_t_u_u(l_33, l_33)))),
             p_9))),
        l_18[1]));
    for (l_33 = 0; (l_33 < 59); l_33 = safe_add_func_int32_t_s_s(l_33, 2)) {
      int32_t *const l_46 = &g_5[0];
      if ((0x918CB0B9L & ((safe_sub_func_uint32_t_u_u(
                              ((safe_add_func_int8_t_s_s((l_46 == (void *)0),
                                                         0xB5L)) <= g_5[0]),
                              p_9)) <= g_24))) {
        int16_t *l_47 = &g_48;
        (*l_46) = (1L >= ((*l_47) |= 0x0D90L));
        if ((*l_46))
          break;
      } else {
        (*l_46) =
            ((((*l_34) ^=
               ((p_9, 0xBDL) ||
                ((((((safe_lshift_func_int8_t_s_s(p_9, 2)) & p_9), 0x453FL),
                   (void *)0) != &g_24) == p_9))) >= g_4[0][0]) |
             0xCDBBF849L);
        if (g_4[0][0])
          break;
      }
    }
  }
  return &g_4[0][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_5[i];
  }
  csmith_sink_ = g_24;
  csmith_sink_ = g_35;
  csmith_sink_ = g_48;
  csmith_sink_ = g_53;
  csmith_sink_ = g_71;
  csmith_sink_ = g_73;
  platform_main_end(0, 0);
  return 0;
}
