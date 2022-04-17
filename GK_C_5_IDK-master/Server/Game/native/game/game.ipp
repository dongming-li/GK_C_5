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

#include "../misc/uuid.hpp"


const misc::uuid &
idk::player::
get_id(void)
{
  return id;
}


idk::player &
idk::game::
current_player(void)
{
  return *current_p;
}
const misc::uuid &
idk::game::
get_id(void)
{
  return id;
}


idk::player &
idk::game::
get_player_1(void)
{
  return player_1;
}

idk::player &
idk::game::
get_player_2(void)
{
  return player_2;
}
