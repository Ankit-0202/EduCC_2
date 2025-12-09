// Options:   --seed 100025 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_025.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint16_t g_2 = 0x61F9L;
static int32_t g_4 = 1L;
static int32_t g_6 = 1L;
static int32_t *volatile g_5 = &g_6;
static int64_t g_15 = 3L;
static uint16_t g_19[4][2] = {{0UL, 0UL}, {0UL, 0UL}, {0UL, 0UL}, {0UL, 0UL}};
static int32_t *g_29 = &g_4;
static int32_t **volatile g_28[4][1] = {{&g_29}, {&g_29}, {&g_29}, {&g_29}};
static uint16_t *g_47 = &g_2;
static uint16_t **g_46 = &g_47;
static uint16_t ***volatile g_45[1][3] = {{&g_46, &g_46, &g_46}};
static uint16_t ***volatile g_48 = &g_46;
static const int32_t g_56 = 0L;
static const int32_t *g_57[3] = {(void *)0, (void *)0, (void *)0};

static int32_t func_1(void);
static const int32_t *func_7(int32_t *p_8, const int16_t p_9,
                             const uint64_t p_10, uint64_t p_11);

static int32_t func_1(void) {
  int32_t *l_3 = &g_4;
  int64_t *l_14 = &g_15;
  int32_t l_16 = 0x2DB8E964L;
  uint16_t *l_17 = &g_2;
  uint16_t *l_18 = &g_19[1][1];
  const int32_t *l_55 = &g_56;
  const int32_t **l_54[4] = {&l_55, &l_55, &l_55, &l_55};
  int i;
  (*g_5) |= ((*l_3) = g_2);
  (*g_29) =
      ((g_57[0] = func_7(
            &g_4,
            (((*l_3),
              (((*l_18) =
                    ((*l_17) = ((safe_div_func_int64_t_s_s(
                                    ((*l_14) = ((*l_3) = 0xCF4C59CDC345FE46LL)),
                                    l_16)),
                                (*l_3)))) >= 65526UL)) < g_6),
            l_16, g_6)) == &g_56);
  return (*l_3);
}

static const int32_t *func_7(int32_t *p_8, const int16_t p_9,
                             const uint64_t p_10, uint64_t p_11) {
  uint16_t *l_26 = &g_2;
  const int32_t l_27 = 0xACB6D64BL;
  int32_t l_33 = (-1L);
  int32_t l_34 = 0x033631AFL;
  int32_t l_35 = 0x5379A1D1L;
  int32_t l_36 = (-1L);
  int32_t l_37 = (-2L);
  int32_t l_38 = 0x05F67326L;
  int32_t l_40[2][3] = {{1L, 1L, (-5L)}, {1L, 1L, (-5L)}};
  int i, j;
  if (((safe_mod_func_uint16_t_u_u(
           ((safe_add_func_int32_t_s_s(
                ((*p_8) &=
                 ((((((safe_mul_func_int16_t_s_s((l_26 != (void *)0),
                                                 ((*g_5) & l_27))),
                      l_27) ||
                     l_27) == g_19[1][1]) > 0x4D8142C78EF8A6EBLL) < g_2)),
                1UL)),
            l_27),
           l_27)),
       (*p_8))) {
    int32_t *l_30 = &g_4;
    l_30 = &g_4;
    return p_8;
  } else {
    int32_t *l_31 = &g_4;
    int32_t *l_32[4] = {&g_6, &g_6, &g_6, &g_6};
    int8_t l_39[1];
    uint64_t l_41 = 1UL;
    int i;
    for (i = 0; i < 1; i++)
      l_39[i] = 0x02L;
    l_41++;
    if ((*l_31)) {
      uint16_t **l_44 = &l_26;
      (*g_48) = l_44;
      for (l_38 = (-19); (l_38 <= (-18));
           l_38 = safe_add_func_uint8_t_u_u(l_38, 1)) {
        if ((*g_5))
          break;
      }
    } else {
      uint16_t l_51 = 0UL;
      --l_51;
    }
  }
  return p_8;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_4;
  csmith_sink_ = g_6;
  csmith_sink_ = g_15;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_19[i][j];
    }
  }
  csmith_sink_ = g_56;
  platform_main_end(0, 0);
  return 0;
}
