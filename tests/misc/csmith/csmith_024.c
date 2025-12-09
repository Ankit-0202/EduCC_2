// Options:   --seed 100024 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_024.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  int32_t f1;
};

struct S5 {
  uint8_t f0;
  int16_t f1;
  uint32_t f2;
};

struct S1 {
  volatile struct S0 f0;
  int16_t f1;
};

struct S9 {
  struct S1 f0;
  volatile struct S0 f1;
};

static volatile int32_t g_3 = 0L;
static volatile int32_t g_4[1] = {(-6L)};
static int32_t g_5[2] = {(-1L), (-1L)};
static int32_t g_7 = 0L;
static int32_t *volatile g_6 = &g_7;
static int32_t g_11 = 3L;
static int32_t *volatile g_10 = &g_11;
static struct S0 g_16 = {0x2E3A4C63L, 0x299FA9EFL};
static struct S5 g_31 = {0x51L, 0xA741L, 0x6315BFEBL};
static struct S5 *volatile g_32 = &g_31;
static int32_t *volatile g_36 = (void *)0;
static struct S9 g_39 = {{{0x6B495482L, -7L}, 1L}, {0UL, 4L}};
static int32_t *g_42 = &g_5[1];
static int32_t **volatile g_41[1] = {&g_42};
static struct S9 g_44 = {{{0UL, 0xB67338D5L}, -10L},
                         {0x9286DF49L, 0xA847E08AL}};

static struct S9 func_1(void);
static int32_t func_12(struct S0 p_13, uint32_t p_14, int32_t *p_15);

static struct S9 func_1(void) {
  uint8_t l_2[4][4] = {{0UL, 0UL, 0UL, 0UL},
                       {0UL, 0UL, 0UL, 0UL},
                       {0UL, 0UL, 0UL, 0UL},
                       {0UL, 0UL, 0UL, 0UL}};
  int32_t *l_40 = &g_7;
  int32_t **l_43 = &g_42;
  int i, j;
  for (g_5[1] = 3; (g_5[1] >= 0); g_5[1] -= 1) {
    int32_t *l_9 = &g_5[1];
    (*g_6) = g_5[0];
    for (g_7 = 0; (g_7 <= 3); g_7 += 1) {
      int32_t *l_8 = &g_5[1];
      int32_t **l_17 = &l_8;
      int32_t *l_19 = &g_5[1];
      int32_t **l_18 = &l_19;
      if (((void *)0 == l_8)) {
        int i, j;
        if (l_2[g_7][g_5[1]])
          break;
      } else {
        (*g_10) ^= ((void *)0 != l_9);
      }
      if (func_12(g_16, (((*l_17) = l_9) != ((*l_18) = &g_5[1])), &g_7)) {
        (*l_17) = &g_5[1];
      } else {
        int32_t *l_38 = &g_7;
        (*l_17) = l_38;
      }
    }
  }
  (*l_43) = (l_40 = (g_39, &g_11));
  return g_44;
}

static int32_t func_12(struct S0 p_13, uint32_t p_14, int32_t *p_15) {
  for (g_16.f0 = 0; (g_16.f0 <= 24);
       g_16.f0 = safe_add_func_uint32_t_u_u(g_16.f0, 6)) {
    for (g_16.f1 = (-11); (g_16.f1 != (-11));
         g_16.f1 = safe_add_func_uint8_t_u_u(g_16.f1, 5)) {
      for (p_13.f1 = 0; (p_13.f1 <= 0); p_13.f1 += 1) {
        int32_t *l_28[3];
        int i;
        for (i = 0; i < 3; i++)
          l_28[i] = &g_11;
        g_4[p_13.f1] =
            ((*g_10) = (safe_mod_func_int16_t_s_s(
                 g_4[p_13.f1], (safe_mul_func_uint16_t_u_u(
                                   (&g_4[p_13.f1] != &g_11), g_5[1])))));
        return (*p_15);
      }
      for (p_13.f1 = 0; (p_13.f1 > (-25));
           p_13.f1 = safe_sub_func_int16_t_s_s(p_13.f1, 5)) {
        (*g_32) = g_31;
      }
    }
  }
  for (g_31.f0 = 0; (g_31.f0 <= 9); ++g_31.f0) {
    uint32_t l_35 = 0xCCF58D91L;
    int32_t *l_37[3];
    int i;
    for (i = 0; i < 3; i++)
      l_37[i] = (void *)0;
    p_13.f1 = l_35;
  }
  return (*p_15);
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_4[i];
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_5[i];
  }
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  csmith_sink_ = g_16.f0;
  csmith_sink_ = g_16.f1;
  csmith_sink_ = g_31.f0;
  csmith_sink_ = g_31.f1;
  csmith_sink_ = g_31.f2;
  csmith_sink_ = g_39.f0.f0.f0;
  csmith_sink_ = g_39.f0.f0.f1;
  csmith_sink_ = g_39.f0.f1;
  csmith_sink_ = g_39.f1.f0;
  csmith_sink_ = g_39.f1.f1;
  csmith_sink_ = g_44.f0.f0.f0;
  csmith_sink_ = g_44.f0.f0.f1;
  csmith_sink_ = g_44.f0.f1;
  csmith_sink_ = g_44.f1.f0;
  csmith_sink_ = g_44.f1.f1;
  platform_main_end(0, 0);
  return 0;
}
