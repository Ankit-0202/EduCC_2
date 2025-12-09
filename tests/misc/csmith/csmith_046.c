// Options:   --seed 100046 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_046.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  int32_t f1;
};

static int16_t g_4 = 0L;
static uint8_t g_12 = 0xB4L;
static uint8_t g_14 = 0UL;
static volatile struct S0 g_15 = {0x278FA8F9L, 0L};
static volatile struct S0 *volatile g_16 = (void *)0;
static volatile struct S0 *volatile g_17 = (void *)0;
static int32_t g_30 = 0x67606E82L;
static struct S0 g_33[1][3] = {
    {{0UL, 0x2955D482L}, {0UL, 0x2955D482L}, {0UL, 0x2955D482L}}};
static volatile int32_t *volatile g_35 = &g_15.f1;
static volatile int32_t *volatile *g_34 = &g_35;
static volatile int32_t *volatile **volatile g_37 = (void *)0;
static volatile int32_t *volatile **volatile g_39 = &g_34;
static int32_t g_41 = 0xBBBB531EL;
static uint8_t g_45 = 0UL;

static uint64_t func_1(void);
static int32_t func_2(uint32_t p_3);

static uint64_t func_1(void) {
  uint32_t l_5 = 18446744073709551615UL;
  uint32_t *l_6 = &l_5;
  struct S0 l_53[3] = {{4294967291UL, 0xBA057618L},
                       {4294967291UL, 0xBA057618L},
                       {4294967291UL, 0xBA057618L}};
  volatile int32_t *volatile **l_57 = &g_34;
  volatile int32_t *volatile ***l_56 = &l_57;
  int i;
  if (func_2(((*l_6) = (g_4 > ((l_5 && l_5) != g_4))))) {
    uint32_t *l_28 = &l_5;
    int32_t *l_29 = &g_30;
    int32_t l_44[2];
    int i;
    for (i = 0; i < 2; i++)
      l_44[i] = (-3L);
    (*l_29) ^= ((void *)0 == l_28);
    for (g_30 = (-29); (g_30 <= (-18));
         g_30 = safe_add_func_int8_t_s_s(g_30, 1)) {
      int32_t *l_40 = &g_41;
      int32_t *l_42 = &g_41;
      int32_t *l_43[4][2] = {
          {&g_41, &g_41}, {&g_41, &g_41}, {&g_41, &g_41}, {&g_41, &g_41}};
      int i, j;
      for (g_14 = 0; (g_14 <= 0); g_14 += 1) {
        volatile int32_t *volatile **l_36 = (void *)0;
        volatile int32_t *volatile **l_38 = (void *)0;
        (*g_39) = g_34;
      }
      g_45++;
    }
  } else {
    uint32_t l_48 = 1UL;
    (**g_34) = l_48;
    (**g_34) = ((safe_add_func_uint64_t_u_u(
                    (safe_mul_func_uint16_t_u_u(
                        (l_53[2],
                         (safe_lshift_func_uint16_t_u_s((g_4 && l_48), g_14))),
                        g_45)),
                    g_14)) ||
                l_5);
  }
  (*l_56) = &g_34;
  return (***l_57);
}

static int32_t func_2(uint32_t p_3) {
  uint64_t l_23 = 0x89A9B8FA48A2B8EALL;
  uint8_t *l_25 = &g_12;
  for (p_3 = 0; (p_3 >= 50); p_3 = safe_add_func_uint8_t_u_u(p_3, 7)) {
    uint8_t *l_11 = &g_12;
    uint8_t *l_13 = &g_14;
    struct S0 l_19[1] = {{0xEE973417L, 0L}};
    int i;
    if ((safe_rshift_func_uint8_t_u_u(0x46L, ((*l_13) &= ((*l_11) = g_4))))) {
      volatile struct S0 *l_18 = &g_15;
      (*l_18) = g_15;
      (*l_18) = l_19[0];
    } else {
      volatile struct S0 *volatile *l_22 = &g_17;
      int32_t l_26 = 0xA82A6F94L;
      int32_t *l_27 = &l_19[0].f1;
      for (g_12 = 0; (g_12 > 18); g_12 = safe_add_func_int32_t_s_s(g_12, 3)) {
        int32_t *l_24 = &l_19[0].f1;
        l_22 = &g_17;
        (*l_24) ^= l_23;
      }
      (*l_27) = (((void *)0 != l_25),
                 (((((((g_14 < 0UL) && g_4) || g_14) > l_23) && 0x4BL) || l_26),
                  l_19[0].f0));
    }
    if (g_12)
      break;
  }
  return p_3;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_12;
  csmith_sink_ = g_14;
  csmith_sink_ = g_15.f0;
  csmith_sink_ = g_15.f1;
  csmith_sink_ = g_30;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  csmith_sink_ = g_41;
  csmith_sink_ = g_45;
  platform_main_end(0, 0);
  return 0;
}
