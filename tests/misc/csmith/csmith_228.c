// Options:   --seed 300228 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_228.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int64_t f0;
};

static uint8_t g_12 = 255UL;
static uint16_t g_28 = 0xB16EL;
static int32_t g_38 = 8L;
static volatile uint16_t g_40[2] = {0x0638L, 0x0638L};
static volatile uint8_t g_53 = 253UL;

static union U0 func_1(void);
static uint32_t func_5(int32_t p_6);
static int32_t func_21(uint32_t p_22, int32_t p_23);

static union U0 func_1(void) {
  const uint16_t l_4 = 65531UL;
  int32_t l_41 = 0L;
  int32_t *l_42 = &g_38;
  int32_t *l_43 = &l_41;
  int32_t *l_44 = &l_41;
  int32_t *l_45 = &g_38;
  int32_t *l_46 = &l_41;
  int32_t *l_47 = (void *)0;
  int32_t *l_48 = (void *)0;
  int32_t *l_49 = &l_41;
  int32_t *l_50 = &l_41;
  int32_t *l_51 = &l_41;
  int32_t *l_52[1];
  union U0 l_56 = {0xF10DEC53312A7FADLL};
  int i;
  for (i = 0; i < 1; i++)
    l_52[i] = &g_38;
  l_41 &=
      (((safe_lshift_func_int8_t_s_u(((l_4 != func_5(l_4)) >= g_40[0]), 3)) &&
        (-1L)) < l_4);
  ++g_53;
  return l_56;
}

static uint32_t func_5(int32_t p_6) {
  int8_t l_9 = 0xFAL;
  int16_t l_18 = (-1L);
  if (((((safe_add_func_int16_t_s_s(
             (((l_9 | ((g_12 &&
                        (!(safe_mod_func_uint8_t_u_u(
                            (safe_lshift_func_int16_t_s_s((0x78L ^ l_9), g_12)),
                            l_9)))) &&
                       g_12)) &
               l_9) ||
              l_18),
             l_9)) ^
         g_12),
        0x8B166C19L) == g_12)) {
    int8_t l_24 = 0x33L;
    for (l_18 = 0; (l_18 >= (-29)); l_18--) {
      uint16_t *l_27 = &g_28;
      int32_t *l_37 = &g_38;
      (*l_37) =
          func_21((((l_24 >= (safe_rshift_func_uint16_t_u_s(((*l_27)--), 11))),
                    (g_28 & (p_6 | g_28))),
                   0x04102249L),
                  p_6);
      if (g_28)
        break;
    }
  } else {
    uint32_t l_39 = 0xDB51FD9AL;
    return l_39;
  }
  return g_12;
}

static int32_t func_21(uint32_t p_22, int32_t p_23) {
  int64_t l_33 = (-5L);
  for (g_12 = 6; (g_12 < 2); --g_12) {
    l_33 &= p_23;
    for (g_28 = 0; (g_28 > 24); g_28 = safe_add_func_int32_t_s_s(g_28, 4)) {
      int64_t l_36[1];
      int i;
      for (i = 0; i < 1; i++)
        l_36[i] = (-1L);
      return l_36[0];
    }
  }
  return l_33;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_12;
  csmith_sink_ = g_28;
  csmith_sink_ = g_38;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_40[i];
  }
  csmith_sink_ = g_53;
  platform_main_end(0, 0);
  return 0;
}
