#include "DebriefEntity.h"

#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Text.h>

#include "GameData.h"
#include "GameHub.h"
#include "GameState.h"

namespace mm {

  DebriefEntity::DebriefEntity(GameHub& game)
  : m_gameState(game.state)
  , m_font(game.resources.getFont("fonts/GoudyBookletter1911.otf"))
  {
  }

  // void DebriefEntity::update(gf::Time time) {
  //
  // }

  void DebriefEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    gf::Text title("Shift End", m_font, coordinates.getRelativeCharacterSize(0.12));
    title.setColor(gf::Color::White);
    title.setParagraphWidth(coordinates.getRelativeSize({ 0.7f, 0.0f }).width);
    title.setAlignment(gf::Alignment::Center);
    title.setPosition(coordinates.getRelativePoint({ 0.5f, 0.05f }));
    title.setAnchor(gf::Anchor::TopCenter);
    title.draw(target, states);

    std::string debriefText;
    debriefText += "Correct choices: " + std::to_string(m_gameState.correctChoices) + "\n";
    debriefText += "Incorrect choices: " + std::to_string(m_gameState.incorrectChoices) + "\n";
    // debriefText += "Total errors: " + std::to_string(3) + "\n";

    gf::Text debrief(debriefText, m_font, coordinates.getRelativeCharacterSize(0.08));
    debrief.setColor(gf::Color::White);
    debrief.setParagraphWidth(coordinates.getRelativeSize({ 0.7f, 0.0f }).width);
    debrief.setAlignment(gf::Alignment::Center);
    debrief.setPosition(coordinates.getRelativePoint({ 0.5f, 0.2f }));
    debrief.setAnchor(gf::Anchor::TopCenter);
    debrief.draw(target, states);
  }

}
