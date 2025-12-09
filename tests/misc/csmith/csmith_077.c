// Options:   --seed 100077 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_077.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint8_t f0;
  volatile uint8_t f1;
};

static uint64_t g_2[3][1] = {
    {0xFDA0E60F951FE77DLL}, {0xFDA0E60F951FE77DLL}, {0xFDA0E60F951FE77DLL}};
static int32_t g_9 = 5L;
static int32_t *volatile g_8 = &g_9;
static int32_t *volatile *volatile g_12[3][1] = {{&g_8}, {&g_8}, {&g_8}};
static int16_t g_15 = (-2L);
static int32_t *volatile g_19 = (void *)0;
static int32_t *volatile g_20 = &g_9;
static union U0 g_22 = {1UL};
static union U0 *g_24 = (void *)0;
static union U0 **volatile g_23 = &g_24;
static int32_t *volatile *volatile *g_42 = &g_12[2][0];
static int32_t g_44 = 0x7A8360E5L;

static uint16_t func_1(void);
static int32_t func_4(int32_t p_5, int32_t p_6);

static uint16_t func_1(void) {
  uint8_t l_16 = 0x1AL;
  union U0 *l_21 = &g_22;
  uint8_t l_45 = 0x14L;
  int64_t l_51[2];
  int8_t l_52 = 0x9CL;
  int32_t l_53 = 0xB38BA701L;
  int16_t l_54[3][1];
  uint8_t l_56 = 1UL;
  uint64_t l_59 = 0x23EAFAF4B0596E72LL;
  int i, j;
  for (i = 0; i < 2; i++)
    l_51[i] = 2L;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_54[i][j] = 0xB77DL;
  }
  if ((g_2[0][0] = (-7L))) {
    uint32_t l_3 = 0x4210E164L;
    int32_t l_49[2];
    int i;
    for (i = 0; i < 2; i++)
      l_49[i] = (-2L);
  lbl_25:
    if ((l_3, (-5L))) {
      int8_t l_7 = 0xFBL;
      if (((func_4(g_2[0][0], l_7), 0x14L) > g_2[0][0])) {
        return g_15;
      } else {
        int16_t *l_18 = &g_15;
        (*g_20) =
            (l_16 & (((+((*l_18) = l_3)) ^ (((l_3 & g_9) ^ g_2[2][0]) ||
                                            l_16)) != 0xC43CC9F196E6C8CALL));
        return l_16;
      }
    } else {
      (*g_23) = l_21;
      if (g_9)
        goto lbl_25;
    }
    if ((safe_rshift_func_int8_t_s_u(
            (safe_lshift_func_int16_t_s_u(
                (safe_mul_func_uint8_t_u_u(
                    (safe_add_func_int16_t_s_s(((&g_24 != (void *)0) ^ g_9),
                                               l_3)),
                    l_3)),
                g_2[1][0])),
            l_3))) {
      int32_t *l_40[4][2] = {
          {&g_9, &g_9}, {&g_9, &g_9}, {&g_9, &g_9}, {&g_9, &g_9}};
      int32_t *const *l_39 = &l_40[3][1];
      int32_t *volatile *volatile **l_41[3];
      int i, j;
      for (i = 0; i < 3; i++)
        l_41[i] = (void *)0;
      for (g_9 = 0; (g_9 == 14); g_9++) {
        int32_t *l_37[3];
        int32_t *const *l_36 = &l_37[1];
        int32_t *const **l_38 = &l_36;
        int i;
        for (i = 0; i < 3; i++)
          l_37[i] = (void *)0;
        l_39 = ((*l_38) = l_36);
      }
      g_42 = &g_12[2][0];
    } else {
      int64_t l_48 = 0x2D4AD4463028EC7DLL;
      int32_t l_50 = 0x35EB13E2L;
      int32_t l_55[3];
      int i;
      for (i = 0; i < 3; i++)
        l_55[i] = 0L;
      for (g_9 = 0; (g_9 <= 0); g_9 += 1) {
        int32_t *l_43[2];
        int i;
        for (i = 0; i < 2; i++)
          l_43[i] = &g_44;
        --l_45;
        ++l_56;
      }
    }
  } else {
    (***g_42) = l_59;
  }
  return g_15;
}

static int32_t func_4(int32_t p_5, int32_t p_6) {
  int32_t *volatile *l_10 = (void *)0;
  int32_t *volatile *l_11 = (void *)0;
  int32_t *volatile *l_13 = &g_8;
  uint32_t l_14 = 8UL;
  (*l_13) = g_8;
  return l_14;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_9;
  csmith_sink_ = g_15;
  csmith_sink_ = g_22.f0;
  csmith_sink_ = g_22.f1;
  csmith_sink_ = g_44;
  platform_main_end(0, 0);
  return 0;
}
