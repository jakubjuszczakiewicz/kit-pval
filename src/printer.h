/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "int128acc.h"

extern char prefix_list[];

typedef struct print_cfg
{
  unsigned int prefix_avail;
  unsigned int acomma;
  uint32_t base;
} print_cfg;

int print_pval(char * output, const uint128_t * val, const print_cfg * config);
