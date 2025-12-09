// Options:   --seed 100006 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_006.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int32_t f0;
  int32_t f1;
};

struct S2 {
  uint16_t f0;
  uint32_t f1;
  volatile int32_t f2;
};

static volatile int32_t g_3 = 0x5B7CEFA9L;
static int32_t g_4 = (-6L);
static const volatile struct S2 g_10 = {0x3E34L, 0x64B5C6F8L, 4L};
static int32_t g_16 = (-1L);
static int32_t *volatile g_15 = &g_16;
static struct S1 g_23 = {0x1A6E483BL, -1L};
static const int32_t g_26 = 0x9B467BB1L;
static int32_t *volatile g_28 = (void *)0;
static int32_t g_34 = 0xE20EEB49L;
static int32_t g_40 = 0xF77771FDL;
static struct S2 g_42 = {0x6A5DL, 0xC9AD537EL, -2L};
static struct S2 *volatile g_43[1] = {(void *)0};
static struct S2 *volatile g_44 = &g_42;

static uint32_t func_1(void);
static struct S2 func_5(uint32_t p_6, int32_t p_7, uint32_t p_8, uint16_t p_9);

static uint32_t func_1(void) {
  int16_t l_2[2];
  int i;
  for (i = 0; i < 2; i++)
    l_2[i] = 0xD491L;
  for (g_4 = 0; (g_4 <= 1); g_4 += 1) {
    int i;
    (*g_44) = func_5(l_2[g_4], (g_10, (safe_mul_func_uint16_t_u_u(g_3, g_4))),
                     g_4, l_2[g_4]);
  }
  return g_10.f1;
}

static struct S2 func_5(uint32_t p_6, int32_t p_7, uint32_t p_8, uint16_t p_9) {
  int32_t *l_21 = &g_4;
  uint8_t l_41 = 255UL;
  if ((safe_sub_func_int64_t_s_s(g_3, (-2L)))) {
    if ((g_3 <= p_9)) {
      (*g_15) ^= p_8;
    } else {
      int32_t **l_22 = &l_21;
      const int32_t *l_25 = &g_26;
      const int32_t **l_24 = &l_25;
      uint16_t l_27[2][1];
      int32_t l_29 = 0x164E62B5L;
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_27[i][j] = 65535UL;
      }
      l_29 ^= (safe_div_func_uint64_t_u_u(
          (((safe_mod_func_uint64_t_u_u(
                (((*l_22) = l_21) != ((*l_24) = (g_23, &g_16))), p_7)) >=
            0UL) <= p_9),
          l_27[0][0]));
    }
  } else {
    const uint32_t l_38 = 18446744073709551615UL;
    for (g_16 = 0; (g_16 < 15); g_16++) {
      int32_t *l_33 = &g_34;
      int32_t *l_39[3];
      int i;
      for (i = 0; i < 3; i++)
        l_39[i] = &g_40;
      (*l_33) &=
          (((!(0x23L >= g_4)) != ((&g_4 == (void *)0) < g_10.f0)) && p_8);
      l_41 ^= (((safe_lshift_func_int8_t_s_u((~(*g_15)),
                                             ((g_26, 251UL), (*l_33)))) <
                0x0BF09457720F84B0LL) < l_38);
    }
  }
  return g_42;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_10.f0;
  csmith_sink_ = g_10.f1;
  csmith_sink_ = g_10.f2;
  csmith_sink_ = g_16;
  csmith_sink_ = g_23.f0;
  csmith_sink_ = g_23.f1;
  csmith_sink_ = g_26;
  csmith_sink_ = g_34;
  csmith_sink_ = g_40;
  csmith_sink_ = g_42.f0;
  csmith_sink_ = g_42.f1;
  csmith_sink_ = g_42.f2;
  platform_main_end(0, 0);
  return 0;
}
