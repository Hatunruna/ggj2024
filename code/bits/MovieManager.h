#ifndef MM_MOVIE_MANAGER_H
#define MM_MOVIE_MANAGER_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/Ref.h>
#include <gf/RenderTexture.h>
#include <gf/Tween.h>
#include <gf/Vector.h>
#include <gf/Views.h>

namespace mm {

  struct GameHub;
  struct GameState;
  struct MovieData;

  class MovieManager: public gf::Entity {
  public:
    MovieManager(GameHub& game);

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    void generateMovieTexture(const MovieData& movie);

  private:
    GameState& m_gameState;

    gf::Font& m_font;
    gf::Texture& m_movieInfoBackgroundTexture;
    gf::Texture& m_movieInfoLightTexture;
    std::vector<gf::Ref<gf::Texture>> m_ratingTextures;
    gf::Texture& m_reviewPositiveTexture;
    gf::Texture& m_reviewNegativeTexture;

    gf::ScreenView m_renderView;
    gf::RenderTexture m_movieRenderTexture;

    float angle = 0.0f;
    gf::Tween<float> m_arrivingTween;
  };

}

#endif // MM_MOVIE_MANAGER_H
