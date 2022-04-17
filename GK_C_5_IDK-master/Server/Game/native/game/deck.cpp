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

#include "deck.hpp"

#include <deque>
#include <algorithm>

#include "card.hpp"


namespace idk
{
  void
  shuffle(deck_t &d)
  {
    srand(unsigned(time(NULL)));
    std::random_shuffle(d.begin(),d.end());
  }

  card &
  draw_card(deck_t &d)
  {
    card &hold = d.front();
    d.pop_front();

    return hold;
  }

  void
  remove_card(deck_t &d, card &c)
  {
    deck_t::iterator it = std::find(d.begin(), d.end(), c);

    if (it != d.end())
    {
      d.erase(it);
    }
  }

  void
  add_card(deck_t &d, card &c)
  {
    d.push_back(c);
  }
}
