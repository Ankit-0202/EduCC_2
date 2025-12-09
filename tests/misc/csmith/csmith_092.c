// Options:   --seed 100092 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_092.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint16_t f0;
  int8_t f1;
  uint64_t f2;
};

union U2 {
  const int32_t f0;
};

static volatile uint16_t g_2 = 0x68C0L;
static union U2 g_9[3] = {{-5L}, {-5L}, {-5L}};
static int16_t g_19 = 0x5B38L;
static int32_t g_22 = 0L;
static uint8_t g_31 = 255UL;
static int8_t g_34 = 0x11L;
static uint8_t g_35 = 0xEFL;

static int64_t func_1(void);
static int16_t func_5(union U2 p_6, uint64_t p_7, uint32_t p_8);

static int64_t func_1(void) {
  uint16_t l_10 = 1UL;
  int32_t l_38 = 0xCFEBDAB6L;
  l_38 |= (g_2 < ((safe_mul_func_int16_t_s_s(func_5(g_9[0], g_9[0].f0, l_10),
                                             g_34)) < g_9[0].f0));
  return g_35;
}

static int16_t func_5(union U2 p_6, uint64_t p_7, uint32_t p_8) {
  struct S0 l_11 = {0x7603L, 0x59L, 0xB68DEE21AFA9B64FLL};
  struct S0 *l_12 = &l_11;
  (*l_12) = l_11;
  for (l_11.f2 = 0; (l_11.f2 < 39); ++l_11.f2) {
    struct S0 **l_17 = &l_12;
    int16_t *l_18 = &g_19;
    int32_t l_20[3][3] = {{(-1L), 0x6F25DB2BL, (-1L)},
                          {(-1L), (-1L), (-1L)},
                          {(-1L), 0x6F25DB2BL, (-1L)}};
    int32_t *l_21 = &g_22;
    int i, j;
    (*l_21) ^= (safe_sub_func_int16_t_s_s(
        ((*l_18) =
             ((((&l_11 == ((*l_17) = (g_9[0], (void *)0))) & 0xEDF0EBF9L) |
               g_9[0].f0) >= l_11.f0)),
        l_20[2][2]));
    for (p_7 = 0; (p_7 == 54); ++p_7) {
      int32_t l_29 = (-1L);
      int32_t *l_32[3];
      int8_t l_33 = 0L;
      int i;
      for (i = 0; i < 3; i++)
        l_32[i] = &l_20[1][0];
      for (l_11.f0 = 0; (l_11.f0 <= 2); l_11.f0 += 1) {
        uint8_t *l_30 = &g_31;
        int i, j;
        l_20[l_11.f0][l_11.f0] = (safe_rshift_func_uint8_t_u_u(
            (safe_mod_func_int8_t_s_s((l_20[l_11.f0][l_11.f0] >= 1UL),
                                      ((*l_30) = ((l_29 == g_19), 1UL)))),
            6));
      }
      ++g_35;
    }
  }
  return g_9[0].f0;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 3; i++) {
  }
  csmith_sink_ = g_19;
  csmith_sink_ = g_22;
  csmith_sink_ = g_31;
  csmith_sink_ = g_34;
  csmith_sink_ = g_35;
  platform_main_end(0, 0);
  return 0;
}
