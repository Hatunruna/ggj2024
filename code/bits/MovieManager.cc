#include "MovieManager.h"

#include <gf/Color.h>
#include <gf/Log.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameHub.h"

namespace {
  constexpr gf::Vector2i RenderTextureSize = gf::vec(1152, 1392);
  constexpr gf::Vector2f MoviePosition = mm::WorldSize * gf::vec(0.60f, 1.20f);
  constexpr float MovieVelocity = gf::Pi * 2.0f; // 2pi rad/s
  constexpr float MovieAngleTarget = -gf::Pi / 16;
}

namespace mm {

  MovieManager::MovieManager(GameHub& game)
  : m_gameData(game.data)
  , m_font(game.resources.getFont("fonts/GoudyBookletter1911.otf"))
  , m_movieInfoBackgroundTexture(game.resources.getTexture("images/movie-info.png"))
  , m_movieInfoLightTexture(game.resources.getTexture("images/movie-info-light.png"))
  , m_movieRenderTexture(RenderTextureSize)
  {
    m_movieRenderTexture.setSmooth();
    m_renderView.setInitialFramebufferSize(RenderTextureSize);
    m_renderView.setSize(RenderTextureSize);
    m_renderView.setCenter(RenderTextureSize * 0.5f);
    m_movieRenderTexture.setView(m_renderView);
  }

  void MovieManager::update(gf::Time time) {

    switch (m_gameData.movieState)
    {
    case MovieState::NoMovie:
      generateMovieTexture();
      m_gameData.movieAngle = -gf::Pi;
      m_gameData.movieState = MovieState::ArrivingMovie;
      break;

    case MovieState::ArrivingMovie:
      m_gameData.movieAngle += MovieVelocity * time.asSeconds();
      if (m_gameData.movieAngle >= MovieAngleTarget) {
        m_gameData.movieAngle = MovieAngleTarget;
        m_gameData.movieState = MovieState::WaitingMovie;
      }
      break;
    }
  }

  void MovieManager::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    target.setActive();

    gf::Sprite movieInfo;
    auto& texture = m_movieRenderTexture.getTexture();
    movieInfo.setScale(2.0f);
    movieInfo.setTexture(m_movieRenderTexture.getTexture());
    movieInfo.setPosition(MoviePosition);
    movieInfo.setOrigin(gf::vec(1036.0f, 1330.0f));
    movieInfo.setRotation(m_gameData.movieAngle);
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
