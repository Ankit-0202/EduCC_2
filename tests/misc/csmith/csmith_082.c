// Options:   --seed 100082 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_082.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_7 = 0x9951EA66L;
static int16_t g_8 = 0x04F3L;
static uint16_t g_31 = 0xC254L;
static int32_t *const volatile g_35 = &g_7;
static int8_t g_51[3][3] = {
    {(-1L), (-1L), (-1L)}, {(-1L), (-1L), (-1L)}, {(-1L), (-1L), (-1L)}};
static int32_t *volatile g_52 = &g_7;
static int32_t *g_54 = &g_7;
static int32_t **volatile g_53[3] = {&g_54, &g_54, &g_54};

static const uint64_t func_1(void);
static int32_t *func_2(int32_t p_3, uint8_t p_4, uint16_t p_5);

static const uint64_t func_1(void) {
  int32_t *l_6 = &g_7;
  int32_t **l_55[4] = {&g_54, &g_54, &g_54, &g_54};
  int32_t *l_56 = &g_7;
  int16_t *l_57 = &g_8;
  int i;
  l_56 = func_2(((-3L) == ((((l_6 == (void *)0) ^ g_8), 1UL) <= (*l_6))), g_7,
                (*l_6));
  (*l_56) = (l_57 == (void *)0);
  return g_31;
}

static int32_t *func_2(int32_t p_3, uint8_t p_4, uint16_t p_5) {
  uint32_t l_9[3];
  uint8_t l_43 = 254UL;
  int32_t l_50 = 0x5D57D38CL;
  int i;
  for (i = 0; i < 3; i++)
    l_9[i] = 0x141A9C21L;
lbl_13:
  l_9[0]++;
  if (p_3) {
    int32_t *l_12[3];
    int i;
    for (i = 0; i < 3; i++)
      l_12[i] = &g_7;
    for (g_8 = 0; (g_8 <= 2); g_8 += 1) {
      int32_t *l_14 = &g_7;
      for (p_3 = 2; (p_3 >= 0); p_3 -= 1) {
        g_7 ^= (&g_7 == l_12[2]);
        if (g_7)
          goto lbl_13;
      }
      return l_14;
    }
  } else {
    uint8_t l_34 = 251UL;
    for (p_3 = 0; (p_3 > (-4)); p_3--) {
      int32_t l_29 = 0xD91F06E8L;
      uint16_t *l_30 = &g_31;
      int32_t *l_32 = (void *)0;
      int32_t *l_33 = &l_29;
      int16_t l_48[1];
      int16_t *l_49[3];
      int i;
      for (i = 0; i < 1; i++)
        l_48[i] = 0x81A7L;
      for (i = 0; i < 3; i++)
        l_49[i] = &l_48[0];
      (*g_35) = ((safe_mul_func_int8_t_s_s(
                     (((safe_rshift_func_uint16_t_u_s(
                           (safe_lshift_func_uint8_t_u_u(
                               (((safe_add_func_int32_t_s_s(
                                     ((*l_33) = (safe_sub_func_int16_t_s_s(
                                          (0x99L >= 0xC4L),
                                          ((*l_30) = (safe_sub_func_uint8_t_u_u(
                                               (l_29 ^ l_9[0]), 0x11L)))))),
                                     g_7)) ||
                                 l_34) < p_5),
                               g_7)),
                           14)) >= l_34),
                      p_3),
                     3UL)) > g_8);
      (*g_52) &=
          ((*l_33) = (safe_mod_func_uint64_t_u_u(
               (safe_mul_func_uint16_t_u_u(
                   6UL, ((g_51[0][0] &= (safe_unary_minus_func_int64_t_s(
                              ((safe_rshift_func_uint8_t_u_u(
                                   (((l_43 !=
                                      (safe_mul_func_int16_t_s_s(
                                          (l_50 = (safe_lshift_func_int16_t_s_u(
                                               0x96DAL, l_48[0]))),
                                          l_34))) |
                                     g_31),
                                    255UL),
                                   g_31)) != g_8)))) ^
                         p_4))),
               p_5)));
    }
  }
  return &g_7;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_8;
  csmith_sink_ = g_31;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_51[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
