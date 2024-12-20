/* Copyright (c) 2024 Krypto-IT Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "int128acc.h"
#include <string.h>

union {
  uint128_t u128;
  uint32_t u32[4];
} digits[] =
{
#ifdef BIG_ENDIAN
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x0000000A } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x00000064 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x000003E8 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x00002710 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x000186A0 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x000F4240 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x00989680 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x05F5E100 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000000, 0x3B9ACA00 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000002, 0x540BE400 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000017, 0x4876E800 } },
  { .u32 = { 0x00000000, 0x00000000, 0x000000E8, 0xD4A51000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00000918, 0x4E72A000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00005AF3, 0x107A4000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x00038D7E, 0xA4C68000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x002386F2, 0x6FC10000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x01634578, 0x5D8A0000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x0DE0B6B3, 0xA7640000 } },
  { .u32 = { 0x00000000, 0x00000000, 0x8AC72304, 0x89E80000 } },
  { .u32 = { 0x00000000, 0x00000005, 0x6BC75E2D, 0x63100000 } },
  { .u32 = { 0x00000000, 0x00000036, 0x35C9ADC5, 0xDEA00000 } },
  { .u32 = { 0x00000000, 0x0000021E, 0x19E0C9BA, 0xB2400000 } },
  { .u32 = { 0x00000000, 0x0000152D, 0x02C7E14A, 0xF6800000 } },
  { .u32 = { 0x00000000, 0x0000D3C2, 0x1BCECCED, 0xA1000000 } },
  { .u32 = { 0x00000000, 0x00084595, 0x16140148, 0x4A000000 } },
  { .u32 = { 0x00000000, 0x0052B7D2, 0xDCC80CD2, 0xE4000000 } },
  { .u32 = { 0x00000000, 0x033B2E3C, 0x9FD0803C, 0xE8000000 } },
  { .u32 = { 0x00000000, 0x204FCE5E, 0x3E250261, 0x10000000 } },
  { .u32 = { 0x00000001, 0x431E0FAE, 0x6D7217CA, 0xA0000000 } },
  { .u32 = { 0x0000000C, 0x9F2C9CD0, 0x4674EDEA, 0x40000000 } },
  { .u32 = { 0x0000007E, 0x37BE2022, 0xC0914B26, 0x80000000 } },
  { .u32 = { 0x000004EE, 0x2D6D415B, 0x85ACEF81, 0x00000000 } },
  { .u32 = { 0x0000314D, 0xC6448D93, 0x38C15B0A, 0x00000000 } },
  { .u32 = { 0x0001ED09, 0xBEAD87C0, 0x378D8E64, 0x00000000 } },
  { .u32 = { 0x00134261, 0x72C74D82, 0x2B878FE8, 0x00000000 } },
  { .u32 = { 0x00C097CE, 0x7BC90715, 0xB34B9F10, 0x00000000 } },
  { .u32 = { 0x0785EE10, 0xD5DA46D9, 0x00F436A0, 0x00000000 } },
  { .u32 = { 0x4B3B4CA8, 0x5A86C47A, 0x098A2240, 0x00000000 } },
#else
  { .u32 = { 0x0000000A, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x00000064, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x000003E8, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x00002710, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x000186A0, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x000F4240, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x00989680, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x05F5E100, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x3B9ACA00, 0x00000000, 0x00000000, 0x00000000 } },
  { .u32 = { 0x540BE400, 0x00000002, 0x00000000, 0x00000000 } },
  { .u32 = { 0x4876E800, 0x00000017, 0x00000000, 0x00000000 } },
  { .u32 = { 0xD4A51000, 0x000000E8, 0x00000000, 0x00000000 } },
  { .u32 = { 0x4E72A000, 0x00000918, 0x00000000, 0x00000000 } },
  { .u32 = { 0x107A4000, 0x00005AF3, 0x00000000, 0x00000000 } },
  { .u32 = { 0xA4C68000, 0x00038D7E, 0x00000000, 0x00000000 } },
  { .u32 = { 0x6FC10000, 0x002386F2, 0x00000000, 0x00000000 } },
  { .u32 = { 0x5D8A0000, 0x01634578, 0x00000000, 0x00000000 } },
  { .u32 = { 0xA7640000, 0x0DE0B6B3, 0x00000000, 0x00000000 } },
  { .u32 = { 0x89E80000, 0x8AC72304, 0x00000000, 0x00000000 } },
  { .u32 = { 0x63100000, 0x6BC75E2D, 0x00000005, 0x00000000 } },
  { .u32 = { 0xDEA00000, 0x35C9ADC5, 0x00000036, 0x00000000 } },
  { .u32 = { 0xB2400000, 0x19E0C9BA, 0x0000021E, 0x00000000 } },
  { .u32 = { 0xF6800000, 0x02C7E14A, 0x0000152D, 0x00000000 } },
  { .u32 = { 0xA1000000, 0x1BCECCED, 0x0000D3C2, 0x00000000 } },
  { .u32 = { 0x4A000000, 0x16140148, 0x00084595, 0x00000000 } },
  { .u32 = { 0xE4000000, 0xDCC80CD2, 0x0052B7D2, 0x00000000 } },
  { .u32 = { 0xE8000000, 0x9FD0803C, 0x033B2E3C, 0x00000000 } },
  { .u32 = { 0x10000000, 0x3E250261, 0x204FCE5E, 0x00000000 } },
  { .u32 = { 0xA0000000, 0x6D7217CA, 0x431E0FAE, 0x00000001 } },
  { .u32 = { 0x40000000, 0x4674EDEA, 0x9F2C9CD0, 0x0000000C } },
  { .u32 = { 0x80000000, 0xC0914B26, 0x37BE2022, 0x0000007E } },
  { .u32 = { 0x00000000, 0x85ACEF81, 0x2D6D415B, 0x000004EE } },
  { .u32 = { 0x00000000, 0x38C15B0A, 0xC6448D93, 0x0000314D } },
  { .u32 = { 0x00000000, 0x378D8E64, 0xBEAD87C0, 0x0001ED09 } },
  { .u32 = { 0x00000000, 0x2B878FE8, 0x72C74D82, 0x00134261 } },
  { .u32 = { 0x00000000, 0xB34B9F10, 0x7BC90715, 0x00C097CE } },
  { .u32 = { 0x00000000, 0x00F436A0, 0xD5DA46D9, 0x0785EE10 } },
  { .u32 = { 0x00000000, 0x098A2240, 0x5A86C47A, 0x4B3B4CA8 } },
#endif
};

const size_t digits_size = sizeof(digits) / sizeof(digits[0]);

#ifdef HAVE_INT128

size_t uint128_import_dec_str(uint128_t * out, const char * in)
{
  const char * ptr = in;

  uint128_t a = 0;
  for (; *ptr; ptr++) {
    char ch = *ptr;
    ch -= '0';
    if ((ch < 0) || (ch > 9))
      return (ptr - in);
    a *= 10;
    a += ch;
  }

  *out = a;
  return (ptr - in);
}

static size_t logA(uint128_t a)
{
  int start = 0;
  int end = digits_size;

  while (end > start) {
    size_t i = (end + start) / 2;
    if (digits[i].u128 == a)
      return i + 2;
    if (digits[i].u128 < a)
      start = i + 1;
    else
      end = i - 1;
  }
  if (digits[start].u128 <= a)
    return start + 2;
  return start + 1;
}

void uint128_export_dec_str(char * out, const uint128_t * in)
{
  uint128_t a = *in;
  char * out2 = out + logA(a);
  *out2 = 0;

  do {
    char ch = '0' + (a % 10);
    a /= 10;
    *--out2 = ch;
  } while (a);
}

uint32_t uint128_div_mod_im(uint128_t * out, const uint128_t * in, uint32_t b)
{
  uint32_t r = *in % b;
  *out = *in / b;
  return r;
}

int uint128_cmp_im(const uint128_t * a, uint32_t b)
{
  if (*a > b)
    return 1;
  if (*a < b)
    return -1;
  return 0;
}

uint32_t uint128_lo32(const uint128_t * in)
{
  return *in;
}

uint64_t uint128_lo64(const uint128_t * in)
{
  return *in;
}

#else

#ifdef BIG_ENDIAN
#define IDX(i, s) ((s) - (i) - 1LU)
#else
#define IDX(i, s) (i)
#endif

static void uint128_mul_add_im(uint128_t * val, uint32_t a, uint32_t b)
{
  uint64_t tmp = (uint64_t)(*val)[IDX(0, 4)];
  tmp *= a;
  tmp += b;
  (*val)[IDX(0, 4)] = tmp & 0xFFFFFFFF;
  tmp >>= 32;
  tmp += (*val)[IDX(1, 4)] * a;
  (*val)[IDX(1, 4)] = tmp & 0xFFFFFFFF;
  tmp >>= 32;
  tmp += (*val)[IDX(2, 4)] * a;
  (*val)[IDX(2, 4)] = tmp & 0xFFFFFFFF;
  tmp >>= 32;
  tmp += (*val)[IDX(3, 4)] * a;
  (*val)[IDX(3, 4)] = tmp & 0xFFFFFFFF;
}

size_t uint128_import_dec_str(uint128_t * out, const char * in)
{
  const char * ptr = in;

  uint128_t a;
  memset(&a, 0, sizeof(a));
  for (; *ptr; ptr++) {
    char ch = *ptr;
    ch -= '0';
    if ((ch < 0) || (ch > 9))
      return (ptr - in);
    uint128_mul_add_im(&a, 10, ch);
  }

  memcpy(out, &a, sizeof(a));
  return (ptr - in);
}

uint32_t uint128_div_mod_im(uint128_t * out, const uint128_t * in, uint32_t b)
{
  uint64_t tmp = (*in)[IDX(3, 4)];
  uint64_t tmp2 = ((tmp % b) << 32) + (*in)[IDX(2, 4)];
  tmp /= b;
  (*out)[IDX(3, 4)] = tmp;
  tmp = ((tmp2 % b) << 32) + (*in)[IDX(1, 4)];
  tmp2 /= b;
  (*out)[IDX(2, 4)] = tmp2;
  tmp2 = ((tmp % b) << 32) + (*in)[IDX(0, 4)];
  tmp /= b;
  (*out)[IDX(1, 4)] = tmp;
  tmp = tmp2 % b;
  tmp2 /= b;
  (*out)[IDX(0, 4)] = tmp2;

  return tmp;
}

static int uint128_cmp(const uint128_t * a, const uint128_t * b)
{
  if ((*a)[IDX(3, 4)] != (*b)[IDX(3, 4)]) {
    if ((*a)[IDX(3, 4)] > (*b)[IDX(3, 4)])
      return 1;
    return -1;
  }
  if ((*a)[IDX(2, 4)] != (*b)[IDX(2, 4)]) {
    if ((*a)[IDX(2, 4)] > (*b)[IDX(2, 4)])
      return 1;
    return -1;
  }
  if ((*a)[IDX(1, 4)] != (*b)[IDX(1, 4)]) {
    if ((*a)[IDX(1, 4)] > (*b)[IDX(1, 4)])
      return 1;
    return -1;
  }
  if ((*a)[IDX(0, 4)] != (*b)[IDX(0, 4)]) {
    if ((*a)[IDX(0, 4)] > (*b)[IDX(0, 4)])
      return 1;
    return -1;
  }
  return 0;
}

static size_t logA(const uint128_t * a)
{
  int start = 0;
  int end = digits_size;

  while (end > start) {
    size_t i = (end + start) / 2;
    int c = uint128_cmp(&digits[i].u128, a);
    if (c == 0)
      return i + 2;
    if (c < 0)
      start = i + 1;
    else
      end = i - 1;
  }
  if (uint128_cmp(&digits[end].u128, a) <= 0)
    return start + 2;
  return start + 1;
}

void uint128_export_dec_str(char * out, const uint128_t * in)
{
  uint128_t a;
  memcpy(a, in, sizeof(a));
  char * out2 = out + logA(&a);
  *out2 = 0;

  do {
    char ch = '0' + uint128_div_mod_im(&a, &a, 10);
    *--out2 = ch;
  } while (uint128_cmp_im(&a, 0) > 0);
}

int uint128_cmp_im(const uint128_t * a, uint32_t b)
{
  if ((*a)[IDX(1, 4)] || (*a)[IDX(2, 4)] || (*a)[IDX(3, 4)])
    return 1;
  if ((*a)[IDX(0, 4)] > b)
    return 1;
  if ((*a)[IDX(0, 4)] < b)
    return -1;
  return 0;
}

uint32_t uint128_lo32(const uint128_t * in)
{
  return (*in)[IDX(0, 4)];
}

uint64_t uint128_lo64(const uint128_t * in)
{
  return ((uint64_t)(*in)[IDX(1, 4)]) << 32 + (*in)[IDX(0, 4)];
}

#endif
