#include "MovieManager.h"

#include <gf/Color.h>
#include <gf/Log.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Time.h>

#include "GameHub.h"

namespace {
  constexpr gf::Vector2i RenderTextureSize = gf::vec(1152, 1392);
  constexpr gf::Vector2f MoviePosition = mm::WorldSize * gf::vec(0.60f, 1.20f);
  constexpr float MovieVelocity = gf::Pi * 2.0f; // 2pi rad/s
  constexpr float MovieAngleInitial = -gf::Pi;
  constexpr float MovieAngleTarget = -gf::Pi / 16;
  constexpr float WaitingTime = 2.0f; // 2 sec (debug)
}

namespace mm {

  MovieManager::MovieManager(GameHub& game)
  : m_gameData(game.data)
  , m_font(game.resources.getFont("fonts/GoudyBookletter1911.otf"))
  , m_movieInfoBackgroundTexture(game.resources.getTexture("images/movie-info.png"))
  , m_movieInfoLightTexture(game.resources.getTexture("images/movie-info-light.png"))
  , m_reviewPositiveTexture(game.resources.getTexture("images/reviews/star-fill.png"))
  , m_reviewNegativeTexture(game.resources.getTexture("images/reviews/star-empty.png"))
  , m_movieRenderTexture(RenderTextureSize)
  , m_arrivingTween(MovieAngleInitial, MovieAngleTarget, m_gameData.movieAngle, gf::milliseconds(500), gf::Ease::backInOut)
  {
    m_movieRenderTexture.setSmooth();
    m_renderView.setInitialFramebufferSize(RenderTextureSize);
    m_renderView.setSize(RenderTextureSize);
    m_renderView.setCenter(RenderTextureSize * 0.5f);
    m_movieRenderTexture.setView(m_renderView);

    m_ratingTextures.emplace_back(game.resources.getTexture("images/ratings/all-ages.png"));
    m_ratingTextures.emplace_back(game.resources.getTexture("images/ratings/above-12.png"));
    m_ratingTextures.emplace_back(game.resources.getTexture("images/ratings/above-16.png"));
    m_ratingTextures.emplace_back(game.resources.getTexture("images/ratings/above-18.png"));

    m_reviewPositiveTexture.setSmooth();
    m_reviewNegativeTexture.setSmooth();
  }

  void MovieManager::update(gf::Time time) {

    switch (m_gameData.movieState)
    {
    case MovieState::NoMovie:
      generateMovieTexture();
      m_gameData.movieState = MovieState::ArrivingMovie;
      m_arrivingTween.restart();
      break;

    case MovieState::ArrivingMovie:
      m_arrivingTween.update(time);
      if (m_arrivingTween.isFinished()) {
        m_elapsedTime = gf::Time::Zero;
        m_gameData.movieState = MovieState::WaitingMovie;
        m_arrivingTween.restart();
      }
      break;

    case MovieState::WaitingMovie:
      m_elapsedTime += time;
      if (m_elapsedTime >= gf::seconds(WaitingTime)) {
        m_gameData.movieState = MovieState::DepartureMovie;
      }
      break;

    case MovieState::DepartureMovie:
      m_gameData.movieAngle -= MovieVelocity * time.asSeconds();
      if (m_gameData.movieAngle <= MovieAngleInitial) {
        m_gameData.movieAngle = MovieAngleInitial;
        m_gameData.movieState = MovieState::ArrivingMovie;
      }
      break;
    }
  }

  void MovieManager::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    target.setActive();

    gf::Sprite movieInfo;
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

      for (int i = 0; i < 5; ++i) {
        gf::Sprite review;
        review.setTexture(m_reviewNegativeTexture);
        review.setPosition(gf::vec(175.0f + i * 80.0f, 640.0f));
        review.setScale(0.35f);
        review.draw(m_movieRenderTexture, gf::RenderStates());
      }

      for (int i = 0; i < 2; ++i) {
        gf::Sprite review;
        review.setTexture(m_reviewPositiveTexture);
        review.setPosition(gf::vec(175.0f + i * 80.0f, 640.0f));
        review.setScale(0.35f);
        review.draw(m_movieRenderTexture, gf::RenderStates());
      }

      gf::Sprite ageRating;
      m_ratingTextures[2].get().setSmooth();
      ageRating.setTexture(m_ratingTextures[2]);
      ageRating.setPosition(gf::vec(650.0f, 625.0f));
      ageRating.setScale(0.5f);
      ageRating.draw(m_movieRenderTexture, gf::RenderStates());

      gf::Sprite light;
      light.setTexture(m_movieInfoLightTexture);
      light.setPosition(gf::vec(0.0f, 0.0f));
      light.draw(m_movieRenderTexture, gf::RenderStates());

      m_movieRenderTexture.display();
    }
  }

}
