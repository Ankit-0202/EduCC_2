// Options:   --seed 200170 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_170.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  uint16_t f0;
  volatile int64_t f1;
};

static union U0 g_7 = {65534UL};
static int64_t g_9 = 6L;
static int32_t g_16[2] = {1L, 1L};
static int32_t *volatile g_65[2][2] = {{&g_16[0], &g_16[0]},
                                       {&g_16[0], &g_16[0]}};
static int32_t *volatile g_66 = &g_16[1];
static float g_73 = 0x0.0A6B56p-61;

static uint32_t func_1(void);
static int32_t func_2(uint16_t p_3, uint32_t p_4);

static uint32_t func_1(void) {
  int64_t *l_8 = &g_9;
  int32_t l_10 = 0L;
  int16_t l_23 = 0xA82EL;
  uint64_t l_25 = 0x6255D580090AE735LL;
  int32_t l_42 = (-2L);
  int32_t l_47 = 4L;
  int32_t l_49 = 0L;
  int32_t l_50 = 6L;
  int32_t l_52 = 0x5721BA6CL;
  int32_t l_53 = 0x479274D8L;
  int32_t l_54 = (-1L);
  int32_t l_55 = 0x6BEAEC5EL;
  int32_t l_56 = 0x1B0934BFL;
  int32_t l_57[2][2];
  int64_t l_71 = (-10L);
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_57[i][j] = 1L;
  }
  if (func_2(((((*l_8) = (safe_sub_func_uint64_t_u_u(
                    ((g_7, 0L) || (-3L)), 7UL))) == l_10) >= 0x3C0BF90AL),
             l_10)) {
    float l_24 = 0x6.488A97p+85;
    int32_t l_37 = 0x5E45DB0FL;
    int32_t l_38 = 0x9A325CF1L;
    int32_t l_39 = 0L;
    int32_t l_40 = 0xF5EB7F46L;
    int32_t l_41 = 1L;
    int32_t l_43 = 0xB686461DL;
    int32_t l_44 = 0xA4AAC465L;
    int32_t l_45 = (-4L);
    int32_t l_48 = 0x441E233CL;
    int32_t l_51[3][4] = {{0x4278D6BFL, 0x4278D6BFL, 0x4278D6BFL, 0x4278D6BFL},
                          {0x4278D6BFL, 0x4278D6BFL, 0x4278D6BFL, 0x4278D6BFL},
                          {0x4278D6BFL, 0x4278D6BFL, 0x4278D6BFL, 0x4278D6BFL}};
    int i, j;
    for (g_9 = 29; (g_9 == 10); g_9--) {
      int32_t *l_19 = &l_10;
      int32_t *l_20 = &l_10;
      int32_t *l_21 = (void *)0;
      int32_t *l_22[1];
      int i;
      for (i = 0; i < 1; i++)
        l_22[i] = &g_16[0];
      --l_25;
    }
    for (g_9 = 15; (g_9 < 7); g_9--) {
      int32_t *l_30 = &g_16[0];
      int32_t *l_31 = &g_16[0];
      int32_t *l_32 = &g_16[1];
      int32_t *l_33 = &g_16[1];
      int32_t *l_34 = &g_16[0];
      int32_t *l_35 = &g_16[1];
      int32_t *l_36[1][3];
      int32_t l_46[1][4];
      uint16_t l_58 = 0xEF87L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_36[i][j] = &g_16[0];
      }
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++)
          l_46[i][j] = 1L;
      }
      --l_58;
    }
  } else {
    if ((&g_9 == &g_9)) {
      (*g_66) |= (safe_mul_func_int16_t_s_s(g_9, (g_9 >= (0x20C4L < g_9))));
    } else {
      float *l_72 = &g_73;
      (*l_72) =
          ((safe_mod_func_int16_t_s_s(
               0x0E86L,
               ((safe_add_func_uint32_t_u_u(g_7.f0, 0xD9B7243DL)), g_16[0]))),
           l_71);
    }
    return g_7.f0;
  }
  return g_9;
}

static int32_t func_2(uint16_t p_3, uint32_t p_4) {
  for (p_4 = 25; (p_4 < 34); p_4 = safe_add_func_int16_t_s_s(p_4, 5)) {
    for (p_3 = 7; (p_3 >= 37); p_3 = safe_add_func_uint16_t_u_u(p_3, 3)) {
      int32_t *l_15 = &g_16[0];
      l_15 = l_15;
    }
    if (g_16[0])
      continue;
  }
  return g_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7.f0;
  csmith_sink_ = g_9;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_16[i];
  }
  csmith_sink_ = g_73;
  platform_main_end(0, 0);
  return 0;
}
