/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "version.h"
#include <string.h>

#define VERSION_MAJOR 1
#define VERSION_MINOR 3
#define VERSION_PATCH 1
#define VERSION_SUBSTR ""

#define STR(s) #s
#define MAKE_VER(ma, mi, pa, st) (STR(ma) "." STR(mi) "." STR(pa) st)

#define VERSION_STR MAKE_VER(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_SUBSTR)

uint16_t kit_pval_version[3] = { VERSION_MAJOR, VERSION_MINOR,
    VERSION_PATCH };
#if (!defined(USE_WINAPI)) || defined(IS_MINGW)
size_t kit_pval_version_str_len = strlen(VERSION_STR);
char kit_pval_version_str[] = VERSION_STR;
#else
char kit_pval_version_str[] = VERSION_STR;
size_t kit_pval_version_str_len = sizeof(kit_pval_version_str) - 1;
#endif
