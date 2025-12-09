// Options:   --seed 300207 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_207.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile uint64_t f0;
  volatile uint8_t f1;
};

union U2 {
  const int8_t f0;
  volatile int16_t f1;
};

static int32_t g_13[2] = {0L, 0L};
static volatile int32_t **g_24 = (void *)0;
static volatile int32_t g_27 = 0xFB91E60EL;
static const union U2 g_29[3] = {{0xF3L}, {0xF3L}, {0xF3L}};
static const union U2 *g_31 = &g_29[1];
static const union U2 **volatile g_30 = &g_31;
static int32_t g_33[2] = {(-1L), (-1L)};
static const int32_t *const g_32 = &g_33[1];
static volatile int32_t g_34 = 0x5EE6D54EL;
static int32_t g_35 = 0x318B4743L;
static union U2 g_42 = {0x49L};
static int32_t *g_45 = &g_35;
static int32_t **volatile g_44 = &g_45;
static int32_t **g_49[3][1] = {{&g_45}, {&g_45}, {&g_45}};
static int32_t ***const volatile g_48 = &g_49[1][0];
static int64_t g_55 = 4L;
static struct S1 g_56 = {0UL, 0x39L};

static struct S1 func_1(void);
static int32_t *func_2(int32_t *p_3, const int32_t *const p_4);
static int32_t *func_5(const uint32_t p_6, int32_t *const p_7, uint32_t p_8,
                       int32_t *p_9, uint8_t p_10);

static struct S1 func_1(void) {
  const uint64_t l_11 = 0UL;
  int32_t *const l_12 = &g_13[0];
  (*g_44) =
      func_2(func_5(l_11, l_12,
                    (safe_lshift_func_uint8_t_u_s(
                        (((((safe_lshift_func_uint16_t_u_s(
                                (safe_rshift_func_int16_t_s_u((-5L), 7)), 0)) &&
                            (*l_12)) > g_13[0]) ||
                          (*l_12)) == 1L),
                        g_13[0])),
                    &g_13[0], g_13[1]),
             g_32);
  if ((safe_unary_minus_func_uint32_t_u((*l_12)))) {
    int32_t **l_47[3];
    int i;
    for (i = 0; i < 3; i++)
      l_47[i] = &g_45;
    (*g_48) = l_47[0];
  } else {
    uint32_t l_52 = 18446744073709551615UL;
    int64_t *l_53 = (void *)0;
    int64_t *l_54 = &g_55;
    (*l_12) =
        (g_33[1] &
         ((g_27 & (((*l_54) = (((safe_add_func_uint64_t_u_u(
                                    0xBFEFA2E5769E8A28LL, g_35)) >= l_52),
                               g_33[1])) < 0xE0133D4965DA1F79LL)) != (*l_12)));
  }
  return g_56;
}

static int32_t *func_2(int32_t *p_3, const int32_t *const p_4) {
  union U2 *l_41 = &g_42;
  union U2 *const *l_40 = &l_41;
  union U2 *const **l_39 = &l_40;
  int32_t *l_43 = &g_35;
  for (g_35 = 0; (g_35 != 5); ++g_35) {
    union U2 *const **l_38[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_38[i][j] = (void *)0;
    }
    l_39 = l_38[1][0];
  }
  return l_43;
}

static int32_t *func_5(const uint32_t p_6, int32_t *const p_7, uint32_t p_8,
                       int32_t *p_9, uint8_t p_10) {
  int32_t *l_20 = (void *)0;
  int32_t **l_21 = &l_20;
  const union U2 *l_28 = &g_29[1];
  (*l_21) = l_20;
  for (p_10 = (-1); (p_10 < 49); p_10 = safe_add_func_int16_t_s_s(p_10, 1)) {
    volatile int32_t *l_26 = &g_27;
    volatile int32_t **l_25 = &l_26;
    if (((*p_9) = (*p_7))) {
      l_25 = g_24;
    } else {
      return p_9;
    }
    (*g_30) = l_28;
  }
  return p_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_13[i];
  }
  csmith_sink_ = g_27;
  for (i = 0; i < 3; i++) {
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_33[i];
  }
  csmith_sink_ = g_34;
  csmith_sink_ = g_35;
  csmith_sink_ = g_42.f0;
  csmith_sink_ = g_55;
  csmith_sink_ = g_56.f0;
  csmith_sink_ = g_56.f1;
  platform_main_end(0, 0);
  return 0;
}
