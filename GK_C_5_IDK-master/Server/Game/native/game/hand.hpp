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

#ifndef HAND_HPP
# define HAND_HPP

# include <vector>

# include "card.hpp"


namespace idk
{
  typedef
  std::vector<card>
  hand_t;

  /**
   *Input: Hand and card
   * Does: remove card from hand
   **/
  void
  discard(hand_t &h, card &c);

  /**
   * Input: Hand and card
   * Does: adds card to hand
   **/
  void
  add_card(hand_t &h, card &c);

  /**
   * Does: nothing yet
   * returns a heap-allocated object
   **/
  hand_t *
  make_hand(void);
}

#endif
