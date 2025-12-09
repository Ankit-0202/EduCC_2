// Options:   --seed 200137 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_137.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_7 = 0xCCE57BF5L;
static int32_t *g_6 = &g_7;
static int8_t g_15 = 0xD7L;
static int32_t g_17 = (-4L);
static uint32_t g_18 = 1UL;
static int32_t **g_24 = &g_6;
static int32_t ***volatile g_23 = &g_24;
static int8_t *g_29 = &g_15;
static uint16_t g_33 = 65530UL;
static int32_t **const volatile g_36[4][1] = {{&g_6}, {&g_6}, {&g_6}, {&g_6}};
static int32_t **volatile g_37 = &g_6;
static int32_t **volatile g_42 = &g_6;
static int32_t *volatile g_54[3] = {&g_7, &g_7, &g_7};
static int32_t *volatile g_55[1] = {(void *)0};

static const float func_1(void);
static int32_t *func_2(int32_t *p_3, uint64_t p_4, float p_5);

static const float func_1(void) {
  float l_8[3][2] = {{0xA.6DEEC5p-11, (-0x7.2p+1)},
                     {0xA.6DEEC5p-11, 0xA.6DEEC5p-11},
                     {(-0x7.2p+1), 0xA.6DEEC5p-11}};
  int32_t l_9[2];
  int i, j;
  for (i = 0; i < 2; i++)
    l_9[i] = 0x5166941FL;
  (*g_37) = func_2(g_6, (l_9[1] ^ l_9[1]), g_7);
  if ((safe_rshift_func_int8_t_s_s(((*g_29) < g_15), 2))) {
    int32_t *const l_40 = &g_7;
    int32_t **l_41[2];
    int i;
    for (i = 0; i < 2; i++)
      l_41[i] = &g_6;
    (*g_42) = l_40;
    for (g_15 = 0; (g_15 < (-18)); g_15 = safe_sub_func_int16_t_s_s(g_15, 5)) {
      uint8_t l_45 = 255UL;
      if (l_45)
        break;
      (*g_24) = (*g_37);
    }
  } else {
    int8_t *l_46 = &g_15;
    int32_t l_47 = 0L;
    const int32_t **const *l_53 = (void *)0;
    int32_t l_60 = 1L;
    for (g_17 = 1; (g_17 >= 0); g_17 -= 1) {
      int32_t *l_56 = &g_7;
      int i;
      (*g_24) = &l_9[g_17];
      (*l_56) ^=
          (l_46 !=
           (((l_47 >=
              (safe_mul_func_int8_t_s_s(
                  ((!(safe_lshift_func_uint16_t_u_u(
                       (((l_53 != (void *)0) ^ 18446744073709551615UL) < g_17),
                       8))) < l_9[g_17]),
                  (*g_29)))) ^
             (**g_24)),
            (void *)0));
    }
    for (g_7 = 1; (g_7 >= 0); g_7 -= 1) {
      int32_t l_57 = 0x40931BC1L;
      int32_t *l_58 = &l_47;
      int32_t *l_59[3];
      uint64_t l_61 = 0UL;
      int i;
      for (i = 0; i < 3; i++)
        l_59[i] = &l_9[1];
      l_61--;
      if ((**g_37))
        break;
    }
  }
  return g_18;
}

static int32_t *func_2(int32_t *p_3, uint64_t p_4, float p_5) {
  int64_t l_10[2];
  int8_t *l_30 = &g_15;
  int32_t *l_35 = &g_7;
  int i;
  for (i = 0; i < 2; i++)
    l_10[i] = 0xBCD76CE4A6F44401LL;
lbl_31:
  for (g_7 = 0; (g_7 <= 1); g_7 += 1) {
    int8_t *l_13 = (void *)0;
    int8_t *l_14 = &g_15;
    int32_t *l_16 = &g_17;
    int32_t **l_22[4][1];
    int32_t ***l_21 = &l_22[2][0];
    int i, j;
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 1; j++)
        l_22[i][j] = &g_6;
    }
    g_18 = ((*l_16) =
                (safe_mul_func_int8_t_s_s(((*l_14) = l_10[g_7]), l_10[g_7])));
    (*g_23) =
        (((p_4 ||
           (safe_lshift_func_uint16_t_u_u((&p_3 != ((*l_21) = (void *)0)), 4))),
          g_18),
         &g_6);
  }
  for (g_17 = 24; (g_17 <= (-23)); g_17 = safe_sub_func_uint64_t_u_u(g_17, 4)) {
    int8_t *l_27 = &g_15;
    int8_t **l_28[3][2] = {
        {(void *)0, (void *)0}, {(void *)0, (void *)0}, {(void *)0, (void *)0}};
    int32_t l_34 = (-1L);
    int i, j;
    if (((g_29 = l_27) == l_30)) {
      return p_3;
    } else {
      if (g_7)
        goto lbl_31;
    }
    if (((**g_24) = (*p_3))) {
      if (g_17)
        goto lbl_31;
    } else {
      uint16_t *l_32 = &g_33;
      (*p_3) ^= (((*l_32) ^= (&l_27 != &l_30)) || l_34);
    }
  }
  return l_35;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_15;
  csmith_sink_ = g_17;
  csmith_sink_ = g_18;
  csmith_sink_ = g_33;
  platform_main_end(0, 0);
  return 0;
}
