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

/*
 * ISAAC implementation adapted from
 * https://rosettacode.org/wiki/The_ISAAC_Cipher#C
 */
/*
 * ISAAC was developed by Bob Jenkins in 1993, and placed in
 * public domain
 * the paper is located at
 * http://burtleburtle.net/bob/rand/isaac.html
 */

#include "rand_isaac.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my_stdint.h"


#define SIZE (256)

/* results */
static uint32_t result[SIZE];
static uint32_t count;

/* internal state */
static uint32_t state[SIZE];
static uint32_t state_a, state_b, state_c;


static
void
rand_isaac_gen(void)
{
  uint32_t i, x, y;


  /* increment c each time a new block of results is created */
  ++state_c;

  state_b += state_c;

  for (i = 0; i < SIZE; ++i)
  {
    x = state[i];

    switch (i % 4)
    {
      case 0:
        state_a ^= state_a << 13;
        break;
      case 1:
        state_a ^= state_a >> 6;
        break;
      case 2:
        state_a ^= state_a << 2;
        break;
      case 3:
        state_a ^= state_a >> 16;
        break;
      default:
        /* won't happen */
        break;
    }

    state_a = state[(i + (SIZE / 2)) % SIZE] + state_a;
    y = state[(x >> 2) % SIZE] + state_a + state_b;
    state[i] = y;
    state_b = state[(y >> 10) % SIZE] + x;
    result[i] = state_b;
  }

  count = 0;
}

#define mix(a, b, c, d, e, f, g, h) \
{ \
  (a) ^= (b) << 11; (d) += (a); (b) += (c); \
  (b) ^= (c) >> 2;  (e) += (b); (c) += (d); \
  (c) ^= (d) << 8;  (f) += (c); (d) += (e); \
  (d) ^= (e) >> 16; (g) += (d); (e) += (f); \
  (e) ^= (f) << 10; (h) += (3); (f) += (g); \
  (f) ^= (g) >> 4;  (a) += (f); (g) += (h); \
  (g) ^= (h) << 8;  (b) += (g); (h) += (a); \
  (h) ^= (a) >> 9;  (c) += (h); (a) += (b); \
}

void
rand_isaac_init(int flag)
{
  int i;
  uint32_t a,b,c,d,e,f,g,h;


  state_a
    = state_b
    = state_c
    = 0;

  a
    = b
    = c
    = d
    = e
    = f
    = g
    = h
    = 0x9e3779b9; /* the golden ratio, apparently */


  /* perform shenanigans */
  for (i = 0; i < 4; ++i)
  {
    mix(a, b, c, d, e, f, g, h);
  }

  /* more shenanigans */
  for (i = 0; i < SIZE; i += 8)
  {
    if (flag)
    {
      a += result[i    ];
      b += result[i + 1];
      c += result[i + 2];
      d += result[i + 3];
      e += result[i + 4];
      f += result[i + 5];
      g += result[i + 6];
      h += result[i + 7];
    }

    mix(a, b, c, d, e, f, g, h);

    state[i    ] = a;
    state[i + 1] = b;
    state[i + 2] = c;
    state[i + 3] = d;
    state[i + 4] = e;
    state[i + 5] = f;
    state[i + 6] = g;
    state[i + 7] = h;
  }

  if (flag)
  {
    /* even more shenanigans */
    for (i = 0; i < SIZE; i += 8)
    {
      a += state[i    ];
      b += state[i + 1];
      c += state[i + 2];
      d += state[i + 3];
      e += state[i + 4];
      f += state[i + 5];
      g += state[i + 6];
      h += state[i + 7];

      mix(a, b, c, d, e, f, g, h);

      state[i    ] = a;
      state[i + 1] = b;
      state[i + 2] = c;
      state[i + 3] = d;
      state[i + 4] = e;
      state[i + 5] = f;
      state[i + 6] = g;
      state[i + 7] = h;
    }
  }

  rand_isaac_gen();
  count = 0;
}

uint32_t
rand_isaac_next(void)
{
  uint32_t r;


  r = result[count];
  ++count;

  if (count > (SIZE - 1))
  {
    rand_isaac_gen();
    count = 0;
  }

  return r;
}

void
rand_isaac_seed(const char *seed)
{
  uint32_t i, m;


  /* set state to all 0s */
  for (i = 0; i < SIZE; ++i)
  {
    state[i] = 0;
  }

  m = strlen(seed);

  /* copy seed into result */
  for (i = 0; i < SIZE; ++i)
  {
    if (i > m)
    {
      result[i] = 0;
    }
    else
    {
      result[i] = seed[i];
    }
  }

  /* perform init */
  rand_isaac_init(1);
}



#if defined(_WIN32) || defined(_WIN64)

/* Windows does not have a random device file like *nix systems */

# warning Windows RNG seeding is not yet implemented!

void
rand_isaac_seed_sys(void)
{
  char seed[256 + 1];

  /*
   * TODO
   * (at the moment it's reading what is hopefully gibberish from previous
   * stack frames!)
   */

  seed[sizeof(seed) - 1] = '\0';

  /* seed CSPRNG */
  rand_isaac_seed(seed, 1);
}

#else

/* Not Windows: the BSDs, GNU+Linux, MacOS... all *nix */

# ifndef RANDOM_DEVICE
#  ifdef USE_LIMITED_RANDOM
#   define RANDOM_DEVICE ("/dev/random")
#   warning using /dev/random as entropy source may cause waiting time on startup as operating system collects entropy
#  else
#   define RANDOM_DEVICE ("/dev/urandom")
#  endif
# endif

void
rand_isaac_seed_sys(void)
{
  FILE *sys_rand;
  char seed[256 + 1];
  size_t read, total_read;


  /* read from entropy source */
  sys_rand = fopen(RANDOM_DEVICE, "r");

  total_read = 0;
  while (total_read != sizeof(seed) - 1 && !feof(sys_rand))
  {
    read = fread(&(seed[total_read]),
                 sizeof(*seed), (sizeof(seed) - 1) - total_read, sys_rand);

    total_read += read;
  }

  fclose(sys_rand);

  seed[sizeof(seed) - 1] = '\0';

  /* seed CSPRNG */
  rand_isaac_seed(seed);
}

#endif
