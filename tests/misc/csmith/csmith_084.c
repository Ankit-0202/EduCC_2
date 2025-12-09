// Options:   --seed 100084 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_084.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint64_t f0;
  uint32_t f1;
};

struct S2 {
  const uint32_t f0;
  const int16_t f1;
};

union U5 {
  struct S1 f0;
  volatile uint32_t f1;
};

static volatile int32_t g_2 = 0L;
static volatile int32_t g_3 = 0x4BF8F0AAL;
static int32_t g_4 = 0xF7FBF212L;
static int32_t g_23 = 0xFA4C8210L;
static int32_t g_26[2][2] = {{0x37D6C505L, 0x37D6C505L},
                             {0x37D6C505L, 0x37D6C505L}};
static int32_t ***volatile g_38 = (void *)0;
static volatile union U5 g_45 = {{0x20245597EEDF6679LL, 4294967288UL}};
static int32_t *g_52 = &g_26[1][0];
static int32_t **volatile g_51 = &g_52;
static struct S1 g_54 = {18446744073709551611UL, 0x64B91BF5L};
static struct S1 *g_55 = (void *)0;
static struct S1 *g_57 = &g_54;
static struct S1 **volatile g_56[1][4] = {{&g_57, &g_57, &g_57, &g_57}};

static int64_t func_1(void);
static uint8_t func_11(int8_t p_12, uint64_t p_13, struct S2 p_14);

static int64_t func_1(void) {
  int8_t l_7 = (-8L);
  uint32_t l_41 = 3UL;
  int32_t *l_49 = &g_23;
  struct S1 *l_59 = &g_54;
  for (g_4 = 0; (g_4 != 9); ++g_4) {
    int64_t l_17 = 0xA1E1C5A3D7F19125LL;
    int32_t l_29 = (-1L);
    uint32_t l_30 = 0x52601C8DL;
    struct S1 *l_53[2];
    struct S1 **l_58[2][4] = {{&l_53[1], &l_53[1], &l_53[1], &l_53[1]},
                              {&l_53[1], &l_53[1], &l_53[1], &l_53[1]}};
    int i, j;
    for (i = 0; i < 2; i++)
      l_53[i] = &g_54;
    if (l_7) {
      int8_t l_10 = 0L;
      struct S2 l_18 = {6UL, 0x46B4L};
      int32_t l_42 = (-1L);
      if ((((safe_rshift_func_uint16_t_u_u(l_10, 10)),
            func_11((l_10 == (0x0A9B27FAL == l_17)), g_4, l_18)) != g_2)) {
        int32_t *l_28[4];
        int i;
        for (i = 0; i < 4; i++)
          l_28[i] = &g_26[0][1];
        ++l_30;
      } else {
        int32_t *l_34 = &g_26[0][1];
        int32_t **l_33[3];
        int32_t ***l_35 = (void *)0;
        int32_t ***l_36 = &l_33[0];
        int32_t ***l_37 = (void *)0;
        int32_t **l_40 = &l_34;
        int32_t ***l_39 = &l_40;
        int i;
        for (i = 0; i < 3; i++)
          l_33[i] = &l_34;
        (*l_39) = ((*l_36) = l_33[0]);
        l_42 ^= (2L == (l_18, (l_41 ^= (***l_39))));
      }
      for (l_7 = 0; (l_7 < (-30)); --l_7) {
        int32_t *l_48 = &l_42;
        int32_t **l_50 = &l_49;
        (*l_48) &=
            (g_45, (safe_sub_func_uint32_t_u_u(
                       ((((((0x3A798BE49C906054LL || 0x53B72B46FAC5ADF6LL),
                            g_45.f0.f1) ||
                           l_29) ||
                          l_18.f0) == 6UL) > (-3L)),
                       g_26[0][1])));
        (*g_51) = ((*l_50) = l_49);
      }
    } else {
      if ((*l_49))
        break;
    }
    l_59 = (g_55 = l_53[1]);
  }
  if (((*g_52) < (*l_49))) {
    (*g_52) ^= 0x6E60E451L;
  } else {
    return g_2;
  }
  return g_45.f0.f0;
}

static uint8_t func_11(int8_t p_12, uint64_t p_13, struct S2 p_14) {
  uint32_t l_21 = 0UL;
  int32_t *l_22 = &g_23;
  uint8_t l_24 = 0x63L;
  int32_t *l_25 = &g_26[0][1];
  int32_t l_27 = 0xC98AAC1EL;
  l_27 |=
      (((*l_25) = (safe_div_func_int32_t_s_s(
            ((*l_22) = l_21), ((((void *)0 != l_22) <= l_21), l_24)))) >= p_12);
  return p_14.f1;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_23;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_26[i][j];
    }
  }
  csmith_sink_ = g_45.f0.f0;
  csmith_sink_ = g_45.f0.f1;
  csmith_sink_ = g_54.f0;
  csmith_sink_ = g_54.f1;
  platform_main_end(0, 0);
  return 0;
}
