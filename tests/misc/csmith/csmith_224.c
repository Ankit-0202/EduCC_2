// Options:   --seed 300224 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_224.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int64_t g_7 = 1L;
static volatile uint16_t g_12 = 0UL;
static int32_t g_16 = 0x2A8D3A18L;
static int32_t *volatile g_36 = &g_16;
static const int32_t g_37[3][2] = {{0L, 5L}, {5L, 0L}, {5L, 5L}};
static int8_t g_64 = 5L;
static uint16_t g_66[3][1] = {{65528UL}, {65528UL}, {65528UL}};
static int64_t *volatile g_73 = &g_7;
static int64_t *volatile *volatile g_72[1] = {&g_73};
static int64_t *volatile *volatile *volatile g_74 = &g_72[0];
static int32_t *g_77 = &g_16;
static int32_t **volatile g_76 = &g_77;

static int32_t func_1(void);
static const uint8_t func_4(uint32_t p_5, int64_t p_6);
static int64_t func_8(int32_t p_9, uint8_t p_10);

static int32_t func_1(void) {
  int16_t l_11 = 0L;
  int32_t l_47 = 0L;
  if (((safe_mod_func_int16_t_s_s(
           ((func_4(g_7, func_8(l_11, g_7)) == g_37[2][0]) >= g_37[2][0]), 1L)),
       (*g_36))) {
    int32_t *l_39 = &g_16;
    int32_t **l_38 = &l_39;
    int16_t *l_46 = &l_11;
    (*l_38) = (void *)0;
    if (((safe_lshift_func_int16_t_s_u(
             ((*l_46) =
                  ((((((l_11 || (safe_rshift_func_uint8_t_u_u(
                                    (g_37[2][0] <
                                     (safe_mul_func_uint8_t_u_u(
                                         ((((*g_36) = (*g_36)) ^ g_7) | (-9L)),
                                         0xE9L))),
                                    g_37[1][0]))) == g_37[2][0]),
                      g_37[2][0]),
                     3L) < g_7) < g_37[2][0])),
             l_47)),
         l_11)) {
      int32_t l_63 = 0L;
      uint16_t *l_65 = &g_66[2][0];
      (*g_36) = (safe_mod_func_uint64_t_u_u(
          (safe_mul_func_uint16_t_u_u(
              (g_16 &&
               ((*l_65) =
                    (g_64 =
                         ((safe_rshift_func_int8_t_s_u(
                              (g_16 >=
                               ((safe_add_func_int32_t_s_s(
                                    ((safe_mul_func_uint16_t_u_u(
                                         (!(safe_add_func_int8_t_s_s(
                                             (l_47 =
                                                  (safe_lshift_func_uint8_t_u_s(
                                                      l_11, l_63))),
                                             g_12))),
                                         g_16)) != l_11),
                                    g_37[2][0])) &
                                l_11)),
                              4)) &&
                          g_37[0][0])))),
              g_37[2][0])),
          g_37[2][0]));
    } else {
      const int32_t l_71 = 7L;
      (*g_74) = ((g_37[2][0] != (((((safe_add_func_int16_t_s_s(
                                        l_11, (safe_mod_func_uint64_t_u_u(
                                                  (g_66[0][0] > l_71), 7UL)))),
                                    l_47) <= 6UL) == l_47) ||
                                 0xE1338462L)),
                 g_72[0]);
    }
  } else {
    int32_t *const l_75 = &g_16;
    (*g_76) = l_75;
  }
  return g_37[2][0];
}

static const uint8_t func_4(uint32_t p_5, int64_t p_6) {
  const int32_t l_25 = (-3L);
  int64_t *l_34 = &g_7;
  int32_t l_35 = 0L;
  (*g_36) =
      ((((safe_mod_func_int32_t_s_s(
             (safe_div_func_uint16_t_u_u(
                 (safe_sub_func_int32_t_s_s(
                     l_25,
                     ((safe_lshift_func_uint8_t_u_u(
                          (((g_7,
                             ((~(l_35 =
                                     ((safe_mul_func_uint8_t_u_u(
                                          (safe_sub_func_uint16_t_u_u(
                                              (((((safe_unary_minus_func_int64_t_s(
                                                      ((*l_34) = g_7))) ^
                                                  g_12) < 0xD23C5AD058BBE58ELL),
                                                0x3D37L) <= p_6),
                                              g_16)),
                                          0x8CL)) <= l_25))) > 3L)) > g_16) >
                           l_25),
                          0)) >= l_25))),
                 (-7L))),
             (-7L))) == l_25) != g_16) == l_25);
  return l_35;
}

static int64_t func_8(int32_t p_9, uint8_t p_10) {
  int32_t *l_15[1][2];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_15[i][j] = &g_16;
  }
  ++g_12;
  g_16 &= ((p_9 = g_7) & ((safe_lshift_func_int16_t_s_u(6L, 1)) <= g_12));
  return p_10;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_12;
  csmith_sink_ = g_16;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_37[i][j];
    }
  }
  csmith_sink_ = g_64;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_66[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
