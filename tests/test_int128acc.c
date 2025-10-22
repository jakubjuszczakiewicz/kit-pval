/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "../src/int128acc.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "xprint.h"

struct {
  union {
    struct {
      uint64_t a, b;
    };
    uint128_t val;
  };
} data[] = {
#ifdef BIG_ENDIAN
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000001LLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000009LLU },
  { .a = 0x0000000000000000LLU, .b = 0x000000000000000ALLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000400LLU },
  { .a = 0x0000000000000000LLU, .b = 0x00000000FFFFFFFFLLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000100000000LLU },
  { .a = 0x0000000000000000LLU, .b = 0xFFFFFFFFFFFFFFFFLLU },
  { .a = 0x0000000000000001LLU, .b = 0x0000000000000000LLU },
  { .a = 0x00000000FFFFFFFFLLU, .b = 0xFFFFFFFFFFFFFFFFLLU },
  { .a = 0x0000000100000000LLU, .b = 0x0000000000000000LLU },
  { .a = 0xFFFFFFFFFFFFFFFFLLU, .b = 0xFFFFFFFFFFFFFFFFLLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000063LLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000064LLU },
  { .a = 0x000000000000D3C2LLU, .b = 0x1BCECCEDA0FFFFFFLLU },
  { .a = 0x000000000000D3C2LLU, .b = 0x1BCECCEDA1000000LLU },
  { .a = 0x000000000000152DLLU, .b = 0x02C7E14AF67FFFFFLLU },
  { .a = 0x000000000000152DLLU, .b = 0x02C7E14AF6800000LLU },
  { .a = 0x0000000000000000LLU, .b = 0x1999999999999999LLU },
  { .a = 0x0000000000000000LLU, .b = 0x0040100401004010LLU },
  { .a = 0x000000000000021ELLU, .b = 0x19E0C9BAB2400000LLU },
  { .a = 0x000000000000152DLLU, .b = 0x02C7E14AF6800006LLU },
#else
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000000000001LLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000000000009LLU, .b = 0x0000000000000000LLU },
  { .a = 0x000000000000000ALLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000000000400LLU, .b = 0x0000000000000000LLU },
  { .a = 0x00000000FFFFFFFFLLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000100000000LLU, .b = 0x0000000000000000LLU },
  { .a = 0xFFFFFFFFFFFFFFFFLLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000001LLU },
  { .a = 0xFFFFFFFFFFFFFFFFLLU, .b = 0x00000000FFFFFFFFLLU },
  { .a = 0x0000000000000000LLU, .b = 0x0000000100000000LLU },
  { .a = 0xFFFFFFFFFFFFFFFFLLU, .b = 0xFFFFFFFFFFFFFFFFLLU },
  { .a = 0x0000000000000063LLU, .b = 0x0000000000000000LLU },
  { .a = 0x0000000000000064LLU, .b = 0x0000000000000000LLU },
  { .a = 0x1BCECCEDA0FFFFFFLLU, .b = 0x000000000000D3C2LLU },
  { .a = 0x1BCECCEDA1000000LLU, .b = 0x000000000000D3C2LLU },
  { .a = 0x02C7E14AF67FFFFFLLU, .b = 0x000000000000152DLLU },
  { .a = 0x02C7E14AF6800000LLU, .b = 0x000000000000152DLLU },
  { .a = 0x1999999999999999LLU, .b = 0x0000000000000000LLU },
  { .a = 0x0040100401004010LLU, .b = 0x0000000000000000LLU },
  { .a = 0x19E0C9BAB2400000LLU, .b = 0x000000000000021ELLU },
  { .a = 0x02C7E14AF6800006LLU, .b = 0x000000000000152DLLU },
#endif
};

struct {
  const char * input;
  size_t result, output;
  size_t (*func)(uint128_t *, const char *);
} const tests_01[] =
{
  { "0",                                       1,  0,  uint128_import_dec_str },
  { "1",                                       1,  1,  uint128_import_dec_str },
  { "9",                                       1,  2,  uint128_import_dec_str },
  { "10",                                      2,  3,  uint128_import_dec_str },
  { "1024",                                    4,  4,  uint128_import_dec_str },
  { "4294967295",                              10, 5,  uint128_import_dec_str },
  { "4294967296",                              10, 6,  uint128_import_dec_str },
  { "18446744073709551615",                    20, 7,  uint128_import_dec_str },
  { "18446744073709551616",                    20, 8,  uint128_import_dec_str },
  { "79228162514264337593543950335",           29, 9,  uint128_import_dec_str },
  { "79228162514264337593543950336",           29, 10, uint128_import_dec_str },
  { "340282366920938463463374607431768211455", 39, 11, uint128_import_dec_str },
  { "340282366920938463463374607431768211456", 39, 0,  uint128_import_dec_str },
};
const size_t tests_01_len = sizeof(tests_01) / sizeof(tests_01[0]);

