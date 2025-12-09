// Options:   --seed 100011 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_011.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int32_t f0;
  int8_t f1;
};

union U3 {
  uint32_t f0;
};

union U4 {
  int8_t *f0;
};

static int8_t g_6 = 0x21L;
static volatile int32_t g_9 = 8L;
static volatile int32_t *g_8 = &g_9;
static int32_t g_19 = (-10L);
static uint16_t g_38 = 0xC746L;
static int32_t *const **volatile g_47 = (void *)0;
static int8_t g_75[1] = {0xF2L};
static struct S0 g_77 = {0x8D8D3B62L, 0x76L};
static union U4 g_79 = {0};

static union U4 func_1(void);
static const int32_t func_3(int8_t *p_4);

static union U4 func_1(void) {
  int32_t l_2[4][3] = {{(-1L), (-1L), (-1L)},
                       {0x18795010L, 0x18795010L, 0x18795010L},
                       {(-1L), (-1L), (-1L)},
                       {0x18795010L, 0x18795010L, 0x18795010L}};
  int8_t *l_5 = &g_6;
  uint8_t l_21 = 0UL;
  const int32_t *l_25 = &g_19;
  const int32_t **l_24 = &l_25;
  int32_t l_53 = 0x5830AF36L;
  int i, j;
  if (l_2[1][0]) {
    int32_t *l_39 = &g_19;
    int32_t *l_40 = &g_19;
    uint64_t l_41 = 6UL;
    if (func_3(l_5)) {
      uint16_t l_17 = 8UL;
      int32_t *l_18 = &g_19;
      int32_t l_20 = 0x974498B9L;
      (*l_18) |= (safe_rshift_func_int16_t_s_u(
          ((safe_mul_func_uint8_t_u_u(
               (!g_9), (((0L > ((l_17 != 0x0FL) == (-1L))) == l_17) | 0x2CL))) <
           1L),
          12));
      for (l_17 = 0; (l_17 <= 2); l_17 += 1) {
        (*g_8) ^= l_20;
        if (l_21)
          continue;
      }
    } else {
      for (g_6 = 0; (g_6 < 5); g_6 = safe_add_func_int32_t_s_s(g_6, 8)) {
        const int32_t **l_26 = &l_25;
        int32_t l_37 = 7L;
        l_26 = l_24;
        (*g_8) = (safe_add_func_int16_t_s_s(
            (g_38 &= ((safe_rshift_func_int16_t_s_s(
                          (safe_lshift_func_uint16_t_u_u(
                              ((safe_lshift_func_uint16_t_u_u(
                                   ((safe_mod_func_uint16_t_u_u(
                                        ((g_19, &g_19) == (*l_24)), l_37)),
                                    0x18A1L),
                                   (**l_24))) &&
                               (**l_24)),
                              g_19)),
                          10)) != (**l_24))),
            g_6));
      }
    }
    l_41--;
  } else {
    int32_t l_73[4] = {1L, 1L, 1L, 1L};
    int i;
    if ((**l_24)) {
      uint32_t l_60 = 0x71B2A125L;
      int8_t *l_74 = &g_75[0];
      struct S0 *l_76 = &g_77;
      if ((safe_rshift_func_int8_t_s_s(0xD7L, 5))) {
        uint16_t l_46 = 65535UL;
        (*g_8) |= (l_46 & 4294967289UL);
        g_47 = g_47;
      } else {
        int32_t l_48 = 0xF82EA917L;
        int32_t *l_49 = &g_19;
        int32_t *l_50 = &g_19;
        int32_t *l_51 = &g_19;
        int32_t *l_52 = &g_19;
        int32_t *l_54 = &l_53;
        uint8_t l_55 = 0x85L;
        ++l_55;
        (*l_54) ^= (safe_mul_func_int8_t_s_s(
            l_60,
            (safe_sub_func_int8_t_s_s(
                (((safe_mod_func_int8_t_s_s(
                      (safe_add_func_int8_t_s_s(
                          (safe_add_func_int32_t_s_s(
                              ((safe_sub_func_int32_t_s_s(
                                   (*l_25),
                                   ((safe_rshift_func_uint16_t_u_u(
                                        (l_60 > l_60), 4)) < (*l_25)))) < 9UL),
                              (*g_8))),
                          0x0DL)),
                      g_6)) <= l_60) >= l_73[2]),
                1L))));
      }
      if ((g_9 < (((*l_74) = ((*l_5) = (((*l_25), ((*l_25) <= 65527UL)) >=
                                        l_60))) <= g_38))) {
        struct S0 **l_78 = &l_76;
        (*l_78) = l_76;
      } else {
        return g_79;
      }
    } else {
      return g_79;
    }
  }
  return g_79;
}

static const int32_t func_3(int8_t *p_4) {
  union U3 l_7[1] = {{0xE81A7ECCL}};
  const uint32_t l_11 = 4UL;
  int i;
  for (g_6 = 0; (g_6 >= 0); g_6 -= 1) {
    volatile int32_t **l_10[3];
    int i;
    for (i = 0; i < 3; i++)
      l_10[i] = &g_8;
    g_8 = g_8;
  }
  return l_11;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  csmith_sink_ = g_9;
  csmith_sink_ = g_19;
  csmith_sink_ = g_38;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_75[i];
  }
  csmith_sink_ = g_77.f0;
  csmith_sink_ = g_77.f1;
  platform_main_end(0, 0);
  return 0;
}
