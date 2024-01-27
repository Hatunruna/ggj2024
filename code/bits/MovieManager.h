#ifndef MM_MOVIE_MANAGER_H
#define MM_MOVIE_MANAGER_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/RenderTexture.h>
#include <gf/Tween.h>
#include <gf/Vector.h>
#include <gf/Views.h>

namespace mm {

  struct GameData;
  struct GameHub;

  class MovieManager: public gf::Entity {
  public:
    MovieManager(GameHub& game);

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    void generateMovieTexture();

  private:
    GameData& m_gameData;

    gf::Font& m_font;
    gf::Texture& m_movieInfoBackgroundTexture;
    gf::Texture& m_movieInfoLightTexture;

    gf::ScreenView m_renderView;
    gf::RenderTexture m_movieRenderTexture;

    gf::Time m_elapsedTime;
    gf::Tween<float> m_arrivingTween;
  };

}

#endif // MM_MOVIE_MANAGER_H
