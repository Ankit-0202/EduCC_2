// Options:   --seed 300239 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_239.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint32_t f0;
  volatile int32_t f1;
};

union U2 {
  int16_t f0;
  volatile uint64_t f1;
};

struct S0 {
  const uint32_t f0;
};

union U3 {
  struct S0 f0;
};

static int32_t g_13 = 0xFB807CFAL;
static int32_t *g_12 = &g_13;
static union U3 g_23 = {{0x49A2F381L}};
static union U3 *g_22 = &g_23;
static union U3 **volatile g_21 = &g_22;
static volatile struct S1 g_25 = {0x855EEC80L, 0x219A6FDDL};
static union U3 **g_32 = &g_22;
static volatile int64_t g_37 = 0x279329BFAEAD2214LL;
static volatile int32_t g_39 = (-6L);
static uint8_t g_40[3][3] = {
    {255UL, 255UL, 255UL}, {255UL, 255UL, 255UL}, {255UL, 255UL, 255UL}};
static int16_t g_57 = 1L;
static uint16_t g_60 = 0UL;
static int32_t g_62 = 0x39440774L;
static const union U2 g_63 = {-9L};
static int32_t **g_66 = (void *)0;
static const int32_t *g_68[3] = {&g_13, &g_13, &g_13};
static const int32_t **volatile g_67 = &g_68[2];

static uint32_t func_1(void);
static const int32_t *func_2(uint8_t p_3, const uint64_t p_4, int32_t *p_5);
static uint8_t func_7(int64_t p_8, int32_t *p_9);

static uint32_t func_1(void) {
  int64_t l_6 = 0x9CC25FA5FEF9D786LL;
  (*g_67) =
      func_2((l_6, func_7((safe_add_func_uint16_t_u_u(65535UL, 2UL)), g_12)),
             g_23.f0.f0, g_12);
  return g_62;
}

static const int32_t *func_2(uint8_t p_3, const uint64_t p_4, int32_t *p_5) {
  union U3 **l_30 = &g_22;
  union U3 ***l_31[3];
  int32_t l_35 = 0xF49DCB7BL;
  int32_t l_58 = 0x8B3027FEL;
  int i;
  for (i = 0; i < 3; i++)
    l_31[i] = &l_30;
  if ((g_25, (safe_div_func_int32_t_s_s(
                 (*g_12), (safe_mul_func_uint8_t_u_u(((g_32 = l_30) != &g_22),
                                                     g_13)))))) {
    int32_t *const l_33[1] = {&g_13};
    int32_t **l_34 = (void *)0;
    int i;
    p_5 = l_33[0];
  } else {
    uint32_t l_43[3][3] = {{0xEFA2E576L, 0xEFA2E576L, 0UL},
                           {0xEFA2E576L, 0xEFA2E576L, 0UL},
                           {0xEFA2E576L, 0xEFA2E576L, 0UL}};
    int32_t *l_46 = &l_35;
    int16_t *l_55 = (void *)0;
    int16_t *l_56 = &g_57;
    uint16_t *l_59 = &g_60;
    int32_t *l_61[2];
    int i, j;
    for (i = 0; i < 2; i++)
      l_61[i] = &g_62;
    if (((-5L) && (l_35 = ((p_3 > p_3) | l_35)))) {
      int32_t *l_36 = (void *)0;
      int32_t *l_38[2];
      int i;
      for (i = 0; i < 2; i++)
        l_38[i] = &g_13;
      ++g_40[1][0];
      l_43[1][1]--;
    } else {
      l_46 = p_5;
      return l_46;
    }
    g_62 |=
        (0x33D4965DL <
         ((*p_5) =
              (((safe_mod_func_uint16_t_u_u(
                    ((*l_59) =
                         ((safe_add_func_uint64_t_u_u(
                              p_4,
                              (((safe_mul_func_uint16_t_u_u(
                                    ((l_58 = ((*l_56) =
                                                  (safe_mul_func_uint16_t_u_u(
                                                      ((*l_46) = 0x4CB0L),
                                                      g_25.f0)))) != 0x5D8BL),
                                    g_40[1][0])) >= p_4) > (-1L)))) < 0xFEL)),
                    p_3)) ^
                (*p_5)) >= g_40[1][0])));
  }
  for (g_13 = 2; (g_13 >= 0); g_13 -= 1) {
    for (l_58 = 0; (l_58 <= 2); l_58 += 1) {
      int32_t **l_64 = &g_12;
      int32_t ***l_65[3];
      int i;
      for (i = 0; i < 3; i++)
        l_65[i] = (void *)0;
      (*l_64) = (g_63, &g_13);
      l_35 = ((g_66 = (void *)0) != (void *)0);
    }
    for (g_60 = 0; (g_60 <= 2); g_60 += 1) {
      int i, j;
      if (g_40[g_13][g_60])
        break;
    }
  }
  return p_5;
}

static uint8_t func_7(int64_t p_8, int32_t *p_9) {
  union U3 *const l_20 = (void *)0;
  int32_t l_24 = 0xC6B79DF9L;
  for (g_13 = (-27); (g_13 != (-21)); ++g_13) {
    for (p_8 = (-15); (p_8 < 9); p_8 = safe_add_func_int64_t_s_s(p_8, 2)) {
      union U3 *l_18 = (void *)0;
      union U3 **l_19 = &l_18;
      (*l_19) = l_18;
      if ((*p_9))
        break;
    }
  }
  (*g_21) = l_20;
  return l_24;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  csmith_sink_ = g_23.f0.f0;
  csmith_sink_ = g_25.f0;
  csmith_sink_ = g_25.f1;
  csmith_sink_ = g_37;
  csmith_sink_ = g_39;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_40[i][j];
    }
  }
  csmith_sink_ = g_57;
  csmith_sink_ = g_60;
  csmith_sink_ = g_62;
  csmith_sink_ = g_63.f0;
  platform_main_end(0, 0);
  return 0;
}
