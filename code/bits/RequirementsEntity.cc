#include "RequirementsEntity.h"

#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Text.h>

#include "GameHub.h"
#include "GameState.h"

namespace mm {

  RequirementsEntity::RequirementsEntity(GameHub& game)
  : m_gameState(game.state)
  , m_font(game.resources.getFont("fonts/GoudyBookletter1911.otf"))
  {
  }

  // void RequirementsEntity::update(gf::Time time) {
  //
  // }

  void RequirementsEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    std::string constraintText;

    for (auto constraint : m_gameState.movieLevel.constraints) {
      constraintText += toString(constraint) + '\n';
    }

    gf::Text text(constraintText, m_font, coordinates.getRelativeCharacterSize(0.08));
    text.setColor(gf::Color::White);
    text.setParagraphWidth(coordinates.getRelativeSize({ 0.7f, 0.0f }).width);
    text.setAlignment(gf::Alignment::Center);
    text.setPosition(coordinates.getRelativePoint({ 0.5f, 0.2f }));
    text.setAnchor(gf::Anchor::TopCenter);

    target.draw(text, states);
  }

}
