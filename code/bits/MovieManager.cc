#include "MovieManager.h"

#include <gf/Color.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>
#include <gf/Time.h>

#include "GameHub.h"
#include "i18n.h"

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
  : m_resources(game.resources)
  , m_game(game)
  , m_gameState(game.state)
  , m_font(game.resources.getFont("fonts/GoudyBookletter1911.otf"))
  , m_movieInfoBackgroundTexture(game.resources.getTexture("images/movie-info.png"))
  , m_movieInfoLightTexture(game.resources.getTexture("images/movie-info-light.png"))
  , m_reviewPositiveTexture(game.resources.getTexture("images/reviews/star-fill.png"))
  , m_reviewNegativeTexture(game.resources.getTexture("images/reviews/star-empty.png"))
  , m_aiTexture(game.resources.getTexture("images/ai.png"))
  , m_movieRenderTexture(RenderTextureSize)
  , m_arrivingTween(MovieAngleInitial, MovieAngleTarget, m_angle, gf::milliseconds(500), gf::Ease::backInOut)
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

    switch (m_gameState.movieState)
    {
    case MovieState::NoMovie:
    {
      const auto& movies = m_gameState.movieLevel.movies;
      int currentMovie = m_gameState.currentMovie;
      if (currentMovie < static_cast<int>(movies.size())) {
        generateMovieTexture(movies[currentMovie]);
        m_gameState.movieState = MovieState::ArrivingMovie;
        m_arrivingTween.restart();
        m_angle = MovieAngleInitial;
      } else {
        m_game.endShift();
      }
      break;
    }

    case MovieState::ArrivingMovie:
      m_arrivingTween.update(time);
      if (m_arrivingTween.isFinished()) {
        m_gameState.movieState = MovieState::WaitingMovie;
        m_arrivingTween.restart();
      }
      break;

    case MovieState::WaitingMovie:
      break;

    case MovieState::DepartureMovie:
      m_angle -= MovieVelocity * time.asSeconds();
      if (m_angle <= MovieAngleInitial) {
        m_angle = MovieAngleInitial;
        m_gameState.movieState = MovieState::NoMovie;
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
    movieInfo.setRotation(m_angle);
    movieInfo.draw(target, states);
  }

  void MovieManager::generateMovieTexture(const MovieData& movie) {
    m_movieRenderTexture.setActive();
    m_movieRenderTexture.setView(m_renderView);

    m_movieRenderTexture.clear(gf::Color::Transparent);

    gf::Sprite background;
    background.setTexture(m_movieInfoBackgroundTexture);
    background.setPosition(gf::vec(0.0f, 0.0f));
    background.draw(m_movieRenderTexture, gf::RenderStates());

    if (movie.generated_by_ai) {
      gf::Vector2f aiPosition;
      aiPosition.x = m_game.random.computeUniformFloat(440.0f, 720.0f);
      aiPosition.y = m_game.random.computeUniformFloat(200.0f, 620.0f);

      gf::Sprite ai;
      ai.setTexture(m_aiTexture);
      ai.setPosition(aiPosition);
      ai.setScale(0.25f);
      ai.setColor(gf::Color::Opaque(0.30f));
      ai.setAnchor(gf::Anchor::Center);
      ai.draw(m_movieRenderTexture, gf::RenderStates());
    }

    gf::Text title;
    title.setFont(m_font);
    title.setCharacterSize(50);
    title.setColor(gf::Color::Black);
    title.setString(movie.title);
    title.setParagraphWidth(600.0f);
    title.setPosition(gf::vec(163, 248));
    title.setAlignment(gf::Alignment::Center);
    title.setAnchor(gf::Anchor::CenterLeft);
    title.draw(m_movieRenderTexture, gf::RenderStates());

    gf::Sprite poster;
    poster.setTexture(m_resources.getTexture(getTexturePath(movie.title)));
    poster.setPosition(gf::vec(195.0f, 325.0f));
    poster.setScale(0.5f);
    poster.draw(m_movieRenderTexture, gf::RenderStates());

    gf::Text info;
    info.setFont(m_font);
    info.setCharacterSize(35);
    info.setColor(gf::Color::Black);
    std::string infoText;
    infoText += _("Duration: ") + std::to_string(movie.duration) + _(" min") + '\n';
    infoText += _("Genre: ") + toString(movie.genre) + '\n';
    infoText += _("Technique: ") + toString(movie.technique) + '\n';
    infoText += _("Country: ") + toString(movie.country) + '\n';
    infoText += _("Year: ") + std::to_string(movie.year) + '\n';
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

    assert(movie.note >= 0 && movie.note <= 5);
    for (int i = 0; i < movie.note; ++i) {
      gf::Sprite review;
      review.setTexture(m_reviewPositiveTexture);
      review.setPosition(gf::vec(175.0f + i * 80.0f, 640.0f));
      review.setScale(0.35f);
      review.draw(m_movieRenderTexture, gf::RenderStates());
    }

    gf::Sprite ageRating;
    m_ratingTextures[2].get().setSmooth();
    int textureIndex = static_cast<int>(movie.rating);
    assert(textureIndex >= 0 && textureIndex <= static_cast<int>(m_ratingTextures.size()));
    ageRating.setTexture(m_ratingTextures[textureIndex]);
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
