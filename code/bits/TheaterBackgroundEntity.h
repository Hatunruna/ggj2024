#ifndef MM_THEATER_BACKGROUND_ENTITY_H
#define MM_THEATER_BACKGROUND_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/Texture.h>

namespace mm {

  class TheaterBackgroundEntity: public gf::Entity {
  public:
    TheaterBackgroundEntity(gf::ResourceManager& resources);

    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Texture& m_backgroundTexture;
  };

}

#endif // MM_THEATER_BACKGROUND_ENTITY_H
