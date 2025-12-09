// Options:   --seed 100079 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_079.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int8_t f0;
  int16_t f1;
  int32_t f2;
};

static int32_t g_5 = 2L;
static const volatile int8_t g_17 = 0L;
static int32_t g_18 = 0L;
static int32_t g_25 = 2L;
static struct S0 *g_28 = (void *)0;
static const struct S0 g_36 = {0L, 0x133DL, 0x965DA1F7L};
static struct S0 g_38 = {0xC6L, 7L, 0x02FF7A2DL};
static volatile uint32_t g_47 = 0xFE137C2BL;

static uint16_t func_1(void);
static int8_t func_6(int16_t p_7, uint32_t p_8, const int32_t p_9,
                     uint16_t p_10);

static uint16_t func_1(void) {
  int16_t l_16[4][2] = {{0x425FL, 0x425FL},
                        {0x425FL, 0x425FL},
                        {0x425FL, 0x425FL},
                        {0x425FL, 0x425FL}};
  int32_t *l_24 = &g_25;
  int64_t l_33 = 0xA5C124380D33B947LL;
  int i, j;
  (*l_24) = (safe_unary_minus_func_int8_t_s((safe_div_func_uint8_t_u_u(
      (g_5 = 0x7BL),
      func_6(((((safe_sub_func_uint32_t_u_u(
                    0x6544D187L, (~(safe_add_func_uint16_t_u_u(
                                     (l_16[0][0] < (-4L)), g_17))))) &&
                g_17) &&
               g_17),
              0xF048L),
             g_18, g_18, g_18)))));
  if ((safe_mul_func_uint16_t_u_u(
          (((void *)0 == g_28) &
           ((safe_mod_func_uint64_t_u_u(
                (safe_mul_func_uint16_t_u_u(
                    (((5UL & g_17) <= 0x9DCB7BE74FD57441LL) || g_5), 65535UL)),
                (-1L))) |
            0x22L)),
          l_33))) {
    struct S0 *l_37 = &g_38;
    (*l_37) =
        ((safe_add_func_int32_t_s_s(
             (0x309063446B7D869ELL || (0x41BBBBFEFA2E5769LL && (g_18 <= g_5))),
             g_5)),
         g_36);
  } else {
    int32_t *l_39 = &g_5;
    int32_t *l_40 = &g_25;
    int32_t l_41 = (-4L);
    int32_t *l_42 = &g_5;
    int32_t *l_43 = &l_41;
    int32_t *l_44 = (void *)0;
    int32_t *l_45 = (void *)0;
    int32_t *l_46 = &g_25;
    g_47--;
  }
  return (*l_24);
}

static int8_t func_6(int16_t p_7, uint32_t p_8, const int32_t p_9,
                     uint16_t p_10) {
  for (g_18 = 0; (g_18 >= 11); g_18++) {
    uint16_t l_21[3];
    struct S0 l_22[2][2] = {{{0L, 0x5EECL, 5L}, {0L, 0x5EECL, 5L}},
                            {{0L, 0x5EECL, 5L}, {0L, 0x5EECL, 5L}}};
    int i, j;
    for (i = 0; i < 3; i++)
      l_21[i] = 1UL;
    for (p_8 = 0; (p_8 <= 2); p_8 += 1) {
      struct S0 *l_23 = &l_22[0][0];
      int i;
      if (l_21[p_8])
        break;
      (*l_23) = l_22[0][0];
    }
  }
  return p_8;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_17;
  csmith_sink_ = g_18;
  csmith_sink_ = g_25;
  csmith_sink_ = g_36.f0;
  csmith_sink_ = g_36.f1;
  csmith_sink_ = g_36.f2;
  csmith_sink_ = g_38.f0;
  csmith_sink_ = g_38.f1;
  csmith_sink_ = g_38.f2;
  csmith_sink_ = g_47;
  platform_main_end(0, 0);
  return 0;
}
