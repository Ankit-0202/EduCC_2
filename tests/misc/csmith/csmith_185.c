// Options:   --seed 200185 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_185.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint8_t f0;
  int8_t f1;
};

struct S1 {
  uint64_t f0;
  int64_t f1;
  volatile uint32_t f2;
};

union U2 {
  uint32_t f0;
};

static uint8_t g_8[4][3] = {{255UL, 255UL, 255UL},
                            {0x7DL, 0x7DL, 0x7DL},
                            {255UL, 255UL, 255UL},
                            {0x7DL, 0x7DL, 0x7DL}};
static struct S1 g_12 = {0x6B8D96378555145CLL, -1L, 0x25245F5BL};
static uint8_t *g_18[3] = {&g_8[0][2], &g_8[0][2], &g_8[0][2]};
static uint32_t g_20 = 4UL;
static uint32_t g_22 = 0x4D4E2095L;
static uint64_t g_24 = 18446744073709551607UL;
static int32_t g_27 = 0x1AF6658DL;
static int32_t *volatile g_44 = &g_27;
static int32_t *const volatile g_50 = &g_27;
static union U2 g_56 = {7UL};
static int32_t g_64 = 1L;
static int32_t **volatile g_68 = (void *)0;

static union U2 func_1(void);
static uint64_t func_2(const float p_3, const uint8_t p_4, struct S0 p_5);

static union U2 func_1(void) {
  const uint32_t l_6[3] = {4294967286UL, 4294967286UL, 4294967286UL};
  uint8_t *l_7 = &g_8[0][1];
  struct S0 l_9 = {0xC3L, 0x5FL};
  int32_t l_65[2];
  int i;
  for (i = 0; i < 2; i++)
    l_65[i] = 0xAF72A6DDL;
  if ((0x4E6DL && (func_2(l_6[1], ((*l_7) = l_6[1]), l_9) < g_12.f1))) {
    int32_t *l_53 = &g_27;
    int32_t **l_54 = &l_53;
    (*l_54) = l_53;
    for (g_12.f0 = 0; g_12.f0 < 4; g_12.f0 += 1) {
      for (g_27 = 0; g_27 < 3; g_27 += 1) {
        g_8[g_12.f0][g_27] = 255UL;
      }
    }
  } else {
    int8_t l_55[4] = {0xD8L, 0xD8L, 0xD8L, 0xD8L};
    int32_t *l_67 = &g_27;
    int i;
    if ((l_55[3] && 0xCBL)) {
      return g_56;
    } else {
      int32_t *l_63[2][2] = {{(void *)0, (void *)0}, {(void *)0, (void *)0}};
      int32_t l_66[1][2];
      int32_t **l_69[2];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++)
          l_66[i][j] = 0xD26BC8B8L;
      }
      for (i = 0; i < 2; i++)
        l_69[i] = &l_67;
      l_66[0][0] ^=
          (l_55[2], (safe_sub_func_int32_t_s_s(
                        (((l_65[1] = (safe_add_func_int8_t_s_s(
                               (safe_add_func_uint64_t_u_u(
                                   (((l_6[1] < ((l_9, l_9.f0), (-5L))) <
                                     g_56.f0) == 0x1EE1L),
                                   (-9L))),
                               0L))),
                          g_8[0][1]) &&
                         0x5603FBD5CED4B89DLL),
                        0x6DCE64F8L)));
      g_44 = l_67;
    }
    (*l_67) ^= (safe_mod_func_uint8_t_u_u(
        ((+l_6[1]) ^ 0x4BL),
        ((safe_div_func_float_f_f((g_24 != g_12.f2), (-0x1.8p-1))), g_20)));
  }
  return g_56;
}

static uint64_t func_2(const float p_3, const uint8_t p_4, struct S0 p_5) {
  union U2 l_15 = {0x3703ACB6L};
  int32_t l_25[3][2] = {{0x20077FEFL, 0x5015E0C0L},
                        {0x20077FEFL, 0x20077FEFL},
                        {0x5015E0C0L, 0x20077FEFL}};
  int32_t l_28 = 9L;
  int16_t l_29 = 0xFEF5L;
  int32_t *l_52[4][2] = {{&l_25[2][0], &l_25[2][0]},
                         {&l_25[2][0], &l_25[2][0]},
                         {&l_25[2][0], &l_25[2][0]},
                         {&l_25[2][0], &l_25[2][0]}};
  int32_t **l_51 = &l_52[2][0];
  int i, j;
  if (((safe_div_func_uint32_t_u_u((g_12, ((void *)0 == &g_8[0][1])),
                                   0x87A5EAFBL)) >= 0x1CB6L)) {
    uint8_t *l_17[3];
    int i;
    for (i = 0; i < 3; i++)
      l_17[i] = &g_8[0][1];
    for (g_12.f0 = 12; (g_12.f0 <= 59); ++g_12.f0) {
      union U2 *l_16 = &l_15;
      uint32_t *l_19 = &g_20;
      uint32_t *l_21 = &g_22;
      uint64_t *l_23 = &g_24;
      int32_t *l_26[4] = {&g_27, &g_27, &g_27, &g_27};
      int i;
      g_27 ^= (l_28 ^=
               (((*l_23) =
                     (((((*l_16) = l_15), 4294967295UL) <=
                       ((*l_21) = ((*l_19) &= ((((g_18[0] = l_17[2]) == &p_4) ==
                                                g_8[3][0]) == p_5.f1)))) &
                      p_5.f0)) >= l_25[0][1]));
    }
  } else {
    uint16_t l_38 = 9UL;
    int16_t l_47[1][1];
    int32_t *l_48 = &l_25[0][1];
    int32_t *l_49 = &l_28;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_47[i][j] = 0xF010L;
    }
    if ((l_29 & 0x9AL)) {
      const uint32_t l_41 = 1UL;
      int32_t *l_42 = &l_25[0][1];
      (*l_42) |= (((safe_sub_func_int16_t_s_s(
                       (safe_mul_func_uint8_t_u_u(
                           (safe_div_func_int32_t_s_s(
                               (((safe_mul_func_uint8_t_u_u(
                                     l_38, (18446744073709551613UL !=
                                            (safe_rshift_func_int16_t_s_s(
                                                l_38, g_12.f2))))) != l_28) &&
                                0x99C826FFL),
                               4294967294UL)),
                           l_41)),
                       p_5.f1)) >= g_27) < g_22);
      (*l_42) &= p_5.f1;
    } else {
      (*g_44) = (~1L);
    }
    (*g_50) =
        ((*l_49) |= ((*l_48) = (safe_mul_func_int8_t_s_s(1L, l_47[0][0]))));
  }
  (*l_51) = &g_27;
  return p_5.f0;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  csmith_sink_ = g_12.f0;
  csmith_sink_ = g_12.f1;
  csmith_sink_ = g_12.f2;
  csmith_sink_ = g_20;
  csmith_sink_ = g_22;
  csmith_sink_ = g_24;
  csmith_sink_ = g_27;
  csmith_sink_ = g_56.f0;
  csmith_sink_ = g_64;
  platform_main_end(0, 0);
  return 0;
}
