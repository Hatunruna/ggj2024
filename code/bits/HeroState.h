#ifndef XY_HERO_STATE_H
#define XY_HERO_STATE_H

#include <gf/Vector.h>

namespace xy {

  struct HeroState {
    gf::Vector2f position;
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, HeroState& state) {
    return ar | state.position;
  }

}

#endif // XY_HERO_STATE_H
