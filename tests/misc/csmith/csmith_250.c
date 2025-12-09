// Options:   --seed 300250 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_250.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_16 = (-1L);
static int32_t g_19 = 9L;
static uint64_t g_20 = 1UL;
static int32_t g_22[2] = {(-5L), (-5L)};
static int32_t *g_21[1][1] = {{&g_22[1]}};
static volatile int32_t g_30 = 0xD5D08818L;
static volatile int32_t *g_29 = &g_30;
static volatile int32_t *volatile *volatile g_28 = &g_29;
static volatile int32_t *volatile *volatile *g_27 = &g_28;
static int32_t *g_33 = (void *)0;

static int64_t func_1(void);
static int32_t *func_2(uint32_t p_3, int32_t *p_4);
static int32_t *func_6(int64_t p_7, uint16_t p_8, int32_t *p_9, int32_t p_10,
                       int8_t p_11);

static int64_t func_1(void) {
  int64_t l_5 = 0x02D149FEBB6748F6LL;
  int8_t l_17 = 0x51L;
  int32_t *l_18 = &g_19;
  uint16_t l_23[1][2];
  int32_t **l_32 = &g_21[0][0];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_23[i][j] = 0xD467L;
  }
  g_33 =
      ((*l_32) = func_2(
           l_5,
           func_6(
               l_5,
               ((safe_add_func_uint16_t_u_u(
                    (((*l_18) =
                          ((((safe_lshift_func_int16_t_s_s(g_16, l_5)) | l_5),
                            l_17) &
                           l_17)) ^
                     g_20),
                    g_20)) &&
                (*l_18)),
               g_21[0][0], l_23[0][0], g_22[1])));
  return g_20;
}

static int32_t *func_2(uint32_t p_3, int32_t *p_4) {
  int32_t **l_26 = &g_21[0][0];
  volatile int32_t *volatile *volatile *l_31 = &g_28;
  (*l_26) = p_4;
  l_31 = g_27;
  return (*l_26);
}

static int32_t *func_6(int64_t p_7, uint16_t p_8, int32_t *p_9, int32_t p_10,
                       int8_t p_11) {
  int32_t **l_25 = (void *)0;
  int32_t ***l_24 = &l_25;
  (*l_24) = &g_21[0][0];
  return (*l_25);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_16;
  csmith_sink_ = g_19;
  csmith_sink_ = g_20;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_22[i];
  }
  csmith_sink_ = g_30;
  platform_main_end(0, 0);
  return 0;
}
