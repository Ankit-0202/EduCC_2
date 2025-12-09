// Options:   --seed 300255 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_255.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  const uint8_t f0;
};

union U1 {
  volatile uint32_t f0;
};

static int8_t g_8 = 1L;
static int32_t g_38 = 1L;
static int32_t *volatile g_39 = &g_38;
static int32_t *g_41 = &g_38;
static int32_t **volatile g_40[1][2] = {{&g_41, &g_41}};
static union U1 g_44 = {1UL};
static const union U0 g_59[3][2] = {
    {{0x7FL}, {0x01L}}, {{0x7FL}, {0x7FL}}, {{0x01L}, {0x7FL}}};
static uint64_t g_72 = 8UL;
static int32_t *volatile g_74 = &g_38;

static int8_t func_1(void);
static int32_t func_4(uint32_t p_5, uint8_t p_6, int32_t p_7);
static uint8_t func_15(union U0 p_16, const int32_t p_17, uint8_t p_18,
                       int32_t p_19, uint32_t p_20);

static int8_t func_1(void) {
  union U0 l_21[1][3] = {{{0UL}, {0UL}, {0UL}}};
  int i, j;
  (*g_74) = ((((safe_add_func_int32_t_s_s(
                   func_4(g_8,
                          (safe_add_func_int32_t_s_s(
                              (safe_lshift_func_int8_t_s_u(
                                  ((((safe_rshift_func_uint8_t_u_s(
                                         func_15(l_21[0][2], g_8, l_21[0][2].f0,
                                                 l_21[0][2].f0, l_21[0][2].f0),
                                         g_8)),
                                     g_59[0][0]),
                                    (*g_41)) > g_59[0][0].f0),
                                  2)),
                              0xD172E30EL)),
                          g_59[0][0].f0),
                   0x8983C1E2L)) ^
               l_21[0][2].f0) <= l_21[0][2].f0),
             l_21[0][2].f0);
  return l_21[0][2].f0;
}

static int32_t func_4(uint32_t p_5, uint8_t p_6, int32_t p_7) {
  uint16_t l_66 = 0x2726L;
  for (p_5 = 0; (p_5 <= 0); p_5 += 1) {
    int32_t *l_60 = &g_38;
    int32_t *l_61 = &g_38;
    int32_t *l_62 = &g_38;
    int32_t *l_63 = &g_38;
    int32_t *l_64 = (void *)0;
    int32_t *l_65[2][2];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_65[i][j] = (void *)0;
    }
    --l_66;
    (*l_60) |= 0x71E8EE62L;
    for (p_7 = 0; (p_7 <= 0); p_7 += 1) {
      uint64_t *l_71 = &g_72;
      int32_t l_73 = 0xEE38976CL;
      l_73 = ((safe_sub_func_uint64_t_u_u(
                  ((*l_71) = g_8), (((l_66 == (g_59[0][0].f0 | g_8)) >= l_73),
                                    (-10L)))) < 254UL);
    }
  }
  return (*g_41);
}

static uint8_t func_15(union U0 p_16, const int32_t p_17, uint8_t p_18,
                       int32_t p_19, uint32_t p_20) {
  int32_t l_25 = 0xB09F5954L;
  int32_t l_58[2];
  int i;
  for (i = 0; i < 2; i++)
    l_58[i] = 0x8F874340L;
  if ((+(((0x7A8CL > (l_25 != g_8)), g_8) || l_25))) {
    if ((!(safe_div_func_uint8_t_u_u(
            (safe_mul_func_int16_t_s_s(
                (0x12E7550730467731LL ||
                 (safe_add_func_uint64_t_u_u(
                     (g_8 || (((safe_mul_func_int8_t_s_s(
                                   (safe_add_func_int32_t_s_s(
                                       (0x9C089CED66E5DC64LL && p_20), 0UL)),
                                   g_8)) >= 0xED4BL) == p_17)),
                     g_8))),
                p_20)),
            0x83L)))) {
      int32_t *l_37 = &g_38;
      (*l_37) ^= 0x402095D7L;
    } else {
      int32_t **l_42 = (void *)0;
      int32_t **l_43 = &g_41;
      (*g_39) = l_25;
      (*l_43) = &g_38;
    }
  } else {
    (*g_41) ^= p_19;
  }
  for (p_19 = 0; (p_19 >= 0); p_19 -= 1) {
    uint32_t l_55 = 0UL;
    (*g_41) |=
        (g_44,
         (safe_lshift_func_int8_t_s_u(
             p_20,
             (safe_unary_minus_func_uint32_t_u(
                 (((safe_add_func_uint8_t_u_u(255UL, p_19)) < p_20) & 3UL))))));
    for (p_18 = 0; (p_18 <= 0); p_18 += 1) {
      int32_t l_50 = 6L;
      uint32_t *l_56 = &l_55;
      uint32_t *l_57 = (void *)0;
      int i, j;
      l_50 = (g_40[p_19][p_19] == &g_41);
      (*g_41) =
          (((safe_sub_func_uint32_t_u_u(
                (l_58[1] = ((*l_56) = (g_44.f0 ^ (safe_lshift_func_int16_t_s_s(
                                                     l_55, 5))))),
                (g_8 >= p_17))) < g_8) ^
           l_50);
    }
  }
  return p_16.f0;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_38;
  csmith_sink_ = g_44.f0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_72;
  platform_main_end(0, 0);
  return 0;
}
