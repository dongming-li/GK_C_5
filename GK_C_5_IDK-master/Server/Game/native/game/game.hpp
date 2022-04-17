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

#ifndef GAME_HPP
# define GAME_HPP

# include "../misc/uuid.hpp"
# include "card.hpp"
# include "hand.hpp"
# include "deck.hpp"
# include "played.hpp"

# include <deque>


# define INIT_PLAYER_HEALTH (20)
# define INIT_PLAYER_MANA   (0)
# define INIT_HAND_SIZE     (7)


namespace idk
{
  class player
  {
   private:
    const misc::uuid id;
    deck_t deck;
    hand_t hand;
    int rank;
    int life;
    int mana;

   public:
    player(const misc::uuid &id, deck_t &deck, hand_t &hand, int rank);

    ~player(void) = default;


    /**
     * Output:player ->rank
     **/
    int
    get_rank(void);

    /**
     * Output: player->life
     **/
    int
    get_life(void);

    /**
     * Input: player's new life amount
     * Does: change players life to amount
     **/
    void
    set_life(int i);

    /**
     * Output: player->mana
     **/
    int
    get_mana(void);

    /**
     * Input: player's set mana
     * Does: change player's mana to int
     **/
    void
    set_mana(int i);

    /**
     * Does: shuffles player's deck
     **/
    void
    shuffle_deck(void);

    /**
     * Output: draws card
     **/
    card &
    draw(void);

    /**
     * Input: card to be inserted
     * Does: put card into player's hand
     **/
    void
    put_card_in_hand(card &c);

    /**
     * Input: card to remove
     * Does: remove card from players hand
     **/
    void
    discard_card(card &c);

    deck_t &
    get_deck(void);

    /**
     * Output: player's hand
     **/
    hand_t &
    get_hand(void);

    /**
     * Output: ID of the player
     **/
    inline
    const misc::uuid &
    get_id(void);
  };

  class game
  {
   private:
    const misc::uuid id;
    player player_1;
    player player_2;
    played_t *played;
    player *current_p;

   public:
    game(const misc::uuid &game_id, player &p1, player &p2);

    ~game(void) = default;

    /**
     * Output: current player
     **/
    inline
    player &
    current_player(void);

    inline
    const misc::uuid &
    get_id(void);

    inline
    player &
    get_player_1(void);

    inline
    player &
    get_player_2(void);

    /**
     * Does: change current player
     **/
    void
    switch_player(void);

    /**
     * Input: player, card, int mode
     * Does: nothing yet
     **/
    void
    cast_card(player &p, card *c, int i);

    /**
     * Input: player
     * Oputput: returns player's hand
     **/
    hand_t
    get_hand(player &pl);

    /**
     * Does: nothing yet
     **/
    void
    next_turn(void);

    /**
     * Does: nothing yet
     **/
    void
    attack(played_card &c, player &p);

    /**
     * Does: nothing yet
     **/
    void
    play_card(card *c, player &p);

    /**
     * Does: nothing yet
     **/
    void
    def_card(card *c, player &p);

    /**
     * Does: nothing yet
     **/
    void
    grave_card(card *c, player &p);
  };
}

# include "game.ipp"

#endif
