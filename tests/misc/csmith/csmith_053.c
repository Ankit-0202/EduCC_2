// Options:   --seed 100053 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_053.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int8_t f0;
};

static uint32_t g_9 = 0xAFC37186L;
static int32_t g_16 = 9L;
static int32_t g_19[2] = {0xD0E75D5FL, 0xD0E75D5FL};
static struct S1 g_22 = {0x9AL};

static uint32_t func_1(void);
static uint8_t func_4(int32_t p_5, uint16_t p_6, int32_t p_7, uint32_t p_8);

static uint32_t func_1(void) {
  uint8_t l_14[3][1];
  int32_t *l_18 = &g_19[0];
  uint16_t l_34 = 0x8036L;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_14[i][j] = 251UL;
  }
lbl_27:
  (*l_18) &=
      ((safe_div_func_uint8_t_u_u(
           func_4((g_9 != ((safe_mod_func_uint8_t_u_u(
                               (safe_sub_func_uint8_t_u_u(0x4CL, (1L > g_9))),
                               l_14[1][0])) > 0xE7L)),
                  l_14[0][0], l_14[1][0], l_14[0][0]),
           g_16)),
       g_16);
  if ((*l_18)) {
    g_16 = (safe_mul_func_int8_t_s_s(
        (g_22, (!0x85L)),
        (safe_lshift_func_int8_t_s_s(
            (((safe_unary_minus_func_int32_t_s((0xC715L | g_22.f0))) ||
              g_19[0]),
             g_19[0]),
            2))));
  } else {
    for (g_16 = 0; (g_16 <= 1); g_16 += 1) {
      int i;
      if (g_9)
        goto lbl_27;
      (*l_18) = (((~(!(safe_rshift_func_uint8_t_u_s(0x19L, g_19[g_16])))) ==
                  (&g_19[0] == &g_19[0])) < g_19[0]);
    }
  }
  return l_34;
}

static uint8_t func_4(int32_t p_5, uint16_t p_6, int32_t p_7, uint32_t p_8) {
  int32_t *l_15 = &g_16;
  int32_t **l_17 = &l_15;
  (*l_17) = l_15;
  return g_16;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_16;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_19[i];
  }
  csmith_sink_ = g_22.f0;
  platform_main_end(0, 0);
  return 0;
}
