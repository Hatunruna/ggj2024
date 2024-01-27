#include "TheaterBackgroundEntity.h"

#include <gf/AnimatedSprite.h>
#include <gf/Sprite.h>

#include "GameHub.h"

namespace {
  constexpr float IdleTime = 1.0f;
}

namespace mm {

  TheaterBackgroundEntity::TheaterBackgroundEntity(GameHub& game)
  : m_gameState(game.state)
  , m_theaterBackgroundTexture(game.resources.getTexture("images/theater-background.png"))
  , m_monsterPause(game.resources.getTexture("images/monster-pause.png"))
  , m_officeBackgroundTexture(game.resources.getTexture("images/office-background.png"))
  {
    constexpr gf::Time frequency = gf::seconds(1.0f/25.0f);

    // Load angry animations
    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/monster-angry-a-0.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-a-1.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-a-2.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-a-3.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-a-4.png"), gf::vec(4, 1), frequency, 2);
      animation.setLoop(false);

      m_angryAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/monster-angry-b-0.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-b-1.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-b-2.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-b-3.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-b-4.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-angry-b-5.png"), gf::vec(4, 1), frequency, 1);
      animation.setLoop(false);

      m_angryAnimations.emplace_back(std::move(animation));
    }

    // Load happy animations
    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/monster-happy-a-0.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-a-1.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-a-2.png"), gf::vec(4, 1), frequency, 4);
      animation.setLoop(false);

      m_happyAnimations.emplace_back(std::move(animation));
    }

    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/monster-happy-b-0.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-b-1.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-b-2.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-b-3.png"), gf::vec(4, 1), frequency, 2);
      animation.setLoop(false);

      m_happyAnimations.emplace_back(std::move(animation));
    }

    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-0.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-1.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-2.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-3.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-4.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-5.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-6.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-7.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.addTileset(game.resources.getTexture("images/projector-6.png"), gf::vec(4, 1), frequency, 4);
    m_projectorAnimation.setLoop(true);
  }

  void TheaterBackgroundEntity::update(gf::Time time)
  {
    switch (m_gameState.monsterState) {
    case MonsterState::Neutral:
      break;

    case MonsterState::Angry:
    {
      gf::Animation& animation = m_angryAnimations[0];

      animation.update(time);
      if (animation.isFinished()) {
        animation.reset();
        m_gameState.monsterState = MonsterState::Neutral;
      }
      break;
    }

    case MonsterState::SoftAngry:
    {
      gf::Animation& animation = m_angryAnimations[1];

      animation.update(time);
      if (animation.isFinished()) {
        animation.reset();
        m_gameState.monsterState = MonsterState::Neutral;
      }
      break;
    }

    case MonsterState::Happy:
    {
      gf::Animation& animation = m_happyAnimations[0];

      animation.update(time);
      if (animation.isFinished()) {
        animation.reset();
        m_gameState.monsterState = MonsterState::Neutral;
      }
      break;
    }

    case MonsterState::SoftHappy:
    {
      gf::Animation& animation = m_happyAnimations[1];

      animation.update(time);
      if (animation.isFinished()) {
        animation.reset();
        m_gameState.monsterState = MonsterState::Neutral;
      }
      break;
    }
    }

    m_projectorAnimation.update(time);
  }

  void TheaterBackgroundEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Sprite theaterBackground;
    theaterBackground.setTexture(m_theaterBackgroundTexture);
    theaterBackground.draw(target, states);

    gf::AnimatedSprite projector;
    projector.setAnimation(m_projectorAnimation);
    projector.setPosition(WorldSize);
    projector.setAnchor(gf::Anchor::BottomRight);
    projector.draw(target, states);

    switch (m_gameState.monsterState) {
    case MonsterState::Neutral:
    {
      gf::Sprite monster;
      monster.setTexture(m_monsterPause);
      monster.setPosition(WorldSize);
      monster.setAnchor(gf::Anchor::BottomRight);
      monster.draw(target, states);
      break;
    }

    case MonsterState::Angry:
    {
      gf::AnimatedSprite monster;
      monster.setAnimation(m_angryAnimations[0]);
      monster.setPosition(WorldSize);
      monster.setAnchor(gf::Anchor::BottomRight);
      monster.draw(target, states);
      break;
    }

    case MonsterState::SoftAngry:
    {
      gf::AnimatedSprite monster;
      monster.setAnimation(m_angryAnimations[1]);
      monster.setPosition(WorldSize);
      monster.setAnchor(gf::Anchor::BottomRight);
      monster.draw(target, states);
      break;
    }

    case MonsterState::Happy:
    {
      gf::AnimatedSprite monster;
      monster.setAnimation(m_happyAnimations[0]);
      monster.setPosition(WorldSize);
      monster.setAnchor(gf::Anchor::BottomRight);
      monster.draw(target, states);
      break;
    }

    case MonsterState::SoftHappy:
    {
      gf::AnimatedSprite monster;
      monster.setAnimation(m_happyAnimations[1]);
      monster.setPosition(WorldSize);
      monster.setAnchor(gf::Anchor::BottomRight);
      monster.draw(target, states);
      break;
    }
    }


    gf::Sprite officeBackground;
    officeBackground.setTexture(m_officeBackgroundTexture);
    officeBackground.draw(target, states);
  }

}
