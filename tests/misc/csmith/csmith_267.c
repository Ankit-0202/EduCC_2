// Options:   --seed 300267 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_267.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int16_t g_7 = 0x8795L;
static uint32_t g_15 = 0UL;
static int32_t g_19 = 0xE7528ACEL;
static uint16_t g_21 = 65535UL;
static uint8_t g_30 = 0x2CL;
static int32_t g_33[1][1] = {{0L}};

static int32_t func_1(void);
static uint8_t func_4(uint32_t p_5, uint32_t p_6);
static uint32_t func_8(uint32_t p_9);

static int32_t func_1(void) {
  uint32_t *l_14[3];
  int32_t l_16 = 0xD564C7B7L;
  int32_t *l_17 = &l_16;
  int32_t *l_18 = &g_19;
  uint16_t *l_20 = &g_21;
  const int32_t l_36 = 0xFB18BA70L;
  const int32_t *l_37 = (void *)0;
  int i;
  for (i = 0; i < 3; i++)
    l_14[i] = &g_15;
  (*l_17) =
      ((safe_rshift_func_uint8_t_u_u(
           func_4(g_7,
                  func_8((safe_rshift_func_int8_t_s_s(
                      (((*l_20) =
                            ((safe_lshift_func_uint16_t_u_u(
                                 ((((*l_18) = ((l_16 |= g_7) ||
                                               ((*l_17) &=
                                                (((void *)0 != &g_15), 1L)))),
                                   0xD8L),
                                  g_7),
                                 4)) |
                             g_15)) > g_15),
                      g_15)))),
           g_7)) ^
       l_36);
  l_37 = &l_36;
  return g_15;
}

static uint8_t func_4(uint32_t p_5, uint32_t p_6) { return g_21; }

static uint32_t func_8(uint32_t p_9) {
  uint16_t l_31 = 65530UL;
  if (g_7) {
    int32_t *l_34 = &g_33[0][0];
    int32_t **l_35 = &l_34;
    for (g_15 = 10; (g_15 < 38); ++g_15) {
      uint32_t l_26 = 4294967286UL;
      uint8_t *l_29 = &g_30;
      int32_t *l_32 = &g_33[0][0];
      (*l_32) &= (safe_div_func_int8_t_s_s(
          ((((((g_15 == (l_26--)) || (((*l_29) = 1UL), g_19)) & (-1L)) <=
             0x9FE9A5A165F5C9B8LL) &&
            l_31) != 0x18F4C6F4L),
          g_7));
    }
    (*l_35) = l_34;
  } else {
    return g_21;
  }
  return g_19;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_15;
  csmith_sink_ = g_19;
  csmith_sink_ = g_21;
  csmith_sink_ = g_30;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_33[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
