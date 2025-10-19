/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef HAVE_INT128

typedef unsigned __int128 uint128_t;

#else

typedef uint32_t uint128_t[4];

#endif

size_t uint128_logA(const uint128_t * a);
size_t uint128_import_dec_str(uint128_t * out, const char * in);
void uint128_export_dec_str(char * out, const uint128_t * in);
uint32_t uint128_div_mod_im(uint128_t * out, const uint128_t * in, uint32_t b);
int uint128_cmp_im(const uint128_t * a, uint32_t b);
uint32_t uint128_lo32(const uint128_t * in);
uint64_t uint128_lo64(const uint128_t * in);
