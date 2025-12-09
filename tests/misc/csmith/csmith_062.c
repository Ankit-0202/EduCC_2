// Options:   --seed 100062 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_062.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile uint16_t f0;
  volatile uint16_t f1;
  volatile uint64_t f2;
};

struct S1 {
  struct S0 f0;
  uint64_t f1;
  int64_t f2;
};

union U3 {
  int64_t f0;
};

static int32_t g_2 = 0x244D513CL;
static int32_t g_6[2] = {(-1L), (-1L)};
static union U3 g_8 = {-4L};
static union U3 *g_7 = &g_8;
static union U3 **volatile g_10 = &g_7;
static int32_t *volatile g_24[2][3] = {{(void *)0, &g_6[1], &g_6[1]},
                                       {(void *)0, &g_6[1], &g_6[1]}};
static int32_t *volatile g_25 = (void *)0;
static int32_t g_28 = (-4L);
static int16_t g_33 = 7L;
static uint64_t g_37 = 0x93046AA1DD5C0AECLL;
static uint8_t g_40 = 1UL;
static int32_t g_44 = 0x50133ECBL;
static struct S1 g_51[2][4] = {{{{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L},
                                {{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L},
                                {{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L},
                                {{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L}},
                               {{{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L},
                                {{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L},
                                {{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L},
                                {{1UL, 0UL, 0x9C85691F3A4B4404LL}, 1UL, 2L}}};

static struct S1 func_1(void);
static uint32_t func_15(union U3 *p_16, uint32_t p_17, union U3 **p_18);

static struct S1 func_1(void) {
  int16_t l_19 = (-1L);
  for (g_2 = 7; (g_2 <= 10); g_2++) {
    uint32_t l_5[1][4] = {{1UL, 1UL, 1UL, 1UL}};
    union U3 **l_20 = &g_7;
    int16_t l_49 = 0x622CL;
    int i, j;
    for (g_6[0] = 0; (g_6[0] >= 0); g_6[0] -= 1) {
      union U3 *l_9 = &g_8;
      int32_t *l_50 = &g_44;
      int i, j;
      (*g_10) = (l_9 = g_7);
      (*l_50) ^= (safe_mod_func_uint32_t_u_u(
          (safe_add_func_uint64_t_u_u(l_5[g_6[0]][(g_6[0] + 3)],
                                      ((func_15((*g_10), l_19, l_20) <
                                        l_5[g_6[0]][(g_6[0] + 3)]) != l_49))),
          g_6[0]));
    }
  }
  return g_51[1][0];
}

static uint32_t func_15(union U3 *p_16, uint32_t p_17, union U3 **p_18) {
  uint32_t l_21[3][1];
  int16_t l_38 = 5L;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_21[i][j] = 0x2C02A306L;
  }
  for (g_8.f0 = 0; g_8.f0 < 3; g_8.f0 += 1) {
    for (p_17 = 0; p_17 < 1; p_17 += 1) {
      l_21[g_8.f0][p_17] = 4UL;
    }
  }
  if ((safe_mul_func_uint16_t_u_u((g_8.f0, (g_6[0], (g_6[0] || 0x0237L))),
                                  p_17))) {
    int32_t *l_26 = (void *)0;
    int32_t *l_27 = &g_28;
    int16_t *l_32 = &g_33;
    uint64_t *l_36 = &g_37;
    uint8_t *l_39 = &g_40;
    (*l_27) = (0L ^ 0xCDD7L);
    (*l_27) =
        (+((*l_39) =
               ((safe_mod_func_int16_t_s_s(
                    ((*l_32) = 0xECA6L),
                    (safe_rshift_func_int8_t_s_u(
                        (((*l_27) && ((*l_36) = 1UL)), l_38), 4)))) >= 0x1DL)));
  } else {
    uint64_t l_45 = 18446744073709551610UL;
    int32_t l_48 = 1L;
    for (g_28 = (-22); (g_28 >= 20);
         g_28 = safe_add_func_uint32_t_u_u(g_28, 1)) {
      int32_t *l_43 = &g_44;
      l_45--;
      if (l_48)
        continue;
    }
  }
  return l_21[0][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_6[i];
  }
  csmith_sink_ = g_8.f0;
  csmith_sink_ = g_28;
  csmith_sink_ = g_33;
  csmith_sink_ = g_37;
  csmith_sink_ = g_40;
  csmith_sink_ = g_44;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
    }
  }
  platform_main_end(0, 0);
  return 0;
}
