// Options:   --seed 300287 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_287.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile uint8_t f0;
};

struct S2 {
  const volatile int8_t f0;
  const uint16_t f1;
};

struct S3 {
  uint32_t f0;
  int16_t f1;
  const int16_t f2;
};

static uint16_t g_15 = 0x89F4L;
static const struct S3 g_16 = {4294967295UL, 0xD65FL, 0xE26CL};
static int64_t g_26 = 0x26ED4BCA925F321ELL;
static int32_t g_28 = (-1L);
static const volatile struct S2 g_39[2][2] = {{{5L, 0x7A76L}, {5L, 0x7A76L}},
                                              {{5L, 0x7A76L}, {5L, 0x7A76L}}};
static int16_t g_45 = (-1L);
static struct S1 g_47 = {1UL};
static int32_t **volatile g_48 = (void *)0;
static int32_t *g_49 = &g_28;
static uint64_t g_54 = 0x135443C7F34FA629LL;

static struct S1 func_1(void);
static struct S3 func_2(int16_t p_3, int64_t p_4, const uint8_t p_5,
                        int32_t p_6);
static uint64_t func_9(int64_t p_10, uint8_t p_11, int8_t p_12,
                       const struct S3 p_13);

static struct S1 func_1(void) {
  int32_t l_14 = 0x278C007CL;
  int16_t *l_44[3];
  int32_t l_46 = 0x27FD5D1AL;
  int8_t l_52 = (-1L);
  uint64_t *l_53 = &g_54;
  int i;
  for (i = 0; i < 3; i++)
    l_44[i] = &g_45;
  if ((0L > (l_46 &= (func_2((safe_add_func_int16_t_s_s(
                                 0x60F7L, (func_9(l_14, g_15, g_15, g_16) !=
                                           0xEBCCE3F50E16FFA9LL))),
                             g_16.f2, g_16.f0, l_14),
                      l_14)))) {
    return g_47;
  } else {
    g_49 = &g_28;
  }
  (*g_49) &=
      (safe_sub_func_uint64_t_u_u(l_52, ((*l_53) = 18446744073709551614UL)));
  return g_47;
}

static struct S3 func_2(int16_t p_3, int64_t p_4, const uint8_t p_5,
                        int32_t p_6) {
  int32_t *l_40 = &g_28;
  (*l_40) &= ((p_4 < 0UL) && ((g_39[1][1], &g_26) == &g_26));
  for (g_28 = 0; (g_28 == (-27)); g_28 = safe_sub_func_int64_t_s_s(g_28, 9)) {
    struct S3 l_43 = {0xE8A77F2AL, -1L, 0x9BADL};
    return l_43;
  }
  return g_16;
}

static uint64_t func_9(int64_t p_10, uint8_t p_11, int8_t p_12,
                       const struct S3 p_13) {
  uint32_t l_24 = 0x3CFCB8F1L;
  int32_t *l_36 = &g_28;
  for (p_10 = 0; (p_10 <= 13); p_10 = safe_add_func_uint8_t_u_u(p_10, 1)) {
    uint32_t l_23 = 0x64939E63L;
    int64_t *l_25 = &g_26;
    int32_t *l_27 = &g_28;
    (*l_27) =
        ((((18446744073709551615UL |
            ((*l_25) =
                 (((safe_sub_func_int16_t_s_s(
                       (safe_mod_func_uint64_t_u_u(l_23, 0xBED857289C089CEDLL)),
                       1UL)) < l_24) &
                  p_13.f0))) >= g_15) |
          g_16.f1) &
         p_10);
  }
  (*l_36) =
      (+(p_12 ||
         (safe_add_func_uint16_t_u_u(
             g_16.f0, ((safe_rshift_func_uint16_t_u_u(
                           ((safe_lshift_func_uint8_t_u_s(p_11, p_12)) >= p_10),
                           g_16.f0)) == 0L)))));
  return g_16.f1;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_15;
  csmith_sink_ = g_16.f0;
  csmith_sink_ = g_16.f1;
  csmith_sink_ = g_16.f2;
  csmith_sink_ = g_26;
  csmith_sink_ = g_28;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_45;
  csmith_sink_ = g_47.f0;
  csmith_sink_ = g_54;
  platform_main_end(0, 0);
  return 0;
}
