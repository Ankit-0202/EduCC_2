// Options:   --seed 100052 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_052.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2[4][1] = {{0xA5D6C05BL}, {0L}, {0xA5D6C05BL}, {0L}};
static int32_t g_3 = 0xD8DA8E97L;
static int32_t g_7 = 0x891C5534L;
static int32_t g_9 = 0xA6E6F7FBL;
static const volatile int32_t *volatile g_18[3] = {&g_2[2][0], &g_2[2][0],
                                                   &g_2[2][0]};
static const volatile int32_t *volatile *volatile g_17 = &g_18[0];
static const volatile int32_t *volatile *volatile *volatile g_19 = (void *)0;
static int32_t g_22 = 0xBCA7B5CFL;
static int32_t *volatile g_21 = &g_22;
static volatile int32_t g_24 = 3L;
static int32_t g_25 = 0x51FA4C82L;
static int32_t g_27 = 1L;
static int32_t g_36 = 1L;
static int64_t g_37 = 0x7C242EA6AE202455LL;
static const volatile int32_t *volatile *volatile *volatile **volatile g_38 =
    (void *)0;
static volatile uint64_t g_57 = 0x5119B5F814D19633LL;
static volatile uint64_t *g_56 = &g_57;
static uint64_t g_60 = 0x6E1851AA8C97D735LL;
static uint64_t g_61 = 7UL;

static uint64_t func_1(void);
static uint32_t func_14(const int32_t *p_15);

static uint64_t func_1(void) {
  uint64_t l_34[2];
  int32_t l_59 = (-1L);
  uint32_t l_62 = 0x1BFDB9CEL;
  int i;
  for (i = 0; i < 2; i++)
    l_34[i] = 3UL;
  for (g_3 = (-20); (g_3 < (-21)); g_3 = safe_sub_func_uint8_t_u_u(g_3, 3)) {
    int32_t *l_6 = &g_7;
    int32_t *l_8 = &g_9;
    uint64_t *l_58 = (void *)0;
    if (((*l_8) &= ((*l_6) |= g_2[3][0]))) {
      const int32_t *l_16 = &g_3;
      for (g_9 = 3; (g_9 <= 25); ++g_9) {
        int32_t *l_35[1][2];
        int i, j;
        for (i = 0; i < 1; i++) {
          for (j = 0; j < 2; j++)
            l_35[i][j] = &g_36;
        }
        g_37 |= (((safe_add_func_uint32_t_u_u((0xAAED6B65L == func_14(l_16)),
                                              l_34[1])) != g_3),
                 (*g_21));
        return (*l_16);
      }
      (*l_6) = ((*l_8) = (*g_21));
    } else {
      const volatile int32_t *volatile *volatile *volatile *l_40 = &g_19;
      const volatile int32_t *volatile *volatile *volatile **l_39 = &l_40;
      (*l_39) = &g_19;
    }
    if ((safe_mul_func_uint8_t_u_u(((*l_6) &= (*l_8)), 0x8BL))) {
      int32_t l_43 = 0x6153B72BL;
      if (l_43)
        break;
    } else {
      int16_t l_44[4] = {0L, 0L, 0L, 0L};
      uint64_t *l_45 = &l_34[0];
      int i;
      (*l_8) &= (l_44[2] !=
                 (((((((--(*l_45)) !=
                       (safe_rshift_func_int8_t_s_s(
                           (g_61 = ((((safe_rshift_func_uint16_t_u_s(
                                          (((safe_add_func_uint8_t_u_u(
                                                ((safe_mul_func_uint16_t_u_u(
                                                     (g_56 == l_58), g_37)) ||
                                                 (*g_56)),
                                                l_59)) &&
                                            g_2[0][0]) < g_60),
                                          l_44[2])) ||
                                      l_59) < l_44[1]) < g_36)),
                           7))) >= g_22),
                     (*l_6)) &&
                    l_44[2]) != 0x1EL) < g_60));
    }
  }
  return l_62;
}

static uint32_t func_14(const int32_t *p_15) {
  const volatile int32_t *volatile l_23 = (void *)0;
  int32_t l_33 = 0x9D62BFEEL;
  for (g_7 = 0; (g_7 >= 0); g_7 -= 1) {
    const volatile int32_t *volatile *volatile *l_20[4];
    int i;
    for (i = 0; i < 4; i++)
      l_20[i] = &g_17;
    g_17 = g_17;
    (*g_21) = (*p_15);
    for (g_22 = 0; (g_22 >= 0); g_22 -= 1) {
      uint32_t l_32 = 1UL;
      l_23 = (*g_17);
      for (g_25 = 0; (g_25 >= 0); g_25 -= 1) {
        int32_t *l_26[2];
        int i, j;
        for (i = 0; i < 2; i++)
          l_26[i] = &g_27;
        g_2[(g_22 + 1)][g_25] = (g_27 |= (*l_23));
        l_33 = ((safe_mul_func_uint16_t_u_u(
                    ((((((safe_sub_func_int64_t_s_s(((void *)0 != &p_15),
                                                    (9UL <= 0xD7D0L))) ^
                         g_22) <= g_3) != g_27) &
                      l_32) >= l_32),
                    0xA796L)) ||
                g_22);
      }
    }
  }
  return l_33;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_7;
  csmith_sink_ = g_9;
  csmith_sink_ = g_22;
  csmith_sink_ = g_24;
  csmith_sink_ = g_25;
  csmith_sink_ = g_27;
  csmith_sink_ = g_36;
  csmith_sink_ = g_37;
  csmith_sink_ = g_57;
  csmith_sink_ = g_60;
  csmith_sink_ = g_61;
  platform_main_end(0, 0);
  return 0;
}
