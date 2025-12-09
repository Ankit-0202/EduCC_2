// Options:   --seed 100040 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_040.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  int64_t f1;
  int64_t f2;
};

static int8_t g_13 = 0x3EL;
static uint8_t g_15 = 0UL;
static struct S0 *volatile g_21 = (void *)0;
static int32_t g_29 = 0L;
static int32_t g_56 = (-1L);
static int32_t *volatile g_55 = &g_56;
static int32_t *g_58[2] = {&g_29, &g_29};
static int32_t **volatile g_57 = &g_58[0];
static uint64_t g_62 = 0xF20CF68020C2888ALL;

static uint8_t func_1(void);
static struct S0 func_2(uint32_t p_3);

static uint8_t func_1(void) {
  uint32_t l_9[1];
  uint16_t l_10 = 0xF9C2L;
  struct S0 l_22 = {4294967295UL, 0x39CEE24B2E809B4ALL, 0x7BDD48407374FD52LL};
  uint8_t *l_25 = &g_15;
  int i;
  for (i = 0; i < 1; i++)
    l_9[i] = 2UL;
  l_22 =
      func_2(((~(0x89L == (safe_div_func_uint8_t_u_u(
                              (7UL < (safe_rshift_func_int16_t_s_u(l_9[0], 6))),
                              l_10)))),
              0xDBBE5689L));
  if (((safe_lshift_func_uint8_t_u_s(
           ((*l_25) = g_15),
           (((1L || (safe_lshift_func_uint8_t_u_u((l_9[0] > l_22.f2), 6))) |
             0xECL),
            l_22.f0))) > 1L)) {
    uint32_t l_44[1][1];
    uint16_t *l_45 = &l_10;
    int32_t l_46 = 0x47D05199L;
    int32_t *l_47 = &l_46;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_44[i][j] = 0x3964E48CL;
    }
    for (l_22.f2 = 0; (l_22.f2 >= 0); l_22.f2 -= 1) {
      int32_t *l_28 = &g_29;
      for (g_13 = 0; (g_13 <= 0); g_13 += 1) {
        int32_t **l_30 = &l_28;
        int i;
        (*l_30) = l_28;
        if (l_9[g_13])
          break;
      }
    }
    (*l_47) = (safe_unary_minus_func_uint16_t_u(
        ((~0x4DB2L) <
         (safe_sub_func_int16_t_s_s(
             (safe_sub_func_uint32_t_u_u(
                 (safe_rshift_func_uint16_t_u_u(
                     (0x3395L > (safe_unary_minus_func_uint16_t_u(
                                    ((*l_45) = (safe_sub_func_uint16_t_u_u(
                                         (safe_div_func_int32_t_s_s(
                                             (g_13, l_44[0][0]), g_29)),
                                         g_13)))))),
                     g_29)),
                 l_46)),
             1L)))));
  } else {
    int16_t l_48 = (-8L);
    if (l_48) {
      (*g_55) &= (safe_mul_func_int8_t_s_s(
          ((((+g_29), (safe_unary_minus_func_int16_t_s(
                          ((safe_rshift_func_uint16_t_u_s(l_10, 11)) <=
                           ((g_15 <= 65535UL) > 1UL))))) <= g_15) >= g_13),
          g_29));
      (*g_57) = &g_29;
    } else {
      const int32_t *l_59[1][3];
      const int32_t **l_60 = &l_59[0][1];
      uint16_t *l_61[3];
      int32_t *l_63 = &g_29;
      int32_t *l_64 = &g_56;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_59[i][j] = &g_29;
      }
      for (i = 0; i < 3; i++)
        l_61[i] = &l_10;
      (*l_60) = l_59[0][1];
      (*l_64) = ((*l_63) = ((g_62 |= (**l_60)) || (8UL ^ g_13)));
    }
  }
  return l_22.f2;
}

static struct S0 func_2(uint32_t p_3) {
  struct S0 l_20 = {0x5799333CL, 4L, -1L};
  for (p_3 = 0; (p_3 < 13); p_3 = safe_add_func_uint16_t_u_u(p_3, 2)) {
    uint8_t *l_14 = &g_15;
    int32_t *l_18 = (void *)0;
    int32_t l_19 = 0xFFD81438L;
    l_19 ^= (((*l_14)++) | g_13);
  }
  return l_20;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  csmith_sink_ = g_15;
  csmith_sink_ = g_29;
  csmith_sink_ = g_56;
  csmith_sink_ = g_62;
  platform_main_end(0, 0);
  return 0;
}
