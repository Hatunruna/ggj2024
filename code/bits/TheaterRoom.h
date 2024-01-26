#ifndef MM_THEATER_ROOM_H
#define MM_THEATER_ROOM_H

#include <gf/Entity.h>

namespace mm {

  class TheaterRoom: public gf::Entity {
  public:
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
  };

}

#endif // MM_THEATER_ROOM_H
