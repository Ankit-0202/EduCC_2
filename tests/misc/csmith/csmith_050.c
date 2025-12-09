// Options:   --seed 100050 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_050.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const volatile int32_t f0;
};

static volatile int32_t g_2[2] = {0x5E7A66FEL, 0x5E7A66FEL};
static int32_t g_3 = 0x13DCE9D0L;
static uint8_t g_16 = 0xA9L;
static uint32_t g_18[3][2] = {{0x0CBEB969L, 0x0CBEB969L},
                              {0x0CBEB969L, 0x0CBEB969L},
                              {0x0CBEB969L, 0x0CBEB969L}};
static uint32_t g_19[4] = {0x7EA0D018L, 0x7EA0D018L, 0x7EA0D018L, 0x7EA0D018L};
static int32_t g_32 = 0xEF57A557L;
static int32_t *const volatile g_45 = &g_32;
static int32_t *g_48[3][2] = {
    {(void *)0, (void *)0}, {(void *)0, (void *)0}, {(void *)0, (void *)0}};
static int32_t **volatile g_47 = &g_48[0][1];
static struct S0 g_71 = {0L};
static uint8_t g_82 = 0UL;
static struct S0 g_84 = {0x408B304FL};

static struct S0 func_1(void);
static int32_t func_6(const int32_t p_7, uint32_t p_8, uint32_t p_9);

static struct S0 func_1(void) {
  const uint8_t l_12 = 0x70L;
  int32_t l_57[1][3];
  int32_t *l_58 = &l_57[0][0];
  int16_t l_80[4] = {0xD1CEL, 0xD1CEL, 0xD1CEL, 0xD1CEL};
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_57[i][j] = 5L;
  }
  for (g_3 = (-11); (g_3 != (-8)); g_3 = safe_add_func_uint64_t_u_u(g_3, 1)) {
    uint8_t *l_15 = &g_16;
    uint32_t *l_17 = &g_18[2][0];
    uint64_t l_20 = 0x039D6B9C2D621EC2LL;
    uint32_t l_62 = 0xAC39FBD0L;
    if (func_6((safe_rshift_func_int16_t_s_u(
                   ((l_12 & 0x3D4E677BL) >
                    (g_19[3] = ((*l_17) = (safe_rshift_func_uint8_t_u_s(
                                    ((*l_15) = l_12), l_12))))),
                   l_20)),
               l_12, g_2[0])) {
      if ((*g_45))
        break;
    } else {
      uint64_t l_49 = 0xDB47DC46221EB1EDLL;
      int32_t *l_61 = (void *)0;
      if (l_49) {
        int32_t **l_50 = &g_48[2][0];
        uint32_t l_55 = 0x6E89BE30L;
        int32_t *l_56[2];
        int i;
        for (i = 0; i < 2; i++)
          l_56[i] = &g_32;
        (*l_50) = (void *)0;
        l_57[0][1] ^=
            ((-1L) ^
             ((((*l_17) = (safe_add_func_uint16_t_u_u(
                    ((safe_mul_func_int16_t_s_s(
                         (0xDF47L != ((0x5DD727AB81002A95LL > l_55) <= (-9L))),
                         0x35CAL)) > g_18[2][0]),
                    g_2[0]))),
               0x80CDL) == l_55));
      } else {
        int32_t **l_59 = (void *)0;
        int32_t **l_60[4][1] = {
            {&g_48[2][1]}, {&g_48[2][1]}, {&g_48[2][1]}, {&g_48[2][1]}};
        int i, j;
        l_61 = l_58;
      }
    }
    (*l_58) = l_62;
  }
  for (g_16 = 0; (g_16 != 54); g_16 = safe_add_func_int32_t_s_s(g_16, 9)) {
    const uint16_t l_65 = 0xF616L;
    int32_t **l_85 = &g_48[1][0];
    if (l_65) {
      int8_t l_68 = 0L;
      (*l_58) = (l_68 |= (safe_lshift_func_uint16_t_u_s((*l_58), 6)));
      for (g_3 = (-27); (g_3 > 13); g_3++) {
        return g_71;
      }
    } else {
      int64_t l_83 = 0xA01C31E92403636CLL;
      for (g_32 = 0; (g_32 >= 28); g_32 = safe_add_func_uint32_t_u_u(g_32, 1)) {
        uint8_t *l_81 = &g_82;
        (*l_58) =
            ((((safe_lshift_func_int16_t_s_s(
                   (safe_rshift_func_uint16_t_u_s((*l_58), 11)), 12)) <=
               ((safe_mul_func_uint8_t_u_u(
                    ((*l_81) =
                         (l_80[1], ((((((void *)0 != &g_48[0][1]) < g_2[0]) &&
                                      g_71.f0) == g_18[1][0]) >= 2UL))),
                    g_19[3])) &
                l_65)) ||
              l_65) >= l_83);
      }
      return g_84;
    }
    (*l_85) = (*g_47);
  }
  return g_71;
}

static int32_t func_6(const int32_t p_7, uint32_t p_8, uint32_t p_9) {
  uint16_t l_27 = 0x9CEAL;
  uint8_t *l_40[4][1];
  int32_t l_41[1][3];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++)
      l_40[i][j] = (void *)0;
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_41[i][j] = 1L;
  }
lbl_46:
  if ((safe_mod_func_int32_t_s_s(
          0x4902314AL,
          (safe_add_func_uint32_t_u_u(
              (((safe_add_func_int64_t_s_s(((g_2[0] & l_27) == l_27), p_7)),
                g_18[2][0]) ^
               p_8),
              p_7))))) {
    int16_t l_28 = 0x9F89L;
    int32_t *l_31[3];
    int i;
    for (i = 0; i < 3; i++)
      l_31[i] = &g_32;
    g_2[1] =
        ((((l_28 !=
            ((l_28, (((safe_rshift_func_int8_t_s_u((-2L), l_28)) > g_2[0]) &&
                     g_18[2][0])),
             l_28)) >= g_18[0][0]) &
          p_8) > 0xC8A0C090L);
    if (p_7)
      goto lbl_46;
  } else {
    uint32_t *l_37 = &g_18[2][0];
    int32_t *l_44 = (void *)0;
    (*g_45) = (safe_mul_func_int8_t_s_s(
        (((l_41[0][2] = ((++(*l_37)) <= ((void *)0 == l_40[0][0]))) ||
          (safe_rshift_func_uint16_t_u_u(((void *)0 != &l_41[0][2]),
                                         g_19[1]))) ||
         g_2[0]),
        g_19[2]));
  }
  (*g_47) = &g_32;
  return p_7;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_16;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_18[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_19[i];
  }
  csmith_sink_ = g_32;
  csmith_sink_ = g_71.f0;
  csmith_sink_ = g_82;
  csmith_sink_ = g_84.f0;
  platform_main_end(0, 0);
  return 0;
}
