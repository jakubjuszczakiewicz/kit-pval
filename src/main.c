/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "version.h"
#include "int128acc.h"
#include "printer.h"

const char * eol = "";

int print_it(const char * str, const print_cfg * config)
{
  uint128_t val;
  char minus = 0;
  char output[48];

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

  int r = print_pval(output, &val, config);
  printf("%s", output);
  return r;
}

void print_help(char * arg0)
{
  fprintf(stderr, "kit-pval %s\n", kit_pval_version_str);
  fprintf(stderr, "Usage: %s [-stnwxkMGTPEZY] decimal_number [suffix]\n" \
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
  print_cfg config;
  config.base = 1024;
  config.acomma = 2;
  config.prefix_avail = 0;

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
          config.base = 1000;
          continue;
        }
        if (arg == 't')
        {
          config.acomma = 3;
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
          config.prefix_avail |= 1;
          continue;
        }
        const char * pref = strchr(prefix_list, arg);
        if (!pref)
        {
          fprintf(stderr, "Invalid option: %c\n", arg);
          return 1;
        }
        config.prefix_avail |= 2 << (pref - prefix_list);
      }
      continue;
    }
    r = print_it(argv[i], &config);
    break;
  }

  for (i++; i < argc; i++) {
    printf("%s", argv[i]);
  }
  printf("%s", eol);

  return r;
}
