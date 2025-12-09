// Options:   --seed 200179 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_179.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile int64_t f0;
};

static float g_8 = 0x6.A485BFp-25;
static volatile int32_t g_9 = (-1L);
static uint32_t g_12 = 0x0734F094L;
static int16_t g_15 = 0x92C5L;
static uint16_t g_16 = 0xE08AL;
static int16_t *g_40[4][4] = {{&g_15, &g_15, &g_15, &g_15},
                              {&g_15, &g_15, &g_15, &g_15},
                              {&g_15, &g_15, &g_15, &g_15},
                              {&g_15, &g_15, &g_15, &g_15}};
static int32_t g_42 = 0xD41BD43DL;
static uint32_t g_43 = 4294967286UL;
static int32_t g_53 = 0xFE01AF02L;
static int32_t g_61 = 1L;
static const int32_t *g_73 = &g_42;
static const int32_t **volatile g_72 = &g_73;
static volatile union U0 g_76[1] = {{1L}};
static int16_t **const g_80 = &g_40[3][3];
static int16_t **const *g_79[2] = {&g_80, &g_80};
static int32_t g_95 = 0xDBFDF841L;
static float g_96 = 0xD.69965Fp+94;
static volatile int64_t g_97[2][2] = {{1L, 1L}, {1L, 1L}};
static int16_t g_98[2][3] = {{(-1L), (-1L), (-1L)}, {0L, 0L, 0L}};
static int32_t g_99 = 0x61642E2BL;
static volatile uint16_t g_100 = 65529UL;

static uint64_t func_1(void);
static uint32_t func_2(int32_t p_3);

static uint64_t func_1(void) {
  int16_t *l_13 = (void *)0;
  int16_t *l_14 = &g_15;
  int32_t l_31[3];
  int32_t l_32 = 1L;
  uint32_t l_69[1][1];
  int32_t *l_90 = &l_31[0];
  int32_t *l_91 = &l_32;
  int32_t *l_92 = &l_32;
  int32_t *l_93 = (void *)0;
  int32_t *l_94[4][4];
  int i, j;
  for (i = 0; i < 3; i++)
    l_31[i] = 0x028F4E1CL;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_69[i][j] = 18446744073709551615UL;
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      l_94[i][j] = &l_31[0];
  }
  if ((g_43 ^=
       (func_2(
            ((g_9 <=
              ((safe_rshift_func_int16_t_s_u((g_16 &= ((*l_14) = g_12)), 1)) >
               (safe_add_func_uint32_t_u_u(
                   (safe_mul_func_int16_t_s_s(
                       (safe_lshift_func_int16_t_s_s(
                           (safe_mod_func_int32_t_s_s(
                               (safe_mod_func_uint64_t_u_u(
                                   (safe_add_func_uint32_t_u_u(
                                       ((l_31[0] ^= (safe_add_func_uint16_t_u_u(
                                             g_12, g_12))) &
                                        0xF1E0C863L),
                                       1UL)),
                                   l_32)),
                               g_12)),
                           l_32)),
                       g_12)),
                   4294967294UL)))) &
             0UL)),
        0L))) {
    int16_t l_50[1];
    uint16_t *l_51 = (void *)0;
    uint16_t *l_52 = &g_16;
    int16_t **l_54[4][3] = {{&l_13, &l_13, &l_14},
                            {&l_13, &l_14, &l_14},
                            {&l_14, &l_14, &g_40[1][1]},
                            {&l_13, &l_14, &l_13}};
    int32_t l_71 = (-1L);
    float *l_77 = &g_8;
    int16_t ***l_81 = (void *)0;
    int32_t *l_82 = &l_71;
    int i, j;
    for (i = 0; i < 1; i++)
      l_50[i] = 0xA2E8L;
    if ((((((safe_div_func_uint16_t_u_u(
                ((safe_lshift_func_uint16_t_u_u(
                     (safe_rshift_func_int8_t_s_s(
                         ((((*l_52) = ((&g_15 != &g_15) ^ l_50[0])) | l_50[0]) &
                          g_12),
                         7)),
                     l_31[0])) <= g_9),
                g_53)),
            &g_40[3][3]) != l_54[2][2]),
          l_32),
         0x2BAC4117L)) {
      uint16_t *l_57 = &g_16;
      int32_t *l_60 = (void *)0;
      int32_t l_70 = 0L;
      g_61 &= (safe_lshift_func_int16_t_s_u(
          (((void *)0 == l_57) ||
           ((*l_14) = (safe_mod_func_uint16_t_u_u(g_9, 65535UL)))),
          g_42));
      l_71 = (safe_div_func_int64_t_s_s(
          ((((+((safe_sub_func_int8_t_s_s(
                    ((safe_sub_func_int64_t_s_s(
                         (((((0UL < ((0x9414028BL > g_15) < 8L)) | 6UL),
                            g_53) <= l_69[0][0]) &
                          l_50[0]),
                         l_70)) < g_16),
                    0x8CL)) &
                0xE49D2A59A03C9D26LL)) < g_16) <= 1UL) &&
           g_53),
          0xB186EC4F4D126829LL));
    } else {
      int16_t ***l_74 = (void *)0;
      int16_t ***l_75 = &l_54[1][0];
      g_72 = g_72;
      (*l_75) = l_54[2][2];
    }
    (*l_82) ^= (g_76[0], (((*l_77) = l_31[0]),
                          ((!(((g_79[1] == l_81) < l_50[0]) == g_15)) ^ 9UL)));
  } else {
    uint32_t l_85[3];
    int32_t *l_88 = (void *)0;
    uint32_t l_89 = 0x56EC073BL;
    int i;
    for (i = 0; i < 3; i++)
      l_85[i] = 0UL;
    if ((safe_sub_func_uint32_t_u_u(
            (((*g_72) !=
              ((l_85[2] < ((safe_mul_func_uint16_t_u_u(g_61, 3L)) ^ g_15)),
               l_88)) ^
             0xD9C50E9BCC685A4BLL),
            0x6156DBBFL))) {
      return l_89;
    } else {
      return g_42;
    }
  }
  g_100--;
  return g_43;
}

static uint32_t func_2(int32_t p_3) {
  uint32_t l_36 = 0x33BD3E01L;
  int16_t *l_37[4];
  int16_t *l_39 = &g_15;
  int16_t **l_38[1];
  int32_t *l_41 = &g_42;
  int i;
  for (i = 0; i < 4; i++)
    l_37[i] = &g_15;
  for (i = 0; i < 1; i++)
    l_38[i] = &l_39;
  for (g_12 = 0; (g_12 != 22); ++g_12) {
    int32_t l_35 = 0x8EE3F2F3L;
    l_36 ^= l_35;
  }
  (*l_41) ^= ((l_37[1] = (g_16, l_37[1])) == (g_40[3][3] = &g_15));
  return (*l_41);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_9;
  csmith_sink_ = g_12;
  csmith_sink_ = g_15;
  csmith_sink_ = g_16;
  csmith_sink_ = g_42;
  csmith_sink_ = g_43;
  csmith_sink_ = g_53;
  csmith_sink_ = g_61;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_95;
  csmith_sink_ = g_96;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_97[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_98[i][j];
    }
  }
  csmith_sink_ = g_99;
  csmith_sink_ = g_100;
  platform_main_end(0, 0);
  return 0;
}
