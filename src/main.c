/* Copyright (c) 2024 Krypto-IT Jakub Juszczakiewicz
 * All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "version.h"
#include "int128acc.h"

char prefix_list[] = "kMGTPEZY";
unsigned int prefix_avail = 0;
uint32_t base = 1024;
unsigned int acomma = 2;
const char * eol = "";

static void int_printf32(uint32_t a, uint32_t r, char prefix)
{
  if (base == 1024) {
    if (acomma == 3)
      printf("%u.%03u%ci", a, (r * 1000) >> 10, prefix);
    else
      printf("%u.%02u%ci", a, (r * 100) >> 10, prefix);
  } else {
    if (acomma == 3)
      printf("%u.%03u%c", a, r, prefix);
    else
      printf("%u.%02u%c", a, r / 10 , prefix);
  }
}

static void int_printf(const uint128_t * a, uint32_t r, char prefix)
{
  char str[40];
  uint128_export_dec_str(str, a);

  if (base == 1024) {
    if (acomma == 3)
      printf("%s.%03u%ci", str, (r * 1000) >> 10, prefix);
    else
      printf("%s.%02u%ci", str, (r * 100) >> 10, prefix);
  } else {
    if (acomma == 3)
      printf("%s.%03u%c", str, r, prefix);
    else
      printf("%s.%02u%c", str, r / 10 , prefix);
  }
}

int print_pval_auto(const uint128_t * val)
{
  if (uint128_cmp_im(val, base) < 0)
  {
    char buf[22] = { 0 };
    uint128_export_dec_str(buf, val);
    printf("%s", buf);
    return 0;
  }
  uint128_t cur, val2;
  memcpy(&cur, val, sizeof(cur));
  uint32_t r = 0;

  for (int i = 0; prefix_list[i]; i++)
  {
    memcpy(&val2, &cur, sizeof(val2));
    r = uint128_div_mod_im(&cur, &cur, base);

    if (uint128_cmp_im(&cur, 1000) < 0)
    {
      int_printf32(uint128_lo32(&cur), r, prefix_list[i]);
      return 0;
    }
  }

  int_printf32(uint128_lo64(&cur), r, 'Y');
  return 0;
}

int print_pval_low(const uint128_t * val)
{
  if (uint128_cmp_im(val, 1000) < 0)
  {
    if (prefix_avail & 1)
    {
      unsigned long long t = uint128_lo64(val);
      printf("%llu", t);
      return 0;
    }
    if (prefix_avail & 2)
    {
      uint32_t v = uint128_lo32(val);
      int_printf32(v / base, v % base, prefix_list[1]);
      return 0;
    }
    for (int i = 2; prefix_list[i]; i++)
    {
      if (prefix_avail & (2 << i))
      {
        printf("0.00%s%c%s", (acomma == 2)?"":"0", prefix_list[i],
            (base == 1024)?"i":"");
        return 0;
      }
    }
    printf("0");
    return 0;
  }
  uint128_t cur, val2;
  uint128_t val_last;
  memcpy(&cur, val, sizeof(cur));
  memset(&val_last, 0, sizeof(cur));
  int i_last = -2;
  uint32_t r = 0, r_last = 0;

  if (prefix_avail & 1)
  {
    i_last = -1;
    memcpy(&val_last, val, sizeof(cur));
  }

  for (int i = 0; prefix_list[i]; i++)
  {
    memcpy(&val2, &cur, sizeof(cur));
    r = uint128_div_mod_im(&cur, &cur, base);

    if (prefix_avail & (2 << i))
    {
      memcpy(&val_last, &cur, sizeof(cur));
      i_last = i;
      r_last = r;
    }

    if (uint128_cmp_im(&cur, 1000) < 0)
    {
      if (i_last >= 0)
      {
        int_printf(&val_last, r_last, prefix_list[i_last]);
        return 0;
      }
      if (prefix_list[i + 1])
      {
        if (prefix_avail & (4 << i))
        {
          int_printf32(0, uint128_lo32(&cur), prefix_list[i + 1]);
          return 0;
        }

        int tmp_i = i;
        for (; i > 0; i--) {
          if (prefix_avail & (2 << i)) {
            memcpy(&cur, val, sizeof(cur));
            for (int j = 0; j < i; j++) {
              r = uint128_div_mod_im(&cur, &cur, base);
            }

            int_printf(&cur, r, prefix_list[i]);
            return 0;
          }
        }
        if (prefix_avail & 1) {
          char str[40];
          uint128_export_dec_str(str, val);
          printf("%s", str);
          return 0;
        }
        i = tmp_i + 2;
        for (; prefix_list[i]; i++)
        {
          if (prefix_avail & (2 << i))
          {
            printf("0.00%s%c%s", (acomma == 2)?"":"0", prefix_list[i],
                (base == 1024)?"i":"");
            return 0;
          }
        }
        char str[40];
        uint128_export_dec_str(str, val);
        printf("%s", str);

        return 0;
      }
    }
  }

  int_printf(&cur, r, 'Y');
  return 0;
}

int print_pval(const char * str)
{
  uint128_t val;
  char minus = 0;

  const char * ptr = str;
  if (*ptr == '-')
  {
    minus = '-';
    ptr++;
  }

  size_t s = uint128_import_dec_str(&val, str);
  if (str[s]) {
    fprintf(stderr, "%s is not valid decinal number\n", str);
    return 2;
  }

  if (minus)
  {
    putchar(minus);
  }
  if (!prefix_avail)
  {
    return print_pval_auto(&val);
  }

  return print_pval_low(&val);
}

void print_help(char * arg0)
{
  fprintf(stderr, "Krypto-IT pval %s\n", kit_pval_version_str);
  fprintf(stderr, "Usage: %s [-stnwxkMGTPEZY] decimal_number\n" \
                  "  -s  - SI prefixes (base = 1000 instead of 1024)\n" \
                  "  -t  - 0.000 instead of 0.00 format\n" \
                  "  -n  - append '\\n' on end (instead of nothing)\n" \
                  "  -w  - append '\\r\\n' on end\n" \
                  "\n" \
                  " Allowed prefixess (default auto):\n" \
                  "  x   - without prefix (base ^ 0)\n" \
                  "  k   - kibi / kilo    (base ^ 1)\n" \
                  "  M   - mebi / mega    (base ^ 2)\n" \
                  "  G   - gibi / giga    (base ^ 3)\n" \
                  "  T   - tebi / tera    (base ^ 4)\n" \
                  "  P   - pebi / peta    (base ^ 5)\n" \
                  "  E   - exbi / exa     (base ^ 6)\n" \
                  "  Z   - zebi / zetta   (base ^ 7)\n" \
                  "  Y   - yobi / yotta   (base ^ 8)\n" \
                  "\n", arg0);
}

int main(int argc, char * argv[])
{
  int r = 0, i;
  for (i = 1; i < argc; i++)
  {
    if (strlen(argv[i]) > 1 && argv[i][0] == '-' && 
         (argv[i][1] < '0' || argv[i][1] > '9'))
    {
      for (int j = 1; argv[i][j]; j++)
      {
        char arg = argv[i][j];
        if (arg == 'h')
        {
          print_help(argv[0]);
          return 0;
        }
        if (arg == 's')
        {
          base = 1000;
          continue;
        }
        if (arg == 't')
        {
          acomma = 3;
          continue;
        }
        if (arg == 'n')
        {
          eol = "\n";
          continue;
        }
        if (arg == 'w')
        {
          eol = "\r\n";
          continue;
        }
        if (arg == 'x')
        {
          prefix_avail |= 1;
          continue;
        }
        const char * pref = strchr(prefix_list, arg);
        if (!pref)
        {
          fprintf(stderr, "Invalid option: %c\n", arg);
          return 1;
        }
        prefix_avail |= 2 << (pref - prefix_list);
      }
      continue;
    }
    r = print_pval(argv[i]);
    break;
  }

  for (i++; i < argc; i++) {
    printf("%s", argv[i]);
  }
  printf("%s", eol);

  return 0;
}
