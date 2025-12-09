// Options:   --seed 100044 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_044.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  const volatile uint64_t f0;
};

union U2 {
  uint32_t f0;
};

static uint64_t g_13 = 6UL;
static int16_t g_20 = 0x2F67L;
static union U0 g_21 = {0x6E229EDCA8FECF79LL};
static uint8_t g_22 = 0UL;
static int32_t g_27 = 0xD96711DBL;
static int32_t *g_26 = &g_27;
static int32_t **volatile g_25 = &g_26;
static int32_t *volatile g_30 = &g_27;
static int8_t g_39[1] = {0x0FL};
static int32_t g_41 = (-2L);
static int32_t *volatile g_40 = &g_41;

static uint32_t func_1(void);
static uint32_t func_2(uint64_t p_3, int32_t p_4, int64_t p_5,
                       const union U2 p_6, int64_t p_7);

static uint32_t func_1(void) {
  uint32_t l_8 = 18446744073709551610UL;
  int32_t l_11 = (-1L);
  uint64_t *l_12 = &g_13;
  const union U2 l_23 = {0x9E3D3B0CL};
  int64_t l_24 = 4L;
  const int32_t *l_36 = &g_27;
  const int32_t **l_35 = &l_36;
  (*g_30) =
      (func_2(l_8,
              ((safe_add_func_uint8_t_u_u(
                   ((((--(*l_12)) >=
                      (safe_mod_func_uint64_t_u_u(
                          (safe_mod_func_uint16_t_u_u(
                              (g_22 = (g_20 & (g_21, 0x24DC41FD9D089051LL))),
                              g_20)),
                          l_8))) >= l_8) < l_11),
                   g_20)) < g_20),
              l_8, l_23, l_24),
       (*g_26));
  for (g_27 = 0; (g_27 > 20); ++g_27) {
    int32_t l_37 = 0L;
    int8_t *l_38 = &g_39[0];
    (*g_40) &=
        (((*l_38) = (safe_div_func_int32_t_s_s((l_35 == (void *)0), l_37))) ||
         (**l_35));
  }
  return g_22;
}

static uint32_t func_2(uint64_t p_3, int32_t p_4, int64_t p_5,
                       const union U2 p_6, int64_t p_7) {
  int32_t *l_28 = &g_27;
  int32_t **l_29 = &g_26;
  (*g_25) = &p_4;
  (*l_29) = l_28;
  return p_5;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_13;
  csmith_sink_ = g_20;
  csmith_sink_ = g_21.f0;
  csmith_sink_ = g_22;
  csmith_sink_ = g_27;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_39[i];
  }
  csmith_sink_ = g_41;
  platform_main_end(0, 0);
  return 0;
}
