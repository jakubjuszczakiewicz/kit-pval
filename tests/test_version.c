/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "../src/version.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
  if (strlen(kit_pval_version_str) != kit_pval_version_str_len) {
    fprintf(stderr, "Invalid version string length");
    return 1;
  }

  return 0;
}
