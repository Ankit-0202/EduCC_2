// Options:   --seed 200160 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_160.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int16_t f0;
};

struct S2 {
  struct S0 f0;
};

struct S3 {
  struct S2 f0;
  uint64_t f1;
};

static int32_t g_16 = 0x40271DBCL;
static int32_t *volatile g_30 = &g_16;
static uint16_t g_36 = 2UL;
static float g_56 = 0x3.C348FBp-72;
static float *volatile g_55 = &g_56;

static int8_t func_1(void);
static float func_3(struct S3 p_4, int32_t p_5, int64_t p_6);

static int8_t func_1(void) {
  struct S3 l_7[4][4] = {{{{{-8L}}, 0x1BC383C67EE39F3FLL},
                          {{{-1L}}, 0UL},
                          {{{-1L}}, 0UL},
                          {{{-8L}}, 0x1BC383C67EE39F3FLL}},
                         {{{{-1L}}, 0UL},
                          {{{-8L}}, 0x1BC383C67EE39F3FLL},
                          {{{0x64FDL}}, 0xE2A8D3A18E418A52LL},
                          {{{0xC810L}}, 1UL}},
                         {{{{-1L}}, 0UL},
                          {{{0x64FDL}}, 0xE2A8D3A18E418A52LL},
                          {{{-1L}}, 0UL},
                          {{{-1L}}, 18446744073709551610UL}},
                         {{{{-8L}}, 0x1BC383C67EE39F3FLL},
                          {{{0xC810L}}, 1UL},
                          {{{-1L}}, 18446744073709551610UL},
                          {{{-1L}}, 18446744073709551610UL}}};
  uint64_t l_17 = 0x7F4A1D2DAFFA898CLL;
  int i, j;
  (*g_55) = (-func_3(
      l_7[3][1],
      (((1UL ==
         (safe_rshift_func_uint8_t_u_s(
             (((safe_lshift_func_uint16_t_u_u(
                   (((safe_div_func_int8_t_s_s(
                         ((safe_add_func_int64_t_s_s(l_7[3][1].f1, g_16)) &&
                          1UL),
                         0x8CL)) ^
                     l_7[3][1].f0.f0.f0) < l_7[3][1].f1),
                   l_7[3][1].f0.f0.f0)) <= g_16) |
              l_17),
             l_17))) <= g_16) ^
       18446744073709551608UL),
      g_16));
  return g_16;
}

static float func_3(struct S3 p_4, int32_t p_5, int64_t p_6) {
  int64_t l_29 = (-5L);
  int32_t *l_34[2];
  struct S2 l_47 = {{-5L}};
  int i;
  for (i = 0; i < 2; i++)
    l_34[i] = &g_16;
  for (p_4.f1 = (-27); (p_4.f1 <= 48); ++p_4.f1) {
    int16_t l_28 = (-9L);
    if ((safe_mul_func_uint8_t_u_u(
            ((safe_mul_func_uint16_t_u_u(
                 (g_16 <=
                  ((safe_mul_func_uint16_t_u_u(
                       (((safe_div_func_int16_t_s_s(p_4.f1, 0xBC01L)), l_28) ||
                        l_29),
                       2UL)),
                   g_16)),
                 p_6)) <= 0x954EB856L),
            p_4.f0.f0.f0))) {
      (*g_30) |= l_28;
    } else {
      uint16_t *l_35 = &g_36;
      (*g_30) = (((p_6 != (+(safe_rshift_func_uint16_t_u_s(
                              ((*l_35) = (&g_16 == l_34[0])), p_4.f1)))),
                  18446744073709551610UL) ^
                 p_6);
    }
    if ((safe_sub_func_int64_t_s_s(
            ((safe_mod_func_int32_t_s_s((p_5 ^ g_36), 0x15CD4DCDL)) > g_16),
            p_4.f1))) {
      return g_16;
    } else {
      float l_48 = 0xA.237FF9p-59;
      int32_t l_49 = 0L;
      int32_t l_54 = 0x47D66A43L;
      l_49 ^=
          (p_5 |
           ((safe_sub_func_int32_t_s_s(
                ((safe_add_func_uint64_t_u_u(
                     (safe_sub_func_uint8_t_u_u(
                         (1UL == ((l_47, 18446744073709551610UL) || p_4.f1)),
                         g_16)),
                     (-7L))) != p_5),
                4294967293UL)) ||
            6UL));
      l_54 |= ((safe_mul_func_int8_t_s_s(
                   (safe_lshift_func_uint16_t_u_u(
                       (p_6 >= (l_49 < ((p_4.f0, 0x29ADL) | g_36))), 15)),
                   g_16)) > g_36);
    }
  }
  return p_6;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_16;
  csmith_sink_ = g_36;
  csmith_sink_ = g_56;
  platform_main_end(0, 0);
  return 0;
}
