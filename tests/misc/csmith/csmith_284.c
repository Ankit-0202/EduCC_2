// Options:   --seed 300284 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_284.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int32_t f0;
  uint8_t f1;
  const uint8_t f2;
};

static uint32_t g_9[1] = {8UL};
static struct S0 *g_11 = (void *)0;
static int32_t g_16 = 0xEF5D870AL;
static int32_t *g_18 = &g_16;
static int32_t **volatile g_17[3] = {&g_18, &g_18, &g_18};
static uint64_t g_36 = 2UL;
static int16_t g_39 = 0L;
static int16_t g_41[3] = {1L, 1L, 1L};
static int16_t g_43[3][1] = {{0x58E7L}, {0x58E7L}, {0x58E7L}};
static struct S0 **volatile g_69 = (void *)0;
static int32_t g_80[2] = {0x3C79A39DL, 0x3C79A39DL};

static uint32_t func_1(void);
static struct S0 *func_2(struct S0 *p_3, uint32_t p_4, int8_t p_5,
                         const uint16_t p_6);
static int32_t func_12(int64_t p_13, int8_t p_14);

static uint32_t func_1(void) {
  struct S0 *l_7[2][3] = {{(void *)0, (void *)0, (void *)0},
                          {(void *)0, (void *)0, (void *)0}};
  int32_t l_8 = 0x0CD50997L;
  int i, j;
  g_11 = func_2(l_7[0][1], l_8, g_9[0], l_8);
  if (func_12(l_8, g_9[0])) {
    struct S0 *l_71 = (void *)0;
    int32_t l_78 = 2L;
    for (g_16 = 0; (g_16 <= 0); g_16 += 1) {
      const int32_t *l_66[3];
      const int32_t **l_67 = (void *)0;
      const int32_t **l_68 = &l_66[1];
      struct S0 **l_70[2][2];
      int32_t *l_79 = &g_80[1];
      int i, j;
      for (i = 0; i < 3; i++)
        l_66[i] = &l_8;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
          l_70[i][j] = &l_7[0][1];
      }
      l_71 =
          func_2(g_11, g_43[2][0], (((*l_68) = l_66[1]) != (void *)0), g_41[0]);
      (*l_79) &= (safe_lshift_func_uint8_t_u_u(
          (((safe_sub_func_int16_t_s_s((0L <= 0UL), l_8)) != l_78) &
           0xEF66F2FCL),
          1));
    }
  } else {
    int32_t *l_84 = &g_80[1];
    for (g_39 = 0; (g_39 < (-29)); g_39--) {
      int32_t *l_83[2][2] = {{(void *)0, (void *)0}, {(void *)0, (void *)0}};
      int i, j;
      l_84 = l_83[0][1];
    }
  }
  return g_43[2][0];
}

static struct S0 *func_2(struct S0 *p_3, uint32_t p_4, int8_t p_5,
                         const uint16_t p_6) {
  struct S0 *l_10 = (void *)0;
  return l_10;
}

static int32_t func_12(int64_t p_13, int8_t p_14) {
  int32_t *l_15 = &g_16;
  int32_t l_37 = 0x69FF4CAAL;
  int32_t l_48 = 0x8EF544BDL;
  int32_t *l_65[2][3] = {{&l_37, &l_37, &g_16}, {&l_37, &l_37, &g_16}};
  int i, j;
  if (g_9[0]) {
    int32_t *l_19 = &g_16;
    l_19 = l_15;
  } else {
    uint32_t l_27 = 0x74EDF0EBL;
    uint64_t *l_35 = &g_36;
    int16_t *l_38 = &g_39;
    int16_t *l_40 = &g_41[1];
    int16_t *l_42 = &g_43[2][0];
    int32_t l_49 = (-3L);
    int32_t l_50 = 0x6862EAE2L;
    int32_t l_51[1];
    int i;
    for (i = 0; i < 1; i++)
      l_51[i] = (-8L);
    if ((safe_mul_func_int8_t_s_s(
            (((*l_42) ^= (safe_unary_minus_func_int16_t_s(
                  ((*l_40) =
                       ((*l_38) = (safe_sub_func_int64_t_s_s(
                            (((safe_mod_func_uint64_t_u_u(
                                  l_27,
                                  (+(safe_add_func_uint64_t_u_u(
                                      l_27,
                                      (((safe_div_func_uint64_t_u_u(
                                            ((*l_35) &=
                                             ((safe_lshift_func_uint8_t_u_s(
                                                  ((void *)0 != g_11), p_14)),
                                              g_9[0])),
                                            l_37)),
                                        g_16) < (*l_15))))))),
                              l_27) |
                             l_27),
                            0x5243B9C309AB83EBLL))))))) > l_27),
            l_27))) {
      int32_t *l_44 = &l_37;
      int32_t *l_45 = &l_37;
      int32_t *l_46 = (void *)0;
      int32_t *l_47[1];
      uint32_t l_52 = 1UL;
      int i;
      for (i = 0; i < 1; i++)
        l_47[i] = &g_16;
      l_52++;
      l_49 ^= (safe_lshift_func_int8_t_s_s(
          (safe_div_func_uint8_t_u_u(
              ((*l_44) != (safe_lshift_func_uint16_t_u_s(p_13, 4))),
              (((((((((*l_45), p_13) & p_14), p_13) > (-9L)) > p_13) > p_14) ||
                0L) |
               g_41[2]))),
          p_13));
    } else {
      uint64_t *l_61 = &g_36;
      const int32_t l_62 = (-9L);
      int32_t l_63[1];
      int32_t **l_64 = &g_18;
      int i;
      for (i = 0; i < 1; i++)
        l_63[i] = 0x1FD00955L;
      (*g_18) ^= (l_63[0] = (((p_13, l_35) == l_61) > l_62));
      (*l_64) = &l_51[0];
    }
    l_65[0][2] = &l_37;
  }
  return p_13;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_9[i];
  }
  csmith_sink_ = g_16;
  csmith_sink_ = g_36;
  csmith_sink_ = g_39;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_41[i];
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_43[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_80[i];
  }
  platform_main_end(0, 0);
  return 0;
}
