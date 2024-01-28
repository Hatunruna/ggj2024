#include "FeedbackEntity.h"

#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameHub.h"

namespace mm {

  namespace {

    constexpr gf::Time TotalTime = gf::seconds(20);

  }

  FeedbackEntity::FeedbackEntity(GameHub& game)
  : m_gameHub(game)
  , m_font(game.resources.getFont("fonts/Renner.ttf"))
  , m_movieTexture(game.resources.getTexture("icons/film-solid.png"))
  , m_timerTexture(game.resources.getTexture("icons/clock-regular.png"))
  , m_timer(TotalTime)
  {
  }

  void FeedbackEntity::update(gf::Time time)
  {
    if (m_gameHub.state.movieState == MovieState::WaitingMovie) {
      m_timer -= time;

      if (m_timer < gf::Time::zero()) {
        m_gameHub.replaceScene(m_gameHub.debrief);
        m_timer = TotalTime;
      }
    }
  }

  void FeedbackEntity::render(gf::RenderTarget &target, const gf::RenderStates &states)
  {
    gf::Sprite movieSprite(m_movieTexture);
    movieSprite.setAnchor(gf::Anchor::BottomLeft);
    movieSprite.setPosition(WorldSize * gf::vec(0.02f, 0.95f));
    movieSprite.setScale(0.3f);
    movieSprite.setColor(gf::Color::Gray(0.6f));
    target.draw(movieSprite, states);

    std::size_t remainingMovies = m_gameHub.state.movieLevel.movies.size() - m_gameHub.state.currentMovie;

    gf::Text movieText(std::to_string(remainingMovies), m_font, 170);
    movieText.setAnchor(gf::Anchor::BottomLeft);
    movieText.setPosition(WorldSize * gf::vec(0.07f, 0.95f));
    movieText.setColor(gf::Color::Gray(0.6f));
    target.draw(movieText, states);

    gf::Sprite timerSprite(m_timerTexture);
    timerSprite.setAnchor(gf::Anchor::CenterLeft);
    timerSprite.setPosition(WorldSize * gf::vec(0.85f, 0.07f));
    timerSprite.setScale(0.3f);
    timerSprite.setColor(gf::Color::Gray(0.6f));
    target.draw(timerSprite, states);

    int remainingSeconds = m_timer.asMilliseconds() / 1000;

    gf::Text timerText(std::to_string(remainingSeconds), m_font, 170);
    timerText.setAnchor(gf::Anchor::CenterLeft);
    timerText.setPosition(WorldSize * gf::vec(0.9f, 0.07f));
    timerText.setColor(gf::Color::Gray(0.6f));
    target.draw(timerText, states);

  }

}
