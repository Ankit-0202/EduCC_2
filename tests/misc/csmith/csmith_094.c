// Options:   --seed 100094 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_094.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int8_t g_8 = 0x83L;
static int32_t g_17 = 0xAB61B583L;
static uint32_t g_18 = 18446744073709551612UL;
static uint64_t g_19 = 0xBC07C2076ACB8F2BLL;

static int32_t func_1(void);
static const int32_t func_2(int8_t *p_3, int8_t *p_4, int32_t p_5);

static int32_t func_1(void) {
  int8_t *l_7[2];
  int8_t **l_6 = &l_7[1];
  int8_t *l_9[2];
  int i;
  for (i = 0; i < 2; i++)
    l_7[i] = &g_8;
  for (i = 0; i < 2; i++)
    l_9[i] = &g_8;
  g_19 |= func_2(((*l_6) = (void *)0), l_9[0], g_8);
  return g_17;
}

static const int32_t func_2(int8_t *p_3, int8_t *p_4, int32_t p_5) {
  uint16_t l_10 = 1UL;
  g_18 |=
      (l_10, (((safe_lshift_func_uint8_t_u_u(
                   ((safe_div_func_int8_t_s_s(
                        ((*p_4) ^= ((safe_mul_func_uint16_t_u_u(
                                        l_10, (&p_3 == (void *)0))) <= l_10)),
                        g_17)) == p_5),
                   6)) &
               l_10) < p_5));
  return g_17;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8;
  csmith_sink_ = g_17;
  csmith_sink_ = g_18;
  csmith_sink_ = g_19;
  platform_main_end(0, 0);
  return 0;
}
