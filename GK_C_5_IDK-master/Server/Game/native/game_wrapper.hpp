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

#ifndef GAME_WRAPPER_HPP
# define GAME_WRAPPER_HPP

# include <node.h>
# include <v8.h>

# include <unordered_map>
# include <vector>
# include <utility>

# include "game/card.hpp"
# include "game/hand.hpp"
# include "game/deck.hpp"
# include "game/played.hpp"
# include "game/game.hpp"

# include "misc/uuid.hpp"


extern
std::unordered_map<misc::uuid, idk::game *>
current_games;

extern
std::unordered_map<misc::uuid, idk::card *>
loaded_cards;

/**
 * Node exit hook.
 * Called when Node terminates. Frees used resources.
 *
 * @param arg
 *   currently unused
 */
void
node_exit_hook_game_wrapper(void *arg);

/**
 * Node wrapper function.
 * Starts a game and stores the heap-allocated game into the current_games map.
 *
 * @param player1Id
 *   the UUID (as js string) of the first player
 * @param player2Id
 *   the UUID (as js string) of the second player
 * @param cards1
 *   the UUIDs of cards (as js array of strings) used by the first player
 * @param cards2
 *   the UUIDs of cards (as js array of strings) used by the second player
 * @return the UUID of the game (as js string)
 */
void
node_start_game(const v8::FunctionCallbackInfo<v8::Value> &args);

const misc::uuid &
start_game(const misc::uuid &p1_id, const misc::uuid &p2_id,
           const std::vector<misc::uuid> &p1_cards,
           const std::vector<misc::uuid> &p2_cards);

/**
 * Node wrapper function.
 * Causes the current player in the indicated game to play the card with the
 * indicated id from their hand. For now, expect card id, not card instance id.
 *
 * @param gameId
 *   the UUID (as js string) of the game
 * @param cardId
 *   the UUID of the card to play
 */
void
node_play_card(const v8::FunctionCallbackInfo<v8::Value> &args);

void
play_card(const misc::uuid &game_id, const misc::uuid &card_id);

/**
 * Node wrapper function.
 * Causes the indicated player in the indicated game to draw a card from their
 * deck.
 *
 * @param gameId
 *   the UUID (as js string) of the game
 * @param which
 *   a js number (either 1 or 2) indicating which player should draw a card
 */
void
node_draw_card(const v8::FunctionCallbackInfo<v8::Value> &args);

void
draw_card(const misc::uuid &game_id, int which);

/**
 * Node wrapper function.
 * Causes the indicated game to end and free its resources.
 *
 * @param gameId
 *   the UUID (as js string) of the game
 */
void
node_end_game(const v8::FunctionCallbackInfo<v8::Value> &args);

void
end_game(const misc::uuid &game_id);

/**
 * Node wrapper function.
 * Gets the IDs of the players playing in the indicated game.
 *
 * @param gameId
 *   the UUID (as js string) of the game
 * @return a js array of length 2 containing player UUIDs (as js strings)
 */
void
node_get_players(const v8::FunctionCallbackInfo<v8::Value> &args);

std::pair<misc::uuid, misc::uuid>
get_players(misc::uuid &game_id);

/**
 * Node wrapper function.
 * Gets the IDs of the cards in the hands of the players playing in the
 * indicated game.
 *
 * @param gameId
 *   the UUID (as js string) of the game
 * @return a js array of length 2 containing js arrays of card UUIDs (as js
 * strings)
 */
void
node_get_hands(const v8::FunctionCallbackInfo<v8::Value> &args);

std::pair<std::vector<misc::uuid>, std::vector<misc::uuid>>
get_hands(const misc::uuid &game_id);


#endif
