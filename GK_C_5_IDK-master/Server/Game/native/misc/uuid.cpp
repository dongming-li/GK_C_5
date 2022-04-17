/*
 * This file is part of IDK Does Kards.
 *
 * IDK Does Kards is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * IDK Does Kards is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IDK Does Kards.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "uuid.hpp"

#include <cstdio>
#include <string>

# include "my_stdint.h"


/**
 *
 */
static
void
init_from_hex(uint64_t *msb, uint64_t *lsb, const char *str);


misc::uuid::
uuid(uint32_t (*rand_gen)(void)) :
  msb(((uint64_t) rand_gen() << 32) | (rand_gen())),
  lsb(((uint64_t) rand_gen() << 32) | (rand_gen()))
{
  /* set version to 4 */
  msb = (msb & ~(UUID_MASK_MSB_VERSION << UUID_SHIFT_MSB_VERSION))
         | (UUID_VERSION_RANDOM << UUID_SHIFT_MSB_VERSION);

  /* set variant bits to 10x */
  lsb = (lsb & ~(UUID_MASK_LSB_VARIANT_2_BIT << UUID_SHIFT_LSB_VARIANT_2_BIT))
         | (0x02ULL << UUID_SHIFT_LSB_VARIANT_2_BIT);
}

misc::uuid::
uuid(uint64_t (*rand_gen)(void)) :
  msb(rand_gen()),
  lsb(rand_gen())
{
  /* set version to 4 */
  msb = (msb & ~(UUID_MASK_MSB_VERSION << UUID_SHIFT_MSB_VERSION))
         | (UUID_VERSION_RANDOM << UUID_SHIFT_MSB_VERSION);

  /* set variant bits to 10x */
  lsb = (lsb & ~(UUID_MASK_LSB_VARIANT_2_BIT << UUID_SHIFT_LSB_VARIANT_2_BIT))
         | (0x02ULL << UUID_SHIFT_LSB_VARIANT_2_BIT);
}

misc::uuid::
uuid(void) :
  msb(0),
  lsb(0)
{
  /* Nothing more necessary */
}

misc::uuid::
uuid(uint64_t msb, uint64_t lsb) :
  msb(msb),
  lsb(lsb)
{
  /* Nothing more necessary */
}

misc::uuid::
uuid(const std::string &str)
{
  const char *c_str;


  c_str = str.c_str();

  init_from_hex(&msb, &lsb, c_str);
}

misc::uuid::
uuid(const char *str)
{
  init_from_hex(&msb, &lsb, str);
}


/***************
 * conversions *
 ***************/


misc::uuid::
operator std::string(void) const
{
  char tmp[37];

  snprintf(tmp, sizeof(tmp), "%08x-%04hx-%04hx-%02hhx%02hhx-%04hx%08x",
           time_low(), time_mid(), time_hi_and_version(),
           clock_seq_hi_and_reserved(), clock_seq_low(), node_msb(),
           node_lsb());

  std::string ret = std::string(tmp);

  return ret;
}

/* local function implementations */

void
init_from_hex(uint64_t *msb, uint64_t *lsb, const char *str)
{
  int i;
  uint8_t d;


  *msb = 0;
  *lsb = 0;

  i = 0;

  while (16 > i)
  {
    if ('\0' == *str)
    {
      /* reached end of string */
      break;
    }

    if ('0' <= *str && '9' >= *str)
    {
      d = *str - '0' + 0x00;
    }
    else if ('a' <= *str && 'f' >= *str)
    {
      d = *str - 'a' + 0x0A;
    }
    else if ('A' <= *str && 'F' >= *str)
    {
      d = *str - 'A' + 0x0A;
    }
    else
    {
      ++str;

      continue;
    }

    *msb = (*msb << 4) | ((*lsb >> 60) & 0x0F);
    *lsb = (*lsb << 4) | d;

    ++str;
  }
}


/*******************************************
 * template specialization implementations *
 *******************************************/


size_t
std::hash<misc::uuid>::
operator ()(const misc::uuid &u) const
{
  return (u.get_msb() >> 32) ^ (u.get_msb())
         ^ (u.get_lsb() >> 32) ^ (u.get_lsb());
}
