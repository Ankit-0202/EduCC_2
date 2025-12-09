// Options:   --seed 100100 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_100.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
};

union U1 {
  volatile struct S0 f0;
};

static int64_t g_23 = 1L;
static uint8_t g_26 = 0x1CL;
static uint32_t g_30 = 4UL;
static uint8_t *g_46 = &g_26;
static uint64_t g_48[4][2] = {{0x3988F15EA3766593LL, 0x3988F15EA3766593LL},
                              {0x3988F15EA3766593LL, 0x3988F15EA3766593LL},
                              {0x3988F15EA3766593LL, 0x3988F15EA3766593LL},
                              {0x3988F15EA3766593LL, 0x3988F15EA3766593LL}};
static int64_t g_64 = 0x81562E43232AF72DLL;
static uint32_t g_65 = 0x13644CADL;
static union U1 g_69 = {{9UL}};
static const uint8_t g_82[4] = {255UL, 255UL, 255UL, 255UL};
static int32_t g_88 = 0x97E54B53L;
static int32_t *g_87 = &g_88;
static int32_t g_93 = (-8L);
static uint64_t *const g_108 = &g_48[2][1];
static uint64_t *const volatile *g_107 = &g_108;
static int8_t g_109 = (-1L);

static int64_t func_1(void);
static int8_t func_6(uint32_t p_7, struct S0 p_8, const uint64_t p_9);

static int64_t func_1(void) {
  uint64_t l_14[4][4];
  uint8_t *l_24 = (void *)0;
  uint8_t *l_25 = &g_26;
  uint32_t *l_27 = (void *)0;
  int32_t l_28 = 0xEE91B76EL;
  uint32_t *l_29 = &g_30;
  struct S0 l_31 = {1UL};
  const uint32_t l_91 = 5UL;
  int32_t *l_92 = &g_93;
  uint64_t *l_106 = &l_14[0][0];
  uint64_t **l_105 = &l_106;
  uint64_t ***l_104 = &l_105;
  uint32_t l_110 = 1UL;
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      l_14[i][j] = 0UL;
  }
  (*l_92) &= (safe_div_func_int8_t_s_s(
      (safe_add_func_int8_t_s_s(
          func_6(
              ((*l_29) &=
               (l_28 = (safe_rshift_func_uint8_t_u_s(
                    (((safe_div_func_uint16_t_u_u(
                          (l_14[0][0] >
                           (safe_mul_func_uint8_t_u_u(
                               (safe_add_func_uint16_t_u_u(
                                   (((safe_sub_func_uint64_t_u_u(
                                         (((*l_25) =
                                               (safe_rshift_func_uint16_t_u_s(
                                                   (((-1L) >= 0xDB959C45L) !=
                                                    g_23),
                                                   l_14[0][0]))) > l_14[3][1]),
                                         g_23)) < 0xE3CAL) < 0x49C23EDBL),
                                   g_23)),
                               g_23))),
                          g_23)) <= 0xF9A8551BL) ||
                     g_23),
                    6)))),
              l_31, l_14[0][0]),
          0xC4L)),
      l_91));
  l_28 &= (safe_rshift_func_int16_t_s_s(
      ((*l_92) || g_65),
      (safe_mul_func_uint16_t_u_u(
          ((safe_add_func_int8_t_s_s(
               ((safe_sub_func_uint64_t_u_u(
                    (((*l_106) ^=
                      ((((*l_104) =
                             (((((safe_div_func_uint64_t_u_u(
                                     ((&g_48[2][1] != &g_48[2][1]) | g_26),
                                     g_48[2][1])) ||
                                 2UL) != (*l_92)) |
                               (*g_87)),
                              (void *)0)) == g_107) <= 0x3EL)),
                     (*l_92)),
                    (*l_92))) ||
                g_64),
               g_109)) > 1UL),
          0L))));
  return l_110;
}

static int8_t func_6(uint32_t p_7, struct S0 p_8, const uint64_t p_9) {
  uint8_t *l_45 = &g_26;
  uint8_t **l_44[2][2];
  uint64_t *l_47 = &g_48[2][1];
  int32_t l_49 = (-1L);
  int32_t l_50[2];
  const uint8_t *l_81 = &g_82[3];
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_44[i][j] = &l_45;
  }
  for (i = 0; i < 2; i++)
    l_50[i] = 0L;
  if (((safe_rshift_func_int16_t_s_s(
           ((safe_rshift_func_uint16_t_u_s(
                (((safe_mod_func_int16_t_s_s(
                      (safe_mod_func_uint16_t_u_u(
                          ((g_30 >=
                            ((*l_47) = (safe_div_func_int64_t_s_s(
                                 (safe_lshift_func_uint16_t_u_u(
                                     ((g_46 = &g_26) != (void *)0), g_26)),
                                 0x59A7032F1EFAE07DLL)))) ||
                           p_8.f0),
                          (-7L))),
                      l_49)) >= g_23),
                 9UL),
                9)),
            g_48[2][1]),
           l_50[1])) < 1L)) {
    int32_t l_63 = 0L;
    uint64_t **l_68 = &l_47;
    for (p_7 = 0; (p_7 <= 32); p_7++) {
      const uint32_t l_56 = 4294967295UL;
      if (((safe_sub_func_uint8_t_u_u((((*g_46) < 255UL), (~0UL)), (*g_46))) <=
           l_56)) {
        int32_t *l_59 = &l_49;
        (*l_59) = (safe_div_func_uint64_t_u_u(
            ((g_26 != l_50[1]) || ((l_49, &g_48[2][1]) != &g_48[0][0])), g_23));
      } else {
        int32_t *l_60 = &l_50[0];
        int32_t *l_61 = &l_49;
        int32_t *l_62[2];
        int i;
        for (i = 0; i < 2; i++)
          l_62[i] = &l_50[1];
        ++g_65;
      }
      l_68 = &l_47;
    }
  } else {
    uint8_t l_76 = 254UL;
    int32_t *l_77 = (void *)0;
    int32_t *l_78 = &l_50[1];
    int32_t *l_89 = (void *)0;
    int32_t *l_90 = &l_49;
    (*l_78) ^=
        (g_69,
         ((((l_76 = (safe_rshift_func_int8_t_s_s(
                 (safe_div_func_uint64_t_u_u(
                     (((((safe_add_func_uint32_t_u_u(
                             4294967295UL, (p_8.f0, 0x2BB7762BL))) >= l_49) &
                        g_23) &
                       1UL),
                      g_69.f0.f0),
                     p_9)),
                 g_23))) ^
            p_7) |
           8L),
          p_9));
    (*l_90) =
        ((*g_87) = (safe_div_func_uint8_t_u_u(
             (l_50[1] = (&l_76 != (l_81 = &g_26))),
             (safe_add_func_int64_t_s_s(
                 (safe_mod_func_int8_t_s_s(
                     (((*l_47) ^= ((l_78 = g_87) == &g_88)) == l_49), (-8L))),
                 p_8.f0)))));
  }
  return l_50[1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_23;
  csmith_sink_ = g_26;
  csmith_sink_ = g_30;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_48[i][j];
    }
  }
  csmith_sink_ = g_64;
  csmith_sink_ = g_65;
  csmith_sink_ = g_69.f0.f0;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_82[i];
  }
  csmith_sink_ = g_88;
  csmith_sink_ = g_93;
  csmith_sink_ = g_109;
  platform_main_end(0, 0);
  return 0;
}
