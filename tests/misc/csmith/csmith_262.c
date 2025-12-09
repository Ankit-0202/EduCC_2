// Options:   --seed 300262 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_262.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int16_t f0;
};

union U1 {
  struct S0 f0;
  int32_t f1;
};

union U2 {
  int32_t f0;
};

static int32_t g_4 = 0xCEFA9D19L;
static union U1 g_14[1] = {{{7L}}};
static int16_t g_33 = 0x3077L;
static int32_t *g_43 = &g_14[0].f1;
static int32_t g_45[1][1] = {{0L}};
static volatile int32_t g_52 = (-9L);
static volatile uint8_t g_53 = 0x72L;
static int32_t g_59 = (-1L);
static volatile int16_t g_62[1][3] = {{(-1L), (-1L), (-1L)}};
static int16_t g_64 = 0x0954L;
static volatile int64_t g_65 = 0x75C8F0ABFABC748ELL;
static volatile uint32_t g_66 = 0xE153341CL;

static uint8_t func_1(void);
static union U1 *func_5(uint16_t p_6, uint8_t p_7, int16_t p_8);
static uint16_t func_9(int32_t *const p_10, union U1 *p_11, uint32_t p_12);

static uint8_t func_1(void) {
  int8_t l_2 = 0xEDL;
  int32_t *l_3[3];
  union U1 *l_13 = &g_14[0];
  uint8_t l_34 = 0x46L;
  union U1 **l_70 = &l_13;
  int i;
  for (i = 0; i < 3; i++)
    l_3[i] = &g_4;
  g_4 |= l_2;
  (*l_70) = func_5(func_9(&g_4, l_13, g_14[0].f0.f0), g_4, l_34);
  return g_45[0][0];
}

static union U1 *func_5(uint16_t p_6, uint8_t p_7, int16_t p_8) {
  struct S0 *l_36[3][1];
  struct S0 **l_35 = &l_36[2][0];
  struct S0 *l_37 = (void *)0;
  int32_t l_46 = 0x8CFB9963L;
  int32_t l_50 = 1L;
  int32_t l_58 = 7L;
  int32_t l_60[1];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_36[i][j] = &g_14[0].f0;
  }
  for (i = 0; i < 1; i++)
    l_60[i] = 0L;
  l_37 = ((*l_35) = (void *)0);
  for (g_33 = 0; (g_33 > 9); g_33++) {
    int32_t *l_42 = (void *)0;
    union U2 l_44 = {0L};
    int32_t l_51 = 0x85063020L;
    int32_t l_56 = 0x92777EF5L;
    int32_t l_57 = (-1L);
    int32_t l_61 = (-8L);
    int32_t l_63 = 0x06A5961BL;
    if (((((safe_lshift_func_uint16_t_u_u(((g_43 = l_42) == (l_44, (void *)0)),
                                          8)) |
           p_8),
          (-10L)) ||
         p_7)) {
      g_4 = ((g_45[0][0] = 0xDE97L) ^ 65526UL);
    } else {
      l_46 ^= p_8;
    }
    if ((l_46 = (-1L))) {
      int32_t *l_47 = (void *)0;
      int32_t *l_48 = (void *)0;
      int32_t *l_49[3][2];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++)
          l_49[i][j] = &g_14[0].f1;
      }
      --g_53;
      ++g_66;
    } else {
      union U1 *l_69[2][1];
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_69[i][j] = &g_14[0];
      }
      return l_69[0][0];
    }
  }
  return &g_14[0];
}

static uint16_t func_9(int32_t *const p_10, union U1 *p_11, uint32_t p_12) {
  uint32_t l_23 = 0xDCA1A1F0L;
  int32_t l_32[2][2];
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_32[i][j] = 0xEE511904L;
  }
  for (p_12 = 0; (p_12 != 59); ++p_12) {
    int8_t l_20[1][2];
    int32_t l_25 = 0x2CF45657L;
    union U1 *l_26 = &g_14[0];
    int32_t l_27 = 0xB3AE5D5EL;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_20[i][j] = 0L;
    }
  }
  return g_33;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_33;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_45[i][j];
    }
  }
  csmith_sink_ = g_52;
  csmith_sink_ = g_53;
  csmith_sink_ = g_59;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_62[i][j];
    }
  }
  csmith_sink_ = g_64;
  csmith_sink_ = g_65;
  csmith_sink_ = g_66;
  platform_main_end(0, 0);
  return 0;
}
