// Options:   --seed 300259 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_259.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
};

static uint32_t g_8[3][2] = {{4294967292UL, 4294967292UL},
                             {4294967292UL, 4294967292UL},
                             {4294967292UL, 4294967292UL}};
static uint64_t g_14 = 1UL;
static uint64_t g_19 = 18446744073709551613UL;
static uint8_t g_40 = 0x08L;
static int8_t g_42 = (-1L);
static struct S0 g_44 = {-3L};
static struct S0 *g_46 = &g_44;
static struct S0 **volatile g_45 = &g_46;
static int32_t g_54 = 4L;
static int32_t *volatile g_53 = &g_54;
static int32_t *g_56 = &g_44.f0;
static int32_t **const volatile g_55 = &g_56;
static int32_t g_58 = 0xD96456CFL;
static int32_t g_60 = 1L;

static uint32_t func_1(void);
static int16_t func_2(uint64_t p_3, int32_t p_4, struct S0 p_5, uint16_t p_6);
static const struct S0 func_10(uint64_t p_11, uint8_t p_12);

static uint32_t func_1(void) {
  int64_t l_7 = 0xC0D37AD4351CDCB3LL;
  struct S0 l_9 = {1L};
  int32_t *l_59[1][2];
  uint32_t l_61 = 2UL;
  int16_t l_63[2];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_59[i][j] = &g_60;
  }
  for (i = 0; i < 2; i++)
    l_63[i] = 0xAFD3L;
  l_61 &= (func_2(l_7, g_8[2][1], l_9, g_8[2][1]) < l_9.f0);
  for (l_61 = 0; (l_61 <= 0); l_61 += 1) {
    int16_t l_62 = 4L;
    for (g_42 = 0; (g_42 <= 0); g_42 += 1) {
      int i, j;
      l_59[l_61][l_61] = l_59[l_61][g_42];
      (*g_46) = l_9;
    }
    if (l_62)
      break;
  }
  return l_63[0];
}

static int16_t func_2(uint64_t p_3, int32_t p_4, struct S0 p_5, uint16_t p_6) {
  uint64_t *l_13 = &g_14;
  uint64_t *l_17 = (void *)0;
  uint64_t *l_18 = &g_19;
  int32_t *l_57 = &g_58;
  (*l_57) |= (func_10(((*l_18) = (--(*l_13))), g_8[1][1]), p_4);
  return g_40;
}

static const struct S0 func_10(uint64_t p_11, uint8_t p_12) {
  uint16_t l_38 = 0xAF9CL;
  uint8_t *l_39 = &g_40;
  int8_t *l_41 = &g_42;
  struct S0 *l_43[3];
  int i;
  for (i = 0; i < 3; i++)
    l_43[i] = &g_44;
  if ((safe_mod_func_uint32_t_u_u(
          (0x6950A4BAL >
           (safe_mul_func_int8_t_s_s(
               ((*l_41) =
                    ((safe_add_func_uint8_t_u_u(
                         ((((safe_lshift_func_uint16_t_u_s(
                                (safe_lshift_func_uint8_t_u_u(
                                    ((safe_lshift_func_uint8_t_u_s(
                                         p_11,
                                         ((safe_div_func_uint32_t_u_u(
                                              (((safe_add_func_uint64_t_u_u(
                                                    ((safe_rshift_func_uint8_t_u_s(
                                                         ((*l_39) |=
                                                          ((g_8[1][1] | l_38),
                                                           0xEAL)),
                                                         7)),
                                                     l_38),
                                                    p_12)) |
                                                g_14),
                                               0xB1857497L),
                                              p_11)),
                                          (-10L)))) != 0x0002L),
                                    0)),
                                l_38)) |
                            g_8[2][0]) |
                           4L) &
                          5L),
                         l_38)) != 0xC5C935CB51404FC4LL)),
               l_38))),
          g_8[2][1]))) {
    (*g_45) = l_43[1];
  } else {
    int8_t *l_49[1];
    int32_t l_51[1];
    int i;
    for (i = 0; i < 1; i++)
      l_49[i] = &g_42;
    for (i = 0; i < 1; i++)
      l_51[i] = 1L;
    for (g_14 = 26; (g_14 != 19); g_14 = safe_sub_func_int64_t_s_s(g_14, 7)) {
      const int8_t *l_50 = &g_42;
      int32_t *l_52 = &g_44.f0;
      (*g_53) = ((*l_52) &= ((((g_40 <= g_8[1][1]) >=
                               (((l_49[0] == l_50) <= 0x11CCFE983D4F39ABLL) >=
                                g_40)) >= 0xAB81D4B4L) < l_51[0]));
      if ((*g_53))
        break;
    }
    return (**g_45);
  }
  (*g_55) = &g_54;
  return (**g_45);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  csmith_sink_ = g_14;
  csmith_sink_ = g_19;
  csmith_sink_ = g_40;
  csmith_sink_ = g_42;
  csmith_sink_ = g_44.f0;
  csmith_sink_ = g_54;
  csmith_sink_ = g_58;
  csmith_sink_ = g_60;
  platform_main_end(0, 0);
  return 0;
}
