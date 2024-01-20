#include "Body.h"

#include <cassert>

#include <gf/Math.h>
#include <gf/Orientation.h>
#include <gf/VectorOps.h>

#include "Constants.h"

namespace xy {

  bool Body::jump()
  {
    if (colliding && std::abs(velocity.y) < gf::Epsilon) {
      velocity += JumpImpulse;
      return true;
    }

    return false;
  }

  void Body::move(gf::Orientation orientation)
  {
    switch (orientation) {
      case gf::Orientation::NorthEast:
      case gf::Orientation::East:
      case gf::Orientation::SouthEast:
        velocity.x = -RunVelocity;
        break;
      case gf::Orientation::North:
      case gf::Orientation::Center:
      case gf::Orientation::South:
        velocity.x = 0.0f;
        break;
      case gf::Orientation::NorthWest:
      case gf::Orientation::West:
      case gf::Orientation::SouthWest:
        velocity.x = +RunVelocity;
        break;
      default:
        assert(false);
        break;
    }
  }

}
