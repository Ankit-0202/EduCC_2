// Options:   --seed 100037 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_037.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint32_t f0;
};

union U2 {
  const volatile int32_t f0;
  int16_t f1;
};

static int32_t g_2[1][4] = {{8L, 8L, 8L, 8L}};
static int32_t g_5 = (-3L);
static uint8_t g_36 = 0xE9L;
static int32_t **volatile g_40 = (void *)0;
static int32_t **volatile g_41[2][3] = {{(void *)0, (void *)0, (void *)0},
                                        {(void *)0, (void *)0, (void *)0}};
static int32_t *g_43 = &g_5;
static int32_t **volatile g_42 = &g_43;
static int8_t g_49 = 0xA8L;
static int32_t g_51 = 0x5EFBE72FL;
static int32_t *volatile g_50 = &g_51;
static union U2 g_62 = {-6L};
static struct S1 g_82 = {0xA6BAE6ACL};
static uint8_t g_91 = 0xE3L;
static uint32_t g_117[3][3] = {{0xF8D3DCD3L, 0xF8D3DCD3L, 0xF8D3DCD3L},
                               {0x94F1BE2EL, 0x7A3C17D6L, 0x94F1BE2EL},
                               {0xF8D3DCD3L, 0xF8D3DCD3L, 0xF8D3DCD3L}};

static const int32_t func_1(void);
static int32_t *func_8(const int8_t p_9, int8_t p_10, int32_t *const p_11);

static const int32_t func_1(void) {
  const int32_t l_61 = 0x01FF3C8DL;
  int32_t **l_64[4];
  int32_t l_102 = 0x5847AAFFL;
  const int8_t l_120 = (-4L);
  int i;
  for (i = 0; i < 4; i++)
    l_64[i] = (void *)0;
lbl_92:
  for (g_2[0][3] = 23; (g_2[0][3] > (-21)); --g_2[0][3]) {
    int16_t l_14 = 0x2045L;
    for (g_5 = (-7); (g_5 != (-18)); --g_5) {
      int16_t l_15 = 0x44C0L;
      (*g_42) = func_8((safe_sub_func_int64_t_s_s(4L, (l_14 <= g_5))), l_15,
                       &g_2[0][0]);
    }
  }
  for (g_5 = 0; (g_5 <= 0); g_5 += 1) {
    uint32_t l_44 = 0x85024D8FL;
    int32_t *l_45 = &g_2[0][3];
    uint64_t l_78 = 0x36D0B4E555501D2DLL;
    int32_t l_93 = (-1L);
    int32_t l_95 = 0x62AF0730L;
    int32_t l_96 = 0x361F4973L;
    int32_t l_97 = (-5L);
    int32_t l_100 = 0L;
    int32_t l_101 = (-5L);
    int32_t l_103 = 0xAED21B86L;
    int32_t l_106 = 0x90277B54L;
    int32_t l_108 = 0xAC18B040L;
    int32_t l_109 = 0x4CDD2EE4L;
    int32_t l_110 = 1L;
    int32_t l_114 = 0xD22BE5E2L;
    if (((*l_45) &= (l_44 | 4L))) {
      int8_t *l_48 = &g_49;
      const int32_t l_60 = 0x3C9E4899L;
      for (l_44 = 0; (l_44 <= 1); l_44 += 1) {
        int i, j;
        (*g_50) ^= (safe_rshift_func_uint8_t_u_u(
            ((g_2[g_5][(g_5 + 2)] = 0xAC89D693L) <=
             (((l_48 != (void *)0) != 0x7FAEL) >= g_49)),
            0));
        (*l_45) = g_2[g_5][(g_5 + 2)];
      }
      if ((safe_mul_func_uint8_t_u_u(
              ((((safe_mul_func_uint8_t_u_u(
                     ((safe_sub_func_int64_t_s_s(
                          (&g_36 != (void *)0),
                          (safe_sub_func_int32_t_s_s(
                              ((((((void *)0 == &g_49) && 0xE38EL), 0x8FL) ||
                                246UL) <= 0xD3L),
                              l_60)))) == g_5),
                     g_2[0][2])) <= l_60),
                (*l_45)),
               g_36),
              l_61))) {
        (*l_45) = (*l_45);
      } else {
        int32_t **l_63 = &l_45;
        (**l_63) =
            (g_62, (l_63 == ((((void *)0 == (*l_63)) ^ 0x7B5901663317A7F3LL),
                             l_64[1])));
      }
    } else {
      uint32_t l_75 = 0xDFF541EDL;
      (*g_50) ^= ((safe_sub_func_uint32_t_u_u(
                      g_49, (safe_mul_func_uint8_t_u_u(
                                (safe_rshift_func_uint16_t_u_u(
                                    (safe_div_func_uint16_t_u_u(
                                        ((safe_sub_func_int16_t_s_s(
                                             l_75, ((safe_add_func_int64_t_s_s(
                                                        g_49, 0UL)) > l_75))) |
                                         g_5),
                                        g_2[0][2])),
                                    0)),
                                l_78)))) >= 0x5676L);
      if (l_75)
        continue;
    }
    for (g_36 = 0; (g_36 <= 0); g_36 += 1) {
      uint8_t *l_90 = &g_91;
      int32_t l_94 = 7L;
      int32_t l_98 = (-2L);
      int32_t l_111 = 0x61D1B06CL;
      int32_t l_112 = 0x5343E278L;
      int32_t l_113 = 0x7E0F1540L;
      int32_t l_115 = (-2L);
      int32_t l_116[4][4] = {{3L, 0x6D33B1CCL, 3L, 0x6D33B1CCL},
                             {3L, 0x6D33B1CCL, 3L, 0x6D33B1CCL},
                             {3L, 0x6D33B1CCL, 3L, 0x6D33B1CCL},
                             {3L, 0x6D33B1CCL, 3L, 0x6D33B1CCL}};
      int i, j;
      if ((safe_unary_minus_func_uint8_t_u(
              ((*l_90) &= (safe_mul_func_int8_t_s_s(
                   (g_82,
                    (safe_div_func_int16_t_s_s(
                        (((safe_lshift_func_int16_t_s_s(
                              (+(safe_sub_func_uint64_t_u_u(g_2[0][3], g_49))),
                              (*l_45))) &
                          g_49) ||
                         9UL),
                        (*l_45)))),
                   0x8FL)))))) {
        if (g_91)
          goto lbl_92;
        if (g_49)
          goto lbl_92;
      } else {
        int32_t l_99 = 0L;
        int32_t l_104 = 0x1FA81E3AL;
        int32_t l_105 = 0x63C46DEBL;
        int32_t l_107[2];
        int i, j;
        for (i = 0; i < 2; i++)
          l_107[i] = (-9L);
        g_51 &= (g_2[g_36][(g_5 + 1)] = (g_41[(g_5 + 1)][g_36] == &g_43));
        --g_117[2][1];
      }
    }
  }
  return l_120;
}

