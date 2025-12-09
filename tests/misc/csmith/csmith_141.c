// Options:   --seed 200141 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_141.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_12 = 0x9729CF30L;
static int32_t g_32 = 7L;
static int32_t *volatile g_31 = &g_32;
static int32_t g_35 = 0L;
static int64_t g_47 = 0x2E510B2D4AD44630LL;
static int32_t g_48 = 0xFFC5A258L;
static int64_t g_50[2][4] = {{(-1L), (-1L), (-1L), (-1L)},
                             {(-1L), (-1L), (-1L), (-1L)}};
static int32_t g_51 = 0x15C87E17L;
static uint64_t g_52 = 18446744073709551606UL;
static int16_t g_62 = (-8L);
static uint16_t g_64 = 0x65D2L;
static int32_t *volatile g_66 = &g_35;
static uint32_t g_70 = 0xCC15C487L;

static uint8_t func_1(void);
static uint64_t func_10(uint32_t p_11);

static uint8_t func_1(void) {
  uint64_t l_15[3][3] = {
      {1UL, 1UL, 1UL},
      {0xEFB6F65E790E8648LL, 0xEFB6F65E790E8648LL, 0xEFB6F65E790E8648LL},
      {1UL, 1UL, 1UL}};
  int32_t *l_55 = &g_48;
  int32_t l_69 = 1L;
  int i, j;
  (*l_55) &= (safe_div_func_uint8_t_u_u(
      (safe_lshift_func_uint16_t_u_u(
          ((safe_lshift_func_int8_t_s_u(
               (safe_sub_func_uint64_t_u_u(
                   func_10(
                       (g_12, (safe_lshift_func_int8_t_s_s(l_15[1][0], 6)))),
                   g_35)),
               g_35)) == l_15[1][1]),
          6)),
      0x35L));
  for (g_12 = 8; (g_12 <= 27); g_12++) {
    int16_t *l_61 = &g_62;
    uint16_t *l_63 = &g_64;
    int32_t l_65 = 0x3AA798D6L;
    int32_t *l_67 = (void *)0;
    int32_t *l_68[3];
    int i;
    for (i = 0; i < 3; i++)
      l_68[i] = &g_32;
    (*g_66) &=
        ((safe_lshift_func_uint8_t_u_u(
             (0x28CDD50170A2C9EALL ==
              (((*l_55) ^ (~((*l_63) = (((*l_61) |= (1L | 0L)) & (-5L))))) ^
               g_51)),
             g_51)),
         l_65);
    g_70++;
  }
  return g_64;
}

static uint64_t func_10(uint32_t p_11) {
  const int8_t l_29 = 2L;
  int32_t l_37 = (-1L);
  int32_t l_39[1];
  int i;
  for (i = 0; i < 1; i++)
    l_39[i] = 0xD79339B8L;
  for (p_11 = 0; (p_11 <= 50); ++p_11) {
    uint64_t l_28[1];
    int32_t l_43 = 0xC17A3F0AL;
    int32_t l_44 = 0x5996FD0FL;
    int32_t l_45 = (-8L);
    int32_t l_46 = 0x969E0CD1L;
    int32_t l_49 = 1L;
    int i;
    for (i = 0; i < 1; i++)
      l_28[i] = 3UL;
    for (g_12 = (-14); (g_12 < (-3));
         g_12 = safe_add_func_uint16_t_u_u(g_12, 2)) {
      const uint16_t l_30 = 0x3CA4L;
      (*g_31) =
          ((safe_div_func_int16_t_s_s(
               ((((safe_mul_func_int8_t_s_s(
                      p_11, ((safe_add_func_int64_t_s_s(
                                 (safe_add_func_uint16_t_u_u(0x123DL, g_12)),
                                 l_28[0])) ||
                             l_29))) ^
                  p_11) &&
                 18446744073709551610UL) != g_12),
               l_30)),
           g_12);
    }
    for (g_32 = 0; (g_32 >= 0); g_32 -= 1) {
      int32_t *l_33 = (void *)0;
      int32_t *l_34 = &g_35;
      int32_t *l_36 = (void *)0;
      int32_t *l_38 = &l_37;
      int32_t *l_40 = &l_39[0];
      int32_t *l_41 = &l_39[0];
      int32_t *l_42[1][3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_42[i][j] = &l_37;
      }
      g_52--;
    }
  }
  return l_29;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_12;
  csmith_sink_ = g_32;
  csmith_sink_ = g_35;
  csmith_sink_ = g_47;
  csmith_sink_ = g_48;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_50[i][j];
    }
  }
  csmith_sink_ = g_51;
  csmith_sink_ = g_52;
  csmith_sink_ = g_62;
  csmith_sink_ = g_64;
  csmith_sink_ = g_70;
  platform_main_end(0, 0);
  return 0;
}
