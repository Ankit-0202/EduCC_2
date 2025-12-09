// Options:   --seed 300203 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_203.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3[1][3] = {{(-7L), (-7L), (-7L)}};
static int32_t g_4 = 0x2A276893L;
static int64_t g_10[1] = {(-1L)};
static int32_t g_31 = 0x18BA70A1L;
static int32_t *volatile g_30[2][2] = {{&g_31, &g_31}, {&g_31, &g_31}};
static int32_t *volatile g_32 = &g_31;
static uint64_t g_36 = 4UL;
static int32_t g_64 = 1L;
static int32_t g_66 = 0xC41D5C68L;
static int32_t *const *g_68 = (void *)0;

static uint32_t func_1(void);
static const int8_t func_5(int32_t p_6);
static int16_t func_12(const int64_t *p_13, int64_t *p_14, int16_t p_15,
                       int64_t *p_16);

static uint32_t func_1(void) {
  uint32_t l_2[1];
  int32_t l_69[3];
  int i;
  for (i = 0; i < 1; i++)
    l_2[i] = 4294967293UL;
  for (i = 0; i < 3; i++)
    l_69[i] = (-8L);
  for (g_4 = 0; (g_4 >= 0); g_4 -= 1) {
    int i;
    l_69[1] =
        (func_5(l_2[g_4]) | (((((g_68 == g_68) ^ g_4) != l_2[0]), 1UL), 0x20L));
  }
  return g_66;
}

static const int8_t func_5(int32_t p_6) {
  int64_t *l_17[1][1];
  int32_t l_50[2];
  int32_t l_51 = (-5L);
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_17[i][j] = &g_10[0];
  }
  for (i = 0; i < 2; i++)
    l_50[i] = (-5L);
  if ((safe_div_func_int16_t_s_s(g_4, (p_6 || (g_3[0][0] || 0xECC2443AL))))) {
    int64_t *l_9[3];
    int32_t l_52 = (-8L);
    int32_t l_53 = 0x66AA6F69L;
    int32_t l_54 = 0x6FE6C8CEL;
    int32_t l_55 = 0L;
    uint16_t l_57 = 0x3243L;
    int32_t *l_60 = &l_54;
    int i;
    for (i = 0; i < 3; i++)
      l_9[i] = &g_10[0];
    if (((g_10[0] = p_6),
         (!(func_12(&g_10[0], l_17[0][0], g_4, &g_10[0]), p_6)))) {
      int32_t *l_43 = &g_31;
      int32_t *l_44 = &g_31;
      int32_t *l_45 = &g_31;
      int32_t *l_46 = &g_31;
      int32_t *l_47 = &g_31;
      int32_t *l_48 = (void *)0;
      int32_t *l_49[1][1];
      int32_t l_56 = 0x7F4FEF51L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_49[i][j] = &g_31;
      }
      ++l_57;
    } else {
      l_60 = &g_31;
    }
  } else {
    int32_t *l_67 = &g_31;
    for (g_31 = 0; (g_31 <= 0); g_31 += 1) {
      int32_t *l_61 = &l_50[1];
      int32_t *l_62 = (void *)0;
      int32_t *l_63 = &g_64;
      int32_t *l_65 = &g_66;
      (*l_65) = ((*l_63) = (4294967286UL ^
                            ((*l_61) = (((void *)0 != l_17[0][0]), 0L))));
    }
    (*l_67) = 0x48F203DAL;
  }
  return g_10[0];
}

static int16_t func_12(const int64_t *p_13, int64_t *p_14, int16_t p_15,
                       int64_t *p_16) {
  int32_t *l_18 = (void *)0;
  int64_t *l_19[2][2];
  int64_t **l_20 = &l_19[1][1];
  const int32_t l_21 = 0x24ADC9FEL;
  int32_t l_24 = 0L;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_19[i][j] = &g_10[0];
  }
  l_18 = l_18;
  if ((((((((((&g_10[0] != ((*l_20) = l_19[1][1])) ^ p_15) ^ 0x4498L),
            &g_3[0][0]) == l_18) |
          l_21) &
         p_15),
        g_10[0]) > 4L)) {
    int32_t *l_29 = &g_4;
    (*g_32) = (safe_add_func_uint8_t_u_u(
        l_24,
        ((safe_lshift_func_int16_t_s_u(p_15, 5)) != (l_29 != (void *)0))));
    return g_3[0][1];
  } else {
    uint64_t *l_35 = &g_36;
    int32_t l_37 = 0x8E576DBDL;
    int32_t **l_42[2];
    int i;
    for (i = 0; i < 2; i++)
      l_42[i] = &l_18;
    if (((l_37 &= (((*l_35) = (safe_lshift_func_int16_t_s_s(0x4153L, 12))),
                   (((0xC7L > g_3[0][0]) == 0x3439L), 0xB6EA4182L))),
         0xC3387DD7L)) {
      int32_t *l_38 = &g_4;
      int32_t **l_39 = &l_18;
      (*l_39) = l_38;
      g_31 |= (((0x4AEFL &&
                 ((safe_div_func_uint8_t_u_u(((void *)0 != l_42[0]), 0x58L)) &
                  p_15)) ^
                p_15) > g_3[0][0]);
    } else {
      return g_4;
    }
  }
  return p_15;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_4;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_10[i];
  }
  csmith_sink_ = g_31;
  csmith_sink_ = g_36;
  csmith_sink_ = g_64;
  csmith_sink_ = g_66;
  platform_main_end(0, 0);
  return 0;
}
