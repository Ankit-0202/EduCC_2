// Options:   --seed 200106 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_106.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile int32_t f0;
  uint32_t f1;
};

static uint64_t g_2 = 0xBA394643CDF98A59LL;
static uint32_t g_25 = 0x4F6CBCB1L;
static int32_t g_29 = 0x3147F59EL;
static volatile union U0 g_38 = {4L};
static int8_t g_46 = 0xEBL;
static uint64_t g_47 = 4UL;
static float g_49 = 0x6.947A33p+5;
static int32_t g_51 = 0x33C66883L;
static union U0 g_52 = {0L};
static int32_t *const volatile g_54 = &g_29;

static int64_t func_1(void);
static union U0 func_13(uint32_t p_14, float p_15);

static int64_t func_1(void) {
  uint16_t l_18 = 0x3C15L;
  uint16_t l_23 = 0xDA8EL;
  uint32_t *l_24 = &g_25;
  int32_t *l_53 = (void *)0;
  ++g_2;
  (*g_54) = (safe_div_func_uint16_t_u_u(
      (safe_mod_func_int64_t_s_s(
          0xEBB0CB8CE3E63E31LL,
          (safe_rshift_func_int16_t_s_s(
              ((safe_lshift_func_uint8_t_u_s(
                   (func_13(
                        (safe_lshift_func_int16_t_s_s(
                            l_18, (safe_lshift_func_int16_t_s_u(
                                      (((*l_24) = (safe_mod_func_uint32_t_u_u(
                                            ((((0xFBL == l_18) <= l_23) !=
                                              0x6501874DL) |
                                             1L),
                                            l_18))) > 0xE815F842L),
                                      5)))),
                        l_18),
                    l_23),
                   g_52.f1)),
               g_52.f0),
              g_52.f1)))),
      l_23));
  return g_46;
}

static union U0 func_13(uint32_t p_14, float p_15) {
  uint32_t l_33 = 0UL;
  int32_t l_44 = (-7L);
  int8_t *l_45 = &g_46;
  int32_t *l_48 = &g_29;
  int32_t *l_50 = &g_51;
  for (g_25 = 0; (g_25 == 14); ++g_25) {
    int32_t *l_28 = &g_29;
    int32_t *l_30 = (void *)0;
    int32_t *l_31 = &g_29;
    int32_t *l_32[4][2] = {
        {&g_29, &g_29}, {&g_29, &g_29}, {&g_29, &g_29}, {&g_29, &g_29}};
    int i, j;
    l_33++;
  }
  (*l_50) ^=
      ((*l_48) =
           ((safe_mod_func_uint16_t_u_u(
                (g_29 ==
                 (g_38,
                  (g_47 = ((*l_45) =
                               ((safe_sub_func_int32_t_s_s(
                                    (((safe_div_func_int8_t_s_s(
                                          ((((+0x00L) & 0x11L), l_33), 0x32L),
                                          l_44)) &
                                      g_25) != 0x256CD219FA4A603DLL),
                                    l_44)) ||
                                0UL))))),
                g_29)),
            0x02AD9236L));
  return g_52;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_25;
  csmith_sink_ = g_29;
  csmith_sink_ = g_38.f0;
  csmith_sink_ = g_38.f1;
  csmith_sink_ = g_46;
  csmith_sink_ = g_47;
  csmith_sink_ = g_49;
  csmith_sink_ = g_51;
  csmith_sink_ = g_52.f0;
  csmith_sink_ = g_52.f1;
  platform_main_end(0, 0);
  return 0;
}
