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

#ifndef UUID_HPP
# define UUID_HPP


# include <string>
# include "my_stdint.h"
# include <utility>


/* most-significant-bits macros */

#define UUID_SHIFT_MSB_TIME_LOW (32)
#define UUID_SHIFT_MSB_TIME_MID (16)
#define UUID_SHIFT_MSB_VERSION  (12)
#define UUID_SHIFT_MSB_TIME_HI  (0)
#define UUID_SHIFT_MSB_TIME_HI_AND_VERSION UUID_SHIFT_MSB_TIME_HI

#define UUID_MASK_MSB_TIME_LOW  (0xFFFFFFFFULL)
#define UUID_MASK_MSB_TIME_MID  (0xFFFFULL)
#define UUID_MASK_MSB_VERSION   (0x0FULL)
#define UUID_MASK_MSB_TIME_HI   (0x0FFFULL)
#define UUID_MASK_MSB_TIME_HI_AND_VERSION ((UUID_MASK_MSB_VERSION <<    \
                                            (UUID_SHIFT_MSB_VERSION     \
                                             - UUID_SHIFT_MSB_TIME_HI)) \
                                           | UUID_MASK_MSB_TIME_HI)

/* least-significant-bits macros */

/* note: variant may not be three bits */
#define UUID_SHIFT_LSB_VARIANT_1_BIT (63)
#define UUID_SHIFT_LSB_VARIANT_2_BIT (62)
#define UUID_SHIFT_LSB_VARIANT_3_BIT (61)
#define UUID_SHIFT_LSB_CLOCK_SEQ_HI  (56)
#define UUID_SHIFT_LSB_CLOCK_SEQ_HI_AND_RES UUID_SHIFT_LSB_CLOCK_SEQ_HI
#define UUID_SHIFT_LSB_CLOCK_SEQ_LOW (48)
#define UUID_SHIFT_LSB_NODE_MSB      (32)
#define UUID_SHIFT_LSB_NODE_LSB      (0)
#define UUID_SHIFT_LSB_NODE          UUID_SHIFT_LSB_NODE_LSB

/* note: variant may not be three bits */
#define UUID_MASK_LSB_VARIANT_1_BIT  (0x01ULL)
#define UUID_MASK_LSB_VARIANT_2_BIT  (0x03ULL)
#define UUID_MASK_LSB_VARIANT_3_BIT  (0x07ULL)
#define UUID_MASK_LSB_CLOCK_SEQ_HI_1_BIT (0x7FULL)
#define UUID_MASK_LSB_CLOCK_SEQ_HI_2_BIT (0x3FULL)
#define UUID_MASK_LSB_CLOCK_SEQ_HI_3_BIT (0x1FULL)
#define UUID_MASK_LSB_CLOCK_SEQ_HI_AND_RES \
  ((UUID_MASK_LSB_VARIANT_3_BIT         \
    << (UUID_SHIFT_LSB_VARIANT_3_BIT    \
        - UUID_SHIFT_LSB_CLOCK_SEQ_HI)) \
   | UUID_MASK_LSB_CLOCK_SEQ_HI_3_BIT)
#define UUID_MASK_LSB_CLOCK_SEQ_LOW  (0xFFULL)
#define UUID_MASK_LSB_NODE_MSB       (0xFFFFULL)
#define UUID_MASK_LSB_NODE_LSB       (0xFFFFFFFFULL)
#define UUID_MASK_LSB_NODE           ((UUID_MASK_LSB_NODE_MSB          \
                                       << (UUID_SHIFT_LSB_NODE_MSB     \
                                           - UUID_SHIFT_LSB_NODE_LSB)) \
                                      | (UUID_MASK_LSB_NODE_LSB))

/* version macros */

#define UUID_VERSION_TIME   (0x01)
#define UUID_VERSION_DCE    (0x02)
#define UUID_VERSION_MD5    (0x03)
#define UUID_VERSION_RANDOM (0x04)
#define UUID_VERSION_SHA    (0x05)


