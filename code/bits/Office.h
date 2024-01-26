#ifndef XY_OFFICE_H
#define XY_OFFICE_H

#include <gf/Entity.h>

namespace xy {

  class Office: public gf::Entity {
  public:
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
  };

}

#endif // XY_OFFICE_H
