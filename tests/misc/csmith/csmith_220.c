// Options:   --seed 300220 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_220.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int64_t f0;
};

struct S3 {
  volatile uint32_t f0;
  int32_t f1;
};

static volatile int32_t g_2 = (-4L);
static int32_t g_3 = 0L;
static struct S1 g_18 = {7L};
static int32_t g_22[3][1] = {{(-2L)}, {(-2L)}, {(-2L)}};
static int32_t *volatile g_21[3][1] = {
    {&g_22[0][0]}, {&g_22[0][0]}, {&g_22[0][0]}};
static int32_t *const volatile g_23[2][1] = {{&g_22[0][0]}, {&g_22[0][0]}};
static int32_t *volatile g_24 = (void *)0;
static int32_t *volatile g_25[1][2] = {{&g_22[0][0], &g_22[0][0]}};
static int32_t g_40 = (-6L);
static const struct S3 g_45[1] = {{0x63F3734BL, 9L}};
static struct S3 g_47 = {0xB405B751L, 0xDB06862EL};
static struct S3 *volatile g_46 = &g_47;
static int16_t g_53[3] = {8L, 8L, 8L};

static uint32_t func_1(void);
static int8_t func_11(int32_t p_12, uint32_t p_13, struct S1 p_14,
                      struct S1 p_15);
static const struct S3 func_28(uint16_t p_29, uint32_t p_30);

static uint32_t func_1(void) {
  int64_t l_10 = 1L;
  int32_t l_17 = 0x16542076L;
  struct S1 l_19 = {0L};
  int64_t *l_55[1];
  int16_t *l_56 = (void *)0;
  int16_t *l_57 = &g_53[2];
  int32_t *l_59[2][1];
  int32_t **l_58 = &l_59[1][0];
  int32_t ***l_60 = (void *)0;
  int32_t ***l_61 = &l_58;
  struct S3 *l_63 = &g_47;
  struct S3 **l_62 = &l_63;
  int i, j;
  for (i = 0; i < 1; i++)
    l_55[i] = &g_18.f0;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_59[i][j] = &l_17;
  }
  for (g_3 = (-10); (g_3 == (-23)); g_3 = safe_sub_func_uint8_t_u_u(g_3, 9)) {
    uint32_t l_16[2];
    int32_t *const l_35[1] = {(void *)0};
    int i;
    for (i = 0; i < 2; i++)
      l_16[i] = 7UL;
    if ((safe_mul_func_uint8_t_u_u(
            (((safe_add_func_int64_t_s_s((l_10 |= 0x5653D42374B1B055LL), g_3)) <
              func_11(l_16[0], l_17, g_18, l_19)) < g_22[0][0]),
            0x2AL))) {
      int32_t *l_31[2];
      int32_t **l_32 = &l_31[1];
      int32_t *l_34 = &g_22[0][0];
      int32_t **l_33 = &l_34;
      int i;
      for (i = 0; i < 2; i++)
        l_31[i] = &g_3;
      (*g_46) =
          func_28(((((*l_33) = ((*l_32) = l_31[0])) != l_35[0]) ==
                   (safe_mod_func_int32_t_s_s(
                       (safe_rshift_func_uint8_t_u_u(g_18.f0, 4)), l_10))),
                  g_40);
      if (l_10)
        break;
    } else {
      int16_t *l_52[2];
      int64_t *l_54 = &l_10;
      int i;
      for (i = 0; i < 2; i++)
        l_52[i] = (void *)0;
      l_17 = (((safe_sub_func_int8_t_s_s(
                   0xBDL, ((g_53[1] |= ((((safe_lshift_func_uint16_t_u_s(
                                              65529UL, 11)) == g_47.f0),
                                         (void *)0) == (void *)0)) != (-6L)))) &
               0UL) > g_47.f1);
      g_47.f1 &= ((((*l_54) = g_22[0][0]) <=
                   ((g_22[2][0] <= ((l_55[0] != (void *)0) ^ 0L)) != g_2)) ||
                  0xCAL);
    }
  }
  if (((g_18.f0 = (((*l_57) = g_53[1]) &&
                   (((*l_61) = l_58) == ((((*l_62) = (void *)0) == &g_47),
                                         &g_23[1][0])))) < g_22[0][0])) {
    const uint32_t l_71 = 4294967295UL;
    for (l_19.f0 = 0; (l_19.f0 >= 0); l_19.f0 -= 1) {
      (***l_61) |= 9L;
      g_25[0][1] = (void *)0;
    }
    for (g_3 = 0; (g_3 <= 2); g_3 += 1) {
      (**l_58) ^= (safe_sub_func_int32_t_s_s(
          (safe_sub_func_int8_t_s_s(
              (safe_mul_func_uint8_t_u_u(g_47.f1, g_22[0][0])),
              (0x85807939L > 4294967291UL))),
          0xA5A418E4L));
      (**l_58) = (!l_71);
    }
  } else {
    struct S1 *l_73 = &g_18;
    struct S1 **l_72 = &l_73;
    (*l_72) = &g_18;
  }
  return g_47.f1;
}

static int8_t func_11(int32_t p_12, uint32_t p_13, struct S1 p_14,
                      struct S1 p_15) {
  const uint32_t l_20 = 18446744073709551615UL;
  int32_t *l_26[2][1];
  uint32_t l_27 = 0xEAE21516L;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_26[i][j] = &g_22[2][0];
  }
  l_27 = l_20;
  return g_18.f0;
}

static const struct S3 func_28(uint16_t p_29, uint32_t p_30) {
  int32_t *l_43 = &g_40;
  int32_t **l_42[2][3];
  int32_t ***l_41 = &l_42[1][1];
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++)
      l_42[i][j] = &l_43;
  }
  for (g_40 = 0; (g_40 <= 0); g_40 += 1) {
    int32_t ***l_44 = &l_42[1][1];
    l_44 = l_41;
    for (p_30 = 0; (p_30 <= 0); p_30 += 1) {
      int i, j;
      g_25[g_40][(g_40 + 1)] = g_25[g_40][(g_40 + 1)];
    }
  }
  return g_45[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_18.f0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_22[i][j];
    }
  }
  csmith_sink_ = g_40;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_47.f0;
  csmith_sink_ = g_47.f1;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_53[i];
  }
  platform_main_end(0, 0);
  return 0;
}
