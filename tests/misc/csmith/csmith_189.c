// Options:   --seed 200189 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_189.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  uint8_t f0;
  const int8_t f1;
  volatile uint32_t f2;
};

union U3 {
  const volatile uint64_t f0;
};

union U4 {
  int32_t f0;
  float f1;
};

static union U4 g_9 = {-5L};
static union U4 *g_8[2] = {&g_9, &g_9};
static int32_t g_17 = (-7L);
static int32_t *const volatile g_16[1] = {&g_17};
static union U4 *g_20 = &g_9;
static uint32_t g_29 = 0x0B2F67ABL;
static const union U3 g_43 = {0x26A25A955069097DLL};
static float g_48 = 0xE.A381E1p-98;
static int64_t g_51 = 0x4198FE831E341F56LL;
static uint16_t g_53 = 0UL;
static struct S1 *g_59 = (void *)0;
static struct S1 g_65[4] = {{251UL, 0x6FL, 7UL},
                            {251UL, 0x6FL, 7UL},
                            {251UL, 0x6FL, 7UL},
                            {251UL, 0x6FL, 7UL}};
static struct S1 *g_64 = &g_65[3];
static struct S1 **volatile g_63[4][3] = {{&g_64, &g_64, &g_64},
                                          {&g_64, &g_64, &g_64},
                                          {&g_64, &g_64, &g_64},
                                          {&g_64, &g_64, &g_64}};
static int32_t g_70 = (-1L);
static int32_t *volatile g_69[3][4] = {{(void *)0, (void *)0, &g_70, &g_70},
                                       {&g_17, &g_70, &g_17, &g_70},
                                       {&g_17, &g_70, &g_70, &g_17}};
static int32_t *volatile g_71 = (void *)0;
static int32_t *volatile g_72[3] = {&g_70, &g_70, &g_70};
static union U3 g_86 = {0x2F7F93178D71A0F8LL};

static union U3 func_1(void);
static union U4 *func_2(const uint64_t p_3, union U4 *p_4, uint32_t p_5,
                        int8_t p_6);

static union U3 func_1(void) {
  const int8_t l_7 = 1L;
  union U4 **l_19 = &g_8[0];
  int32_t l_32 = 0x644184EBL;
  int32_t l_56[2];
  int32_t l_81 = 0xA78CD4FCL;
  int i;
  for (i = 0; i < 2; i++)
    l_56[i] = 5L;
  g_20 = ((*l_19) =
              func_2(l_7, g_8[0],
                     (safe_lshift_func_int16_t_s_u(
                         (safe_sub_func_int64_t_s_s(
                             (safe_sub_func_uint64_t_u_u(18446744073709551615UL,
                                                         0xE7ED6F1860EC01E6LL)),
                             0xBD3AEB59008CF5A8LL)),
                         g_9.f0)),
                     l_7));
  if ((l_7 | l_7)) {
    float l_30 = 0x3.7p+1;
    int32_t l_52 = 0x774D2AD0L;
    int32_t l_54 = (-1L);
    for (g_9.f0 = (-30); (g_9.f0 == 22); ++g_9.f0) {
      int8_t l_23 = 0xB6L;
      uint32_t *l_28 = &g_29;
      int32_t *l_31[2];
      int64_t *l_49 = (void *)0;
      int64_t *l_50[3][2] = {{&g_51, &g_51}, {&g_51, &g_51}, {&g_51, &g_51}};
      uint16_t *l_55[2];
      int i, j;
      for (i = 0; i < 2; i++)
        l_31[i] = &g_17;
      for (i = 0; i < 2; i++)
        l_55[i] = (void *)0;
      l_32 |= (l_23 > ((((*l_28) = (safe_mod_func_int64_t_s_s(
                             (((*l_19) = (*l_19)) != &g_9),
                             0x5F4B3F4B14151C8BLL))) <= 0UL) &&
                       0xD9C7279CL));
      l_56[1] ^=
          (l_32 =
               (l_54 =
                    ((safe_mod_func_uint8_t_u_u(
                         ((safe_rshift_func_int8_t_s_u(
                              ((g_53 =
                                    ((safe_sub_func_int64_t_s_s(
                                         (safe_mod_func_uint32_t_u_u(
                                             ((safe_rshift_func_uint8_t_u_s(
                                                  (g_43, g_17),
                                                  (safe_sub_func_uint8_t_u_u(
                                                      (((l_52 =
                                                             (safe_mul_func_uint16_t_u_u(
                                                                 g_29,
                                                                 (-1L)))) >
                                                        g_29) ^
                                                       g_29),
                                                      g_53)))) >= g_29),
                                             g_17)),
                                         0xD4D34437F0D30663LL)) <= l_54)) !=
                               l_54),
                              g_9.f0)) ||
                          0UL),
                         g_29)) >= 0xF548F9F0L)));
    }
    for (g_17 = 7; (g_17 < (-10)); g_17 = safe_sub_func_int64_t_s_s(g_17, 9)) {
      struct S1 **l_60 = (void *)0;
      struct S1 **l_61 = (void *)0;
      struct S1 **l_62 = &g_59;
      struct S1 **l_66 = &g_64;
      int32_t *l_73 = &l_56[1];
      (*l_66) = ((*l_62) = g_59);
      (*l_73) = (safe_rshift_func_uint8_t_u_s(l_32, 3));
    }
  } else {
    int32_t *l_74 = &g_70;
    int32_t *l_75 = &l_56[1];
    int32_t *l_76 = (void *)0;
    int32_t *l_77 = &g_70;
    int32_t *l_78 = (void *)0;
    int32_t *l_79 = &g_70;
    int32_t *l_80[2][3];
    int8_t l_82 = 0x7FL;
    uint64_t l_83 = 18446744073709551607UL;
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 3; j++)
        l_80[i][j] = &g_70;
    }
    l_83--;
  }
  return g_86;
}

static union U4 *func_2(const uint64_t p_3, union U4 *p_4, uint32_t p_5,
                        int8_t p_6) {
  int32_t *volatile l_18 = &g_17;
  l_18 = g_16[0];
  return &g_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9.f0;
  csmith_sink_ = g_9.f1;
  csmith_sink_ = g_17;
  csmith_sink_ = g_29;
  csmith_sink_ = g_43.f0;
  csmith_sink_ = g_48;
  csmith_sink_ = g_51;
  csmith_sink_ = g_53;
  for (i = 0; i < 4; i++) {
  }
  csmith_sink_ = g_70;
  csmith_sink_ = g_86.f0;
  platform_main_end(0, 0);
  return 0;
}
