#ifndef XY_GAME_STATE_H
#define XY_GAME_STATE_H

#include <cstdint>

#include <gf/Path.h>

#include "HeroState.h"
#include "MapState.h"

namespace xy {

  struct GameState {
    static constexpr uint16_t Version = 1;

    GameState(gf::Random& random)
    {
      map.generate(random);
    }

    HeroState hero;
    MapState map;

    void loadFromFile(const gf::Path& filename);
    void saveToFile(const gf::Path& filename);
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, GameState& state) {
    return ar | state.hero | state.map;
  }

}


#endif // XY_GAME_STATE_H
