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


/**************************
 * inline implementations *
 **************************/


uint64_t
misc::uuid::
get_msb(void) const
{
  return msb;
}

uint64_t
misc::uuid::
get_lsb(void) const
{
  return lsb;
}


/*************
 * operators *
 *************/


misc::uuid &
misc::uuid::
operator =(const uuid &copy)
{
  this->msb = copy.msb;
  this->lsb = copy.lsb;

  return *this;
}

bool
misc::uuid::
operator ==(const uuid &other) const
{
  return this->msb == other.msb && this->lsb == other.lsb;
}

bool
misc::uuid::
operator !=(const uuid &other) const
{
  return !(*this == other);
}

bool
misc::uuid::
operator >=(const uuid &other) const
{
  return this->msb > other.msb
         || (this->msb == other.msb && this->lsb >= other.lsb);
}

bool
misc::uuid::
operator <=(const uuid &other) const
{
  return this->msb < other.msb
         || (this->msb == other.msb && this->lsb <= other.lsb);
}

bool
misc::uuid::
operator >(const uuid &other) const
{
  return !(*this <= other);
}

bool
misc::uuid::
operator <(const uuid &other) const
{
  return !(*this >= other);
}


/****************************
 * RFC 4122 field accessors *
 ****************************/

uint8_t
misc::uuid::
get_variant_bits(void) const
{
  return (uint8_t) ((lsb >> UUID_SHIFT_LSB_VARIANT_3_BIT)
                    & UUID_MASK_LSB_VARIANT_3_BIT);
}

uint8_t
misc::uuid::
get_variant(void) const
{
  uint8_t bits;


  bits = get_variant_bits();

  if (0 == (bits & 0x04))
  {
    return 0;
  }
  else if (0 == (bits & 0x02))
  {
    return 1;
  }
  else if (0 == (bits & 0x01))
  {
    return 2;
  }
  else
  {
    return 255;
  }
}

uint8_t
misc::uuid::
get_version(void) const
{
  return (uint8_t) ((msb >> UUID_SHIFT_MSB_VERSION) & UUID_MASK_MSB_VERSION);
}

uint16_t
misc::uuid::
get_time_hi(void) const
{
  return (uint16_t) ((msb >> UUID_SHIFT_MSB_TIME_HI)
                     & UUID_MASK_MSB_TIME_HI);
}

uint32_t
misc::uuid::
time_low(void) const
{
  return (uint32_t) ((msb >> UUID_SHIFT_MSB_TIME_LOW)
                     & UUID_MASK_MSB_TIME_LOW);
}

uint16_t
misc::uuid::
time_mid(void) const
{
  return (uint16_t) ((msb >> UUID_SHIFT_MSB_TIME_MID)
                     & UUID_MASK_MSB_TIME_MID);
}

uint16_t
misc::uuid::
time_hi_and_version(void) const
{
  return (uint16_t) ((msb >> UUID_SHIFT_MSB_TIME_HI_AND_VERSION)
                     & UUID_MASK_MSB_TIME_HI_AND_VERSION);
}

uint8_t
misc::uuid::
clock_seq_hi_and_reserved(void) const
{
  return (uint8_t) ((lsb >> UUID_SHIFT_LSB_CLOCK_SEQ_HI_AND_RES)
                    & UUID_MASK_LSB_CLOCK_SEQ_HI_AND_RES);
}

uint8_t
misc::uuid::
clock_seq_low(void) const
{
  return (uint8_t) ((lsb >> UUID_SHIFT_LSB_CLOCK_SEQ_LOW)
                    & UUID_MASK_LSB_CLOCK_SEQ_LOW);
}

uint64_t
misc::uuid::
node(void) const
{
  return ((lsb >> UUID_SHIFT_LSB_NODE) & UUID_MASK_LSB_NODE);
}

uint16_t
misc::uuid::
node_msb(void) const
{
  return (uint16_t) ((lsb >> UUID_SHIFT_LSB_NODE_MSB)
                     & UUID_MASK_LSB_NODE_MSB);
}

uint32_t
misc::uuid::
node_lsb(void) const
{
  return (uint32_t) ((lsb >> UUID_SHIFT_LSB_NODE_LSB)
                     & UUID_MASK_LSB_NODE_LSB);
}
