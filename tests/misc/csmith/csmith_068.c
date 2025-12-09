// Options:   --seed 100068 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_068.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const uint64_t f0;
};

union U1 {
  volatile struct S0 f0;
};

union U2 {
  volatile int8_t *f0;
};

static int8_t g_9 = 1L;
static volatile uint8_t g_14[3] = {1UL, 1UL, 1UL};
static uint16_t g_17 = 0x98CEL;
static int8_t g_20 = 0x55L;
static int8_t *const g_19 = &g_20;
static union U2 g_22[4] = {{0}, {0}, {0}, {0}};
static union U2 *volatile g_21 = &g_22[1];
static uint32_t g_33 = 0xBFF7828EL;
static uint16_t g_39 = 1UL;
static volatile union U1 g_42 = {{0x3144D9913D709C59LL}};
static int32_t g_43 = (-1L);
static uint32_t g_57 = 4294967288UL;
static int64_t g_58 = 0xA5A1D01971A050D6LL;
static union U2 **volatile g_62[2] = {(void *)0, (void *)0};
static union U2 **volatile g_63 = (void *)0;
static union U2 **volatile g_64 = (void *)0;

static int64_t func_1(void);
static union U2 *func_2(uint16_t p_3, int8_t *const p_4, int32_t p_5);

static int64_t func_1(void) {
  int8_t *l_8 = &g_9;
  int32_t l_15[2][3] = {{0x8B166C19L, 1L, 0x8B166C19L},
                        {0x8B166C19L, 1L, 0x8B166C19L}};
  int32_t *l_16 = &l_15[1][2];
  int8_t l_18 = 8L;
  union U2 *l_61 = &g_22[2];
  union U2 **l_60 = &l_61;
  union U2 *l_65 = &g_22[0];
  int16_t l_66 = 0x3C4FL;
  int i, j;
  l_65 = ((*l_60) = func_2(
              (((safe_rshift_func_int8_t_s_u(
                    ((*l_8) = (-2L)),
                    (((((safe_mul_func_uint8_t_u_u(
                            ((g_14[2] ||
                              ((*l_16) = (((((g_14[2], 18446744073709551611UL),
                                             g_14[2]) <= 0x2F3DL) ^
                                           l_15[1][1]) ^
                                          l_15[1][0]))) > 0xDB39L),
                            0xDDL)) |
                        g_17) <= l_18),
                      g_14[2]) &&
                     0L))) >= g_17) != g_17),
              g_19, g_17));
  return l_66;
}

static union U2 *func_2(uint16_t p_3, int8_t *const p_4, int32_t p_5) {
  union U2 *volatile *l_23 = &g_21;
  int32_t l_29 = 8L;
  uint64_t l_56[2][3];
  union U2 *l_59 = &g_22[1];
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++)
      l_56[i][j] = 18446744073709551613UL;
  }
  (*l_23) = g_21;
  for (g_20 = 0; (g_20 <= 4); g_20 = safe_add_func_uint32_t_u_u(g_20, 7)) {
    int32_t *l_28[4];
    int i;
    for (i = 0; i < 4; i++)
      l_28[i] = (void *)0;
    if ((l_29 = (safe_lshift_func_int8_t_s_u((*g_19), 4)))) {
      if (l_29)
        break;
    } else {
      int16_t l_30 = 0x032FL;
      if ((g_14[1] && ((l_29 < ((void *)0 == l_23)) <= l_30))) {
        int8_t l_37 = 0x04L;
        int32_t l_38[1];
        int i;
        for (i = 0; i < 1; i++)
          l_38[i] = 1L;
        g_33 ^= (g_14[2] > (safe_add_func_int16_t_s_s(g_9, 0x6593L)));
        l_38[0] |= (+(safe_add_func_uint8_t_u_u(
            ((((g_20 < (l_37 == g_20)) > p_3) == 0UL), 1UL), (*g_19))));
      } else {
        int64_t l_40 = 0x48ECA1AEA07874D2LL;
        int32_t l_41[3];
        int i;
        for (i = 0; i < 3; i++)
          l_41[i] = (-1L);
        l_40 = (g_39 = (-1L));
        l_41[2] = l_29;
      }
      g_43 = (0x6136L > ((g_42, (0x86CB52F5L && g_33)) <= l_30));
    }
    g_58 &=
        (g_57 = (l_29 ||
                 (safe_mod_func_int32_t_s_s(
                     (safe_lshift_func_uint16_t_u_u(
                         (safe_rshift_func_uint16_t_u_u(
                             (((((safe_add_func_uint16_t_u_u(
                                     ((safe_div_func_int64_t_s_s(
                                          (((safe_div_func_uint64_t_u_u(
                                                (((&g_21 != l_23) & g_14[2]) <=
                                                 l_56[0][0]),
                                                0x021B0A093F774032LL)),
                                            g_14[2]) ||
                                           p_5),
                                          g_20)) > g_43),
                                     l_56[0][0])) == (*g_19)) >= 0L) < p_3) ||
                              g_14[1]),
                             5)),
                         p_5)),
                     p_5))));
  }
  return l_59;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_14[i];
  }
  csmith_sink_ = g_17;
  csmith_sink_ = g_20;
  csmith_sink_ = g_33;
  csmith_sink_ = g_39;
  csmith_sink_ = g_42.f0.f0;
  csmith_sink_ = g_43;
  csmith_sink_ = g_57;
  csmith_sink_ = g_58;
  platform_main_end(0, 0);
  return 0;
}
