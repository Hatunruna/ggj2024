#include "MovieManager.h"

#include <gf/Color.h>
#include <gf/Log.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameData.h"

namespace {
  constexpr gf::Vector2i RenderTextureSize = gf::vec(1152, 1392);
}

namespace mm {

  MovieManager::MovieManager(gf::ResourceManager& resources)
  : m_font(resources.getFont("fonts/GoudyBookletter1911.otf"))
  , m_movieInfoBackgroundTexture(resources.getTexture("images/movie-info.png"))
  , m_movieInfoLightTexture(resources.getTexture("images/movie-info-light.png"))
  , m_movieRenderTexture(RenderTextureSize)
  {
    m_movieRenderTexture.setSmooth();
    m_renderView.setInitialFramebufferSize(RenderTextureSize);
    m_renderView.setSize(RenderTextureSize);
    m_renderView.setCenter(RenderTextureSize * 0.5f);
    m_movieRenderTexture.setView(m_renderView);
  }

  void MovieManager::update(gf::Time time) {
    generateMovieTexture();
  }

  void MovieManager::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    target.setActive();

    gf::Sprite movieInfo;
    auto& texture = m_movieRenderTexture.getTexture();
    movieInfo.setScale(2.0f);
    movieInfo.setTexture(m_movieRenderTexture.getTexture());
    movieInfo.setPosition(WorldSize * gf::vec(0.30f, 0.65f));
    constexpr float angle = -gf::Pi / 16.0f;
    movieInfo.setRotation(angle);
    movieInfo.setAnchor(gf::Anchor::Center);
    movieInfo.draw(target, states);
  }

  void MovieManager::generateMovieTexture() {
    static bool alreadyRendered = false;
    if (!alreadyRendered) {
      gf::Log::debug("Asset generated\n");
      alreadyRendered = true;

      m_movieRenderTexture.setActive();
      m_movieRenderTexture.setView(m_renderView);

      m_movieRenderTexture.clear(gf::Color::Transparent);

      gf::Sprite background;
      background.setTexture(m_movieInfoBackgroundTexture);
      background.setPosition(gf::vec(0.0f, 0.0f));
      background.draw(m_movieRenderTexture, gf::RenderStates());

      gf::Text title;
      title.setFont(m_font);
      title.setCharacterSize(50);
      title.setColor(gf::Color::Black);
      title.setString("Enemy In The Beginning");
      title.setParagraphWidth(600.0f);
      title.setPosition(gf::vec(163, 248));
      title.setAlignment(gf::Alignment::Center);
      title.setAnchor(gf::Anchor::CenterLeft);
      title.draw(m_movieRenderTexture, gf::RenderStates());

      gf::Text info;
      info.setFont(m_font);
      info.setCharacterSize(35);
      info.setColor(gf::Color::Black);
      std::string infoText;
      infoText += "Duration: 142 min\n";
      infoText += "Genre: Action\n";
      infoText += "Technique: Live Action\n";
      infoText += "Country: Temeria\n";
      infoText += "Year: 2014\n";
      info.setString(infoText);
      info.setParagraphWidth(363.0f);
      info.setPosition(gf::vec(400, 460));
      info.setAnchor(gf::Anchor::CenterLeft);
      info.draw(m_movieRenderTexture, gf::RenderStates());

      gf::Sprite light;
      light.setTexture(m_movieInfoLightTexture);
      light.setPosition(gf::vec(0.0f, 0.0f));
      light.draw(m_movieRenderTexture, gf::RenderStates());

      m_movieRenderTexture.display();
    }
  }

}
