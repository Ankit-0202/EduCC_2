// Options:   --seed 300283 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_283.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 0x313DD33AL;
static int64_t g_36 = 0x6FA66FA4BC4433ACLL;
static int32_t g_42 = 0x871D0C0BL;
static uint8_t g_51 = 252UL;
static int32_t g_58 = 0x12EF6116L;
static int32_t *g_66[2] = {&g_58, &g_58};
static int32_t g_68 = 0xA3FEE22EL;
static int32_t *volatile g_67 = &g_68;

static int8_t func_1(void);
static int32_t func_5(uint64_t p_6, int32_t p_7, uint16_t p_8, uint32_t p_9,
                      int32_t p_10);
static int32_t func_16(const uint32_t p_17, uint64_t p_18, uint16_t p_19,
                       int8_t p_20);

static int8_t func_1(void) {
  uint64_t l_13 = 1UL;
  int32_t l_63 = 0x74C3FC6CL;
  for (g_2 = 0; (g_2 != (-16)); g_2--) {
    int32_t l_25 = 5L;
    int64_t *l_64 = &g_36;
    (*g_67) |= func_5(
        (safe_mod_func_int64_t_s_s(
            ((*l_64) =
                 ((((l_13 = g_2),
                    (safe_mod_func_int32_t_s_s(
                        0x6D6092F6L, func_16(((((safe_sub_func_uint8_t_u_u(
                                                    (safe_sub_func_uint16_t_u_u(
                                                        (g_2 | l_25), 1UL)),
                                                    g_2)) &&
                                                l_13) >= 8L),
                                              g_2),
                                             g_2, g_2, l_13)))),
                   l_63) >= 1L)),
            l_63)),
        g_2, g_2, g_2, l_25);
  }
  return l_63;
}

static int32_t func_5(uint64_t p_6, int32_t p_7, uint16_t p_8, uint32_t p_9,
                      int32_t p_10) {
  int32_t **l_65[3];
  int i;
  for (i = 0; i < 3; i++)
    l_65[i] = (void *)0;
  g_66[0] = &p_7;
  return p_8;
}

static int32_t func_16(const uint32_t p_17, uint64_t p_18, uint16_t p_19,
                       int8_t p_20) {
  int32_t l_30 = 4L;
  int32_t l_62 = 0xD5E714ABL;
  for (p_18 = 19; (p_18 > 4); p_18 = safe_sub_func_uint8_t_u_u(p_18, 9)) {
    int64_t *l_35 = &g_36;
    int32_t l_39 = (-3L);
    uint32_t l_40 = 18446744073709551611UL;
    int32_t *l_41 = &g_42;
    for (p_19 = (-26); (p_19 == 2); p_19++) {
      l_30 &= p_17;
    }
    (*l_41) ^= ((safe_rshift_func_int16_t_s_s(
                    (safe_mul_func_int8_t_s_s(
                        (0x8451D77F17245C2FLL >=
                         (((*l_35) = l_30),
                          ((safe_div_func_uint64_t_u_u(l_39, l_40)) >= 0L))),
                        l_40)),
                    g_2)) |
                0x5A27557BC7756237LL);
  }
  for (p_19 = 4; (p_19 != 37); p_19 = safe_add_func_int32_t_s_s(p_19, 1)) {
    int32_t *l_48[1];
    int32_t **l_47 = &l_48[0];
    uint8_t *l_50[3][3] = {
        {&g_51, &g_51, &g_51}, {&g_51, &g_51, &g_51}, {&g_51, &g_51, &g_51}};
    int8_t l_52 = 0L;
    int i, j;
    for (i = 0; i < 1; i++)
      l_48[i] = &g_2;
    if ((safe_sub_func_uint32_t_u_u(
            (p_20 ^ (((*l_47) = (void *)0) !=
                     (((((+((g_51 = p_20) & g_2)) >= p_20) > 8UL) < l_52),
                      (void *)0))),
            8UL))) {
      int8_t l_53[1][1];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_53[i][j] = 1L;
      }
      l_53[0][0] = 0x605DD88BL;
      g_58 |= (safe_sub_func_int32_t_s_s(
          g_2, (safe_mul_func_int8_t_s_s(p_18, ((p_19 | p_17) && g_42)))));
    } else {
      uint32_t l_59 = 0UL;
      l_59--;
    }
    g_58 ^= (g_42 |= (l_62 = (-5L)));
  }
  return p_17;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_36;
  csmith_sink_ = g_42;
  csmith_sink_ = g_51;
  csmith_sink_ = g_58;
  csmith_sink_ = g_68;
  platform_main_end(0, 0);
  return 0;
}
