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

#ifndef PLAYED_HPP
# define PLAYED_HPP

# include <vector>

# include "card.hpp"


namespace idk
{
  typedef
  struct
  {
    std::vector<played_card> pl1;
    std::vector<played_card> pl1def;
    std::vector<played_card> pl1Grave;
    std::vector<played_card> pl2;
    std::vector<played_card> pl2def;
    std::vector<played_card> pl2Grave;
  }
  played_t;
}

#endif
