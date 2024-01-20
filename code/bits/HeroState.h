#ifndef XY_GAME_HERO_STATE_H
#define XY_GAME_HERO_STATE_H

#include <gf/Vector.h>

#include "Body.h"

namespace xy {

  struct HeroState {
    Body body;
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, HeroState& state) {
    return ar | state.body;
  }

}

#endif // XY_GAME_HERO_STATE_H
