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

#ifndef DECK_HPP
# define DECK_HPP

# include "card.hpp"

# include <deque>


namespace idk
{
  typedef
  std::deque<card>
  deck_t;

  /**
   * Input: deck to be shuffled
   * Does: shuffle deck
   **/
  void
  shuffle(deck_t &d);

  /**
   * Input: deck to draw from
   * Does: return card from deck, pop card from deck
   * Output: card from deck
   **/
  card &
  draw_card(deck_t &d);

  /**
   * Input: deck and card to remove
   * Does: remove card from deck
   **/
  void
  remove_card(deck_t &d, card &c);

  /**
   * Input: deck and card to add
   * Does: add card to the deck
   **/
  void
  add_card(deck_t &d, card &c);
}

#endif
