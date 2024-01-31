#include "GameOverEntity.h"

#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/AnimatedSprite.h>
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
    constexpr gf::Time FrameRate = gf::seconds(1.0f / 25.0f);

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-0.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-1.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-2.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-3.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-4.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-5.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-6.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-7.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-8.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-9.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-10.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-11.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-12.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-13.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-14.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-15.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-16.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-17.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-18.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-19.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-20.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-21.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-22.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-23.png"), gf::vec(1, 2), FrameRate, 2);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-0.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-1.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-2.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-3.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-4.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-5.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-6.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-7.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-8.png"), gf::vec(1, 2), FrameRate, 1);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-0.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-1.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-2.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-3.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-4.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-5.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-6.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-7.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-8.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-9.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-10.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-11.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-12.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-13.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-14.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-15.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-16.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-17.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-18.png"), gf::vec(1, 2), FrameRate, 1);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-0.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-1.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-2.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-3.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-4.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-5.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-6.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-7.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-8.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-9.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-10.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-11.png"), gf::vec(1, 2), FrameRate, 1);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-0.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-1.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-2.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-3.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-4.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-5.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-6.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-7.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-8.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-9.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-10.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-11.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-12.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-13.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-14.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-15.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-16.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-17.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-18.png"), gf::vec(1, 2), FrameRate, 2);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-19.png"), gf::vec(1, 2), FrameRate, 2);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }
  }

  void GameOverEntity::update(gf::Time time) {
    if (m_game.state.monsterHappiness != MonsterHappiness::Happy && m_game.state.monsterHappiness != MonsterHappiness::VeryHappy) {
      if (m_game.state.currentGameOverAnimation < m_badEndingAnimations.size()) {
        if (m_badEndingAnimations[m_game.state.currentGameOverAnimation].isFinished()) {
          m_badEndingAnimations[m_game.state.currentGameOverAnimation].reset();
          ++m_game.state.currentGameOverAnimation;
        }
      }

      if (m_game.state.currentGameOverAnimation < m_badEndingAnimations.size()) {
        m_badEndingAnimations[m_game.state.currentGameOverAnimation].update(time);
      }
    }
  }

  void GameOverEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    if (m_game.state.monsterHappiness == MonsterHappiness::Happy || m_game.state.monsterHappiness == MonsterHappiness::VeryHappy) {
      gf::Sprite background(m_backgroundTexture);
      background.setColor(gf::Color::Opaque(0.25));
      target.draw(background, states);

      std::string string = _("Congratulations! The monster has enjoyed this midnights movies and laughs openly.\nYou have saved the city (and our life).\nEnjoy your vacations!");

      gf::Text text(string, m_font, coordinates.getRelativeCharacterSize(0.08));
      text.setColor(gf::Color::White);
      text.setParagraphWidth(coordinates.getRelativeSize({ 0.9f, 0.0f }).width);
      text.setAlignment(gf::Alignment::Center);
      text.setPosition(coordinates.getRelativePoint({ 0.5f, 0.5f }));
      text.setAnchor(gf::Anchor::Center);
      text.draw(target, states);
    } else {
      if (m_game.state.currentGameOverAnimation < m_badEndingAnimations.size()) {
        gf::AnimatedSprite animation;
        animation.setAnimation(m_badEndingAnimations[m_game.state.currentGameOverAnimation]);

        // Handle rumble
        if (m_game.state.currentGameOverAnimation == 1 || m_game.state.currentGameOverAnimation == 3) {
          const float rumble = m_game.random.computeUniformFloat(-0.01f, 0.01f);
          animation.setPosition(WorldSize * rumble);
        }

        animation.draw(target, states);
      } else {
        gf::Sprite background(m_backgroundTexture);
        background.setColor(gf::Color::Opaque(0.25));
        target.draw(background, states);

        std::string string = _("Unfortunately, the monster was not satisfied by your performance.\nAfter feeding the monster, he left the cinema and start to destroying the town.\nGood luck in another life!");

        gf::Text text(string, m_font, WorldSize.height * 0.08);
        text.setColor(gf::Color::White);
        text.setParagraphWidth(WorldSize.width * 0.9f);
        text.setAlignment(gf::Alignment::Center);
        text.setPosition(WorldSize * gf::vec(0.5f, 0.5f));
        text.setAnchor(gf::Anchor::Center);
        text.draw(target, states);
      }
    }

  }

  bool GameOverEntity::hasFinishedCutScene() const {
    if (m_game.state.monsterHappiness == MonsterHappiness::Happy || m_game.state.monsterHappiness == MonsterHappiness::VeryHappy) {
      return true;
    }

    return m_game.state.currentGameOverAnimation >= m_badEndingAnimations.size();
  }

}
