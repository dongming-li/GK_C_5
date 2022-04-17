{
  "targets":
  [
    {
      "target_name": "game",
      "sources":
      [
        "native/wrapper.cpp",
        "native/game_wrapper.cpp",

        "native/misc/rand_isaac.c",
        "native/misc/uuid.cpp",

        "native/game/card.hpp",
        "native/game/card.cpp",
        "native/game/deck.hpp",
        "native/game/deck.cpp",
        "native/game/game.hpp",
        "native/game/game.cpp",
        "native/game/hand.hpp",
        "native/game/hand.cpp",
        "native/game/played.hpp",
        "native/game/played.cpp"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ]
    }
  ]
}
