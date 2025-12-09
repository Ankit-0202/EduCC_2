// Options:   --seed 100075 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_075.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int64_t f0;
};

union U1 {
  struct S0 f0;
};

static uint16_t g_13[4] = {65534UL, 65534UL, 65534UL, 65534UL};
static int16_t g_20[4][1] = {{7L}, {7L}, {7L}, {7L}};
static volatile uint64_t g_34[3][2] = {
    {0UL, 0x83518F4C6F444694LL}, {0UL, 0UL}, {0x83518F4C6F444694LL, 0UL}};
static struct S0 g_37 = {0x352FB29D945AD33DLL};
static volatile int32_t g_46 = 0xFC518F82L;
static volatile int32_t *volatile g_45 = &g_46;
static volatile int32_t *volatile *g_44 = &g_45;
static struct S0 *volatile g_49 = &g_37;
static union U1 g_53[2] = {{{0L}}, {{0L}}};

static union U1 func_1(void);
static struct S0 func_2(uint32_t p_3, int16_t p_4, int64_t p_5, int32_t p_6,
                        int8_t p_7);

static union U1 func_1(void) {
  uint32_t l_18 = 1UL;
  int16_t *l_19 = &g_20[2][0];
lbl_52:
  (*g_49) = func_2(
      (!((safe_div_func_uint16_t_u_u(
             (safe_add_func_uint16_t_u_u(
                 g_13[3], (safe_add_func_uint64_t_u_u(
                              (safe_div_func_uint32_t_u_u(
                                  l_18, (((*l_19) |= 0x52D0L) & 65531UL))),
                              g_13[3])))),
             g_13[2])) != 0UL)),
      g_13[3], l_18, g_13[3], g_13[0]);
  for (l_18 = (-9); (l_18 > 6); l_18 = safe_add_func_int64_t_s_s(l_18, 4)) {
    if (l_18)
      goto lbl_52;
  }
  return g_53[0];
}

static struct S0 func_2(uint32_t p_3, int16_t p_4, int64_t p_5, int32_t p_6,
                        int8_t p_7) {
  uint16_t l_29 = 65535UL;
  for (p_5 = 0; (p_5 > (-10)); --p_5) {
    uint64_t l_23 = 1UL;
    int32_t l_31 = (-10L);
    int32_t *l_48 = (void *)0;
    int32_t **l_47 = &l_48;
    if ((l_23 & 0xF2EF51AEL)) {
      uint32_t l_30 = 18446744073709551609UL;
      int32_t l_33[4][3];
      int i, j;
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++)
          l_33[i][j] = 0xE72C34CCL;
      }
      l_30 |= (p_5, (safe_add_func_uint8_t_u_u(
                        ((safe_unary_minus_func_uint64_t_u(p_5)) &&
                         (safe_rshift_func_uint8_t_u_u((p_6, l_23), l_29))),
                        l_23)));
      if (p_7) {
        int32_t *l_32 = &l_31;
        g_34[2][0]--;
      } else {
        return g_37;
      }
    } else {
      int32_t *l_39[3][1];
      int32_t **l_38 = &l_39[2][0];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_39[i][j] = (void *)0;
      }
      (*l_38) = &l_31;
      if (((safe_div_func_uint64_t_u_u(
               (((l_29 < (((~((~(p_4 = (g_37.f0,
                                        ((0x9FCB6EA418246746LL != g_20[2][0]) ^
                                         g_13[3])))) != (-1L))) != g_13[3]) !=
                          g_13[1])) == g_13[0]) ||
                1UL),
               g_20[2][0])) |
           1L)) {
        (**g_44) ^= (g_44 != l_47);
      } else {
        if ((**g_44))
          break;
      }
    }
  }
  return g_37;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_13[i];
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_20[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_34[i][j];
    }
  }
  csmith_sink_ = g_37.f0;
  csmith_sink_ = g_46;
  for (i = 0; i < 2; i++) {
  }
  platform_main_end(0, 0);
  return 0;
}