static int32_t *func_8(const int8_t p_9, int8_t p_10, int32_t *const p_11) {
  int32_t l_16[4][2];
  int32_t *l_17 = &g_2[0][3];
  uint8_t *l_35 = &g_36;
  int8_t l_37 = (-1L);
  int8_t *l_38 = &l_37;
  int32_t l_39 = 0xFBC6A687L;
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++)
      l_16[i][j] = 0xB3BFA32AL;
  }
  for (p_10 = 1; (p_10 >= 0); p_10 -= 1) {
    return l_17;
  }
  l_39 |=
      ((safe_unary_minus_func_int32_t_s((safe_rshift_func_int8_t_s_u(
           ((*l_38) =
                ((safe_div_func_uint64_t_u_u(
                     (safe_rshift_func_int16_t_s_u(
                         ((safe_sub_func_int64_t_s_s(
                              ((safe_sub_func_uint8_t_u_u(
                                   ((!(((p_9 ^
                                         (g_5 >
                                          (+(safe_rshift_func_int16_t_s_s(
                                              (((*l_35) =
                                                    (safe_lshift_func_uint8_t_u_u(
                                                        255UL, 5))) ||
                                               1UL),
                                              l_37))))) ||
                                        p_10),
                                       (-1L))) != g_2[0][3]),
                                   p_10)),
                               p_9),
                              g_2[0][3])) != g_5),
                         g_2[0][2])),
                     0xEF34EA885C82F744LL)) <= g_2[0][0])),
           (*l_17))))),
       (*p_11));
  return &g_5;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_5;
  csmith_sink_ = g_36;
  csmith_sink_ = g_49;
  csmith_sink_ = g_51;
  csmith_sink_ = g_62.f0;
  csmith_sink_ = g_62.f1;
  csmith_sink_ = g_82.f0;
  csmith_sink_ = g_91;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_117[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
