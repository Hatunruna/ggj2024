#ifndef MM_OFFICE_H
#define MM_OFFICE_H

#include <gf/Entity.h>

namespace mm {

  class Office: public gf::Entity {
  public:
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
  };

}

#endif // MM_OFFICE_H
