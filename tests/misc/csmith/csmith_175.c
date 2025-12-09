// Options:   --seed 200175 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_175.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = (-7L);
static int8_t g_4[1][4] = {{(-8L), (-8L), (-8L), (-8L)}};
static int32_t g_14 = 0x403CA955L;
static int32_t g_18 = (-1L);
static int32_t *volatile g_17 = &g_18;
static volatile int32_t g_26 = 1L;
static uint32_t g_30 = 0x92AD5889L;
static uint8_t g_33 = 4UL;
static volatile int32_t **volatile g_36 = (void *)0;
static volatile int32_t **volatile g_37 = (void *)0;
static volatile int32_t *g_39 = &g_26;
static volatile int32_t **volatile g_38[3] = {&g_39, &g_39, &g_39};
static float g_42 = 0x6.Cp+1;
static int8_t g_51[2][1] = {{1L}, {1L}};
static volatile int16_t g_65 = 0x1912L;
static uint16_t g_109[1] = {0x1F5BL};

static float func_1(void);
static int8_t *func_8(int8_t p_9);

static float func_1(void) {
  int8_t *l_3 = &g_4[0][2];
  const int32_t l_7 = (-1L);
  int32_t l_25 = (-1L);
  int32_t l_43 = (-8L);
  int32_t l_61 = 0x701E4A26L;
  int32_t l_62 = 0L;
  float l_63 = 0x3.D7759Bp+54;
  int32_t l_64[2];
  uint64_t l_66 = 0xAAFB2D28ECC62B0ELL;
  int32_t *l_88 = &g_2;
  int64_t l_96[3];
  int i;
  for (i = 0; i < 2; i++)
    l_64[i] = 0x1A53EA2BL;
  for (i = 0; i < 3; i++)
    l_96[i] = 0x7632338F47762CD2LL;
lbl_53:
  if ((((*l_3) = g_2) ==
       ((safe_rshift_func_int16_t_s_s(g_2, 13)), ((l_7, 1UL), g_2)))) {
    int8_t **l_19 = &l_3;
    int32_t l_20 = 0xC7E318B4L;
    int8_t *l_21[4][2] = {{(void *)0, (void *)0},
                          {(void *)0, (void *)0},
                          {(void *)0, (void *)0},
                          {(void *)0, (void *)0}};
    int32_t l_27[3];
    int32_t l_28 = 0x2D225D8BL;
    int i, j;
    for (i = 0; i < 3; i++)
      l_27[i] = 1L;
    if ((((*l_19) = func_8(l_7)) != (l_20, l_21[1][0]))) {
      int32_t *l_22 = &g_14;
      int32_t *l_23 = (void *)0;
      int32_t *l_24[2][2] = {{&g_14, &g_14}, {&g_14, &g_14}};
      int8_t l_29[4];
      int i, j;
      for (i = 0; i < 4; i++)
        l_29[i] = 0x66L;
      --g_30;
      ++g_33;
    } else {
      volatile int32_t **l_40 = &g_39;
      (*l_40) = &g_26;
    }
    return g_4[0][2];
  } else {
    for (g_18 = 0; (g_18 <= 0); g_18 += 1) {
      float *l_41 = &g_42;
      int i;
      g_38[(g_18 + 1)] = g_38[(g_18 + 2)];
      (*l_41) = (g_4[0][2] != g_2);
    }
  }
  if ((l_43 != l_43)) {
    int8_t *l_50 = &g_51[1][0];
    int32_t l_59 = 0L;
    int32_t l_60[1][4] = {{0xDEE7B07EL, 0xDEE7B07EL, 0xDEE7B07EL, 0xDEE7B07EL}};
    int i, j;
    if ((safe_add_func_int8_t_s_s(
            ((*l_50) = ((*l_3) = (safe_sub_func_uint32_t_u_u(
                            0x900E2E80L,
                            (((7L && (safe_sub_func_uint8_t_u_u(l_25, 255UL))),
                              0x9DE5L) >= l_43))))),
            g_18))) {
      uint32_t l_52 = 0UL;
      return l_52;
    } else {
      int32_t *l_54 = &g_18;
      int32_t *l_55 = &g_18;
      int32_t *l_56 = &g_14;
      int32_t *l_57 = &l_25;
      int32_t *l_58[3][1];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_58[i][j] = &l_43;
      }
      if (l_7)
        goto lbl_53;
      ++l_66;
    }
    if ((g_2 || (g_4[0][2] && (safe_lshift_func_int16_t_s_u(
                                  (18446744073709551609UL | g_30), 6))))) {
      int32_t *l_75 = &g_14;
      uint8_t *l_80 = (void *)0;
      uint8_t *l_81 = &g_33;
      g_42 = ((g_26, ((safe_sub_func_float_f_f(
                          ((((safe_div_func_int8_t_s_s(
                                 6L, (((*l_75) = 0x65D05681L) | l_7))) ||
                             l_59),
                            l_59) > g_30),
                          g_4[0][2])) > g_30)) >= l_61);
      g_17 = ((((safe_lshift_func_int8_t_s_s(
                    (((*l_81) = (g_4[0][2], g_51[1][0])) & (g_4[0][0] <= g_14)),
                    4)) &
                0UL) > l_60[0][3]),
              l_75);
    } else {
      uint32_t l_91 = 2UL;
      (*g_39) = ((((((((safe_div_func_int32_t_s_s(
                           (safe_mod_func_int8_t_s_s(
                               (safe_add_func_uint32_t_u_u(
                                   g_51[1][0], (&g_33 == (void *)0))),
                               0x3FL)),
                           0xDACC5E6FL)) |
                       l_59),
                      l_88) == &g_2) >= g_51[1][0]),
                   0x992E5D78L),
                  l_64[0]) < g_2);
      (*g_39) =
          (((safe_mod_func_int64_t_s_s(
                (l_91 ==
                 (safe_mod_func_uint16_t_u_u(
                     (((safe_mod_func_int32_t_s_s(
                           (((l_62 = (l_59 & 9L)) == l_60[0][3]), 0xCD2DBF4BL),
                           (-1L))) >= g_51[0][0]) ^
                      l_96[2]),
                     0x3706L))),
                0xAEB0C8D9F5F5C486LL)) |
            g_51[1][0]) ^
           l_91);
    }
  } else {
    uint32_t *l_102 = &g_30;
    uint16_t *l_103 = (void *)0;
    int32_t l_106 = 1L;
    if ((((l_61 = ((safe_rshift_func_int16_t_s_u(0xE486L, g_14)) |
                   ((~((*l_102) = (((safe_lshift_func_int8_t_s_s(
                                        g_4[0][3], 2)) <= 0x79E170EDL) &&
                                   4294967295UL))) == 0xE805CA6D59963902LL))) ==
          0x3902L) <= 3UL)) {
      int64_t *l_107 = &l_96[1];
      uint16_t *l_108 = &g_109[0];
      (*g_39) =
          ((((*l_108) = (safe_add_func_int64_t_s_s(
                 ((*l_107) = (l_106 && ((0xCAA3BF25L < l_43), l_43))), g_2))) ^
            g_33) &
           0x67L);
      g_42 =
          ((l_64[0] == (0x8.99989Ep+95 != ((((0xE.99174Bp+4 < 0xF.D3FFD6p+93) !=
                                             g_42) < l_106) > l_106))) < l_106);
    } else {
      return g_51[1][0];
    }
  }
  return g_18;
}

static int8_t *func_8(int8_t p_9) {
  int8_t *l_12 = (void *)0;
  int32_t *l_13 = &g_14;
  int32_t *l_15 = &g_2;
  int16_t l_16 = 0x16EBL;
  (*g_17) =
      ((((((*l_15) = (safe_mod_func_uint64_t_u_u(
               (((((*l_13) = (((l_12 != &p_9), 0xAE49A2F3817D1DC6LL) && p_9)) ||
                  0L) &&
                 p_9) ^
                g_4[0][2]),
               g_4[0][3]))),
          g_4[0][2]),
         (void *)0) != &g_4[0][3]) &
       l_16);
  return l_12;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  csmith_sink_ = g_14;
  csmith_sink_ = g_18;
  csmith_sink_ = g_26;
  csmith_sink_ = g_30;
  csmith_sink_ = g_33;
  csmith_sink_ = g_42;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_51[i][j];
    }
  }
  csmith_sink_ = g_65;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_109[i];
  }
  platform_main_end(0, 0);
  return 0;
}
