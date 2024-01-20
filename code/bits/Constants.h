#ifndef XY_GAME_CONSTANTS_H
#define XY_GAME_CONSTANTS_H

#include <gf/Vector.h>

namespace xy {

  constexpr int MapWidth = 250;
  constexpr int MapHeight = 250;

  constexpr gf::Vector2f TileSize = gf::vec(128.0f, 128.0f);

  constexpr gf::Vector2f Gravity = gf::vec(0.0f, 2000.0f);
  constexpr gf::Vector2f JumpImpulse = gf::vec(0.0f, -1200.f);
  constexpr float RunVelocity = 500.0f;

}

#endif // XY_GAME_CONSTANTS_H
