#include "GameOverEntity.h"

#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include "GameData.h"
#include "GameHub.h"
#include "GameState.h"
#include "i18n.h"

namespace mm {

  GameOverEntity::GameOverEntity(GameHub& game)
  : m_game(game)
  , m_font(game.resources.getFont("fonts/Ignotum-Regular.ttf"))
  , m_backgroundTexture(game.resources.getTexture("images/title.png"))
  {
  }

  // void GameOverEntity::update(gf::Time time) {
  //
  // }

  void GameOverEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    float backgroundHeight = coordinates.getRelativeSize(gf::vec(0.0f, 1.0f)).height;
    float backgroundScale = backgroundHeight / m_backgroundTexture.getSize().height;

    gf::Sprite background(m_backgroundTexture);
    background.setColor(gf::Color::Opaque(0.25));
    background.setPosition(coordinates.getCenter());
    background.setAnchor(gf::Anchor::Center);
    background.setScale(backgroundScale);
    target.draw(background, states);

    if (m_game.state.monsterHappiness == MonsterHappiness::Happy || m_game.state.monsterHappiness == MonsterHappiness::VeryHappy) {
      std::string string = _("Congratulations! The monster has enjoyed this midnights movies and laughs openly.\nYou have saved the city (and our life).\nEnjoy your vacations!");

      gf::Text text(string, m_font, coordinates.getRelativeCharacterSize(0.08));
      text.setColor(gf::Color::White);
      text.setParagraphWidth(coordinates.getRelativeSize({ 0.9f, 0.0f }).width);
      text.setAlignment(gf::Alignment::Center);
      text.setPosition(coordinates.getRelativePoint({ 0.5f, 0.5f }));
      text.setAnchor(gf::Anchor::Center);
      text.draw(target, states);
    } else {
      std::string string = _("Unfortunately, the monster was not satisfied by your performance.\nAfter feeding the monster, he left the cinema and start to destroying the town.\nGood luck in another life!");

      gf::Text text(string, m_font, coordinates.getRelativeCharacterSize(0.08));
      text.setColor(gf::Color::White);
      text.setParagraphWidth(coordinates.getRelativeSize({ 0.9f, 0.0f }).width);
      text.setAlignment(gf::Alignment::Center);
      text.setPosition(coordinates.getRelativePoint({ 0.5f, 0.5f }));
      text.setAnchor(gf::Anchor::Center);
      text.draw(target, states);
    }

  }

}
