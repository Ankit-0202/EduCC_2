// Options:   --seed 200195 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_195.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int8_t g_6 = 0x23L;
static int8_t g_7 = 0L;
static volatile int32_t g_11 = 0xF6802998L;
static volatile int32_t *volatile g_10 = &g_11;
static volatile int32_t *volatile g_13[1][1] = {{&g_11}};
static volatile int32_t *volatile g_14 = (void *)0;
static int32_t g_18[4] = {7L, 7L, 7L, 7L};
static int32_t g_19 = 1L;

static int8_t func_1(void);
static int8_t func_3(int64_t p_4, int8_t p_5);

static int8_t func_1(void) {
  uint32_t l_2[3][3] = {{4294967290UL, 0xF1DBECCCL, 0xF1DBECCCL},
                        {4294967290UL, 0xF1DBECCCL, 0xF1DBECCCL},
                        {4294967290UL, 0xF1DBECCCL, 0xF1DBECCCL}};
  int8_t *l_16 = &g_7;
  int32_t *l_17 = &g_18[3];
  int i, j;
  g_19 &= ((*l_17) &= ((l_2[2][2], 0xC0L) | ((*l_16) = func_3(g_6, g_7))));
  return (*l_17);
}

static int8_t func_3(int64_t p_4, int8_t p_5) {
  volatile int32_t *l_15[3][3] = {{&g_11, &g_11, &g_11},
                                  {(void *)0, (void *)0, (void *)0},
                                  {&g_11, &g_11, &g_11}};
  int i, j;
  for (p_5 = 0; (p_5 >= 10); p_5++) {
    volatile int32_t *volatile *l_12 = &g_10;
    (*l_12) = g_10;
    (*l_12) = (*l_12);
  }
  (*g_10) = (*g_10);
  return p_4;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_18[i];
  }
  csmith_sink_ = g_19;
  platform_main_end(0, 0);
  return 0;
}
