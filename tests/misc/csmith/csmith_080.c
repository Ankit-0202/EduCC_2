// Options:   --seed 100080 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_080.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint16_t f0;
};

static uint32_t g_10 = 0xC7516A20L;
static uint16_t g_14 = 0x8F98L;
static volatile uint32_t g_18 = 0xB8575526L;
static volatile uint32_t *volatile g_17 = &g_18;
static uint8_t g_20 = 1UL;
static int16_t g_21 = 8L;
static int32_t g_22 = 9L;
static int32_t g_24 = 0x835A7AB5L;
static int32_t *volatile g_23 = &g_24;
static uint64_t g_33[2][1] = {{0xF77D900D2964071CLL}, {0xF77D900D2964071CLL}};
static uint64_t *g_39 = &g_33[0][0];
static uint64_t **g_38[2] = {&g_39, &g_39};
static uint64_t ***volatile g_37 = &g_38[0];
static volatile uint8_t *volatile *g_40 = (void *)0;
static volatile uint8_t *volatile **volatile g_41 = (void *)0;
static union U0 g_43 = {0x63A4L};

static uint32_t func_1(void);
static union U0 func_25(uint8_t *p_26, int32_t p_27, uint16_t p_28,
                        int32_t p_29, uint16_t p_30);

static uint32_t func_1(void) {
  uint32_t *l_9[4][3] = {{&g_10, &g_10, &g_10},
                         {&g_10, &g_10, &g_10},
                         {&g_10, &g_10, &g_10},
                         {&g_10, &g_10, &g_10}};
  int32_t l_11[1];
  uint8_t *l_19 = &g_20;
  uint32_t l_47[2];
  int i, j;
  for (i = 0; i < 1; i++)
    l_11[i] = 0xC3D069F4L;
  for (i = 0; i < 2; i++)
    l_47[i] = 2UL;
  g_22 =
      ((safe_lshift_func_int8_t_s_s(
           ((!(((safe_mul_func_int16_t_s_s(
                    (safe_mul_func_int16_t_s_s(
                        (((*l_19) = (((g_10--) <=
                                      (((g_14 = l_11[0]),
                                        (((safe_lshift_func_uint8_t_u_s(
                                              ((void *)0 != g_17), l_11[0])) ||
                                          l_11[0]) ^
                                         0x209C3997B09B37D0LL)) ||
                                       0x62C4DF8EL)) ^
                                     0xF1L)) >= l_11[0]),
                        l_11[0])),
                    0x44F4L)),
                l_11[0]) ||
               g_14)) < g_21),
           6)) != l_11[0]);
  for (g_20 = 0; (g_20 <= 2); g_20 += 1) {
    const int32_t l_31 = (-1L);
    int32_t l_48[4];
    int i;
    for (i = 0; i < 4; i++)
      l_48[i] = (-6L);
    (*g_23) &= g_22;
    for (g_21 = 2; (g_21 >= 0); g_21 -= 1) {
      uint64_t *l_32 = &g_33[0][0];
      int32_t l_34[4][2] = {{(-3L), (-3L)},
                            {0x040C8E82L, (-3L)},
                            {(-3L), 0x040C8E82L},
                            {(-3L), (-3L)}};
      union U0 *l_44 = &g_43;
      uint8_t l_45[3];
      int32_t *l_46[1];
      uint64_t l_49 = 0x1356723FF4914D86LL;
      int i, j;
      for (i = 0; i < 3; i++)
        l_45[i] = 1UL;
      for (i = 0; i < 1; i++)
        l_46[i] = &g_22;
      g_22 ^=
          (((((*l_44) = func_25(&g_20,
                                (g_20 & ((((*l_32) |= ((l_31 != g_14) &&
                                                       0xC4B79A97A8D1D9D6LL)) ==
                                          18446744073709551611UL) ||
                                         l_11[0])),
                                l_34[3][1], l_11[0], g_10)),
             l_45[2]) > 0xF8L) |
           0x0A862252705104E0LL);
      for (g_24 = 2; (g_24 >= 0); g_24 -= 1) {
        l_48[1] = l_47[1];
        l_49 ^= 0x3564F696L;
      }
    }
  }
  return (*g_17);
}

static union U0 func_25(uint8_t *p_26, int32_t p_27, uint16_t p_28,
                        int32_t p_29, uint16_t p_30) {
  uint64_t *l_36 = (void *)0;
  uint64_t **l_35 = &l_36;
  volatile uint8_t *volatile **l_42 = &g_40;
  (*g_37) = l_35;
  (*l_42) = g_40;
  return g_43;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_10;
  csmith_sink_ = g_14;
  csmith_sink_ = g_18;
  csmith_sink_ = g_20;
  csmith_sink_ = g_21;
  csmith_sink_ = g_22;
  csmith_sink_ = g_24;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_33[i][j];
    }
  }
  csmith_sink_ = g_43.f0;
  platform_main_end(0, 0);
  return 0;
}
