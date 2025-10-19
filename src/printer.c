/* Copyright (c) 2025 Jakub Juszczakiewicz
 * All rights reserved.
 */

#include "printer.h"
#include <string.h>
#include <stdio.h>

char prefix_list[] = "kMGTPEZY";

static void int_printf32(char * output, uint32_t a, uint32_t r, char prefix,
    uint32_t base, unsigned int acomma)
{
  if (base == 1024) {
    if (acomma == 3)
      sprintf(output, "%u.%03u%ci", a, (r * 1000) >> 10, prefix);
    else
      sprintf(output, "%u.%02u%ci", a, (r * 100) >> 10, prefix);
  } else {
    if (acomma == 3)
      sprintf(output, "%u.%03u%c", a, r, prefix);
    else
      sprintf(output, "%u.%02u%c", a, r / 10 , prefix);
  }
}

static void int_printf(char * output, const uint128_t * a, uint32_t r,
    char prefix, uint32_t base, unsigned int acomma)
{
  char str[40];
  uint128_export_dec_str(str, a);

  if (base == 1024) {
    if (acomma == 3)
      sprintf(output, "%s.%03u%ci", str, (r * 1000) >> 10, prefix);
    else
      sprintf(output, "%s.%02u%ci", str, (r * 100) >> 10, prefix);
  } else {
    if (acomma == 3)
      sprintf(output, "%s.%03u%c", str, r, prefix);
    else
      sprintf(output, "%s.%02u%c", str, r / 10 , prefix);
  }
}

static int print_pval_auto(char * output, const uint128_t * val,
    const print_cfg * config)
{
  if (uint128_cmp_im(val, config->base) < 0)
  {
    char buf[22] = { 0 };
    uint128_export_dec_str(buf, val);
    sprintf(output, "%s", buf);
    return 0;
  }
  uint128_t cur, val2;
  memcpy(&cur, val, sizeof(cur));
  uint32_t r = 0;

  for (int i = 0; prefix_list[i]; i++)
  {
    memcpy(&val2, &cur, sizeof(val2));
    r = uint128_div_mod_im(&cur, &cur, config->base);

    if (uint128_cmp_im(&cur, 1000) < 0)
    {
      int_printf32(output, uint128_lo32(&cur), r, prefix_list[i], config->base,
          config->acomma);
      return 0;
    }
  }

  int_printf(output, &cur, r, 'Y', config->base, config->acomma);
  return 0;
}

static int print_pval_low(char * output, const uint128_t * val,
    const print_cfg * config)
{
  if (uint128_cmp_im(val, 1000) < 0)
  {
    if (config->prefix_avail & 1)
    {
      unsigned long long t = uint128_lo64(val);
      sprintf(output, "%llu", t);
      return 0;
    }
    if (config->prefix_avail & 2)
    {
      uint32_t v = uint128_lo32(val);
      int_printf32(output, v / config->base, v % config->base, prefix_list[0],
          config->base, config->acomma);
      return 0;
    }
    for (int i = 2; prefix_list[i]; i++)
    {
      if (config->prefix_avail & (2 << i))
      {
        sprintf(output, "0.00%s%c%s", (config->acomma == 2)?"":"0",
            prefix_list[i], (config->base == 1024)?"i":"");
        return 0;
      }
    }
    sprintf(output, "0");
    return 0;
  }
  uint128_t cur, val2;
  uint128_t val_last;
  memcpy(&cur, val, sizeof(cur));
  memset(&val_last, 0, sizeof(cur));
  int i_last = -2;
  uint32_t r = 0, r_last = 0;

  if (config->prefix_avail & 1)
  {
    i_last = -1;
    memcpy(&val_last, val, sizeof(cur));
  }

  for (int i = 0; prefix_list[i]; i++)
  {
    memcpy(&val2, &cur, sizeof(cur));
    r = uint128_div_mod_im(&cur, &cur, config->base);

    if (config->prefix_avail & (2 << i))
    {
      memcpy(&val_last, &cur, sizeof(cur));
      i_last = i;
      r_last = r;
    }

    if (uint128_cmp_im(&cur, 1000) < 0)
    {
      if (i_last >= 0)
      {
        int_printf(output, &val_last, r_last, prefix_list[i_last], config->base,
            config->acomma);
        return 0;
      }
      if (prefix_list[i + 1])
      {
        if (config->prefix_avail & (4 << i))
        {
          int_printf32(output, 0, uint128_lo32(&cur), prefix_list[i + 1],
              config->base, config->acomma);
          return 0;
        }

        int tmp_i = i;
        for (; i > 0; i--) {
          if (config->prefix_avail & (2 << i)) {
            memcpy(&cur, val, sizeof(cur));
            for (int j = 0; j < i; j++) {
              r = uint128_div_mod_im(&cur, &cur, config->base);
            }

            int_printf(output, &cur, r, prefix_list[i], config->base,
                config->acomma);
            return 0;
          }
        }
        if (config->prefix_avail & 1) {
          char str[40];
          uint128_export_dec_str(str, val);
          sprintf(output, "%s", str);
          return 0;
        }
        i = tmp_i + 2;
        for (; prefix_list[i]; i++)
        {
          if (config->prefix_avail & (2 << i))
          {
            sprintf(output, "0.00%s%c%s", (config->acomma == 2)?"":"0",
                prefix_list[i], (config->base == 1024)?"i":"");
            return 0;
          }
        }
        char str[40];
        uint128_export_dec_str(str, val);
        sprintf(output, "%s", str);

        return 0;
      }
    }
  }

  if (i_last == -1) {
    uint128_export_dec_str(output, val);
    return 0;
  }

  int_printf(output, &cur, r, 'Y', config->base, config->acomma);
  return 0;
}

int print_pval(char * output, const uint128_t * val, const print_cfg * config)
{
  if ((config->prefix_avail == 0) || (config->prefix_avail == 255))
    return print_pval_auto(output, val, config);
  return print_pval_low(output, val, config);
}
