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

#ifndef RAND_ISAAC_H
# define RAND_ISSAC_H


# include <stdlib.h>

# include "my_stdint.h"


# ifdef __cplusplus
extern "C"
{
# endif


/**
 * Returns the next 32-bit integer from the ISAAC CSPRNG.
 * Note that void rand_isaac_seed(const char *) should be called before using
 * this function.
 * @return the next 32-bit integer from the ISAAC CSPRNG
 */
uint32_t
rand_isaac_next(void);

/**
 * Seeds the ISAAC cipher.
 * @param seed the up-to-256-character seed for the ISAAC CSPRNG
 */
void
rand_isaac_seed(const char *seed);

/**
 * Seeds the ISAAC cipher reading from the system's entropy source.
 * Calls void rand_isaac_seed(const char *) with the data read.
 */
void
rand_isaac_seed_sys(void);


# ifdef __cplusplus
}
# endif

#endif
