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

#include "game_wrapper.hpp"

#include <node.h>
#include <v8.h>

#include <unordered_map>
#include <vector>
#include <utility>
#include <stdexcept>
#include <new>

#include "game/card.hpp"
#include "game/hand.hpp"
#include "game/deck.hpp"
#include "game/played.hpp"
#include "game/game.hpp"

#include "misc/uuid.hpp"
#include "misc/rand_isaac.h"


std::unordered_map<misc::uuid, idk::game *>
current_games;

std::unordered_map<misc::uuid, idk::card *>
loaded_cards;


static
misc::uuid
js_str_to_uuid(const v8::String &str);

static
std::vector<misc::uuid>
js_arr_to_uuids(v8::Array &arr, v8::Isolate *isolate);

static
idk::game *
get_game(const misc::uuid &id);

static
idk::card *
get_card(const misc::uuid &id);


void
node_exit_hook_game_wrapper(void *arg)
{
  /* clear current_games */
  std::unordered_map<misc::uuid, idk::game *>::iterator it_cg =
    current_games.begin();
  for ( ; current_games.end() != it_cg; ++it_cg)
  {
    delete (*it_cg).second;
  }

  current_games.clear();


  /* clear loaded_cards */
  std::unordered_map<misc::uuid, idk::card *>::iterator it_lc =
    loaded_cards.begin();
  for ( ; loaded_cards.end() != it_lc; ++it_lc)
  {
    delete (*it_lc).second;
  }

  loaded_cards.clear();
}

const misc::uuid &
start_game(const misc::uuid &p1_id, const misc::uuid &p2_id,
           const std::vector<misc::uuid> &p1_cards,
           const std::vector<misc::uuid> &p2_cards)
{
  idk::deck_t p1_deck = idk::deck_t();
  idk::deck_t p2_deck = idk::deck_t();


  std::vector<misc::uuid>::const_iterator it = p1_cards.begin();
  for ( ; p1_cards.end() != it; ++it)
  {
    idk::card *card = get_card(*it);

    if (NULL == card)
    {
      throw std::runtime_error("could not load card");
    }

    p1_deck.push_back(*card);
  }

  it = p2_cards.begin();
  for ( ; p2_cards.end() != it; ++it)
  {
    idk::card *card = get_card(*it);

    if (NULL == card)
    {
      throw std::runtime_error("could not load card");
    }

    p2_deck.push_back(*card);
  }


  idk::hand_t p1_hand = idk::hand_t();
  idk::hand_t p2_hand = idk::hand_t();

  idk::player p1 = idk::player(p1_id, p1_deck, p1_hand, 0);
  idk::player p2 = idk::player(p2_id, p2_deck, p2_hand, 0);

  misc::uuid game_id = misc::uuid(&rand_isaac_next);

  idk::game *game = new idk::game(game_id, p1, p2);

  current_games.insert(std::pair<misc::uuid, idk::game *>(game_id, game));

  return game->get_id();
}

void
play_card(const misc::uuid &game_id, const misc::uuid &card_id)
{
  idk::game *game = get_game(game_id);

  if (NULL == game)
  {
    throw std::runtime_error("game does not exist");
  }

  idk::card *card = get_card(card_id);

  if (NULL == card)
  {
    throw std::runtime_error("card not loaded");
  }

  game->cast_card(game->current_player(), card, 0);
}

void
draw_card(const misc::uuid &game_id, int which)
{
  if (1 != which && 2 != which)
  {
    throw std::invalid_argument("must be 1 or 2");
  }

  idk::game *game = get_game(game_id);

  if (NULL == game)
  {
    throw std::runtime_error("game does not exist");
  }

  idk::player &p = (1 == which) ? game->get_player_1() : game->get_player_2();

  p.get_hand().push_back(p.draw());
}

void
end_game(const misc::uuid &game_id)
{
  std::unordered_map<misc::uuid, idk::game *>::iterator it =
    current_games.find(game_id);

  if (current_games.end() == it)
  {
    throw std::runtime_error("game does not exist");
  }

  delete (*it).second;

  current_games.erase(it);
}

std::pair<misc::uuid, misc::uuid>
get_players(misc::uuid &game_id)
{
  idk::game *game = get_game(game_id);

  if (NULL == game)
  {
    throw std::runtime_error("game does not exist");
  }

  return std::pair<misc::uuid, misc::uuid>(game->get_player_1().get_id(),
                                           game->get_player_2().get_id());
}

