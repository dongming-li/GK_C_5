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

#include <node.h>
#include <v8.h>

#include "misc/uuid.hpp"
#include "misc/rand_isaac.h"

#include "game_wrapper.hpp"


void
node_rand_isaac(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate * const isolate = args.GetIsolate();


  uint32_t rand_res = rand_isaac_next();

  v8::Local<v8::Number> num = v8::Number::New(isolate, (double) rand_res);


  args.GetReturnValue().Set(num);
}

void
node_rand_uuid(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate * const isolate = args.GetIsolate();


  misc::uuid u(&rand_isaac_next);

  v8::Local<v8::String> str =
    v8::String::NewFromUtf8(isolate, ((std::string) u).c_str());


  args.GetReturnValue().Set(str);
}


void
init(v8::Local<v8::Object> exports)
{
  rand_isaac_seed_sys();

  NODE_SET_METHOD(exports, "randIsaac", &node_rand_isaac);
  NODE_SET_METHOD(exports, "randUUID", &node_rand_uuid);
  NODE_SET_METHOD(exports, "startGame", &node_start_game);
  NODE_SET_METHOD(exports, "playCard", &node_play_card);
  NODE_SET_METHOD(exports, "drawCard", &node_draw_card);
  NODE_SET_METHOD(exports, "endGame", &node_end_game);
  NODE_SET_METHOD(exports, "getPlayers", &node_get_players);
  NODE_SET_METHOD(exports, "getHands", &node_get_hands);

  node::AtExit(&node_exit_hook_game_wrapper, NULL);
}

NODE_MODULE(addon, init)
