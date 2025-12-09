// Options:   --seed 300218 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_218.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int16_t f0;
  int8_t f1;
};

static int32_t g_2 = (-4L);
static struct S0 g_11 = {5L, 8L};
static volatile uint16_t g_31 = 1UL;
static int32_t g_42 = 0x2D16CF05L;
static int64_t g_44 = 4L;
static int64_t g_45 = 0x97D63F7CEC7E9A03LL;
static int32_t g_55 = (-5L);
static int32_t *g_68 = &g_42;
static int32_t **volatile g_67 = &g_68;

static int32_t func_1(void);
static uint8_t func_6(int32_t p_7, struct S0 p_8);
static uint64_t func_20(int32_t p_21);

static int32_t func_1(void) {
  uint32_t l_5 = 1UL;
  for (g_2 = 4; (g_2 == (-11)); g_2 = safe_sub_func_uint64_t_u_u(g_2, 5)) {
    return g_2;
  }
  if (l_5) {
    int32_t *l_53 = (void *)0;
    int32_t *l_54 = &g_55;
    (*l_54) ^= (func_6((safe_lshift_func_uint16_t_u_s(65532UL, 9)), g_11), 6L);
  } else {
    int32_t *l_66 = (void *)0;
    if ((safe_add_func_int64_t_s_s(
            g_2,
            (safe_add_func_int64_t_s_s(
                ((safe_add_func_int32_t_s_s(
                     (safe_mod_func_int16_t_s_s(
                         0x5A1BL,
                         (((safe_add_func_uint16_t_u_u(
                               (((l_66 == &g_2) & 0x18344157F02CAA0ELL) > g_42),
                               g_44)) ||
                           g_11.f0),
                          0xA8D2L))),
                     0xCED0F2FEL)) < 0xD5900A0D1F898AFBLL),
                2UL))))) {
      (*g_67) = &g_2;
    } else {
      const int8_t l_69[3][2] = {{1L, 1L}, {1L, 1L}, {1L, 1L}};
      int i, j;
      (*g_68) ^= l_69[0][1];
    }
  }
  return (*g_68);
}

static uint8_t func_6(int32_t p_7, struct S0 p_8) {
  int16_t l_24 = (-10L);
  int32_t *l_34 = &g_2;
  int32_t *l_36 = &g_2;
  int8_t l_37 = (-6L);
  int64_t *l_47 = &g_44;
  if ((safe_sub_func_int32_t_s_s(
          (safe_div_func_uint16_t_u_u(
              (safe_rshift_func_uint16_t_u_u(
                  ((safe_div_func_uint16_t_u_u(
                       (func_20(((safe_div_func_int8_t_s_s(
                                     l_24, ((((l_24 <= 0xD890L) | p_7) != l_24),
                                            l_24))) == 0x434392F20920A6FFLL)) <=
                        p_8.f1),
                       65530UL)) >= p_8.f1),
                  g_2)),
              p_7)),
          p_7))) {
    int32_t **l_35[1];
    int i;
    for (i = 0; i < 1; i++)
      l_35[i] = &l_34;
    (*l_36) &= ((((((l_34 = l_34) == l_36) && ((p_7 < g_11.f1), 0xBCL)) < l_37),
                 g_11.f1) |
                0x32L);
  } else {
    uint32_t l_40 = 0xCF2BBA2DL;
    int32_t *l_41 = &g_42;
    int64_t *l_43 = &g_44;
    g_45 ^=
        (((*l_43) = ((((*l_41) ^=
                       (g_2 ^ (0x83A38C8AL <= (safe_mod_func_uint64_t_u_u(
                                                  (l_40, 0x4EE00B46F9F11119LL),
                                                  g_31))))) != p_8.f1) ||
                     0UL)),
         p_8.f0);
  }
  g_2 =
      ((~((l_47 == (((*l_36) &
                     ((~(safe_add_func_uint32_t_u_u(
                          (safe_lshift_func_int8_t_s_s((p_8.f0 ^ g_11.f0), 5)),
                          0xFD77138BL))) ||
                      g_42)),
                    &g_45)),
          p_8.f1)),
       0L);
  return g_2;
}

static uint64_t func_20(int32_t p_21) {
  int32_t *l_25 = &g_2;
  int32_t *l_26 = &g_2;
  int32_t *l_27 = (void *)0;
  int32_t *l_28 = (void *)0;
  int32_t *l_29 = &g_2;
  int32_t *l_30[2];
  int i;
  for (i = 0; i < 2; i++)
    l_30[i] = &g_2;
  g_31++;
  return (*l_25);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_11.f0;
  csmith_sink_ = g_11.f1;
  csmith_sink_ = g_31;
  csmith_sink_ = g_42;
  csmith_sink_ = g_44;
  csmith_sink_ = g_45;
  csmith_sink_ = g_55;
  platform_main_end(0, 0);
  return 0;
}
