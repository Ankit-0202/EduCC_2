// Options:   --seed 300292 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_292.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  const uint32_t f0;
};

static int32_t g_2 = 1L;
static uint32_t g_28[1] = {0UL};
static union U0 g_32 = {0xAF9F7C8BL};
static volatile uint32_t g_44 = 18446744073709551611UL;
static int32_t g_55 = 3L;
static uint64_t g_65 = 1UL;
static uint32_t g_68[1][1] = {{1UL}};
static int32_t g_71 = 0x4C7C9A7BL;
static int32_t *volatile g_70[3] = {&g_71, &g_71, &g_71};

static int64_t func_1(void);
static int32_t func_6(int64_t p_7, union U0 p_8);
static const int64_t func_13(int8_t p_14, union U0 p_15, int8_t p_16);

static int64_t func_1(void) {
  uint8_t l_5[2][1];
  union U0 l_9 = {18446744073709551614UL};
  int32_t l_69 = 0x7FC3FE76L;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_5[i][j] = 8UL;
  }
  for (g_2 = (-19); (g_2 != (-28)); g_2 = safe_sub_func_int16_t_s_s(g_2, 3)) {
    return l_5[0][0];
  }
  if (func_6(g_2, l_9)) {
    int32_t *const l_47 = &g_2;
    int32_t **l_48 = (void *)0;
    int32_t *l_50 = &g_2;
    int32_t **l_49[2][1];
    int32_t **l_51[1][3];
    int32_t **l_52 = &l_50;
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_49[i][j] = &l_50;
    }
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_51[i][j] = &l_50;
    }
    (*l_52) = l_47;
    for (g_2 = 0; (g_2 != 14); g_2 = safe_add_func_uint64_t_u_u(g_2, 7)) {
      g_55 ^= g_32.f0;
      if (g_2)
        break;
    }
  } else {
    uint8_t l_66 = 0x6CL;
    uint64_t *l_67 = (void *)0;
    int32_t *l_72 = &g_71;
    (*l_72) &=
        ((safe_sub_func_uint16_t_u_u(
             ((g_68[0][0] = (((safe_div_func_int32_t_s_s(
                                  ((safe_mod_func_int8_t_s_s(
                                       ((!g_55) && 0xA8ACL),
                                       (g_65 ^= ((safe_div_func_int16_t_s_s(
                                                     0x12A7L, l_5[0][0])) ^
                                                 g_28[0])))) != l_5[0][0]),
                                  4294967287UL)),
                              l_66) != l_9.f0)) > g_2),
             0x481DL)) |
         l_69);
  }
  return l_5[1][0];
}

static int32_t func_6(int64_t p_7, union U0 p_8) {
  uint32_t *l_27 = &g_28[0];
  uint64_t l_31 = 7UL;
  uint32_t l_33 = 0x3691F6F4L;
  const int32_t l_38 = 0L;
  int32_t l_39 = 0L;
  int32_t *l_40 = &g_2;
  int32_t *l_41 = &l_39;
  int32_t *l_42 = &g_2;
  int32_t *l_43[1][2];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_43[i][j] = &l_39;
  }
  l_39 ^= (+(safe_mul_func_int16_t_s_s(
      (func_13(((safe_mul_func_int16_t_s_s(
                    (((safe_mul_func_uint16_t_u_u(
                          (safe_mul_func_int16_t_s_s(
                              ((safe_sub_func_int32_t_s_s(p_7, (++(*l_27)))) <
                               4294967289UL),
                              g_2)),
                          g_2)) ^
                      0L) &&
                     l_31),
                    g_2)) != 0L),
               g_32, l_33) != l_38),
      0UL)));
  --g_44;
  return g_28[0];
}

static const int64_t func_13(int8_t p_14, union U0 p_15, int8_t p_16) {
  int32_t *l_35 = &g_2;
  int32_t **l_34 = &l_35;
  (*l_34) = (void *)0;
  for (g_2 = (-18); (g_2 == 10); g_2 = safe_add_func_uint64_t_u_u(g_2, 5)) {
    if (p_15.f0)
      break;
    if (g_28[0])
      continue;
  }
  return p_14;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_28[i];
  }
  csmith_sink_ = g_32.f0;
  csmith_sink_ = g_44;
  csmith_sink_ = g_55;
  csmith_sink_ = g_65;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_68[i][j];
    }
  }
  csmith_sink_ = g_71;
  platform_main_end(0, 0);
  return 0;
}
