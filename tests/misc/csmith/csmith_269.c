// Options:   --seed 300269 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_269.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0xA8EAC8B1L;
static volatile int32_t g_3 = 0xA4F833FCL;
static volatile int32_t g_4[3] = {0xBF34FDA0L, 0xBF34FDA0L, 0xBF34FDA0L};
static volatile int32_t g_5 = 0xFE77DD68L;
static int32_t g_6 = 1L;
static volatile int32_t g_9 = 0x210E164CL;
static int32_t g_10 = 2L;
static uint16_t g_22 = 0UL;
static int32_t g_26 = 2L;

static int64_t func_1(void);

static int64_t func_1(void) {
  uint64_t l_24 = 18446744073709551615UL;
  int32_t l_27[2][3] = {{8L, 0L, 8L}, {8L, 0L, 8L}};
  int i, j;
  for (g_6 = 0; (g_6 != 18); g_6 = safe_add_func_uint64_t_u_u(g_6, 3)) {
    int32_t l_20 = 0x7B051AF7L;
    int32_t l_23 = 0x9FE57F6CL;
    for (g_10 = 0; (g_10 >= 10); g_10++) {
      uint16_t *l_21 = &g_22;
      int32_t *l_25[1][3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_25[i][j] = &g_26;
      }
      l_27[0][2] = ((safe_sub_func_uint64_t_u_u(
                        (((safe_mod_func_int8_t_s_s(
                              g_5, (l_23 = (safe_div_func_uint16_t_u_u(
                                        ((*l_21) = ((+g_6), l_20)), g_10))))) <
                          0xCA3191B4956E74E8LL),
                         g_10),
                        g_10)),
                    l_24);
    }
  }
  return g_9;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_4[i];
  }
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_9;
  csmith_sink_ = g_10;
  csmith_sink_ = g_22;
  csmith_sink_ = g_26;
  platform_main_end(0, 0);
  return 0;
}