std::pair<std::vector<misc::uuid>, std::vector<misc::uuid>>
get_hands(const misc::uuid &game_id)
{
  idk::game *game = get_game(game_id);

  if (NULL == game)
  {
    throw std::runtime_error("game does not exist");
  }

  std::vector<misc::uuid> p1_id, p2_id;
  idk::hand_t &p1_hand = game->get_player_1().get_hand();
  idk::hand_t &p2_hand = game->get_player_2().get_hand();

  for (idk::hand_t::iterator it = p1_hand.begin(); it != p1_hand.end(); ++it)
  {
    p1_id.push_back((*it).get_id());
  }
  for (idk::hand_t::iterator it = p2_hand.begin(); it != p2_hand.end(); ++it)
  {
    p2_id.push_back((*it).get_id());
  }

  return std::pair<std::vector<misc::uuid>, std::vector<misc::uuid>>(p1_id,
                                                                     p2_id);
}


/*****************
 * node wrappers *
 *****************/


void
node_start_game(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate * const isolate = args.GetIsolate();

  if (4 > args.Length())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  if (!args[0]->IsString() || !args[1]->IsString()
      || !args[2]->IsArray() || !args[3]->IsArray())
  {
    args.GetReturnValue().Set(false);

    return;
  }

  misc::uuid p1_id = js_str_to_uuid(*v8::String::Cast(*args[0]));
  misc::uuid p2_id = js_str_to_uuid(*v8::String::Cast(*args[1]));

  idk::deck_t p1_deck;
  idk::deck_t p2_deck;

  std::vector<misc::uuid> p1_deck_ids =
    js_arr_to_uuids(*v8::Array::Cast(*args[2]), isolate);
  std::vector<misc::uuid> p2_deck_ids =
    js_arr_to_uuids(*v8::Array::Cast(*args[3]), isolate);

  std::vector<misc::uuid>::iterator it = p1_deck_ids.begin();
  for ( ; it < p1_deck_ids.end(); ++it)
  {
    idk::card *card = get_card(*it);

    if (NULL == card)
    {
      args.GetReturnValue().Set(false);

      return;
    }

    p1_deck.push_back(*card);
  }

  it = p2_deck_ids.begin();
  for ( ; it < p2_deck_ids.end(); ++it)
  {
    idk::card *card = get_card(*it);

    if (NULL == card)
    {
      args.GetReturnValue().Set(false);

      return;
    }

    p2_deck.push_back(*card);
  }

  idk::hand_t p1_hand;
  idk::hand_t p2_hand;

  idk::player p1 = idk::player(p1_id, p1_deck, p1_hand, 0);
  idk::player p2 = idk::player(p2_id, p2_deck, p2_hand, 0);

  misc::uuid game_id = misc::uuid(&rand_isaac_next);

  idk::game *game = new idk::game(game_id, p1, p2);

  current_games.insert(std::pair<misc::uuid, idk::game *>(game->get_id(),
                                                          game));


  v8::Local<v8::String> ret =
    v8::String::NewFromUtf8(isolate, ((std::string) game->get_id()).c_str());

  args.GetReturnValue().Set(ret);
}

void
node_play_card(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  if (2 > args.Length())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  if (!args[0]->IsString() || !args[1]->IsString())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  misc::uuid game_id = js_str_to_uuid(*v8::String::Cast(*args[0]));
  misc::uuid card_id = js_str_to_uuid(*v8::String::Cast(*args[0]));

  play_card(game_id, card_id);


  args.GetReturnValue().Set(true);
}

void
node_draw_card(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  if (2 > args.Length())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  if (!args[0]->IsString() || !args[1]->IsNumber())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  misc::uuid game_id = js_str_to_uuid(*v8::String::Cast(*args[0]));
  double which = v8::Number::Cast(*args[1])->Value();

  if (1.0 != which || 2.0 != which)
  {
    /* some people just don't listen */
    args.GetReturnValue().Set(false);

    return;
  }

  draw_card(game_id, (int) which);


  args.GetReturnValue().Set(true);
}

void
node_end_game(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  if (1 > args.Length())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  if (!args[0]->IsString())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  misc::uuid game_id = js_str_to_uuid(*v8::String::Cast(*args[0]));

  try
  {
    end_game(game_id);
  }
  catch (...)
  {
    /* game doesn't exist */

    args.GetReturnValue().Set(false);

    return;
  }


  args.GetReturnValue().Set(true);
}

