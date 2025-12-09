// Options:   --seed 300215 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_215.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
  int64_t f1;
};

struct S1 {
  uint16_t f0;
};

union U3 {
  uint32_t f0;
};

union U4 {
  int16_t f0;
};

union U5 {
  volatile uint8_t f0;
  struct S0 f1;
};

static volatile int32_t g_5 = 0xA98815CBL;
static const uint64_t g_10 = 0x393DDA37BB00868BLL;
static int32_t g_14 = (-1L);
static volatile int32_t g_16 = 0x5DEA311CL;
static int8_t g_17 = 0x6AL;
static volatile int32_t g_18 = 0xA2F617A9L;
static volatile int64_t g_19 = 0x58A922A19820B275LL;
static volatile int64_t g_20 = 0xFEDAACDA2A4F2A6CLL;
static volatile uint8_t g_48 = 0x43L;
static int32_t *g_52 = &g_14;
static int32_t **volatile g_51 = &g_52;
static volatile struct S0 g_63 = {0L, 0x4EE0C605F77832D1LL};
static int32_t **volatile g_67 = &g_52;
static uint8_t g_68[3][3] = {
    {0x7EL, 0x7EL, 0x7EL}, {0x47L, 0x47L, 0x47L}, {0x7EL, 0x7EL, 0x7EL}};
static volatile uint8_t g_69 = 0xBDL;
static const union U5 g_77 = {1UL};
static union U4 g_84 = {0x40E3L};
static union U3 g_90[1][3] = {{{0xCD1CB452L}, {0xCD1CB452L}, {0xCD1CB452L}}};
static volatile union U5 *volatile g_91[3][2] = {
    {(void *)0, (void *)0}, {(void *)0, (void *)0}, {(void *)0, (void *)0}};
static uint8_t g_101 = 0xBFL;

static union U4 func_1(void);
static int32_t *func_24(union U4 p_25);
static union U4 func_26(int32_t *p_27, int64_t p_28, int32_t *p_29,
                        uint8_t p_30);

static union U4 func_1(void) {
  uint16_t l_2 = 0xE932L;
  int32_t l_15 = 0x8C537847L;
  uint16_t l_21[1];
  uint8_t l_89 = 0x37L;
  struct S1 l_93[1][2] = {{{65528UL}, {65528UL}}};
  union U4 l_102 = {1L};
  int i, j;
  for (i = 0; i < 1; i++)
    l_21[i] = 2UL;
  if (((l_2 == (safe_add_func_uint16_t_u_u(
                   g_5, (safe_div_func_uint32_t_u_u(
                            ((safe_lshift_func_int8_t_s_u(g_10, 4)) != g_10),
                            g_10))))) &&
       g_10)) {
    int32_t *l_31[2][2];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_31[i][j] = &l_15;
    }
    for (l_2 = (-2); (l_2 < 2); ++l_2) {
      int32_t *l_13[1];
      int i;
      for (i = 0; i < 1; i++)
        l_13[i] = &g_14;
      l_21[0]++;
      (*g_67) = func_24(
          func_26(l_31[1][0],
                  (((g_14 || (safe_div_func_uint32_t_u_u(g_18, 0xAFB1CAD2L))) &&
                    g_20) > 0x3EL),
                  l_31[0][0], g_10));
    }
    if ((g_68[0][2] &= (**g_51))) {
      uint32_t l_76 = 0xDBBA4700L;
      int32_t *l_78[2][1];
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_78[i][j] = &g_14;
      }
      --g_69;
      (*g_52) = (safe_add_func_int32_t_s_s(
          ((l_76 > ((g_77, l_78[1][0]) == l_31[0][0])) ^ 1UL), 0UL));
    } else {
      int32_t **l_81 = &l_31[1][0];
      (*g_52) = (safe_rshift_func_int8_t_s_s(l_21[0], 5));
      (*l_81) = (*g_51);
    }
  } else {
    for (g_17 = 0; (g_17 > 5); ++g_17) {
      return g_84;
    }
  }
  if ((safe_mul_func_uint8_t_u_u(
          (safe_mul_func_uint8_t_u_u(
              l_89, (((g_90[0][1], (g_63, (void *)0)) != &l_15) != l_89))),
          l_21[0]))) {
    union U3 l_92 = {0xAF2BE463L};
    struct S1 *l_94 = &l_93[0][1];
    g_91[1][0] = (void *)0;
    (*l_94) = (l_92, l_93[0][1]);
  } else {
    uint32_t l_99 = 0x492C6236L;
    uint16_t *l_100 = (void *)0;
    (*g_52) |=
        (l_93[0][1],
         (g_90[0][2],
          (safe_div_func_uint16_t_u_u(
              ((g_101 = (safe_rshift_func_int8_t_s_u(l_99, 7))) <= 0x8696L),
              1UL))));
  }
  return l_102;
}

static int32_t *func_24(union U4 p_25) {
  int32_t *l_39 = (void *)0;
  int32_t l_47 = 2L;
  int64_t l_60 = 0L;
  volatile struct S0 l_64 = {0x2D6FA87DL, 0x7FB053AAA0C7D0B6LL};
  int32_t *l_65[3];
  int32_t *l_66 = &l_47;
  int i;
  for (i = 0; i < 3; i++)
    l_65[i] = &l_47;
  if (((void *)0 == l_39)) {
    int32_t *l_42 = &g_14;
    int64_t l_43 = 6L;
    int32_t l_45 = 0xA9320AF4L;
    int32_t l_46[2][1];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_46[i][j] = 0x87147D86L;
    }
    if ((((safe_rshift_func_int16_t_s_s((-8L), 4)) !=
          ((g_10 && (l_42 != l_39)) | (*l_42))) &&
         l_43)) {
      int32_t *l_44[1][3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_44[i][j] = (void *)0;
      }
      g_48++;
      (*g_51) = &g_14;
    } else {
      int32_t *l_53 = &l_45;
      return (*g_51);
    }
    return (*g_51);
  } else {
    int32_t **l_58 = (void *)0;
    int32_t **l_59 = &l_39;
    (**g_51) = (safe_add_func_int32_t_s_s((**g_51), (*g_52)));
    l_60 |=
        (safe_mod_func_uint8_t_u_u((((p_25, p_25.f0) && g_16) >= l_47), 0xF8L));
  }
  for (l_60 = 0; (l_60 <= (-6)); l_60 = safe_sub_func_int64_t_s_s(l_60, 7)) {
    l_64 = g_63;
  }
  return (*g_51);
}

static union U4 func_26(int32_t *p_27, int64_t p_28, int32_t *p_29,
                        uint8_t p_30) {
  union U4 l_38 = {0x53BDL};
  for (g_14 = 0; (g_14 < (-1)); g_14 = safe_sub_func_int32_t_s_s(g_14, 6)) {
    for (g_17 = 0; (g_17 < (-8)); g_17--) {
      (*p_29) = (*p_29);
    }
  }
  return l_38;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_10;
  csmith_sink_ = g_14;
  csmith_sink_ = g_16;
  csmith_sink_ = g_17;
  csmith_sink_ = g_18;
  csmith_sink_ = g_19;
  csmith_sink_ = g_20;
  csmith_sink_ = g_48;
  csmith_sink_ = g_63.f0;
  csmith_sink_ = g_63.f1;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_68[i][j];
    }
  }
  csmith_sink_ = g_69;
  csmith_sink_ = g_77.f0;
  csmith_sink_ = g_84.f0;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  csmith_sink_ = g_101;
  platform_main_end(0, 0);
  return 0;
}
