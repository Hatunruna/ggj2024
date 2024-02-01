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
  , m_theaterBackgroundTexture(game.resources.getTexture("images/theater-background.png"))
  , m_officeBackgroundTexture(game.resources.getTexture("images/office-background.png"))
  {
    constexpr gf::Time FrameRate = gf::seconds(1.0f / 25.0f);

    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-0.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-1.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-2.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-3.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-4.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-5.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-6.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-7.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-6.png"), gf::vec(4, 1), FrameRate, 4);
    m_projectorAnimation.setLoop(true);

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-0.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-1.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-2.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-3.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-4.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-5.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-6.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-7.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-8.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-9.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-10.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-start-11.png"), gf::vec(2, 2), FrameRate, 4);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-0.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-1.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-2.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-3.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene1-rumble-end-4.png"), gf::vec(2, 2), FrameRate, 1);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-0.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-1.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-2.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-3.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-4.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-5.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-6.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-7.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-8.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-start-9.png"), gf::vec(2, 2), FrameRate, 1);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-0.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-1.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-2.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-3.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-4.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-middle-5.png"), gf::vec(2, 2), FrameRate, 3);
      animation.setLoop(false);
      m_badEndingAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-0.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-1.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-2.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-3.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-4.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-5.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-6.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-7.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-8.png"), gf::vec(2, 2), FrameRate, 4);
      animation.addTileset(game.resources.getTexture("images/animation/bad-ending/bad-ending-scene2-end-9.png"), gf::vec(2, 2), FrameRate, 4);
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

      m_projectorAnimation.update(time);
    }
  }

  void GameOverEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    if (m_game.state.monsterHappiness == MonsterHappiness::Happy || m_game.state.monsterHappiness == MonsterHappiness::VeryHappy) {
      gf::Sprite background(m_backgroundTexture);
      background.setColor(gf::Color::Opaque(0.25));
      target.draw(background, states);

      std::string string = _("Congratulations! The monster has enjoyed this midnights movies and laughs openly. You have saved the city (and our life).\nEnjoy your vacations!");

      gf::Text text(string, m_font, WorldSize.height * 0.08);
      text.setColor(gf::Color::White);
      text.setParagraphWidth(WorldSize.width * 0.9f);
      text.setAlignment(gf::Alignment::Center);
      text.setPosition(WorldSize * gf::vec(0.5f, 0.5f));
      text.setAnchor(gf::Anchor::Center);
      text.draw(target, states);
    } else {
      if (m_game.state.currentGameOverAnimation < m_badEndingAnimations.size()) {
        if (m_game.state.currentGameOverAnimation < 2) {
          const float rumble = m_game.random.computeUniformFloat(-0.01f, 0.01f);
          const gf::Vector2f rumbleOffset = rumble * WorldSize;
          const bool needRumble = m_game.state.currentGameOverAnimation == 1;

          gf::Sprite theaterBackground;
          theaterBackground.setTexture(m_theaterBackgroundTexture);
          if (needRumble) {
            theaterBackground.setPosition(rumbleOffset);
          }
          theaterBackground.draw(target, states);

          gf::AnimatedSprite projector;
          projector.setAnimation(m_projectorAnimation);
          if (needRumble) {
            projector.setPosition(WorldSize + rumbleOffset);
          } else {
            projector.setPosition(WorldSize);
          }
          projector.setAnchor(gf::Anchor::BottomRight);
          projector.draw(target, states);

          gf::AnimatedSprite animation;
          animation.setAnimation(m_badEndingAnimations[m_game.state.currentGameOverAnimation]);

          // Handle rumble
          if (needRumble) {
            animation.setPosition(WorldSize + rumbleOffset);
          } else {
            animation.setPosition(WorldSize);
          }
          animation.setAnchor(gf::Anchor::BottomRight);
          animation.draw(target, states);

          gf::Sprite officeBackground;
          officeBackground.setTexture(m_officeBackgroundTexture);
          if (needRumble) {
            officeBackground.setPosition(rumbleOffset);
          }
          officeBackground.draw(target, states);
        } else {
          gf::AnimatedSprite animation;
          animation.setAnimation(m_badEndingAnimations[m_game.state.currentGameOverAnimation]);

          // Handle rumble
          if (m_game.state.currentGameOverAnimation == 3) {
            const float rumble = m_game.random.computeUniformFloat(-0.01f, 0.01f);
            animation.setPosition(WorldSize * (gf::vec(0.5f, 0.5f) + rumble));
          } else {
            animation.setPosition(WorldSize * gf::vec(0.5f, 0.5f));
          }
          animation.setAnchor(gf::Anchor::Center);

          animation.draw(target, states);
        }
      } else {
        gf::Sprite background(m_backgroundTexture);
        background.setColor(gf::Color::Opaque(0.25));
        target.draw(background, states);

        std::string string = _("Unfortunately, the monster was not satisfied by your performance.\nGood luck in another life!");

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
