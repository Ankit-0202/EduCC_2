// Options:   --seed 300219 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_219.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_9 = 0x735E4B78L;
static int16_t g_25[3][3] = {{0xF446L, 0xF446L, 0xF446L},
                             {(-7L), (-10L), (-7L)},
                             {0xF446L, 0xF446L, 0xF446L}};
static int32_t g_28 = 0xC2F1FCC1L;
static int32_t *volatile g_32[3][2] = {
    {(void *)0, (void *)0}, {(void *)0, (void *)0}, {(void *)0, (void *)0}};
static int32_t *volatile g_33 = &g_28;
static int32_t g_37 = (-1L);
static int32_t *g_40 = &g_37;
static int32_t **volatile g_39 = &g_40;

static int16_t func_1(void);
static uint16_t func_2(uint16_t p_3, uint16_t p_4, uint32_t p_5,
                       const uint32_t p_6, int8_t p_7);
static const int32_t func_12(int32_t p_13, uint16_t p_14);

static int16_t func_1(void) {
  int16_t l_8[3];
  int32_t *l_36 = &g_37;
  int32_t **l_38 = &l_36;
  int i;
  for (i = 0; i < 3; i++)
    l_8[i] = 0L;
  (*l_36) |= (0x76AAL || func_2((l_8[1] <= l_8[1]), g_9, g_9, g_9, l_8[1]));
  (*g_39) = ((*l_38) = &g_28);
  return g_37;
}

static uint16_t func_2(uint16_t p_3, uint16_t p_4, uint32_t p_5,
                       const uint32_t p_6, int8_t p_7) {
  uint16_t l_16 = 65529UL;
  for (g_9 = 2; (g_9 > 15); ++g_9) {
    uint8_t l_15 = 8UL;
    (*g_33) = func_12(l_15, l_16);
    for (p_5 = 0; (p_5 != 4); p_5 = safe_add_func_uint32_t_u_u(p_5, 4)) {
      if (p_7)
        break;
    }
  }
  return l_16;
}

static const int32_t func_12(int32_t p_13, uint16_t p_14) {
  int32_t l_23 = 0x26128F3BL;
  int16_t *l_24 = &g_25[1][2];
  int32_t *l_26 = (void *)0;
  int32_t *l_27 = &g_28;
  (*l_27) &=
      ((safe_sub_func_uint16_t_u_u(
           0xE652L, ((*l_24) ^= (safe_rshift_func_uint8_t_u_s(
                         ((safe_rshift_func_uint8_t_u_s(
                              (g_9 || ((l_23 & g_9) < 0x87E3BC4AEE507704LL)),
                              3)) != l_23),
                         2))))) >= p_13);
  if ((*l_27)) {
    int32_t **l_29 = &l_26;
    (*l_29) = &p_13;
  } else {
    (*l_27) &= ((safe_lshift_func_uint16_t_u_s((0xF844L | 0x928FL), 11)) | 1L);
  }
  return p_13;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_25[i][j];
    }
  }
  csmith_sink_ = g_28;
  csmith_sink_ = g_37;
  platform_main_end(0, 0);
  return 0;
}
