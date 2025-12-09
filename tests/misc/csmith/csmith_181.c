// Options:   --seed 200181 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_181.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  const uint32_t f0;
};

static int64_t g_7[2] = {0xCB4C23AFC3718654LL, 0xCB4C23AFC3718654LL};
static int32_t g_8 = 7L;
static volatile union U1 g_14 = {18446744073709551612UL};
static volatile union U1 *volatile g_13 = &g_14;
static int32_t g_17 = 0L;
static volatile int8_t g_33 = 0x3EL;
static uint32_t g_34 = 0UL;
static int16_t g_62 = 0x1425L;
static int32_t *volatile g_68 = &g_17;
static uint16_t g_74 = 65533UL;

static int32_t func_1(void);
static union U1 func_3(int64_t p_4, uint32_t p_5);

static int32_t func_1(void) {
  int16_t l_2 = (-1L);
  int64_t *l_6 = &g_7[0];
  uint32_t *l_9 = (void *)0;
  int32_t l_10 = 0xC7AF5AF8L;
  int32_t l_49[2];
  int8_t l_79 = 0x1FL;
  int i;
  for (i = 0; i < 2; i++)
    l_49[i] = 0L;
  if ((l_2 == (func_3(((*l_6) = l_2), (l_10 = g_8)), l_10))) {
    int32_t *l_27 = &g_17;
    int32_t *l_28 = &l_10;
    int32_t *l_29 = (void *)0;
    int32_t *l_30 = &l_10;
    int32_t *l_31 = &l_10;
    int32_t *l_32[2][3];
    union U1 l_41 = {0x65DD4D14L};
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 3; j++)
        l_32[i][j] = &l_10;
    }
    g_34++;
    for (l_2 = 0; (l_2 > (-23)); l_2 = safe_sub_func_int32_t_s_s(l_2, 8)) {
      float l_46 = 0xA.314325p+41;
      float *l_47 = &l_46;
      int32_t l_48 = 0xB974DB9BL;
      (*l_47) = (safe_sub_func_float_f_f(
          ((l_41, (safe_add_func_float_f_f(
                      (g_34 >
                       (safe_div_func_float_f_f((0x6.9p+1 == l_46), 0x1.9p-1))),
                      g_33))) < g_8),
          0x5.Bp+1));
      return l_48;
    }
  } else {
    int8_t l_52 = (-2L);
    int32_t l_53 = 0x88A746C2L;
    if ((l_49[0] || (safe_mul_func_uint8_t_u_u(g_7[0], (g_33, g_8))))) {
      uint32_t **l_60 = (void *)0;
      uint32_t *l_61 = &g_34;
      int16_t *l_63[1][1];
      int32_t l_64 = 0x05A9AD1DL;
      int32_t l_65 = 0x792F5726L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_63[i][j] = &l_2;
      }
      l_53 &= l_52;
      l_65 &= (safe_div_func_int16_t_s_s(
          (l_64 = (safe_rshift_func_int16_t_s_s(
               (g_62 &= (safe_sub_func_uint8_t_u_u(
                    l_10, ((l_49[1] > ((l_61 = &g_34) == (void *)0)) ||
                           0x54A037A762AFEDDDLL)))),
               l_49[0]))),
          g_33));
    } else {
      uint16_t *l_73[4];
      uint32_t l_75[3][3];
      int32_t l_76[3][4] = {{(-9L), 0xDDB3F0F5L, 0xDDB3F0F5L, (-9L)},
                            {0xDDB3F0F5L, (-9L), 0xDDB3F0F5L, 0xDDB3F0F5L},
                            {(-9L), (-9L), 0x25F3D189L, (-9L)}};
      int8_t *l_77 = &l_52;
      int32_t *l_78[1];
      int i, j;
      for (i = 0; i < 4; i++)
        l_73[i] = &g_74;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
          l_75[i][j] = 0x13110EA9L;
      }
      for (i = 0; i < 1; i++)
        l_78[i] = &l_53;
      (*g_68) = (safe_rshift_func_int8_t_s_u((g_34 || (l_53 || g_33)), g_8));
      l_10 |= (safe_lshift_func_uint16_t_u_s(
          (safe_sub_func_uint32_t_u_u(
              ((l_75[0][0] ^= l_2) ==
               ((((*l_77) ^= (l_49[0] = l_76[1][1])) >= g_33), 0xF7CFL)),
              0L)),
          g_7[0]));
    }
  }
  return l_79;
}

static union U1 func_3(int64_t p_4, uint32_t p_5) {
  int32_t *l_16 = &g_17;
  union U1 l_26[2] = {{5UL}, {5UL}};
  int i;
  for (p_4 = (-1); (p_4 > (-17)); --p_4) {
    volatile union U1 *volatile *l_15 = &g_13;
    (*l_15) = g_13;
    l_16 = l_16;
  }
  (*l_16) = (safe_mod_func_int32_t_s_s(
      (g_8 != (safe_rshift_func_uint16_t_u_u(
                  (safe_mod_func_uint8_t_u_u(
                      ((safe_mod_func_int32_t_s_s((2L && 0x46E33A79L),
                                                  0x99A56718L)) >= g_7[0]),
                      p_5)),
                  g_7[1]))),
      4294967291UL));
  return l_26[1];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_7[i];
  }
  csmith_sink_ = g_8;
  csmith_sink_ = g_14.f0;
  csmith_sink_ = g_17;
  csmith_sink_ = g_33;
  csmith_sink_ = g_34;
  csmith_sink_ = g_62;
  csmith_sink_ = g_74;
  platform_main_end(0, 0);
  return 0;
}
