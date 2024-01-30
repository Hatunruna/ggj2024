#include "RequirementsEntity.h"

#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameHub.h"
#include "GameState.h"
#include "i18n.h"

namespace mm {

  RequirementsEntity::RequirementsEntity(GameHub& game)
  : m_gameState(game.state)
  , m_font(game.resources.getFont("fonts/Renner.ttf"))
  , m_backgroundTexture(game.resources.getTexture("images/title.png"))
  , m_aiTexture(game.resources.getTexture("images/ai.png"))
  {
  }

  // void RequirementsEntity::update(gf::Time time) {
  //
  // }

  void RequirementsEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    float backgroundHeight = coordinates.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
    float backgroundScale = backgroundHeight / m_backgroundTexture.getSize().height;

    gf::Sprite background(m_backgroundTexture);
    background.setColor(gf::Color::Opaque(0.25));
    background.setPosition(coordinates.getCenter());
    background.setAnchor(gf::Anchor::Center);
    background.setScale(backgroundScale);
    target.draw(background, states);

    std::string constraintText;

    for (auto constraint : m_gameState.movieLevel.constraints) {
      constraintText += toString(constraint) + '\n';
    }

    gf::Text text(constraintText, m_font, coordinates.getRelativeCharacterSize(0.08));
    text.setColor(gf::Color::White);
    text.setParagraphWidth(coordinates.getRelativeSize({ 0.9f, 0.0f }).width);
    text.setAlignment(gf::Alignment::Center);
    text.setPosition(coordinates.getRelativePoint({ 0.5f, 0.4f }));
    text.setAnchor(gf::Anchor::Center);

    target.draw(text, states);


    gf::Text noAiText(_("And of course, no AI!"), m_font, coordinates.getRelativeCharacterSize(0.05));
    noAiText.setColor(gf::Color::White);
    noAiText.setPosition(coordinates.getRelativePoint({ 0.9f, 0.95f }));
    noAiText.setAnchor(gf::Anchor::CenterRight);

    target.draw(noAiText, states);


    float noAiHeight = coordinates.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
    float noAiScale = noAiHeight / m_aiTexture.getSize().height * 0.08f;

    gf::Sprite noAiSprite(m_aiTexture);
    noAiSprite.setPosition(coordinates.getRelativePoint({ 0.92f, 0.95f }));
    noAiSprite.setScale(noAiScale);
    noAiSprite.setAnchor(gf::Anchor::CenterLeft);

    target.draw(noAiSprite, states);

  }

}
