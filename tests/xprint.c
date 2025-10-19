/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "xprint.h"
#include <stdio.h>
#include <stdint.h>

void xprint(uint8_t * val, size_t count)
{
  for (size_t i = 0; i < count; i++) {
    printf("%02hhX", *val++);
  }
}
