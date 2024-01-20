#ifndef XY_GAME_BODY_H
#define XY_GAME_BODY_H

#include <gf/Orientation.h>
#include <gf/Vector.h>

namespace xy {

  struct Body {
    gf::Vector2f position;
    gf::Vector2f velocity;
    gf::Vector2f size;
    bool colliding = false;

    bool jump();
    void move(gf::Orientation orientation);

  };

  template<typename Archive>
  Archive& operator|(Archive& ar, Body& body) {
    return ar | body.position | body.velocity | body.size | body.colliding;
  }

}

#endif // XY_GAME_BODY_H
