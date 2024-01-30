#include "FeedbackEntity.h"

#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameHub.h"

namespace mm {

  FeedbackEntity::FeedbackEntity(GameHub& game)
  : m_gameHub(game)
  , m_font(game.resources.getFont("fonts/Renner.ttf"))
  , m_movieTexture(game.resources.getTexture("icons/film-solid.png"))
  , m_timerTexture(game.resources.getTexture("icons/clock-regular.png"))
  {
  }

  void FeedbackEntity::update(gf::Time time)
  {
    if (m_gameHub.state.movieState == MovieState::WaitingMovie) {
      m_gameHub.state.shitTimer -= time;

      if (m_gameHub.state.shitTimer < gf::Time::zero()) {
        m_gameHub.endShift();
        m_gameHub.state.shitTimer = TotalShiftTime;
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

    const gf::Color4f timerColor = m_gameHub.state.shitTimer < gf::seconds(10) ? gf::Color::Red : gf::Color::Gray(0.6f);

    gf::Sprite timerSprite(m_timerTexture);
    timerSprite.setAnchor(gf::Anchor::CenterLeft);
    timerSprite.setPosition(WorldSize * gf::vec(0.85f, 0.07f));
    timerSprite.setScale(0.3f);
    timerSprite.setColor(timerColor);
    target.draw(timerSprite, states);

    int remainingSeconds = m_gameHub.state.shitTimer.asMilliseconds() / 1000;

    gf::Text timerText(std::to_string(remainingSeconds), m_font, 170);
    timerText.setAnchor(gf::Anchor::CenterLeft);
    timerText.setPosition(WorldSize * gf::vec(0.9f, 0.07f));
    timerText.setColor(timerColor);
    target.draw(timerText, states);

  }

}
