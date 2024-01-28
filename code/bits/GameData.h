#ifndef MM_GAME_DATA_H
#define MM_GAME_DATA_H

#include <gf/Vector.h>

#include "MovieData.h"

namespace mm {

  constexpr gf::Vector2i WorldSize = gf::vec(3840, 2160);
  constexpr float AngerLimit = 0.5f;    // >50% fail = -1 happiness
  constexpr float NeutralLimit = 0.80f; // >20% fail = same happiness
                                        // <20% fail = +1 happiness

  struct LevelSettings {
    int constraintCount = 0;
    int movieCount = 0;
  };

  struct GameData {
    std::vector<MovieData> movieDatabase;

    std::array<LevelSettings, 5> levelSettings = {
      LevelSettings{ 1, 10 },
      LevelSettings{ 2, 10 },
      LevelSettings{ 2, 15 },
      LevelSettings{ 3, 15 },
      LevelSettings{ 4, 15 },
    };
  };

}

#endif // MM_GAME_DATA_H
