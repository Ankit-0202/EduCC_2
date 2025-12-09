// Options:   --seed 100064 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_064.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint8_t g_13 = 0UL;
static volatile uint32_t g_16[3][1] = {
    {0xAB3921DEL}, {0xAB3921DEL}, {0xAB3921DEL}};
static int8_t g_17 = 0x70L;
static int32_t g_23 = 0xBC383C67L;
static volatile uint8_t g_42 = 0x89L;
static int16_t g_47[3] = {7L, 7L, 7L};

static uint8_t func_1(void);
static int32_t func_2(uint64_t p_3, uint8_t p_4, int16_t p_5);

static uint8_t func_1(void) {
  uint8_t *l_12 = &g_13;
  uint8_t l_81 = 255UL;
  l_81 = func_2(
      ((safe_rshift_func_uint8_t_u_s(
           (safe_add_func_int32_t_s_s(
               (safe_sub_func_uint8_t_u_u(((*l_12)++), g_16[1][0])), g_17)),
           (safe_mod_func_int32_t_s_s(
               (safe_add_func_int32_t_s_s(g_17, 0x2733582FL)), g_17)))),
       0xB58E17C10977A124LL),
      g_17, g_17);
  return g_47[1];
}

static int32_t func_2(uint64_t p_3, uint8_t p_4, int16_t p_5) {
  int32_t *l_22 = &g_23;
  int32_t *l_24 = &g_23;
  int32_t *l_25 = (void *)0;
  int32_t *l_26 = &g_23;
  int32_t *l_27 = (void *)0;
  int32_t *l_28 = &g_23;
  int32_t *l_29 = (void *)0;
  int32_t *l_30 = &g_23;
  int32_t *l_31 = (void *)0;
  int32_t *l_32 = &g_23;
  int32_t *l_33 = (void *)0;
  int32_t *l_34 = &g_23;
  int32_t l_35 = (-8L);
  int32_t *l_36 = &l_35;
  int32_t *l_37 = (void *)0;
  int32_t *l_38 = &g_23;
  int32_t *l_39 = &l_35;
  int32_t *l_40 = &l_35;
  int32_t *l_41[3][3];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      l_41[i][j] = &g_23;
  }
  g_42--;
  if (((&g_23 != &g_23) != (&p_4 != (void *)0))) {
    int32_t l_45 = 0L;
    (*l_36) |= (((l_45, ((((void *)0 == &l_45) || g_23) &&
                         0x53DDB2097E65FBC0LL)) <= g_42) |
                g_13);
    (*l_34) = p_5;
  } else {
    int32_t l_52[1];
    int32_t l_63 = 0x19D5C01CL;
    int i;
    for (i = 0; i < 1; i++)
      l_52[i] = (-10L);
    for (p_4 = 0; (p_4 <= 0); p_4 += 1) {
      int32_t l_46 = 0x060A3B7DL;
      int32_t l_61 = 0L;
      int16_t *l_68 = (void *)0;
      int16_t *l_69 = (void *)0;
      int16_t *l_70 = (void *)0;
      if (((((p_3 && (g_47[1] = l_46)),
             (safe_lshift_func_int8_t_s_s(
                 ((safe_div_func_uint8_t_u_u(l_52[0], p_3)) == 0x1589A458L),
                 3))) > p_3) <= l_52[0])) {
        int8_t *l_62[1][1];
        int i, j;
        for (i = 0; i < 1; i++) {
          for (j = 0; j < 1; j++)
            l_62[i][j] = (void *)0;
        }
        (*l_22) |= (safe_add_func_uint32_t_u_u((6L >= l_52[0]), (-6L)));
        (*l_40) &=
            ((p_4 ||
              (l_63 = (((safe_div_func_uint32_t_u_u(
                            ((safe_add_func_int64_t_s_s(
                                 (((((l_61 = (((safe_mod_func_uint8_t_u_u(
                                                   0xECL, p_3)) &&
                                               g_23) != g_42)) |
                                     0x50L) |
                                    p_5) > 0xDBEC8B24L) == 1L),
                                 g_13)) < l_46),
                            g_23)) < g_47[1]),
                       g_23))) <= p_4);
      } else {
        (*l_28) = 5L;
      }
      (*l_40) ^= (safe_mod_func_int64_t_s_s(
          ((safe_mul_func_uint16_t_u_u(p_3, (l_61 ^= 0x172CL))) <= 0x15L),
          g_23));
      for (l_35 = 0; (l_35 >= 0); l_35 -= 1) {
        int8_t l_73 = 0x61L;
        int16_t l_80 = 0x6224L;
        (*l_22) |= (safe_mod_func_uint32_t_u_u(
            l_73, (safe_add_func_int16_t_s_s(
                      ((safe_sub_func_uint32_t_u_u(
                           ((safe_div_func_uint64_t_u_u(
                                ((0x62C7DCB2139E6D59LL <= l_80) && l_46),
                                p_3)) > p_4),
                           g_42)),
                       1L),
                      l_73))));
      }
    }
    return p_5;
  }
  return g_23;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_16[i][j];
    }
  }
  csmith_sink_ = g_17;
  csmith_sink_ = g_23;
  csmith_sink_ = g_42;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_47[i];
  }
  platform_main_end(0, 0);
  return 0;
}
