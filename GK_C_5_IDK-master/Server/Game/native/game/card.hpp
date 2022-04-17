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

#ifndef CARD_HPP
# define CARD_HPP

# include <string>

# include "../misc/uuid.hpp"


namespace idk
{
  class card
  {
   private:
    misc::uuid id;

   public:
    card(const misc::uuid &id);

    virtual
    ~card(void) = default;


    const misc::uuid &
    get_id(void);

    card &
    operator =(const card &other);

    bool
    operator ==(const card &rhs) const;
  };

  class played_card : public card
  {
   private:
    const misc::uuid &instance_id;

   public:
    played_card(const misc::uuid &instance_id);

    ~played_card(void);


    const misc::uuid &
    get_instance_id(void);
  };
}

#endif
