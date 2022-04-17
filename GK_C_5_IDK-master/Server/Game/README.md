C++ game implementation  
No fancy UI here. This is an API used by the NodeJS server.

 - to build, run `npm run build`
 - to clean, run `npm run clean`
 - to rebuild, run `npm run rebuild`

The file used by node is output in `build/Release`, which is annoying, so there
is a `game_wrapper.js` to be `require()`d by other node files.

Req:
Game State 
 - Turn
 - Players
 - Battlefield

Turn
 - Current player turn

Player
 - pID (used for player id)
 - Username (User pID for references)
 - Health
 - Hand
 - Mana
 - Deck

Deck
 - Card order

Hand
 - Cards in hand
 
Battlefield
 - Creatures in play

 