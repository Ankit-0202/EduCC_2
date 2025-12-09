// Options:   --seed 100005 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_005.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4 = 0xBA339924L;
static int32_t *volatile g_33[1] = {(void *)0};
static int32_t g_35 = 0x01D976D9L;
static int32_t *const volatile g_36 = (void *)0;
static int32_t g_47 = 6L;
static int32_t *volatile g_46 = &g_47;

static uint64_t func_1(void);
static uint16_t func_7(uint32_t p_8, int64_t p_9, int8_t p_10);

static uint64_t func_1(void) {
  uint8_t l_18[3];
  int32_t *l_37 = &g_35;
  int i;
  for (i = 0; i < 3; i++)
    l_18[i] = 0x72L;
  (*l_37) =
      ((safe_div_func_int64_t_s_s(
           g_4,
           (safe_add_func_uint16_t_u_u(
               func_7(((+(safe_rshift_func_uint16_t_u_u(
                           ((safe_rshift_func_int8_t_s_s(
                                (safe_lshift_func_uint8_t_u_s(
                                    (l_18[0] &&
                                     (safe_mod_func_int8_t_s_s(
                                         ((safe_lshift_func_uint16_t_u_u(
                                              (safe_mul_func_int16_t_s_s(
                                                  g_4, l_18[1])),
                                              g_4)) <= 0x7D0B0A3531F145BALL),
                                         g_4))),
                                    2)),
                                3)),
                            l_18[0]),
                           l_18[0]))),
                       l_18[1]),
                      l_18[2], l_18[0]),
               65526UL)))) == l_18[1]);
  for (g_35 = 0; (g_35 > (-28)); g_35 = safe_sub_func_int8_t_s_s(g_35, 6)) {
    int64_t l_45[4];
    int i;
    for (i = 0; i < 4; i++)
      l_45[i] = 0x3F85024D8F3B1AD3LL;
    for (g_4 = 0; (g_4 <= 0); g_4 += 1) {
      uint32_t l_44 = 4294967295UL;
      (*g_46) = (safe_div_func_int8_t_s_s(
          ((g_35 | ((safe_lshift_func_uint16_t_u_u(65535UL, g_35)) != l_44)) ^
           g_4),
          l_45[1]));
    }
  }
  return (*l_37);
}

static uint16_t func_7(uint32_t p_8, int64_t p_9, int8_t p_10) {
  int8_t l_32 = 0x4FL;
  int32_t *l_34 = &g_35;
  (*l_34) = (safe_mul_func_uint16_t_u_u(
      (safe_lshift_func_uint8_t_u_u(
          ((0x4868FDADL > (!p_8)) || (0x8F738F58L <= l_32)), l_32)),
      g_4));
  return g_35;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_35;
  csmith_sink_ = g_47;
  platform_main_end(0, 0);
  return 0;
}
