/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "../src/printer.h"
#include <stdio.h>
#include <string.h>

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
  { .a = 0x0000000000000000LLU, .b = 0x00000000000003E7LLU },
  { .a = 0x0000000000000000LLU, .b = 0x00000000000F423FLLU },
  { .a = 0x0000000000000000LLU, .b = 0x0004000000000000LLU },
  { .a = 0xFFFFFFFFFFFFFFFFLLU, .b = 0xFFFFFFFFFFFFFFFFLLU },
#else
  { .a = 0x0000000000000000LLU, .b = 0x0000000000000000LLU },
  { .a = 0x00000000000003E7LLU, .b = 0x0000000000000000LLU },
  { .a = 0x00000000000F423FLLU, .b = 0x0000000000000000LLU },
  { .a = 0x0004000000000000LLU, .b = 0x0000000000000000LLU },
  { .a = 0xFFFFFFFFFFFFFFFFLLU, .b = 0xFFFFFFFFFFFFFFFFLLU },
#endif
};

struct {
  size_t idx1;
  const char * output;
  unsigned int prefix_avail;
  unsigned int acomma;
  uint32_t base;
  int (*func)(char *, const uint128_t *, const print_cfg * config);
} const tests_01[] =
{
  { 0, "0",                                       0,  2, 1024, print_pval },
  { 1, "0.97ki",                                  2,  2, 1024, print_pval },
  { 2, "976.56ki",                                0,  2, 1024, print_pval },
  { 2, "976.56ki",                                3,  2, 1024, print_pval },
  { 2, "976.56ki",                                7,  2, 1024, print_pval },
  { 2, "0.95Mi",                                  4,  2, 1024, print_pval },
  { 2, "0.00Gi",                                  8,  2, 1024, print_pval },
  { 3, "1.00Pi",                                  0,  2, 1024, print_pval },
  { 3, "1125899906842624",                        1,  2, 1024, print_pval },
  { 3, "1099511627776.00ki",                      2,  2, 1024, print_pval },
  { 3, "1125899906842.62k",                       2,  2, 1000, print_pval },
  { 3, "1073741824.00Mi",                         4,  2, 1024, print_pval },
  { 3, "1125899906.84M",                          4,  2, 1000, print_pval },
  { 3, "1.00Pi",                                  32, 2, 1024, print_pval },
  { 3, "1.12P",                                   32, 2, 1000, print_pval },
  { 3, "1.125P",                                  32, 3, 1000, print_pval },
  { 3, "1073741824.000Mi",                        4,  3, 1024, print_pval },
  { 3, "1125899906.842M",                         4,  3, 1000, print_pval },
  { 3, "0.001E",                                  64, 3, 1000, print_pval },
  { 3, "0.001E",                                  64, 3, 1000, print_pval },
  { 4, "281474976710655.99Yi",                    0,  2, 1024, print_pval },
  { 4, "340282366920938.46Y",                     0,  2, 1000, print_pval },
  { 4, "340282366920938463463374607431768211455", 1,  2, 1024, print_pval },
};
const size_t tests_01_len = sizeof(tests_01) / sizeof(tests_01[0]);

int test_print_pval(void)
{
  for (size_t i = 0; i < tests_01_len; i++) {
    uint128_t input;
    memcpy(&input, &data[tests_01[i].idx1].val, sizeof(uint128_t));
    print_cfg config;
    config.prefix_avail = tests_01[i].prefix_avail;
    config.base = tests_01[i].base;
    config.acomma = tests_01[i].acomma;
    char output[48];
    memset(output, 0, sizeof(output));

    size_t r = tests_01[i].func(output, &input, &config);
    if (r != 0) {
      fprintf(stderr, "Test (01a) %zu failed\n", i + 1);
      fprintf(stderr, "%zu\n0\n", r);
      return 1;
    }
    if (strcmp(output, tests_01[i].output) != 0) {
      fprintf(stderr, "Test (01b) %zu failed\n", i + 1);
      fprintf(stderr, "%s\n%s\n", tests_01[i].output, output);
      return 1;
    }
  }

  return 0;
}

int main(void)
{
  int r = test_print_pval();
  if (r)
    return r;
  return 0;
}
