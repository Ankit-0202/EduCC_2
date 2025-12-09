// Options:   --seed 100076 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_076.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
  const int32_t f1;
};

struct S1 {
  const int32_t f0;
  volatile uint32_t f1;
};

struct S2 {
  uint8_t f0;
  uint32_t f1;
  uint64_t f2;
};

static struct S0 g_8 = {1L, 0x6E229EDCL};
static int32_t g_24 = (-1L);
static int32_t *g_28 = &g_24;
static int32_t **const volatile g_27 = &g_28;
static struct S2 g_37 = {9UL, 4294967289UL, 0xBE76DCB0C7B249E3LL};
static struct S2 *volatile g_36 = &g_37;
static struct S1 g_44[3][2] = {
    {{0xD1F73E70L, 0xB68169B2L}, {0xD1F73E70L, 0xB68169B2L}},
    {{0xD1F73E70L, 0xB68169B2L}, {0xD1F73E70L, 0xB68169B2L}},
    {{0xD1F73E70L, 0xB68169B2L}, {0xD1F73E70L, 0xB68169B2L}}};
static struct S1 g_47 = {1L, 0xF624E194L};

static struct S2 func_1(void);
static struct S2 func_2(uint64_t p_3, struct S0 p_4, struct S0 p_5);

static struct S2 func_1(void) {
  int32_t l_6[1];
  struct S0 l_7 = {-9L, 0x7213EC75L};
  struct S2 *l_48 = &g_37;
  int i;
  for (i = 0; i < 1; i++)
    l_6[i] = 0x0FECAFE8L;
  (*l_48) = func_2(l_6[0], l_7, g_8);
  return (*l_48);
}

static struct S2 func_2(uint64_t p_3, struct S0 p_4, struct S0 p_5) {
  uint32_t l_13 = 18446744073709551612UL;
  int32_t *l_25 = &g_24;
  struct S2 l_26 = {0x95L, 0x20F30385L, 0UL};
  struct S1 *l_46 = &g_47;
  if (((0xBCL && (p_4.f0 != (safe_lshift_func_uint16_t_u_u(
                                (safe_sub_func_uint16_t_u_u(l_13, l_13)),
                                l_13)))) > 1UL)) {
    uint32_t l_22[1][2];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_22[i][j] = 1UL;
    }
  lbl_38:
    if (((safe_mul_func_uint16_t_u_u(
             (safe_mul_func_uint64_t_u_u(
                 1UL, (((safe_sub_func_int8_t_s_s(
                            ((safe_mod_func_int16_t_s_s((p_4.f1 & p_3), 5UL)) >
                             g_8.f0),
                            l_22[0][1])) >= g_8.f1) >= l_13))),
             p_5.f0)) &&
         g_8.f1)) {
      int32_t *l_23 = &g_24;
      l_25 = l_23;
    } else {
      (*g_27) = (l_26, l_25);
    }
    for (p_3 = 0; (p_3 >= 5); p_3 = safe_add_func_uint16_t_u_u(p_3, 5)) {
      for (l_13 = 0; (l_13 <= 27); ++l_13) {
        (*l_25) &= 0x769867F5L;
      }
      for (p_5.f0 = 0; (p_5.f0 >= 29);
           p_5.f0 = safe_add_func_uint32_t_u_u(p_5.f0, 9)) {
        struct S2 l_35 = {0UL, 0UL, 8UL};
        (*g_36) = l_35;
        if (p_3)
          goto lbl_38;
      }
    }
  } else {
    struct S2 *l_40 = &g_37;
    struct S2 **l_39[1];
    int i;
    for (i = 0; i < 1; i++)
      l_39[i] = &l_40;
    g_36 = (void *)0;
  }
  for (p_5.f0 = (-13); (p_5.f0 > (-19));
       p_5.f0 = safe_sub_func_int16_t_s_s(p_5.f0, 6)) {
    struct S1 *l_43[4] = {&g_44[2][1], &g_44[2][1], &g_44[2][1], &g_44[2][1]};
    struct S1 **l_45[3];
    int i;
    for (i = 0; i < 3; i++)
      l_45[i] = (void *)0;
    l_46 = l_43[0];
  }
  return l_26;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8.f0;
  csmith_sink_ = g_8.f1;
  csmith_sink_ = g_24;
  csmith_sink_ = g_37.f0;
  csmith_sink_ = g_37.f1;
  csmith_sink_ = g_37.f2;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_47.f0;
  csmith_sink_ = g_47.f1;
  platform_main_end(0, 0);
  return 0;
}
