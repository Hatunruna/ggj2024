#ifndef XY_THEATER_ROOM_H
#define XY_THEATER_ROOM_H

#include <gf/Entity.h>

namespace xy {

  class TheaterRoom: public gf::Entity {
  public:
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
  };

}

#endif // XY_THEATER_ROOM_H