struct {
  size_t input;
  size_t result;
  size_t (*func)(const uint128_t *);
} const tests_02[] =
{
  { 0,  1,  uint128_logA },
  { 1,  1,  uint128_logA },
  { 2,  1,  uint128_logA },
  { 3,  2,  uint128_logA },
  { 4,  4,  uint128_logA },
  { 5,  10, uint128_logA },
  { 6,  10, uint128_logA },
  { 7,  20, uint128_logA },
  { 8,  20, uint128_logA },
  { 9,  29, uint128_logA },
  { 10, 29, uint128_logA },
  { 11, 39, uint128_logA },
  { 12, 2,  uint128_logA },
  { 13, 3,  uint128_logA },
  { 14, 24, uint128_logA },
  { 15, 25, uint128_logA },
};
const size_t tests_02_len = sizeof(tests_02) / sizeof(tests_02[0]);

struct {
  const char * output;
  size_t input;
  void (*func)(char *, const uint128_t *);
} const tests_03[] =
{
  { "0",                                       0,  uint128_export_dec_str },
  { "1",                                       1,  uint128_export_dec_str },
  { "9",                                       2,  uint128_export_dec_str },
  { "10",                                      3,  uint128_export_dec_str },
  { "1024",                                    4,  uint128_export_dec_str },
  { "4294967295",                              5,  uint128_export_dec_str },
  { "4294967296",                              6,  uint128_export_dec_str },
  { "18446744073709551615",                    7,  uint128_export_dec_str },
  { "18446744073709551616",                    8,  uint128_export_dec_str },
  { "79228162514264337593543950335",           9,  uint128_export_dec_str },
  { "79228162514264337593543950336",           10, uint128_export_dec_str },
  { "340282366920938463463374607431768211455", 11, uint128_export_dec_str },
  { "99999999999999999999999",                 16, uint128_export_dec_str },
  { "100000000000000000000000",                17, uint128_export_dec_str },
};
const size_t tests_03_len = sizeof(tests_03) / sizeof(tests_03[0]);

struct {
  size_t output, idx1;
  uint32_t val2, result;
  uint32_t (*func)(uint128_t *, const uint128_t *, uint32_t);
} const tests_04[] =
{
  { 18, 7,  10,   5,  uint128_div_mod_im },
  { 19, 7,  1023, 15, uint128_div_mod_im },
  { 20, 17, 10,   0,  uint128_div_mod_im },
  { 20, 21, 10,   6,  uint128_div_mod_im },
};
const size_t tests_04_len = sizeof(tests_04) / sizeof(tests_04[0]);

struct {
  size_t idx1;
  uint32_t val2;
  int result;
  int (*func)(const uint128_t *, uint32_t);
} const tests_05[] =
{
  { 0, 0, 0,          uint128_cmp_im },
  { 0, 1, -1,         uint128_cmp_im },
  { 1, 0, 1,          uint128_cmp_im },
  { 4, 1000, 1,       uint128_cmp_im },
  { 4, 1024, 0,       uint128_cmp_im },
  { 4, 1025, -1,      uint128_cmp_im },
  { 6, 0xFFFFFFFF, 1, uint128_cmp_im },
  { 9, 0xFFFFFFFF, 1, uint128_cmp_im },
};
const size_t tests_05_len = sizeof(tests_05) / sizeof(tests_05[0]);

struct {
  size_t idx1;
  uint32_t result;
  uint32_t (*func)(const uint128_t *);
} const tests_06[] =
{
  { 0,  0,          uint128_lo32 },
  { 1,  1,          uint128_lo32 },
  { 4,  1024,       uint128_lo32 },
  { 5,  0xFFFFFFFF, uint128_lo32 },
  { 6,  0,          uint128_lo32 },
  { 7,  0xFFFFFFFF, uint128_lo32 },
  { 14, 0xA0FFFFFF, uint128_lo32 },
};
const size_t tests_06_len = sizeof(tests_06) / sizeof(tests_06[0]);

struct {
  size_t idx1;
  uint64_t result;
  uint64_t (*func)(const uint128_t *);
} const tests_07[] =
{
  { 0,  0,                  uint128_lo64 },
  { 1,  1,                  uint128_lo64 },
  { 4,  1024,               uint128_lo64 },
  { 7,  0xFFFFFFFFFFFFFFFF, uint128_lo64 },
};
const size_t tests_07_len = sizeof(tests_07) / sizeof(tests_07[0]);

