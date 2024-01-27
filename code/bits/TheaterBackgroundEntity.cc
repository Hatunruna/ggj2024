#include "TheaterBackgroundEntity.h"

#include <gf/AnimatedSprite.h>
#include <gf/Sprite.h>

#include "GameHub.h"

namespace {
  constexpr float IdleTime = 1.0f;
}

namespace mm {

  TheaterBackgroundEntity::TheaterBackgroundEntity(GameHub& game)
  : m_gameData(game.data)
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

    // Load happy animations
    {
      gf::Animation animation;
      animation.addTileset(game.resources.getTexture("images/monster-happy-a-0.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-a-1.png"), gf::vec(4, 1), frequency, 4);
      animation.addTileset(game.resources.getTexture("images/monster-happy-a-2.png"), gf::vec(4, 1), frequency, 4);
      animation.setLoop(false);

      m_happyAnimations.emplace_back(std::move(animation));
    }
  }

  void TheaterBackgroundEntity::update(gf::Time time)
  {
    switch (m_gameData.monsterState) {
    case MonsterState::Neutral:
      m_elapsedTime += time;
      if (m_elapsedTime.asSeconds() >= IdleTime) {
        m_elapsedTime = gf::Time::Zero;

        m_gameData.monsterState = MonsterState::Angry;
      }
      break;

    case MonsterState::Angry:
    {
      assert(m_currentAnimation < m_angryAnimations.size());
      gf::Animation& animation = m_angryAnimations[m_currentAnimation];

      animation.update(time);
      if (animation.isFinished()) {
        animation.reset();
        m_gameData.monsterState = MonsterState::Happy;
      }
      break;
    }

    case MonsterState::Happy:
    {
      assert(m_currentAnimation < m_happyAnimations.size());
      gf::Animation& animation = m_happyAnimations[m_currentAnimation];

      animation.update(time);
      if (animation.isFinished()) {
        animation.reset();
        m_gameData.monsterState = MonsterState::Neutral;
      }
      break;
    }
    }
  }

  void TheaterBackgroundEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Sprite theaterBackground;
    theaterBackground.setTexture(m_theaterBackgroundTexture);
    theaterBackground.draw(target, states);

    switch (m_gameData.monsterState) {
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
      assert(m_currentAnimation < m_angryAnimations.size());

      gf::AnimatedSprite monster;
      monster.setAnimation(m_angryAnimations[m_currentAnimation]);
      monster.setPosition(WorldSize);
      monster.setAnchor(gf::Anchor::BottomRight);
      monster.draw(target, states);
      break;
    }

    case MonsterState::Happy:
    {
      assert(m_currentAnimation < m_happyAnimations.size());

      gf::AnimatedSprite monster;
      monster.setAnimation(m_happyAnimations[m_currentAnimation]);
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
