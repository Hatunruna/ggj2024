#include "GameHub.h"

#include <gf/Log.h>

#include "config.h"

namespace mm {

  GameHub::GameHub()
  : GameManager("Midnight Movies", { GAME_DATADIR })
  , common(*this)
  , start(*this)
  , listFirst(*this, ConstraintListType::First)
  , theater(*this)
  , listRecall(*this, ConstraintListType::Recall)
  , debrief(*this)
  , gameOver(*this)
  {
    std::vector<gf::Ref<gf::Scene>> scenes;
    scenes.push_back(common);
    scenes.push_back(start);

    pushScenes(scenes);
  }

  void GameHub::startNewShift() {
    assert(state.currentLevel < static_cast<int>(data.levelSettings.size()));

    const auto& levelSettings = data.levelSettings[state.currentLevel];
    gf::Log::debug("Level Settings: %d constraints %d movies\n", levelSettings.constraintCount, levelSettings.movieCount);
    state.movieLevel = computeLevel(data.movieDatabase, levelSettings.constraintCount, levelSettings.movieCount, random);
    state.currentMovie = 0;
    state.correctChoices = 0;
    state.incorrectChoices = 0;
    state.movieState = MovieState::NoMovie;
  }

  void GameHub::endShift() {
    const int totalMovies = data.levelSettings[state.currentLevel].movieCount;
    const float ratio = static_cast<float>(state.correctChoices) / static_cast<float>(totalMovies);

    if (ratio >= NeutralLimit) {
      int newHappinessValue = gf::clamp(static_cast<int>(state.monsterHappiness) + 1, 0, 4);
      state.monsterHappiness = static_cast<MonsterHappiness>(newHappinessValue);
    } else if (ratio <= AngerLimit) {
      int newHappinessValue = gf::clamp(static_cast<int>(state.monsterHappiness) - 1, 0, 4);
      state.monsterHappiness = static_cast<MonsterHappiness>(newHappinessValue);
    }

    replaceScene(debrief);
  }

}