int test_uint128_import_dec_str(void)
{
  for (size_t i = 0; i < tests_01_len; i++) {
    uint128_t res, output;
    memcpy(&res, &data[tests_01[i].output].val, sizeof(uint128_t));

    size_t r = tests_01[i].func(&output, tests_01[i].input);
    if (r != tests_01[i].result) {
      fprintf(stderr, "Test (01a) %zu failed\n", i + 1);
      fprintf(stderr, "%zu\n%zu\n", r, tests_01[i].result);
      return 1;
    }
    if (memcmp(&res, &output, sizeof(uint128_t)) != 0) {
      fprintf(stderr, "Test (01b) %zu failed\n", i + 1);
      xprint((uint8_t *)&output, 16);
      putchar('\n');
      xprint((uint8_t *)&res, 16);
      putchar('\n');
      return 1;
    }
  }

  return 0;
}

int test_uint128_logA(void)
{
  for (size_t i = 0; i < tests_02_len; i++) {
    uint128_t input;
    memcpy(&input, &data[tests_02[i].input].val, sizeof(uint128_t));

    size_t r = tests_02[i].func(&input);
    if (r != tests_02[i].result) {
      fprintf(stderr, "Test (02) %zu failed\n", i + 1);
      fprintf(stderr, "%zu\n%zu\n", r, tests_02[i].result);
      return 1;
    }
  }

  return 0;
}

int test_uint128_export_dec_str(void)
{
  char output[48];
  for (size_t i = 0; i < tests_03_len; i++) {
    uint128_t input;
    memcpy(&input, &data[tests_03[i].input].val, sizeof(uint128_t));
    memset(output, 0, sizeof(output));

    tests_03[i].func(output, &input);
    if (strcmp(tests_03[i].output, output) != 0) {
      fprintf(stderr, "Test (03) %zu failed\n", i + 1);
      fprintf(stderr, "%s\n%s\n", tests_03[i].output, output);
      return 1;
    }
  }

  return 0;
}

int test_uint128_div_mod_im(void)
{
  for (size_t i = 0; i < tests_04_len; i++) {
    uint128_t a, output, res;
    memcpy(&res, &data[tests_04[i].output].val, sizeof(uint128_t));
    memcpy(&a, &data[tests_04[i].idx1].val, sizeof(uint128_t));
    uint32_t b = tests_04[i].val2;

    uint32_t r = tests_04[i].func(&output, &a, b);
    if (r != tests_04[i].result) {
      fprintf(stderr, "Test (04a) %zu failed\n", i + 1);
      fprintf(stderr, "%u\n%u\n", r, tests_04[i].result);
      return 1;
    }
    if (memcmp(&res, &output, sizeof(uint128_t)) != 0) {
      fprintf(stderr, "Test (04b) %zu failed\n", i + 1);
      xprint((uint8_t *)&output, 16);
      putchar('\n');
      xprint((uint8_t *)&res, 16);
      putchar('\n');
      return 1;
    }
  }

  return 0;
}

int test_uint128_cmp_im(void)
{
  for (size_t i = 0; i < tests_05_len; i++) {
    uint128_t a;
    memcpy(&a, &data[tests_05[i].idx1].val, sizeof(uint128_t));
    uint32_t b = tests_05[i].val2;

    int r = tests_05[i].func(&a, b);
    if (r != tests_05[i].result) {
      fprintf(stderr, "Test (05) %zu failed\n", i + 1);
      fprintf(stderr, "%d\n%d\n", r, tests_05[i].result);
      return 1;
    }
  }

  return 0;
}

int test_uint128_lo32(void)
{
  for (size_t i = 0; i < tests_06_len; i++) {
    uint128_t a;
    memcpy(&a, &data[tests_06[i].idx1].val, sizeof(uint128_t));

    uint32_t r = tests_06[i].func(&a);
    if (r != tests_06[i].result) {
      fprintf(stderr, "Test (06) %zu failed\n", i + 1);
      fprintf(stderr, "%08X\n%08X\n", r, tests_06[i].result);
      return 1;
    }
  }

  return 0;
}

int test_uint128_lo64(void)
{
  for (size_t i = 0; i < tests_07_len; i++) {
    uint128_t a;
    memcpy(&a, &data[tests_07[i].idx1].val, sizeof(uint128_t));

    uint64_t r = tests_07[i].func(&a);
    if (r != tests_07[i].result) {
      fprintf(stderr, "Test (07) %zu failed\n", i + 1);
      fprintf(stderr, "%016" PRIu64 "X\n%016" PRIu64 "X\n", r,
          tests_07[i].result);
      return 1;
    }
  }

  return 0;
}

int main(void)
{
  int r;
  r = test_uint128_import_dec_str();
  if (r)
    return r;
  r = test_uint128_logA();
  if (r)
    return r;
  r = test_uint128_export_dec_str();
  if (r)
    return r;
  r = test_uint128_div_mod_im();
  if (r)
    return r;
  r  = test_uint128_cmp_im();
  if (r)
    return r;
  r = test_uint128_lo32();
  if (r)
    return r;
  r = test_uint128_lo64();
  if (r)
    return r;

  return 0;
}
