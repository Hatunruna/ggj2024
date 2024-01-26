#ifndef XY_PROJECTOR_H
#define XY_PROJECTOR_H

#include <gf/Entity.h>

namespace xy {

  class Projector: public gf::Entity {
  public:
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
  };

}

#endif // XY_PROJECTOR_H
