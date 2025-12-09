// Options:   --seed 200173 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_173.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4[3][4] = {
    {0x0E60F951L, 0x0E60F951L, 0x0E60F951L, 0x0E60F951L},
    {0x0E60F951L, 0x0E60F951L, 0x0E60F951L, 0x0E60F951L},
    {0x0E60F951L, 0x0E60F951L, 0x0E60F951L, 0x0E60F951L}};
static int32_t *g_16 = (void *)0;
static int32_t *volatile *volatile g_15 = &g_16;
static uint32_t g_18[2] = {0x88C55612L, 0x88C55612L};
static int32_t **volatile g_20 = &g_16;

static uint32_t func_1(void);
static int32_t *func_7(uint32_t p_8, const int32_t *p_9);

static uint32_t func_1(void) {
  uint32_t l_2 = 0x3FCB50BFL;
  int32_t *l_3 = &g_4[2][3];
  int32_t l_27[3];
  int i;
  for (i = 0; i < 3; i++)
    l_27[i] = 1L;
  if (((*l_3) = l_2)) {
    uint16_t l_5[3];
    int i;
    for (i = 0; i < 3; i++)
      l_5[i] = 65535UL;
    if (l_5[1]) {
      int64_t l_6[1][4] = {{1L, 1L, 1L, 1L}};
      int i, j;
      return l_6[0][1];
    } else {
      uint32_t *l_21 = &g_18[0];
      uint32_t *l_25 = &g_18[0];
      uint32_t **l_24 = &l_25;
      int32_t l_26 = 0xA1DD7933L;
      (*g_20) = func_7(g_4[2][3], &g_4[0][3]);
      l_27[1] ^=
          ((l_21 == ((*l_24) = ((safe_add_func_uint32_t_u_u(
                                    g_4[2][3], ((l_5[1] ^ 0L) == 0x209AL))),
                                &g_18[0]))) == l_26);
    }
  } else {
    int32_t *l_28 = &g_4[0][3];
    int32_t *l_29 = (void *)0;
    int32_t *l_30 = &g_4[1][3];
    int32_t *l_31 = &g_4[0][0];
    int32_t *l_32 = &l_27[0];
    int32_t *l_33 = &g_4[0][3];
    int32_t *l_34 = (void *)0;
    int32_t *l_35 = &g_4[2][3];
    int32_t *l_36 = &l_27[1];
    int32_t *l_37[3][3];
    uint32_t l_38 = 0UL;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++)
        l_37[i][j] = (void *)0;
    }
    l_38--;
    return (*l_3);
  }
  return g_4[2][3];
}

static int32_t *func_7(uint32_t p_8, const int32_t *p_9) {
  const int32_t *l_11 = &g_4[0][3];
  const int32_t **l_10 = &l_11;
  uint32_t *l_17 = &g_18[0];
  int32_t l_19 = (-8L);
  (*l_10) = p_9;
  l_19 |= (safe_div_func_uint32_t_u_u(
      ((~(g_15 == &g_16)), ((*l_17) |= (g_4[2][3] != (*l_11)))), 0xD0C11E04L));
  return &g_4[0][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_18[i];
  }
  platform_main_end(0, 0);
  return 0;
}
