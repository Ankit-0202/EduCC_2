// Options:   --seed 300236 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_236.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  volatile int32_t f0;
};

union U4 {
  volatile uint32_t f0;
  uint32_t f1;
};

union U5 {
  int16_t f0;
};

static int8_t g_5[1] = {(-1L)};
static int64_t g_9 = 0xAFE8B0D193E0566ALL;
static union U4 g_14 = {4294967290UL};
static int32_t g_19 = 0xF93BD5DEL;
static volatile uint64_t g_21[1][1] = {{18446744073709551615UL}};
static int32_t g_26 = 0x22ABF7C2L;
static union U4 g_27 = {4294967286UL};
static uint16_t g_30 = 0x668DL;
static union U1 g_33 = {9L};
static volatile uint16_t **g_36 = (void *)0;
static union U5 g_47 = {0x984BL};
static volatile int32_t g_51 = 0x9B2B2933L;
static uint8_t g_53 = 0xC5L;

static const union U5 func_1(void);
static union U4 func_2(int16_t p_3, int8_t p_4);
static int16_t func_6(int64_t p_7);

static const union U5 func_1(void) {
  int8_t l_28[2];
  int32_t *l_34 = &g_26;
  union U5 l_44[3][3] = {{{0xC7B2L}, {0xC7B2L}, {0xC7B2L}},
                         {{0x38E0L}, {0x8D3FL}, {0x38E0L}},
                         {{0xC7B2L}, {0xC7B2L}, {0xC7B2L}}};
  int i, j;
  for (i = 0; i < 2; i++)
    l_28[i] = (-1L);
  if ((func_2(g_5[0], g_5[0]), l_28[0])) {
    uint16_t *l_29 = &g_30;
    const int32_t *const l_35 = &g_19;
    int64_t *l_45 = (void *)0;
    int64_t **l_46 = &l_45;
    union U1 *l_56[3];
    int i;
    for (i = 0; i < 3; i++)
      l_56[i] = &g_33;
    if ((((*l_29)++) >= ((g_33, l_34) != l_35))) {
      g_36 = g_36;
    } else {
      union U4 **l_37 = (void *)0;
      union U4 *l_38 = &g_27;
      int32_t l_41 = 0x1CC0C7FDL;
      int32_t l_43 = 0xB87C2657L;
      l_38 = &g_14;
      l_43 &= (safe_mod_func_uint32_t_u_u(
          (((l_41 < (((!3L) == 0x1067DCC3L), l_41)), g_27.f0), 0xD8EB7BFBL),
          (*l_35)));
    }
    if ((l_44[2][2], (((*l_46) = l_45) != (g_47, &g_9)))) {
      int32_t *l_48 = &g_19;
      int32_t *l_49 = &g_19;
      int32_t *l_50 = (void *)0;
      int32_t *l_52 = &g_26;
      (*l_34) ^= (-1L);
      ++g_53;
    } else {
      uint32_t l_59 = 0x064544A9L;
      l_56[0] = &g_33;
      (*l_34) = (safe_add_func_uint64_t_u_u(l_59, (g_9 = (-1L))));
    }
  } else {
    for (g_47.f0 = (-26); (g_47.f0 > (-15)); ++g_47.f0) {
      return g_47;
    }
  }
  (*l_34) |= (-9L);
  return g_47;
}

static union U4 func_2(int16_t p_3, int8_t p_4) {
  int64_t *l_8 = &g_9;
  int32_t *l_24 = (void *)0;
  int32_t *l_25 = &g_26;
  (*l_25) |= ((func_6(((*l_8) = ((-10L) <= p_4))) == g_14.f1), g_14.f1);
  return g_27;
}

static int16_t func_6(int64_t p_7) {
  int64_t *l_13 = &g_9;
  int16_t *l_15 = (void *)0;
  int32_t l_16 = 4L;
  int32_t l_17[3];
  int32_t *l_18 = &g_19;
  int32_t *l_20[1];
  int i;
  for (i = 0; i < 3; i++)
    l_17[i] = 0xB6F9B691L;
  for (i = 0; i < 1; i++)
    l_20[i] = (void *)0;
  (*l_18) ^= (safe_mul_func_uint16_t_u_u((!(l_16 ^= (l_13 != (g_14, l_13)))),
                                         l_17[1]));
  g_21[0][0]--;
  return p_7;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_5[i];
  }
  csmith_sink_ = g_9;
  csmith_sink_ = g_14.f0;
  csmith_sink_ = g_14.f1;
  csmith_sink_ = g_19;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_21[i][j];
    }
  }
  csmith_sink_ = g_26;
  csmith_sink_ = g_27.f0;
  csmith_sink_ = g_27.f1;
  csmith_sink_ = g_30;
  csmith_sink_ = g_33.f0;
  csmith_sink_ = g_47.f0;
  csmith_sink_ = g_51;
  csmith_sink_ = g_53;
  platform_main_end(0, 0);
  return 0;
}
