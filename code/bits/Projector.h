#ifndef MM_PROJECTOR_H
#define MM_PROJECTOR_H

#include <gf/Entity.h>

namespace mm {

  class Projector: public gf::Entity {
  public:
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
  };

}

#endif // MM_PROJECTOR_H
