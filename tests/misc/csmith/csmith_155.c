// Options:   --seed 200155 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_155.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint16_t f0;
  int32_t f1;
};

union U4 {
  const int8_t *f0;
  int8_t *f1;
};

union U5 {
  int8_t *f0;
  struct S1 f1;
};

static volatile int32_t g_3 = 0x4B2AB76DL;
static int32_t g_4 = 9L;
static int8_t g_17[4][1] = {{2L}, {2L}, {2L}, {2L}};
static union U4 g_18 = {0};
static uint16_t g_23 = 0UL;
static int32_t g_25[4][4] = {{(-1L), (-1L), (-1L), (-1L)},
                             {(-1L), (-1L), (-1L), (-1L)},
                             {(-1L), (-1L), (-1L), (-1L)},
                             {(-1L), (-1L), (-1L), (-1L)}};
static int32_t *g_27 = &g_25[2][0];
static int32_t **volatile g_26[2][1] = {{&g_27}, {&g_27}};
static int32_t **volatile g_28[3] = {(void *)0, (void *)0, (void *)0};
static int32_t **volatile g_29 = (void *)0;
static int32_t **volatile g_30 = &g_27;
static int32_t *volatile g_33[4][3] = {{&g_4, &g_4, &g_25[0][1]},
                                       {(void *)0, (void *)0, &g_4},
                                       {&g_4, &g_4, &g_25[0][1]},
                                       {(void *)0, (void *)0, &g_4}};
static int32_t g_35 = 0x8185F187L;
static int32_t *volatile g_34 = &g_35;
static union U5 g_38[1][4] = {{{0}, {0}, {0}, {0}}};
static int32_t g_85 = 0x13849F51L;
static volatile struct S1 g_89 = {65534UL, -1L};
static int32_t *volatile g_97[2] = {(void *)0, (void *)0};

static uint8_t func_1(void);
static int32_t func_5(int8_t *p_6, uint32_t p_7, union U4 p_8, uint32_t p_9);

static uint8_t func_1(void) {
  int32_t l_2[4][2] = {
      {0x0BD035C5L, 0x0BD035C5L}, {1L, 1L}, {1L, 0L}, {1L, 1L}};
  int8_t *l_10[4] = {(void *)0, (void *)0, (void *)0, (void *)0};
  int8_t *l_16[4] = {(void *)0, (void *)0, (void *)0, (void *)0};
  int8_t **l_15 = &l_16[3];
  int8_t l_64 = 5L;
  int64_t l_66[1];
  int8_t l_68 = 0x0AL;
  uint16_t l_73 = 65533UL;
  int16_t l_84 = (-8L);
  int i, j;
  for (i = 0; i < 1; i++)
    l_66[i] = 0x87FAFF4B716CAE9CLL;
  for (g_4 = 1; (g_4 >= 0); g_4 -= 1) {
    int8_t **l_11 = (void *)0;
    int8_t **l_12 = &l_10[0];
    int32_t l_19 = 0x6128F3B8L;
    int32_t l_56 = 0xEA280505L;
    int32_t l_57 = (-4L);
    int32_t l_58 = 0x982AEBACL;
    int8_t l_59 = 0xF0L;
    int32_t l_61 = 3L;
    int32_t l_62 = (-10L);
    int32_t l_63 = 9L;
    int32_t l_67 = 0x5FB73896L;
    int32_t l_69 = 4L;
    int32_t l_70 = (-1L);
    int32_t l_71 = 0x20052CD3L;
    int32_t l_72 = 8L;
    uint8_t l_86 = 0x6EL;
    if (func_5(
            ((*l_12) = l_10[0]), l_2[0][1],
            ((safe_add_func_float_f_f(((void *)0 != l_15), g_17[1][0])), g_18),
            l_19)) {
      uint32_t l_31 = 1UL;
      int32_t *l_32 = (void *)0;
      (*g_30) = &g_4;
      (*g_34) &= ((l_2[3][0] = 4294967295UL) ^ (l_31 != g_25[2][0]));
    } else {
      union U5 *l_39 = &g_38[0][3];
      int32_t l_40 = 3L;
      int32_t *l_41 = &l_40;
      int32_t *l_42 = (void *)0;
      int32_t *l_43 = &g_35;
      int32_t *l_44 = &l_40;
      int32_t *l_45 = &l_2[0][1];
      int32_t *l_46 = &g_25[2][1];
      int32_t *l_47 = &g_38[0][3].f1.f1;
      int32_t *l_48 = &g_35;
      int32_t *l_49 = &l_40;
      int32_t *l_50 = (void *)0;
      int32_t *l_51 = &g_25[1][1];
      int32_t *l_52 = &g_25[2][0];
      int32_t *l_53 = &g_25[2][0];
      int32_t *l_54 = &l_2[1][0];
      int32_t *l_55[1][1];
      float l_60 = 0x4.C95D4Ep+24;
      int64_t l_65 = 0xFCA15F1EE03666D7LL;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_55[i][j] = &g_35;
      }
      g_35 &= ((safe_div_func_uint8_t_u_u(
                   (((((l_19 == ((((*l_12) = &g_17[1][0]) ==
                                  ((((*l_39) = g_38[0][3]), 0xEBCBL),
                                   &g_17[3][0])) > g_4)) <= g_25[3][1]) >
                      18446744073709551608UL) == l_40) != g_23),
                   l_2[3][0])) &
               (**g_30));
      l_73++;
    }
    for (g_35 = 0; (g_35 <= 1); g_35 += 1) {
      int32_t *l_76 = &l_56;
      int32_t *l_77 = &l_72;
      int32_t *l_78 = &l_71;
      int32_t *l_79 = (void *)0;
      int32_t *l_80 = &l_56;
      float l_81 = (-0x2.Ep-1);
      int32_t *l_82 = &g_38[0][3].f1.f1;
      int32_t *l_83[1][3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_83[i][j] = (void *)0;
      }
      ++l_86;
    }
    for (l_63 = 0; (l_63 <= 1); l_63 += 1) {
      volatile struct S1 l_90 = {65530UL, -1L};
      l_90 = g_89;
      return l_58;
    }
  }
  for (g_4 = 23; (g_4 >= 9); --g_4) {
    union U4 l_96 = {0};
    int32_t *l_98 = &g_85;
    (*l_98) ^= (((~((safe_mul_func_int8_t_s_s(
                        ((g_25[2][1], l_96), (&g_34 == &g_33[3][2])), 0x46L)) <=
                    0x8460L)) == 0xD21617112B7E6810LL) ^
                g_25[0][1]);
  }
  return g_25[2][0];
}

static int32_t func_5(int8_t *p_6, uint32_t p_7, union U4 p_8, uint32_t p_9) {
  int64_t *l_22 = (void *)0;
  int32_t *l_24 = &g_25[2][0];
  (*l_24) ^=
      (safe_sub_func_uint64_t_u_u(0xBC4AEE5077045B36LL, (g_23 &= (-1L))));
  return (*l_24);
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
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_17[i][j];
    }
  }
  csmith_sink_ = g_23;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_25[i][j];
    }
  }
  csmith_sink_ = g_35;
  csmith_sink_ = g_85;
  csmith_sink_ = g_89.f0;
  csmith_sink_ = g_89.f1;
  platform_main_end(0, 0);
  return 0;
}
