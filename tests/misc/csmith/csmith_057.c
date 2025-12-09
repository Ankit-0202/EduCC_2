// Options:   --seed 100057 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_057.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint64_t f0;
  int32_t f1;
  uint32_t f2;
};

struct S1 {
  const volatile int8_t f0;
  int16_t f1;
  int32_t f2;
};

struct S3 {
  struct S1 f0;
  uint64_t f1;
  uint16_t f2;
};

static int8_t g_9 = 0xD3L;
static const struct S1 g_11 = {0x5FL, 0x46C2L, -10L};
static uint32_t g_17 = 0x664A1160L;
static uint16_t g_24 = 0x4E2BL;
static struct S3 g_30 = {
    {0L, 0xD814L, 0xC78EF8A6L}, 0xBBFAD0D7276CC72BLL, 65528UL};
static uint8_t g_38 = 9UL;
static struct S0 g_46[2] = {{18446744073709551615UL, -1L, 0xC3231A29L},
                            {18446744073709551615UL, -1L, 0xC3231A29L}};
static struct S0 g_49 = {0x781BE2FC3C737ECELL, -5L, 0x81B93497L};
static struct S0 *volatile g_48[1] = {&g_49};
static int8_t g_66 = 0x18L;
static uint32_t g_67 = 4294967287UL;
static int32_t g_73 = 0x21EB7CCDL;
static int64_t g_75 = 0x8752EB69FE437344LL;
static volatile int32_t g_76[3][1] = {
    {0xFA13A89CL}, {0xFA13A89CL}, {0xFA13A89CL}};
static const struct S1 g_94 = {0L, 1L, -9L};

static const struct S1 func_1(void);
static struct S0 func_12(int32_t p_13, uint32_t p_14, uint8_t p_15);

static const struct S1 func_1(void) {
  uint64_t l_2 = 0x7CF2E5664DC9ED9BLL;
  uint8_t l_29 = 0xA9L;
  int64_t l_69 = 0xC8B8ECDE22F50FADLL;
  int32_t l_74[4];
  int i;
  for (i = 0; i < 4; i++)
    l_74[i] = (-1L);
  ++l_2;
  for (l_2 = (-30); (l_2 > 15); l_2++) {
    uint32_t l_10 = 3UL;
    struct S0 l_51 = {0x5D0BC5DE30EA3BBELL, 0L, 4UL};
    uint8_t *const l_53 = &l_29;
    int32_t l_77 = (-3L);
    int32_t l_78[3];
    uint8_t l_91 = 0x99L;
    int i;
    for (i = 0; i < 3; i++)
      l_78[i] = 1L;
    if ((safe_mod_func_uint8_t_u_u(g_9, l_10))) {
      return g_11;
    } else {
      uint32_t *l_16 = &g_17;
      int32_t l_22 = 0xB6A7F4EAL;
      uint16_t *l_23 = &g_24;
      struct S0 *l_47 = &g_46[0];
      struct S0 *l_50 = &g_49;
      (*l_50) =
          ((*l_47) = func_12(
               (((((*l_16)--) !=
                  (0L && (safe_mul_func_int16_t_s_s(l_22, ((*l_23)--))))) |
                 (safe_add_func_int64_t_s_s(l_2, 1UL))),
                l_29),
               l_10, l_10));
      (*l_50) = l_51;
    }
    if (((l_2, (!((((&l_29 != l_53) && 0xC5108D7EBC4D5916LL), g_46[1].f0) >
                  0xA1FBL))) <= 7L)) {
      return g_11;
    } else {
      int16_t l_58 = (-2L);
      int8_t *l_65 = &g_66;
      int32_t l_72[3][2];
      int32_t l_84[4] = {3L, 3L, 3L, 3L};
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++)
          l_72[i][j] = 5L;
      }
      if ((safe_lshift_func_int16_t_s_u(
              ((safe_sub_func_int16_t_s_s(
                   ((g_67 = ((*l_65) =
                                 (l_58 >=
                                  (safe_lshift_func_int8_t_s_s(
                                      (g_9 = (safe_mod_func_int32_t_s_s(
                                           l_58, ((safe_rshift_func_int8_t_s_s(
                                                      (l_58 != (-5L)), 7)) |
                                                  (-1L))))),
                                      3))))) == l_29),
                   l_10)) >= l_58),
              10))) {
        int32_t *l_68 = &g_49.f1;
        int32_t *l_70 = &l_51.f1;
        int32_t *l_71[3];
        int32_t l_79 = 0x1F8A7072L;
        uint16_t l_80 = 0x9849L;
        int i;
        for (i = 0; i < 3; i++)
          l_71[i] = &g_49.f1;
        --l_80;
      } else {
        int32_t *l_83 = &g_46[1].f1;
        (*l_83) &= (l_78[2] || ((l_77 != l_58) == (-9L)));
        if (l_84[3])
          break;
      }
      for (l_51.f2 = 0; (l_51.f2 != 45); l_51.f2++) {
        int32_t *l_87 = &l_74[2];
        int32_t *l_88 = &l_77;
        int32_t *l_89 = &l_74[2];
        int32_t *l_90[2];
        int i;
        for (i = 0; i < 2; i++)
          l_90[i] = &l_72[2][0];
        l_91--;
        (*l_88) = 0xBD54ED7DL;
      }
    }
  }
  return g_94;
}

static struct S0 func_12(int32_t p_13, uint32_t p_14, uint8_t p_15) {
  uint64_t l_31 = 0x7FEFB659BAAA4F69LL;
  struct S0 l_32 = {18446744073709551615UL, 0xF6658D83L, 0x7CD3E5C7L};
  uint8_t *l_37 = &g_38;
  uint16_t *l_39 = &g_24;
  uint64_t *l_43[4] = {&l_31, &l_31, &l_31, &l_31};
  int32_t *l_44[2];
  int32_t l_45 = 0x09D89C1CL;
  int i;
  for (i = 0; i < 2; i++)
    l_44[i] = &g_30.f0.f2;
  g_30.f0.f2 =
      (((((g_30, (l_31 & ((l_32, g_30.f1) <= p_14))) > 0xFEF5379AL), p_14),
        0L) < p_15);
  l_45 &=
      (((*l_39) |= (safe_add_func_uint8_t_u_u(((*l_37) = g_11.f0), l_32.f1))) ^
       ((g_30.f1 ^= (safe_rshift_func_int8_t_s_s((~p_14), l_32.f2))) != p_13));
  return g_46[1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_11.f0;
  csmith_sink_ = g_11.f1;
  csmith_sink_ = g_11.f2;
  csmith_sink_ = g_17;
  csmith_sink_ = g_24;
  csmith_sink_ = g_30.f0.f0;
  csmith_sink_ = g_30.f0.f1;
  csmith_sink_ = g_30.f0.f2;
  csmith_sink_ = g_30.f1;
  csmith_sink_ = g_30.f2;
  csmith_sink_ = g_38;
  for (i = 0; i < 2; i++) {
  }
  csmith_sink_ = g_49.f0;
  csmith_sink_ = g_49.f1;
  csmith_sink_ = g_49.f2;
  csmith_sink_ = g_66;
  csmith_sink_ = g_67;
  csmith_sink_ = g_73;
  csmith_sink_ = g_75;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_76[i][j];
    }
  }
  csmith_sink_ = g_94.f0;
  csmith_sink_ = g_94.f1;
  csmith_sink_ = g_94.f2;
  platform_main_end(0, 0);
  return 0;
}