void
node_get_players(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate * const isolate = args.GetIsolate();


  if (1 > args.Length())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  if (!args[0]->IsString())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  misc::uuid game_id = js_str_to_uuid(*v8::String::Cast(*args[0]));

  std::pair<misc::uuid, misc::uuid> ids;

  try
  {
    ids = get_players(game_id);
  }
  catch (...)
  {
    /* game doesn't exist */

    args.GetReturnValue().Set(false);

    return;
  }

  v8::Local<v8::Context> ctx = v8::Context::New(isolate);

  v8::Local<v8::Array> arr = v8::Array::New(isolate, 2);
  v8::Local<v8::String> str1 =
    v8::String::NewFromUtf8(isolate, ((std::string) ids.first).c_str());
  v8::Local<v8::String> str2 =
    v8::String::NewFromUtf8(isolate, ((std::string) ids.second).c_str());

  arr->Set(ctx, 0, str1);
  arr->Set(ctx, 1, str2);

  args.GetReturnValue().Set(arr);
}

void
node_get_hands(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate * const isolate = args.GetIsolate();


  if (1 > args.Length())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  if (!args[0]->IsString())
  {
    args.GetReturnValue().Set(false);

    return;
  }


  misc::uuid game_id = js_str_to_uuid(*v8::String::Cast(*args[0]));

  idk::game *game = get_game(game_id);

  if (NULL == game)
  {
    args.GetReturnValue().Set(false);

    return;
  }

  v8::Local<v8::Context> ctx = v8::Context::New(isolate);

  uint32_t len, i;
  idk::hand_t *hand;

  /* player 1 hand */
  hand = &(game->get_player_1().get_hand());
  len = hand->size();
  v8::Local<v8::Array> p1_hand = v8::Array::New(isolate, len);

  for (i = 0; i < len; ++i)
  {
    v8::Local<v8::String> card_id =
      v8::String::NewFromUtf8(isolate,
                              ((std::string) (*hand)[i].get_id()).c_str());
    p1_hand->Set(ctx, i, card_id);
  }

  /* player 2 hand */
  hand = &(game->get_player_2().get_hand());
  len = hand->size();
  v8::Local<v8::Array> p2_hand = v8::Array::New(isolate, len);

  for (i = 0; i < len; ++i)
  {
    v8::Local<v8::String> card_id =
      v8::String::NewFromUtf8(isolate,
                              ((std::string) (*hand)[i].get_id()).c_str());
    p2_hand->Set(ctx, i, card_id);
  }


  v8::Local<v8::Array> ret = v8::Array::New(isolate, 2);

  ret->Set(ctx, 0, p1_hand);
  ret->Set(ctx, 1, p2_hand);

  args.GetReturnValue().Set(ret);
}


/**********************************
 * definitions of local functions *
 **********************************/


misc::uuid
js_str_to_uuid(const v8::String &str)
{
  char buf[37];


  str.WriteUtf8(buf, sizeof(buf));

  misc::uuid id = misc::uuid(buf);

  return id;
}

std::vector<misc::uuid>
js_arr_to_uuids(v8::Array &arr, v8::Isolate *isolate)
{
  std::vector<misc::uuid> vect;
  uint32_t len, i;
  v8::Local<v8::Context> ctx = v8::Context::New(isolate);


  len = arr.Length();
  for (i = 0; i < len; ++i)
  {
    v8::MaybeLocal<v8::Value> item = arr.Get(ctx, i);

    if (item.IsEmpty())
    {
      continue;
    }

    v8::String *str = v8::String::Cast(*item.ToLocalChecked());

    vect.push_back(js_str_to_uuid(*str));
  }

  return vect;
}

idk::game *
get_game(const misc::uuid &id)
{
  std::unordered_map<misc::uuid, idk::game *>::iterator it =
    current_games.find(id);

  if (current_games.end() != it)
  {
    return (*it).second;
  }

  return NULL;
}

idk::card *
get_card(const misc::uuid &id)
{
  std::unordered_map<misc::uuid, idk::card *>::iterator it =
    loaded_cards.find(id);

  if (loaded_cards.end() != it)
  {
    return (*it).second;
  }

  idk::card *card;

  try
  {
    card = new idk::card(id);
  }
  catch (...)
  {
    return NULL;
  }

  loaded_cards.insert(std::pair<misc::uuid, idk::card *>(id, card));

  return card;
}
