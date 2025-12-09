// Options:   --seed 100041 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_041.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
  int64_t f1;
};

struct S1 {
  volatile uint64_t f0;
  int64_t f1;
  int16_t f2;
};

static volatile int32_t g_2[4] = {0xD386CCE5L, 0xD386CCE5L, 0xD386CCE5L,
                                  0xD386CCE5L};
static volatile int32_t g_3 = 6L;
static int32_t g_4 = 0xA6DEEC54L;
static volatile int32_t g_7[4][1] = {
    {(-1L)}, {0x0FA51669L}, {(-1L)}, {0x0FA51669L}};
static volatile int32_t g_8 = 0xA57B5BF2L;
static volatile int32_t g_9 = 0x5047C4D1L;
static volatile int32_t g_10 = 0L;
static volatile int32_t g_11[1][2] = {{0xCE4A6F44L, 0xCE4A6F44L}};
static volatile int32_t g_12 = 1L;
static int32_t g_13 = 0xEA53061EL;
static int8_t g_20[1] = {0x45L};
static int8_t *g_19 = &g_20[0];
static struct S1 g_21[3] = {
    {0x9E885DC1B6EAB3CFLL, 0x1320F2D6273D5943LL, 0x2F7CL},
    {0x9E885DC1B6EAB3CFLL, 0x1320F2D6273D5943LL, 0x2F7CL},
    {0x9E885DC1B6EAB3CFLL, 0x1320F2D6273D5943LL, 0x2F7CL}};
static int16_t g_29[3] = {0xF767L, 0xF767L, 0xF767L};
static uint16_t g_35 = 65529UL;
static uint16_t g_37 = 65535UL;
static int32_t g_40 = 0x0E848967L;
static struct S0 g_56 = {-4L, 0x4A98A1BD053A6575LL};
static struct S0 *g_55 = &g_56;
static struct S0 *g_60 = &g_56;
static struct S0 *g_61 = &g_56;

static uint32_t func_1(void);
static int64_t func_16(int8_t *p_17, int8_t *const p_18);

static uint32_t func_1(void) {
  uint8_t l_62 = 0x7AL;
  for (g_4 = (-24); (g_4 >= (-5)); g_4 = safe_add_func_uint32_t_u_u(g_4, 1)) {
    for (g_13 = 0; (g_13 < (-3)); g_13 = safe_sub_func_int16_t_s_s(g_13, 3)) {
      uint16_t l_51[3][3] = {{5UL, 5UL, 5UL}, {5UL, 5UL, 5UL}, {5UL, 5UL, 5UL}};
      int32_t *l_52 = &g_40;
      int i, j;
      (*l_52) = (func_16(g_19, (g_21[2], &g_20[0])) & l_51[2][1]);
      for (g_37 = 0; (g_37 > 44); g_37 = safe_add_func_int16_t_s_s(g_37, 6)) {
        struct S0 **l_57 = &g_55;
        struct S0 *l_59[4] = {(void *)0, (void *)0, (void *)0, (void *)0};
        struct S0 **l_58[3];
        int i;
        for (i = 0; i < 3; i++)
          l_58[i] = &l_59[3];
        g_61 = (g_60 = ((*l_57) = g_55));
        return (*l_52);
      }
    }
  }
  return l_62;
}

static int64_t func_16(int8_t *p_17, int8_t *const p_18) {
  int8_t **l_24[4];
  int32_t l_25 = 0xAFE2499EL;
  int16_t *l_26 = &g_21[2].f2;
  int16_t *l_27 = (void *)0;
  int16_t *l_28 = &g_29[0];
  int32_t l_32 = 2L;
  int32_t l_41 = 0x98BA832AL;
  int i;
  for (i = 0; i < 4; i++)
    l_24[i] = &g_19;
  if (((safe_rshift_func_int16_t_s_s(
           ((*l_28) = ((*l_26) = (((g_19 = (void *)0) == &g_20[0]) <= l_25))),
           2)) |
       (-9L))) {
    uint16_t *l_36[4];
    int32_t l_38 = 0xDFDA84ADL;
    int i;
    for (i = 0; i < 4; i++)
      l_36[i] = &g_37;
    for (l_25 = (-2); (l_25 < 2); ++l_25) {
      uint16_t *l_33 = (void *)0;
      uint16_t *l_34 = &g_35;
      int32_t *l_39[4];
      int i;
      for (i = 0; i < 4; i++)
        l_39[i] = &g_40;
      l_41 &= (((l_32 ^ ((*l_34) = 1UL)) == (l_36[3] == &g_37)) >= l_38);
    }
  } else {
    uint16_t l_48 = 65533UL;
    for (g_40 = 23; (g_40 >= (-3)); g_40--) {
      for (l_32 = 1; (l_32 > (-23)); --l_32) {
        int32_t *l_46 = &l_41;
        int32_t *l_47[2];
        int i;
        for (i = 0; i < 2; i++)
          l_47[i] = &l_25;
        l_48--;
      }
      return g_37;
    }
  }
  return l_32;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_7[i][j];
    }
  }
  csmith_sink_ = g_8;
  csmith_sink_ = g_9;
  csmith_sink_ = g_10;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_11[i][j];
    }
  }
  csmith_sink_ = g_12;
  csmith_sink_ = g_13;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_20[i];
  }
  for (i = 0; i < 3; i++) {
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_29[i];
  }
  csmith_sink_ = g_35;
  csmith_sink_ = g_37;
  csmith_sink_ = g_40;
  csmith_sink_ = g_56.f0;
  csmith_sink_ = g_56.f1;
  platform_main_end(0, 0);
  return 0;
}
