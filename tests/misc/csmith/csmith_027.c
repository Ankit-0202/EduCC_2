// Options:   --seed 100027 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_027.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int8_t f0;
};

static const int32_t g_7 = (-1L);
static const int32_t *g_6 = &g_7;
static int32_t g_11 = 0xB76D6092L;
static int32_t *const volatile g_20 = &g_11;
static uint64_t g_35 = 0x212908CDAC369029LL;
static int32_t g_41 = 0xC2674D90L;
static int8_t g_54 = 0x47L;
static volatile union U0 g_59 = {0x46L};
static volatile union U0 *volatile g_58 = &g_59;
static volatile union U0 *volatile *volatile g_60 = &g_58;
static union U0 g_63 = {0x57L};
static union U0 *g_66 = &g_63;
static union U0 **g_65 = &g_66;
static int32_t g_68 = 0xEA3FEE22L;
static uint64_t g_70 = 0x40466E1A5BDB26F1LL;

static uint32_t func_1(void);
static int32_t *func_2(const int32_t *p_3, uint32_t p_4, int16_t p_5);

static uint32_t func_1(void) {
  int32_t *const l_10 = &g_11;
  union U0 *l_62 = &g_63;
  union U0 **l_61[4][4] = {{(void *)0, &l_62, &l_62, (void *)0},
                           {(void *)0, &l_62, &l_62, (void *)0},
                           {(void *)0, &l_62, &l_62, (void *)0},
                           {(void *)0, &l_62, &l_62, (void *)0}};
  union U0 *l_64 = &g_63;
  int32_t *l_67 = &g_68;
  uint32_t l_69 = 4294967295UL;
  int i, j;
  g_6 = func_2(
      g_6,
      ((*l_10) = ((((safe_sub_func_int8_t_s_s(((l_10 == (void *)0), (*l_10)),
                                              g_7)) <= 0xEEDAL) ^
                   (*l_10)) >= (*g_6))),
      g_7);
  g_70 |= (l_69 = ((*g_6) ==
                   ((*l_67) = ((l_61[2][2] !=
                                (g_65 = ((l_64 != (*g_60)), g_65))) >= g_35))));
  return g_68;
}

static int32_t *func_2(const int32_t *p_3, uint32_t p_4, int16_t p_5) {
  int64_t l_12 = (-1L);
  union U0 l_19 = {0L};
  uint64_t *l_47 = &g_35;
  uint64_t l_53 = 4UL;
  int32_t *l_55 = &g_11;
  if ((l_12 &&
       ((*p_3) & (safe_mod_func_int32_t_s_s(
                     (safe_rshift_func_uint8_t_u_s(0x25L, g_7)), l_12))))) {
    int32_t *const l_29 = &g_11;
    int32_t *l_30 = &g_11;
    uint64_t *l_33 = (void *)0;
    uint64_t *l_34 = &g_35;
    int32_t l_42 = 0x40B36FE0L;
  lbl_57:
    (*g_20) = ((safe_lshift_func_int16_t_s_s((0xE5L >= 0x70L), 5)) &&
               (((p_3 != p_3), l_19), (-7L)));
    if ((safe_sub_func_uint32_t_u_u(
            (((*l_34) = (safe_mod_func_int64_t_s_s(
                  ((safe_sub_func_uint8_t_u_u(
                       (safe_rshift_func_int8_t_s_u((l_29 == (l_30 = &g_11)),
                                                    4)),
                       ((safe_add_func_uint32_t_u_u(((g_7 != 9UL) > g_7),
                                                    g_11)) < (*l_29)))) ^
                   g_11),
                  0x032F82966B9117A5LL))) &
             0xEC1A2C9DBE4FCD58LL),
            1L))) {
      uint64_t *l_36 = &g_35;
      if ((l_36 != &g_35)) {
        return &g_11;
      } else {
        uint64_t *l_39 = (void *)0;
        int32_t *l_40[1];
        int i;
        for (i = 0; i < 1; i++)
          l_40[i] = &g_41;
        l_42 ^= (((safe_rshift_func_uint16_t_u_s(
                      ((g_7, &g_7) != (((void *)0 == l_39), &g_7)), (*l_30))) &
                  p_5),
                 0x88BA54F9L);
        (*l_29) = (*p_3);
      }
      if (((((g_54 = ((safe_lshift_func_uint16_t_u_s(
                          (safe_lshift_func_uint8_t_u_u(
                              (l_47 == l_36), (safe_mod_func_uint64_t_u_u(
                                                  (safe_rshift_func_int16_t_s_s(
                                                      (+(*p_3)), g_41)),
                                                  g_41)))),
                          l_53)) >= (*p_3))) &
             (*p_3)) > g_11) >= g_11)) {
        return &g_41;
      } else {
        int32_t **l_56 = &l_30;
        (*l_56) = l_55;
      }
    } else {
      if (p_5)
        goto lbl_57;
    }
  } else {
    (*g_60) = g_58;
  }
  return l_55;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  csmith_sink_ = g_35;
  csmith_sink_ = g_41;
  csmith_sink_ = g_54;
  csmith_sink_ = g_59.f0;
  csmith_sink_ = g_63.f0;
  csmith_sink_ = g_68;
  csmith_sink_ = g_70;
  platform_main_end(0, 0);
  return 0;
}
