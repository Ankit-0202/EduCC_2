// Options:   --seed 200186 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_186.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2[2][4] = {{6L, 6L, 6L, 6L}, {6L, 6L, 6L, 6L}};
static float g_17[4] = {(-0x8.8p+1), (-0x8.8p+1), (-0x8.8p+1), (-0x8.8p+1)};
static int32_t g_19 = 0L;
static int32_t *volatile g_18[3][4] = {{&g_19, &g_19, &g_19, &g_19},
                                       {&g_19, &g_19, &g_19, &g_19},
                                       {&g_19, &g_19, &g_19, &g_19}};
static int16_t g_38 = (-1L);
static uint16_t g_42[4] = {1UL, 1UL, 1UL, 1UL};
static int64_t g_58 = 0xD40FD77138BF9CC5LL;
static int64_t g_60 = 0x3DF1C911B6BEFC54LL;
static uint32_t g_79 = 0UL;

static uint32_t func_1(void);
static int32_t *func_5(const int32_t *p_6, uint8_t p_7);

static uint32_t func_1(void) {
  const int32_t *l_8 = (void *)0;
  const int32_t l_16 = 0xA40F2FDAL;
  uint8_t l_68 = 0x8DL;
  int32_t l_73 = 0x01D5BC3FL;
  int32_t l_74 = 5L;
  int32_t l_75[4] = {0xA9B86155L, 0xA9B86155L, 0xA9B86155L, 0xA9B86155L};
  int i;
  for (g_2[0][3] = 0; (g_2[0][3] < 18); g_2[0][3]++) {
    int32_t *l_15 = &g_2[0][2];
    int32_t l_71 = 0xEAA97CADL;
    int32_t l_72 = 0xA8ABF266L;
    int32_t l_76[2];
    int i;
    for (i = 0; i < 2; i++)
      l_76[i] = 0x9B4FD71AL;
    g_18[0][1] = func_5(
        l_8, (g_2[1][1] &
              (safe_lshift_func_int16_t_s_s(
                  ((safe_mul_func_int8_t_s_s(
                       (safe_sub_func_int32_t_s_s((l_15 != (void *)0), l_16)),
                       0UL)) ||
                   g_2[0][0]),
                  4))));
    for (g_38 = 26; (g_38 != 29); ++g_38) {
      int32_t *l_67[3];
      float l_77 = 0x8.Bp+1;
      int8_t l_78 = 6L;
      int i;
      for (i = 0; i < 3; i++)
        l_67[i] = &g_19;
      ++l_68;
      ++g_79;
    }
  }
  if (l_16) {
    int32_t l_84[2][4] = {{0L, 6L, 6L, 0L}, {6L, 0L, 6L, 6L}};
    float *l_85 = (void *)0;
    const uint32_t l_86 = 0x70EA8E11L;
    float *l_87[4];
    int i, j;
    for (i = 0; i < 4; i++)
      l_87[i] = (void *)0;
    g_17[3] = ((safe_div_func_float_f_f((l_75[0] = (g_38 >= l_84[1][2])),
                                        (g_79, l_86))) != g_38);
  } else {
    int32_t *l_88[4][3] = {{&l_75[2], &l_75[2], &l_75[2]},
                           {&l_73, &l_73, &l_73},
                           {&l_75[2], &l_75[2], &l_75[2]},
                           {&l_73, &l_73, &l_73}};
    uint32_t l_89 = 1UL;
    int i, j;
    ++l_89;
    l_75[3] ^= 0xCF6E471BL;
  }
  return g_58;
}

static int32_t *func_5(const int32_t *p_6, uint8_t p_7) {
  int64_t l_21 = 0L;
  uint64_t l_39 = 0x404D4644688D239BLL;
  int32_t *l_64 = &g_2[0][3];
  for (p_7 = 0; (p_7 <= 3); p_7 += 1) {
    int32_t *l_20[3][4];
    uint64_t l_22 = 0xCAAD901516EA3DE8LL;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 4; j++)
        l_20[i][j] = &g_19;
    }
    l_21 = p_7;
    for (l_21 = 3; (l_21 >= 0); l_21 -= 1) {
      int i;
      g_17[p_7] = 0xB.C00EADp-49;
      if (l_22)
        break;
    }
  }
  for (l_21 = (-3); (l_21 > 26); l_21 = safe_add_func_int8_t_s_s(l_21, 1)) {
    int16_t *l_37 = &g_38;
    const int32_t l_40 = (-10L);
    uint16_t *l_41 = &g_42[0];
    if ((g_2[0][3] >=
         (safe_sub_func_int16_t_s_s(
             ((safe_add_func_float_f_f(
                  (((*l_41) = (safe_sub_func_int32_t_s_s(
                        ((((safe_div_func_uint32_t_u_u(
                               (safe_rshift_func_int16_t_s_u(
                                   ((*l_37) = (safe_lshift_func_int8_t_s_s(
                                        (-3L), 1))),
                                   12)),
                               l_39)) < 0xBC712BADL) >= p_7),
                         l_40),
                        l_21))),
                   (-0x1.6p+1)),
                  p_7)),
              0x122AL),
             l_21)))) {
      int16_t l_48 = 0x1191L;
      int32_t *l_51 = &g_19;
      (*l_51) = (safe_mod_func_uint16_t_u_u(
          (safe_mod_func_uint32_t_u_u(
              ((~l_39),
               ((l_48 ^ (safe_sub_func_int8_t_s_s(g_2[0][3], 0x16L))), g_19)),
              p_7)),
          (-1L)));
      return &g_2[0][3];
    } else {
      int8_t l_56[3][3] = {
          {(-1L), (-1L), 0L}, {(-1L), (-1L), 0L}, {(-1L), (-1L), 0L}};
      int64_t *l_57 = &g_58;
      int64_t *l_59 = &g_60;
      int32_t *l_61 = &g_19;
      int i, j;
      (*l_61) &=
          (((*l_59) = ((*l_57) = (safe_mod_func_uint16_t_u_u(
                           ((g_42[3] & (safe_sub_func_int8_t_s_s(
                                           l_56[1][2], ((1UL > 0L) || p_7)))) &
                            1L),
                           p_7)))) ^
           0x9A830F13E0CA2CDFLL);
      (*l_61) = (safe_lshift_func_uint16_t_u_s(
          ((((*l_61) == 0xD024BFCCL), g_19) < (*l_61)), 15));
    }
  }
  return l_64;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_17[i];
  }
  csmith_sink_ = g_19;
  csmith_sink_ = g_38;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_42[i];
  }
  csmith_sink_ = g_58;
  csmith_sink_ = g_60;
  csmith_sink_ = g_79;
  platform_main_end(0, 0);
  return 0;
}
