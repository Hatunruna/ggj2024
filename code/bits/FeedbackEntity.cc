#include "FeedbackEntity.h"

#include <gf/Coordinates.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameHub.h"

namespace mm {

  FeedbackEntity::FeedbackEntity(GameHub& game)
  : m_gameState(game.state)
  , m_font(game.resources.getFont("fonts/Renner.ttf"))
  , m_texture(game.resources.getTexture("icons/film-solid.png"))
  {
  }

  void FeedbackEntity::update(gf::Time time)
  {
  }

  void FeedbackEntity::render(gf::RenderTarget &target, const gf::RenderStates &states)
  {
    gf::Sprite movieSprite(m_texture);
    movieSprite.setAnchor(gf::Anchor::BottomLeft);
    movieSprite.setPosition(WorldSize * gf::vec(0.02f, 0.95f));
    movieSprite.setScale(0.3f);
    movieSprite.setColor(gf::Color::Gray(0.6f));
    target.draw(movieSprite, states);

    std::size_t remaining = m_gameState.movieLevel.movies.size() - m_gameState.currentMovie;

    gf::Text movieCount(std::to_string(remaining), m_font, 170);
    movieCount.setAnchor(gf::Anchor::BottomLeft);
    movieCount.setPosition(WorldSize * gf::vec(0.07f, 0.95f));
    movieCount.setColor(gf::Color::Gray(0.6f));
    target.draw(movieCount);

  }

}
