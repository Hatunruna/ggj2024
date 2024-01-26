#include "MovieManager.h"

#include <gf/Color.h>
#include <gf/Log.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameData.h"

namespace {
  constexpr gf::Vector2i RenderTextureSize = gf::vec(1000, 1000);
}

namespace mm {

  MovieManager::MovieManager(gf::ResourceManager& resources)
  : m_font(resources.getFont("fonts/GoudyBookletter1911.otf"))
  , m_movieInfoBackgroundTexture(resources.getTexture("images/movie-info.png"))
  , m_movieRenderTexture(RenderTextureSize)
  {
    m_movieRenderTexture.setSmooth();
    m_renderView.setInitialFramebufferSize(RenderTextureSize);
    m_renderView.setSize(RenderTextureSize);
    m_renderView.setCenter(RenderTextureSize * 0.5f);
    m_renderView.setViewport(gf::RectF::fromPositionSize(gf::vec(0.0f, 0.0f), gf::vec(1.0f, 1.0f)));
    m_movieRenderTexture.setView(m_renderView);
  }

  void MovieManager::update(gf::Time time) {
    generateMovieTexture();
  }

  void MovieManager::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    target.setActive();

    gf::Sprite movieInfo;
    auto& texture = m_movieRenderTexture.getTexture();
    // gf::Log::debug("texture size: %dx%d\n", texture.getSize().width, texture.getSize().height);
    movieInfo.setTexture(m_movieRenderTexture.getTexture());
    movieInfo.setPosition(WorldSize * 0.5f);
    movieInfo.draw(target, states);
  }

  void MovieManager::generateMovieTexture() {
    static bool alreadyRendered = false;
    if (!alreadyRendered) {
      gf::Log::debug("Asset generated\n");
      alreadyRendered = true;

      auto& view = m_movieRenderTexture.getView();
      gf::Log::debug("view: %gx%g, %gx%g\n", view.getCenter().x, view.getCenter().y, view.getSize().width, view.getSize().height);

      m_movieRenderTexture.setActive();
      m_movieRenderTexture.setView(m_renderView);

      m_movieRenderTexture.clear(gf::Color::Blue);

      gf::RectangleShape box;
      box.setColor(gf::Color::Cyan);
      box.setOutlineColor(gf::Color::Red);
      box.setSize(gf::vec(998, 998));
      box.setPosition(gf::vec(1.0f, 1.0f));
      box.setOutlineThickness(10.0f);
      box.draw(m_movieRenderTexture, gf::RenderStates());

      gf::RectangleShape test;
      test.setColor(gf::Color::Yellow);
      test.setPosition(RenderTextureSize * 0.5f);
      test.setSize(gf::vec(100, 100));
      test.setAnchor(gf::Anchor::Center);
      test.draw(m_movieRenderTexture, gf::RenderStates());

      // gf::Sprite background;
      // background.setTexture(m_movieInfoBackgroundTexture);
      // background.setPosition(gf::vec(0.0f, 0.0f));
      // background.draw(m_movieRenderTexture, gf::RenderStates());

      // gf::Text title;
      // title.setFont(m_font);
      // title.setCharacterSize(36);
      // title.setColor(gf::Color::Black);
      // title.setString("Title");
      // title.setPosition(gf::vec(200,200));
      // title.draw(m_movieRenderTexture, gf::RenderStates());

      m_movieRenderTexture.display();
      // target.setActive();

      auto image = m_movieRenderTexture.capture();
      image.saveToFile("/tmp/test.png");
    }
  }

}
