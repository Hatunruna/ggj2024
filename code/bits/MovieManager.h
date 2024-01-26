#ifndef MM_MOVIE_MANAGER_H
#define MM_MOVIE_MANAGER_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/RenderTexture.h>
#include <gf/ResourceManager.h>
#include <gf/Vector.h>
#include <gf/Views.h>

namespace mm {

  class MovieManager: public gf::Entity {
  public:
    MovieManager(gf::ResourceManager& resources);

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    void generateMovieTexture();

  private:
    gf::Font& m_font;
    gf::Texture& m_movieInfoBackgroundTexture;
    gf::Texture& m_movieInfoLightTexture;

    gf::ScreenView m_renderView;
    gf::RenderTexture m_movieRenderTexture;

  };

}

#endif // MM_MOVIE_MANAGER_H