namespace
misc
{
  /**
   * UUID (Universally Unique IDentifier) class.
   * Conforms to RFC 4122.
   * (See https://www.ietf.org/rfc/rfc4122.txt
   * or https://tools.ietf.org/html/rfc4122).
   */
  class uuid
  {
   private:
    /**
     * The most significant bits of the UUID.
     */
    uint64_t msb;

    /**
     * The least significant bits of the UUID.
     */
    uint64_t lsb;

   public:
    /**
     * Creates a random (version 4) UUID.
     *
     * @param rand_gen the random number generator to use
     */
    uuid(uint32_t (*rand_gen)(void));

    /**
     * Creates a random (version 4) UUID.
     *
     * @param rand_gen the random number generator to use
     */
    uuid(uint64_t (*rand_gen)(void));

    /**
     * Creates a zero UUID.
     */
    uuid(void);

    /**
     * Creates a UUID with the given bits.
     *
     * @param msb the most significant bits
     * @param lsb the least significant bits
     */
    uuid(uint64_t msb, uint64_t lsb);

    /**
     * Creates a UUID from the given hexadecimal string.
     * Ignores case for a-f/A-F.
     * Ignores non-hexadecimal-digit characters.
     *
     * @param str the string to convert into a uuid
     */
    uuid(const std::string &str);

    /**
     * Creates a UUID from the given hexadecimal string.
     * Ignores case for a-f/A-F.
     * Ignores non-hexadecimal-digit characters.
     *
     * @param str the string to convert into a uuid
     */
    uuid(const char *str);

    /**
     * Creates a UUID that is a copy of the given one.
     *
     * @param copy the UUID to copy
     */
    uuid(const uuid &copy) = default;

    /**
     * Deconstructs the UUID. No extra operations are performed.
     */
    ~uuid(void) = default;


    /**
     * Returns the most significant bits of the UUID.
     *
     * @return the most significant bits of the UUID
     */
    inline
    uint64_t
    get_msb(void) const;

    /**
     * Returns the least significant bits of the UUID.
     *
     * @return the least significant bits of the UUID
     */
    inline
    uint64_t
    get_lsb(void) const;


    /***************
     * conversions *
     ***************/


    /**
     * Returns the string representation of the UUID. The format of the string
     * is "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx" where x is a hexidecimal
     * digit (in the set { 0, 1, ..., 9, a, b, ..., f }).
     *
     * @return the string representation of the UUID
     */
    explicit
    operator std::string(void) const;


    /*************
     * operators *
     *************/


    /**
     * Assigns the value of the given UUID to this one.
     *
     * @param copy the UUID to copy
     * @return this UUID
     */
    inline
    uuid &
    operator =(const uuid &copy);

    /**
     * Tests whether the given UUID is equal to this one.
     *
     * @param other the UUID to compare to this one
     * @return true if and only if this UUID is bit-identical to the given one
     */
    inline
    bool
    operator ==(const uuid &other) const;

    /**
     * Tests whether the given UUID is not equal to this one.
     *
     * @param other the UUID to compare to this one
     * @return true if and only if this UUID is not bit-identical to the given
     * one
     */
    inline
    bool
    operator !=(const uuid &other) const;

    /**
     * Tests whether this UUID is greater than or equal to the given one.
     *
     * @param other the UUID that is the right operand of the >= operator
     * @return true if and only if this UUID is greater than or equal to the
     * given one
     */
    inline
    bool
    operator >=(const uuid &other) const;

    /**
     * Tests whether this UUID is less than or equal to the given one.
     *
     * @param other the UUID that is the right operand of the <= operator
     * @return true if and only if this UUID is less than or equal to the
     * given one
     */
    inline
    bool
    operator <=(const uuid &other) const;

    /**
     * Tests whether this UUID is greater than the given one.
     *
     * @param other the UUID that is the right operand of the > operator
     * @return true if and only if this UUID is greater than the given one
     */
    inline
    bool
    operator >(const uuid &other) const;

    /**
     * Tests whether this UUID is less than the given one.
     *
     * @param other the UUID that is the right operand of the < operator
     * @return true if and only if this UUID is less than the given one
     */
    inline
    bool
    operator <(const uuid &other) const;


    /****************************
     * RFC 4122 field accessors *
     ****************************/


    /**
     * Returns the variant bits (bits 63-61, with 0 being least significant)
     * of the UUID. As the variant takes up up to 3 bits, the returned value
     * will always be in the range [0, 7].
     *
     * @return the 3 variant bits of the UUID
     */
    inline
    uint8_t
    get_variant_bits(void) const;

    /**
     * Returns the variant of the UUID, or 255 if the variant does not match
     * a specified pattern.
     *
     * The following are patterns specifying variants:
     *  - variant 0 is indicated by the pattern 0xx;
     *  - variant 1 is indicated by the pattern 10x;
     *  - variant 2 is indicated by the pattern 110;
     *  - the pattern 111 is reserved for future variants.
     * Thus:
     *  - if the variant bits represent 0 through 3, the variant is 0;
     *  - if the variant bits represent 4 through 5, the variant is 1;
     *  - if the variant bits represent 6, the variant is 2;
     * If the variant bits do not match a known pattern (i.e. represent 7),
     * this method will return 255.
     *
     *
     * @return the variant of the UUID
     */
    inline
    uint8_t
    get_variant(void) const;

    /**
     * Returns the version bits (bits 79-76, with 0 being least significant)
     * of the UUID. As the version takes up 4 bits, the returned value will
     * always be in the range [0, 15].
     *
     * @return the 4 version bits of the UUID
     */
    inline
    uint8_t
    get_version(void) const;

    /**
     * Returns the time_hi bits (bits 75-64, with 0 being least significant)
     * of the UUID. As the time_hi field takes up 12 bits, the returned value
     * will always be in the range [0, 2^12-1] = [0, 4095].
     *
     * @return the 12 time_hi bits of the UUID.
     */
    inline
    uint16_t
    get_time_hi(void) const;

    /**
     * Returns the time_low field of the UUID.
     *
     * @return the time_low field of the UUID
     */
    inline
    uint32_t
    time_low(void) const;

    /**
     * Returns the time_mid field of the UUID.
     *
     * @return the time_mid field of the UUID
     */
    inline
    uint16_t
    time_mid(void) const;

    /**
     * Returns the time_hi_and_version field of the UUID.
     * This field contains the version in the most significant 4 bits.
     *
     * @return the time_hi_and_version field of the UUID
     */
    inline
    uint16_t
    time_hi_and_version(void) const;

    /**
     * Returns the clock_seq_hi_and_reserved field of the UUID.
     * This field contains the variant of the UUID in at most the most
     * significant 3 bits. Note that the variant does not necessarily take up
     * 3 bits; see RFC 4122 for details.
     *
     * @return the clock_seq_hi_and_reserved field of the UUID
     */
    inline
    uint8_t
    clock_seq_hi_and_reserved(void) const;

    /**
     * Returns the clock_seq_low field of the UUID.
     *
     * @return the clock_seq_low field of the UUID
     */
    inline
    uint8_t
    clock_seq_low(void) const;

    /**
     * Returns the node field of the UUID.
     * As the node field is only 48 bits wide, the returned value will always
     * be in the range [0, 2 ^ 48 - 1].
     *
     * @return the node field of the UUID
     */
    inline
    uint64_t
    node(void) const;

    /**
     * Returns the 16 most significant bits of the node field of the UUID.
     *
     * @return the 16 most significant bits of the node field of the UUID
     */
    inline
    uint16_t
    node_msb(void) const;

    /**
     * Returns the 32 least significant bits of the node field of the UUID.
     *
     * @return the 32 least significant bits of the node field of the UUID
     */
    inline
    uint32_t
    node_lsb(void) const;
  };
}

namespace
std
{
  template <>
  struct
  hash<misc::uuid>
  {
    size_t
    operator ()(const misc::uuid &u) const;
  };
}

# include "uuid.ipp"

#endif
