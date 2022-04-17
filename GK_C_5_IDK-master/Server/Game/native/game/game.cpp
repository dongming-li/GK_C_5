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

#include "game.hpp"

#include <deque>

#include "card.hpp"
#include "hand.hpp"
#include "deck.hpp"
#include "played.hpp"

#include "../misc/uuid.hpp"


namespace idk
{
  player::
  player(const misc::uuid &id, deck_t &deck, hand_t &hand, int rank) :
    id(id),
    deck(deck),
    hand(hand),
    rank(rank)
  {
    /* nothing more necessary */
  }

  int
  player::
  get_rank(void)
  {
    return rank;
  }

  int
  player::
  get_life(void)
  {
    return life;
  }

  void
  player::
  set_life(int i)
  {
    life = i;
  }

  int
  player::
  get_mana(void)
  {
    return mana;
  }

  void
  player::
  set_mana(int i)
  {
    mana = i;
  }

  void
  player::
  shuffle_deck(void)
  {
    shuffle(deck);
  }

  card &
  player::
  draw(void)
  {
    return draw_card(deck);
  }

  void
  player::
  put_card_in_hand(card &c)
  {
    add_card(hand, c);
  }

  void
  player::
  discard_card(card &c)
  {
    discard(hand, c);
  }

  deck_t &
  player::
  get_deck(void)
  {
    return deck;
  }

  hand_t &
  player::
  get_hand(void)
  {
    return hand;
  }

  void
  game::
  switch_player(void)
  {
    if (current_p == &player_1)
    {
      current_p = &player_2;
    }
    else
    {
      current_p = &player_1;
    }
  }

  game::
  game(const misc::uuid &game_id, player &p1, player &p2) :
    id(game_id),
    player_1(p1),
    player_2(p2),
    current_p(&player_1)
  {
    if (player_1.get_rank() > player_2.get_rank())
    {
      switch_player();
    }
    else if (player_1.get_rank() == player_2.get_rank())
    {
      srand(time(NULL));
      if ((rand() % 2) == 1) //player 2 won the flip
      {
        switch_player();
      }
    }

    player_1.set_life(INIT_PLAYER_HEALTH);
    player_2.set_life(INIT_PLAYER_HEALTH);
    player_1.set_mana(INIT_PLAYER_MANA);
    player_2.set_mana(INIT_PLAYER_MANA);
    player_1.shuffle_deck();
    player_2.shuffle_deck();

    for (int j = 0; j < INIT_HAND_SIZE; ++j)
    {
      if (!player_1.get_deck().empty())
      {
        player_1.put_card_in_hand(player_1.draw());
      }

      if (!player_2.get_deck().empty())
      {
        player_2.put_card_in_hand(player_2.draw());
      }
    }
  }

  /**
     /card is removed from hand
     /card affects happen
     /int i can be used for the cards target, its mode, or ect.
  */
  void
  game::
  cast_card(player &p, card *c,int i)
  {
    if(p.get_id() == player_1.get_id())
    {
      player_1.discard_card(*c);
    }
    else if(p.get_id() == player_2.get_id())
    {
      player_2.discard_card(*c);
    }
  }

  /**
     / if we implement hand size it goes here
     / changes current player to the other
     / player draws a card
     /other effects?
  */
  void
  game::
  next_turn(void)
  {
    switch_player();

    if(current_p == &player_1)
    {
      player_2.draw();
    }
    else
    {
      player_1.draw();
    }
  }

  void
  game::
  play_card(card *c, player &p)
  {
    if(p.get_id() == player_1.get_id())
    {
    }
    else
    {
    }
  }

  void
  game::
  def_card(card *c, player &p)
  {
    if(p.get_id() == player_1.get_id())
    {
    }
    else
    {
    }
  }

  void
  game::
  grave_card(card *c, player &p)
  {
    if(p.get_id() == player_1.get_id())
    {
    }
    else
    {
    }
  }
}
