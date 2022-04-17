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

#include "hand.hpp"
#include <algorithm>

namespace idk
{
  void
  discard(hand_t &h, card &c)
  {
    hand_t::iterator it = std::find(h.begin(), h.end(), c);

    if (h.end() != it)
    {
      h.erase(it);
    }
  }

  void
  add_card(hand_t &h, card &c)
  {
    h.push_back(c);
  }

  hand_t *
  make_hand(void)
  {
    hand_t *hand = new hand_t;

    return hand;
  }
}
