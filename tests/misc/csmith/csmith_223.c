// Options:   --seed 300223 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_223.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_4 = 0xA35F394AL;
static const uint32_t g_9[1][1] = {{0x76715F0EL}};
static uint16_t g_32 = 0xA912L;
static uint64_t g_35 = 8UL;
static int32_t g_40[1][2] = {{4L, 4L}};
static uint8_t g_54[1][3] = {{3UL, 3UL, 3UL}};
static const int32_t *g_73 = (void *)0;
static const int32_t *volatile *g_72 = &g_73;
static int16_t g_76 = 0x7EF9L;
static volatile int16_t *volatile *g_77 = (void *)0;

static int8_t func_1(void);
static uint8_t func_12(uint8_t p_13, uint64_t p_14, int32_t p_15, int8_t p_16,
                       int32_t p_17);
static uint8_t func_18(uint32_t p_19, int8_t p_20, int8_t p_21, int16_t p_22,
                       int32_t p_23);

static int8_t func_1(void) {
  uint16_t l_24[1];
  int16_t *l_75 = &g_76;
  volatile int16_t *volatile *l_78 = (void *)0;
  int32_t *l_80 = &g_40[0][0];
  int i;
  for (i = 0; i < 1; i++)
    l_24[i] = 0x278CL;
  if ((((safe_mul_func_int8_t_s_s(
            g_4,
            (safe_mul_func_int16_t_s_s(
                ((*l_75) =
                     ((safe_sub_func_int64_t_s_s(
                          g_9[0][0],
                          ((safe_add_func_int16_t_s_s(
                               (func_12(func_18(g_9[0][0], l_24[0], g_9[0][0],
                                                l_24[0], l_24[0]),
                                        l_24[0], g_9[0][0], g_9[0][0],
                                        g_9[0][0]) == l_24[0]),
                               g_9[0][0])),
                           g_9[0][0]))) |
                      1L)),
                g_9[0][0])))) <= (-1L)) |
       g_9[0][0])) {
    return g_35;
  } else {
    uint8_t l_79 = 1UL;
    for (g_76 = 0; (g_76 >= 0); g_76 -= 1) {
      if (l_24[0])
        break;
      l_78 = g_77;
    }
    if (l_79) {
      (*g_72) = (*g_72);
    } else {
      (*g_72) = l_80;
    }
  }
  return (*l_80);
}

static uint8_t func_12(uint8_t p_13, uint64_t p_14, int32_t p_15, int8_t p_16,
                       int32_t p_17) {
  int64_t l_59 = 8L;
  const int32_t *const l_62 = (void *)0;
  if (((((p_15 ==
          (safe_rshift_func_uint8_t_u_s(
              ((((l_59 ||
                  (((safe_mod_func_uint32_t_u_u(l_59, p_15)) ^ l_59), p_15)),
                 l_59) >= p_13) != l_59),
              3))),
         &g_40[0][1]) == l_62) >= g_40[0][0])) {
    int32_t *l_63[2][1];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_63[i][j] = &g_40[0][0];
    }
    p_15 &= p_13;
  } else {
    for (g_35 = 0; (g_35 == 8); g_35++) {
      int32_t *l_66 = (void *)0;
      int32_t **l_67 = &l_66;
      if (p_16)
        break;
      (*l_67) = l_66;
    }
  }
  for (g_35 = 0; (g_35 > 50); ++g_35) {
    int32_t **l_71 = (void *)0;
    int32_t ***l_70 = &l_71;
    int32_t *l_74 = &g_40[0][0];
    (*l_74) = (((*l_70) = (void *)0) != g_72);
  }
  return p_13;
}

static uint8_t func_18(uint32_t p_19, int8_t p_20, int8_t p_21, int16_t p_22,
                       int32_t p_23) {
  int64_t l_47[2];
  int32_t l_50 = 0xA5CF69BAL;
  int64_t l_51 = (-1L);
  int i;
  for (i = 0; i < 2; i++)
    l_47[i] = 0x3F36FC75DFCC9F71LL;
  for (p_23 = 0; (p_23 < (-2)); p_23 = safe_sub_func_uint32_t_u_u(p_23, 1)) {
    if (p_23)
      break;
  }
  for (p_22 = 14; (p_22 <= (-9)); p_22--) {
    uint16_t *l_31 = &g_32;
    int32_t l_48 = (-1L);
    int32_t l_52 = 0x8AF769BFL;
    int32_t l_53 = 0x1A25D001L;
    if (((safe_div_func_int32_t_s_s((p_22 >= (g_35 = ((*l_31)--))), p_22)) |
         (safe_mod_func_int64_t_s_s((p_23 || p_23), p_20)))) {
      return p_21;
    } else {
      int16_t l_38 = 0L;
      int32_t *l_39 = &g_40[0][0];
      int32_t *l_41 = (void *)0;
      int32_t *l_42 = &g_40[0][0];
      int32_t *l_43 = &g_40[0][1];
      int32_t *l_44 = (void *)0;
      int32_t *l_45 = &g_40[0][0];
      int32_t *l_46[3][1];
      int16_t l_49 = 0xE068L;
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_46[i][j] = &g_40[0][0];
      }
      if (l_38)
        break;
      g_54[0][2]++;
    }
    if (p_19)
      continue;
  }
  return p_19;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_9[i][j];
    }
  }
  csmith_sink_ = g_32;
  csmith_sink_ = g_35;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_40[i][j];
    }
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_54[i][j];
    }
  }
  csmith_sink_ = g_76;
  platform_main_end(0, 0);
  return 0;
}
