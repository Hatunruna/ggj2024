#ifndef MM_GAME_DATA_H
#define MM_GAME_DATA_H

#include <gf/Vector.h>

#include "MovieData.h"

namespace mm {

  constexpr gf::Vector2i WorldSize = gf::vec(3840, 2160);

  struct GameData {
    std::vector<MovieData> movieDatabase;
  };

}

#endif // MM_GAME_DATA_H
