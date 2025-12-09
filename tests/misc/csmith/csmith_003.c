// Options:   --seed 100003 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_003.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int8_t f0;
};

static uint32_t g_2 = 0xDF1FEBAEL;
static int32_t g_19 = 0x9F7A9D2EL;
static int32_t *volatile g_18 = &g_19;
static uint8_t g_30 = 1UL;
static int32_t *volatile g_34[1] = {(void *)0};
static int32_t g_37[1][3] = {{(-1L), (-1L), (-1L)}};
static int32_t *g_42 = &g_37[0][0];
static int32_t **volatile g_41 = &g_42;
static volatile uint8_t g_60 = 0xA0L;
static volatile uint8_t *g_59 = &g_60;
static volatile uint8_t *volatile *volatile g_58 = &g_59;
static int32_t g_65 = 3L;

static uint32_t func_1(void);
static int32_t func_5(int8_t p_6, uint16_t p_7, int64_t p_8, uint32_t p_9);

static uint32_t func_1(void) {
  uint16_t l_12 = 0x0F68L;
  int32_t *l_32 = &g_19;
  union U0 l_45 = {0xA5L};
  uint8_t l_67 = 0xAAL;
lbl_53:
  g_2++;
  if (func_5((((g_2 && (safe_lshift_func_uint16_t_u_u(g_2, 7))) &&
               18446744073709551609UL) <= 0x81CED8F6EFBA1A4DLL),
             l_12, g_2, l_12)) {
    uint32_t l_31[2][2] = {{4294967293UL, 4294967293UL},
                           {4294967293UL, 4294967293UL}};
    int32_t *l_33 = &g_19;
    int32_t l_38 = 1L;
    int i, j;
    for (l_12 = 0; (l_12 == 45); l_12 = safe_add_func_uint32_t_u_u(l_12, 2)) {
      uint8_t *l_29 = &g_30;
      int32_t *l_35 = (void *)0;
      int32_t *l_36[3][1];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_36[i][j] = &g_37[0][0];
      }
      l_38 &= ((0L && (safe_mod_func_int16_t_s_s(
                          (+((((((safe_rshift_func_uint16_t_u_s(
                                     (((*l_29) = (safe_lshift_func_int8_t_s_s(
                                           g_19, (0x82L >= 0x00L)))) ^
                                      l_31[1][1]),
                                     g_2)),
                                 l_32) != l_33) < (*l_32)),
                              (*l_32)) == g_19)),
                          0x19C3L))) &
               (*l_33));
      for (g_30 = 2; (g_30 >= 52); ++g_30) {
        if ((*g_18))
          break;
        (*g_41) = &g_37[0][0];
      }
    }
    return g_37[0][2];
  } else {
    uint8_t *l_51 = &g_30;
    uint8_t **const l_50[2][3] = {{&l_51, &l_51, &l_51}, {&l_51, &l_51, &l_51}};
    const uint8_t *l_62 = (void *)0;
    const uint8_t **l_61 = &l_62;
    int32_t *l_66[3][2] = {
        {&g_37[0][1], &g_19}, {&g_37[0][1], &g_37[0][1]}, {&g_19, &g_37[0][1]}};
    int i, j;
    for (l_12 = 0; (l_12 <= 21); l_12 = safe_add_func_uint16_t_u_u(l_12, 2)) {
      uint32_t l_49 = 0x5344FFA2L;
      uint8_t **l_52 = &l_51;
      if ((((l_45, (g_37[0][1] ^
                    ((+(safe_rshift_func_int16_t_s_s((g_37[0][0] == l_49), 8))),
                     g_37[0][2]))) |
            (*l_32)) ^
           250UL)) {
        l_52 = l_50[1][0];
      } else {
        const uint8_t ***l_63 = &l_61;
        int32_t *l_64 = &g_65;
        if (g_2)
          goto lbl_53;
        (*l_64) ^= ((0xDD9CL < (safe_lshift_func_int8_t_s_s(
                                   ((safe_add_func_int8_t_s_s(
                                        ((g_58 != ((*l_63) = l_61)), (*l_32)),
                                        0xA6L)) > g_37[0][0]),
                                   0))),
                    l_49);
      }
    }
    --l_67;
  }
  return g_65;
}

static int32_t func_5(int8_t p_6, uint16_t p_7, int64_t p_8, uint32_t p_9) {
  uint16_t l_17 = 0x40EBL;
  (*g_18) =
      ((g_2 >
        (safe_mod_func_int16_t_s_s(
            (safe_rshift_func_uint8_t_u_u(
                ((((-1L) <= (4294967289UL == l_17)) && p_7) == 249UL), l_17)),
            1UL))),
       p_8);
  return l_17;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_19;
  csmith_sink_ = g_30;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_37[i][j];
    }
  }
  csmith_sink_ = g_60;
  csmith_sink_ = g_65;
  platform_main_end(0, 0);
  return 0;
}
