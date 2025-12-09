// Options:   --seed 300254 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_254.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int32_t f0;
  const int32_t f1;
  const volatile uint8_t f2;
};

static int32_t g_2 = 1L;
static uint16_t g_22 = 0xCB8FL;
static uint16_t g_24[2][1] = {{0xC28CL}, {0xC28CL}};
static int32_t g_27 = (-1L);
static int32_t *g_41 = &g_27;
static int32_t **volatile g_40[3] = {&g_41, &g_41, &g_41};
static volatile struct S0 g_46 = {-8L, 0x4EBF8C32L, 0x19L};
static int32_t g_48 = 0x11E8E103L;
static int64_t g_53 = 0xAE446F941663B350LL;
static volatile uint32_t g_59 = 0xB7473AC0L;

static int8_t func_1(void);
static uint32_t func_7(uint64_t p_8, int32_t p_9, uint8_t p_10);
static uint16_t func_15(int32_t p_16, uint32_t p_17, int8_t p_18);

static int8_t func_1(void) {
  uint8_t l_25 = 1UL;
  int64_t l_54 = (-10L);
  int32_t l_55 = 0x2FCEC4EEL;
  int32_t l_56 = 0xC5B6CC60L;
  int32_t l_57 = (-2L);
  int32_t l_58 = 4L;
  for (g_2 = 0; (g_2 <= 20); g_2 = safe_add_func_uint16_t_u_u(g_2, 3)) {
    uint64_t l_11 = 0xF48C443EB6069300LL;
    uint32_t l_14 = 0x1C71BC7DL;
    uint16_t *l_21 = &g_22;
    uint16_t *l_23 = &g_24[0][0];
    int32_t l_52[1][1];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_52[i][j] = 0x7B9FFBDDL;
    }
    if ((safe_rshift_func_uint16_t_u_s(
            (func_7(
                 l_11,
                 (safe_sub_func_uint16_t_u_u(
                     l_14,
                     func_15((((safe_mul_func_int16_t_s_s(
                                   ((((((*l_23) = ((*l_21) |=
                                                   (g_2, 0xC07CL))) != g_2) &&
                                      g_22),
                                     g_2) > 246UL),
                                   l_14)) > 0x78D7CBAE8B012130LL) ||
                              l_25),
                             l_14, l_25))),
                 l_11) <= g_2),
            l_25))) {
      int32_t *l_47 = &g_48;
      (*l_47) &= ((g_27 > ((*l_21) = (g_46, g_27))) >= g_27);
    } else {
      int32_t *l_49 = (void *)0;
      int32_t *l_50 = &g_27;
      int32_t *l_51[1][3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_51[i][j] = (void *)0;
      }
      --g_59;
    }
  }
  for (g_53 = (-6); (g_53 >= (-2)); ++g_53) {
    int32_t *l_64 = &g_48;
    if (l_55)
      break;
    (*l_64) ^= (*g_41);
  }
  return l_54;
}

static uint32_t func_7(uint64_t p_8, int32_t p_9, uint8_t p_10) {
  int32_t *l_38[2][2] = {{&g_2, &g_2}, {&g_2, &g_2}};
  int32_t **l_37 = &l_38[0][0];
  int32_t ***l_39 = &l_37;
  int32_t **volatile *l_42[2][2] = {{&g_40[1], &g_40[1]}, {&g_40[1], &g_40[1]}};
  int i, j;
  if ((safe_mul_func_uint8_t_u_u(
          (safe_rshift_func_int16_t_s_u(
              (safe_add_func_uint32_t_u_u(
                  ((((*l_39) = l_37) != g_40[1]) | p_10), 0UL)),
              10)),
          (-4L)))) {
    for (p_9 = 0; (p_9 >= 0); p_9 -= 1) {
      int i;
      l_42[0][0] = &g_40[p_9];
    }
  } else {
    uint8_t l_43 = 0xD4L;
    l_43++;
  }
  return p_8;
}

static uint16_t func_15(int32_t p_16, uint32_t p_17, int8_t p_18) {
  int32_t *l_26 = &g_27;
  const int32_t *l_30 = &g_2;
  const int32_t **l_29 = &l_30;
  (*l_29) = (((((*l_26) = p_18) | (!0x6446BD29A2A67F6ALL)) || p_16), (void *)0);
  (*l_29) = &g_2;
  return g_27;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_22;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_24[i][j];
    }
  }
  csmith_sink_ = g_27;
  csmith_sink_ = g_46.f0;
  csmith_sink_ = g_46.f1;
  csmith_sink_ = g_46.f2;
  csmith_sink_ = g_48;
  csmith_sink_ = g_53;
  csmith_sink_ = g_59;
  platform_main_end(0, 0);
  return 0;
}
