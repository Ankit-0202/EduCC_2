// Options:   --seed 300241 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_241.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint32_t f0;
  int8_t f1;
};

union U3 {
  const int16_t f0;
  volatile uint16_t f1;
};

static volatile int16_t g_22[3] = {0x4361L, 0x4361L, 0x4361L};
static uint16_t g_23 = 65535UL;
static volatile union U3 g_26[1][3] = {{{9L}, {9L}, {9L}}};
static uint8_t g_28[1][2] = {{249UL, 249UL}};
static uint8_t *g_27[3] = {&g_28[0][1], &g_28[0][1], &g_28[0][1]};
static int32_t g_31[3][1] = {{0L}, {0L}, {0L}};
static int32_t *g_32 = (void *)0;
static int32_t g_34 = 0L;
static int64_t g_78 = 0x0B4FC89CDC83B1EFLL;
static int32_t **const volatile g_84 = &g_32;

static int32_t func_1(void);
static int32_t *func_2(uint8_t p_3, int32_t *p_4, int32_t *const p_5);
static uint8_t func_6(const uint8_t p_7, int8_t p_8, int16_t p_9, uint8_t p_10,
                      int64_t p_11);

static int32_t func_1(void) {
  uint8_t l_17[2][2];
  uint8_t *l_18[3][2];
  int32_t l_19 = 0x5BC42206L;
  int32_t l_24 = 0xE7B1B0CAL;
  int8_t l_25 = 0L;
  int32_t *const l_33 = &g_34;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_17[i][j] = 248UL;
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++)
      l_18[i][j] = &l_17[1][1];
  }
  (*g_84) = func_2(func_6((safe_mod_func_int32_t_s_s(
                              (+(((safe_div_func_uint8_t_u_u(
                                      (((l_19 = (0xFDC8L != l_17[1][1])) >
                                        (safe_mul_func_int16_t_s_s(
                                            (g_22[1] != g_23), l_24))) > l_24),
                                      l_24)),
                                  g_22[0]) ^
                                 g_23)),
                              l_17[1][0])),
                          l_24, l_25, g_23, l_17[1][1]),
                   g_32, l_33);
  return (*l_33);
}

static int32_t *func_2(uint8_t p_3, int32_t *p_4, int32_t *const p_5) {
  uint8_t **l_37 = &g_27[2];
  uint32_t l_38 = 18446744073709551615UL;
  int32_t l_39 = 0x8393131EL;
  int32_t l_41 = 1L;
  int32_t l_42 = (-1L);
  int32_t l_43 = 0x04E266BCL;
  int32_t l_45 = 5L;
  int32_t l_47 = (-6L);
  int32_t l_48 = (-7L);
  int32_t l_49 = 0xAF70C77BL;
  int32_t l_50 = 0xD4896031L;
  int32_t l_51 = 0x0074354AL;
  int32_t l_52 = 0x6E73BF60L;
  int32_t l_53 = 0L;
  int32_t l_54 = 9L;
  int32_t l_55[1][2];
  union U0 l_70 = {0x2D9EA3BDL};
  int8_t l_79 = 0x24L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_55[i][j] = 0xDD0D489CL;
  }
  if ((g_22[2] > (((l_38 |= (((safe_lshift_func_int8_t_s_s((l_37 != (void *)0),
                                                           g_28[0][1])) &&
                              p_3) ||
                             g_31[2][0])),
                   p_3) > 0x9978L))) {
    int32_t *l_40[3][1];
    int32_t l_44 = 0L;
    int8_t l_46 = 0x2CL;
    uint16_t l_56[2];
    int16_t l_62 = 0xB232L;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_40[i][j] = &g_34;
    }
    for (i = 0; i < 2; i++)
      l_56[i] = 65528UL;
    l_56[1]++;
    for (l_54 = 0; (l_54 == 28); ++l_54) {
      int64_t l_61[3][1];
      uint32_t l_63 = 18446744073709551615UL;
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_61[i][j] = 0xFF4F296794CA015BLL;
      }
      ++l_63;
      (*p_5) = 0xD4ABAF97L;
    }
  } else {
    for (l_39 = 0; (l_39 != (-5)); l_39 = safe_sub_func_int8_t_s_s(l_39, 5)) {
      l_41 |= ((*p_5) = l_47);
    }
  }
  if (((p_3 < ((**l_37) = ((l_70, (void *)0) != l_37))) != p_3)) {
    return &g_31[0][0];
  } else {
    int64_t l_74 = 0x73AEC32A7D5B95D3LL;
    int32_t l_75 = 1L;
    int32_t l_76 = 0x192FD70EL;
    int32_t l_77[2][2];
    uint8_t l_81 = 0UL;
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_77[i][j] = 0x249C3678L;
    }
    for (l_54 = 2; (l_54 >= 0); l_54 -= 1) {
      int32_t *l_71 = &l_53;
      int32_t *l_72 = &l_55[0][1];
      int32_t *l_73[1];
      int8_t l_80 = 0xDCL;
      int i;
      for (i = 0; i < 1; i++)
        l_73[i] = &g_34;
      if ((*p_5))
        break;
      ++l_81;
    }
  }
  return &g_31[2][0];
}

static uint8_t func_6(const uint8_t p_7, int8_t p_8, int16_t p_9, uint8_t p_10,
                      int64_t p_11) {
  uint8_t **l_29 = &g_27[2];
  int32_t *l_30 = &g_31[2][0];
  (*l_30) = ((g_26[0][1], ((*l_29) = g_27[1])) != (void *)0);
  return p_10;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_22[i];
  }
  csmith_sink_ = g_23;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_28[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_31[i][j];
    }
  }
  csmith_sink_ = g_34;
  csmith_sink_ = g_78;
  platform_main_end(0, 0);
  return 0;
}
