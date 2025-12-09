// Options:   --seed 300201 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_201.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile uint32_t f0;
};

struct S2 {
  volatile uint32_t f0;
  uint32_t f1;
  volatile int8_t f2;
};

static int32_t g_2 = 0xBC6E5C7AL;
static volatile struct S1 g_26 = {0xF2D6273DL};
static uint32_t g_28 = 0xC4DDB84CL;
static int32_t g_31 = 0x6B59229AL;
static volatile struct S2 g_36[3][2] = {
    {{0x48298BBEL, 0x927EED05L, 0xB7L}, {0x48298BBEL, 0x927EED05L, 0xB7L}},
    {{0x48298BBEL, 0x927EED05L, 0xB7L}, {0x48298BBEL, 0x927EED05L, 0xB7L}},
    {{0x48298BBEL, 0x927EED05L, 0xB7L}, {0x48298BBEL, 0x927EED05L, 0xB7L}}};
static volatile struct S2 g_44 = {1UL, 0x1140AE77L, -9L};
static volatile struct S1 g_45 = {0xD5FCA44BL};
static int32_t **volatile g_46 = (void *)0;
static int32_t *g_48[1][3] = {{&g_2, &g_2, &g_2}};
static int32_t **volatile g_47 = &g_48[0][0];

static uint32_t func_1(void);
static int32_t *func_5(int32_t *p_6, uint8_t p_7, uint8_t p_8, uint16_t p_9);
static int32_t *func_10(int32_t p_11, int32_t *p_12);

static uint32_t func_1(void) {
  uint32_t *l_27 = &g_28;
  int32_t *l_29 = (void *)0;
  int32_t *l_30 = &g_31;
  int32_t l_32 = 0x217C7128L;
  uint32_t l_38 = 8UL;
  for (g_2 = 0; (g_2 <= 26); g_2 = safe_add_func_uint16_t_u_u(g_2, 9)) {
    if (g_2)
      break;
  }
  (*g_47) = func_5(
      func_10(
          (+(safe_sub_func_uint32_t_u_u(
              (safe_sub_func_int8_t_s_s(
                  (g_2 >=
                   (safe_add_func_uint16_t_u_u(
                       (safe_lshift_func_uint8_t_u_u(0xEBL, 0)),
                       ((((safe_div_func_uint64_t_u_u(
                              ((safe_add_func_int64_t_s_s(
                                   (((((*l_30) = (((*l_27) = (g_26, g_26.f0)) ||
                                                  g_26.f0)) < l_32) &
                                     65535UL) &&
                                    g_28),
                                   g_2)) > g_2),
                              g_2)) |
                          0L) &&
                         g_31),
                        65527UL)))),
                  g_2)),
              g_2))),
          &g_2),
      l_32, g_2, l_38);
  return g_36[1][1].f0;
}

static int32_t *func_5(int32_t *p_6, uint8_t p_7, uint8_t p_8, uint16_t p_9) {
  int64_t l_41 = 0x7ED469F41AF53C8CLL;
  (*p_6) &= (safe_div_func_uint32_t_u_u(
      l_41,
      (safe_lshift_func_uint8_t_u_u((((g_44, g_45), 246UL) < l_41), g_28))));
  return p_6;
}

static int32_t *func_10(int32_t p_11, int32_t *p_12) {
  volatile struct S2 *l_37 = &g_36[2][1];
  (*l_37) = ((((safe_mul_func_int8_t_s_s(p_11, (+0x6CL))), &g_2) != &p_11),
             g_36[1][1]);
  return &g_2;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_26.f0;
  csmith_sink_ = g_28;
  csmith_sink_ = g_31;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_44.f0;
  csmith_sink_ = g_44.f1;
  csmith_sink_ = g_44.f2;
  csmith_sink_ = g_45.f0;
  platform_main_end(0, 0);
  return 0;
}
