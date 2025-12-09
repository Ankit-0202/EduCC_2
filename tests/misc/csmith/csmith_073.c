// Options:   --seed 100073 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_073.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile uint32_t f0;
  uint16_t f1;
};

struct S1 {
  const volatile int16_t f0;
  uint32_t f1;
  int16_t f2;
};

struct S2 {
  int32_t f0;
  uint64_t f1;
};

struct S3 {
  const volatile int8_t f0;
};

struct S4 {
  const struct S3 f0;
  struct S1 f1;
};

static const int64_t g_2 = 0x6C74AA0D72276B87LL;
static struct S4 g_12 = {{-1L}, {0L, 18446744073709551612UL, 0xACD7L}};
static struct S4 *g_11 = &g_12;
static int32_t g_16 = 2L;
static int32_t *g_20[1][3] = {{(void *)0, (void *)0, (void *)0}};
static int32_t **volatile g_19 = &g_20[0][2];
static int32_t *volatile g_23 = (void *)0;
static struct S2 g_33 = {1L, 0x12FD89D6848298BBLL};
static int32_t *volatile g_36[3][4] = {{&g_16, &g_16, &g_16, &g_16},
                                       {&g_16, &g_16, &g_16, &g_16},
                                       {&g_16, &g_16, &g_16, &g_16}};
static int32_t g_38 = (-1L);
static int32_t *volatile g_37[1] = {&g_38};
static int32_t *volatile g_39 = &g_38;
static volatile uint32_t g_54[1] = {0UL};
static struct S4 **g_59 = &g_11;
static struct S4 ***volatile g_58 = &g_59;
static volatile struct S0 g_69 = {8UL, 65535UL};

static const uint32_t func_1(void);
static struct S4 *func_3(int32_t p_4, uint8_t p_5, uint64_t p_6,
                         struct S4 *p_7);

static const uint32_t func_1(void) {
  uint64_t l_21 = 0x43E5EC35211521FALL;
  int32_t l_41 = (-1L);
  int32_t l_44 = 0L;
  int32_t l_46 = 0x18CC907FL;
  int32_t l_47[4];
  int32_t l_49 = 0x8BB1B5B3L;
  struct S4 **l_57 = &g_11;
  uint32_t l_66 = 4294967295UL;
  volatile struct S0 *l_70 = &g_69;
  int i;
  for (i = 0; i < 4; i++)
    l_47[i] = 9L;
  if ((0xC541L > g_2)) {
    int8_t l_22 = 0xCAL;
    int32_t l_48 = 0xBD053A65L;
    int32_t l_50 = 5L;
    int32_t l_51 = 6L;
    int32_t l_52 = 0L;
    g_11 = func_3((g_2, ((+g_2) != (safe_rshift_func_int16_t_s_s(g_2, 1)))),
                  g_2, g_2, g_11);
    if (l_21) {
      int32_t *l_24 = &g_16;
      int32_t l_45 = 0xAB92A1DDL;
      int32_t l_53 = 2L;
      (*l_24) &= l_22;
      for (g_16 = 25; (g_16 >= (-23));
           g_16 = safe_sub_func_int64_t_s_s(g_16, 7)) {
        const uint64_t l_34 = 0x93CC9D6C8400B8F3LL;
        uint64_t *l_35 = &g_33.f1;
        int32_t *l_40 = &g_38;
        int32_t *l_42 = &l_41;
        int32_t *l_43[1];
        int i;
        for (i = 0; i < 1; i++)
          l_43[i] = &l_41;
        (*g_39) = (safe_mod_func_uint8_t_u_u(
            (safe_add_func_uint32_t_u_u(
                ((*l_24) > (((*l_35) = ((safe_mod_func_uint64_t_u_u(
                                            (g_33, (l_34 == 255UL)),
                                            0xBF12959AF2C67A95LL)),
                                        g_12.f1.f1)) ||
                            l_22)),
                0x726F2C0EL)),
            l_34));
        g_54[0]++;
      }
    } else {
      (*g_58) = l_57;
    }
  } else {
    uint64_t l_62[4];
    int i;
    for (i = 0; i < 4; i++)
      l_62[i] = 1UL;
    for (g_33.f0 = (-30); (g_33.f0 <= 6);
         g_33.f0 = safe_add_func_uint8_t_u_u(g_33.f0, 6)) {
      int32_t *l_63 = &l_46;
      int32_t *l_64 = (void *)0;
      int32_t *l_65[4][2] = {
          {&l_46, &l_46}, {&l_46, &l_46}, {&l_46, &l_46}, {&l_46, &l_46}};
      int i, j;
      if (l_62[2])
        break;
      l_66++;
    }
  }
  (*l_70) = g_69;
  return g_2;
}

static struct S4 *func_3(int32_t p_4, uint8_t p_5, uint64_t p_6,
                         struct S4 *p_7) {
  int32_t *const l_17 = &g_16;
  for (p_5 = 23; (p_5 != 31); p_5 = safe_add_func_int8_t_s_s(p_5, 8)) {
    int32_t *l_15 = &g_16;
    int32_t **l_18 = (void *)0;
    (*l_15) |= (&g_12 != (g_12.f1, (void *)0));
    (*g_19) = l_17;
  }
  return &g_12;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_12.f0.f0;
  csmith_sink_ = g_12.f1.f0;
  csmith_sink_ = g_12.f1.f1;
  csmith_sink_ = g_12.f1.f2;
  csmith_sink_ = g_16;
  csmith_sink_ = g_33.f0;
  csmith_sink_ = g_33.f1;
  csmith_sink_ = g_38;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_54[i];
  }
  csmith_sink_ = g_69.f0;
  csmith_sink_ = g_69.f1;
  platform_main_end(0, 0);
  return 0;
}
