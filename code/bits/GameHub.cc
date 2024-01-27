#include "GameHub.h"

#include <gf/Log.h>

#include "config.h"

namespace mm {

  GameHub::GameHub()
  : GameManager("Game", { GAME_DATADIR })
  , common(*this)
  , start(*this)
  , listFirst(*this, ConstraintListType::First)
  , theater(*this)
  , listRecall(*this, ConstraintListType::Recall)
  , debrief(*this)
  {
    std::vector<gf::Ref<gf::Scene>> scenes;
    scenes.push_back(common);
    scenes.push_back(start);

    pushScenes(scenes);
  }

  bool GameHub::startNewShift() {
    if (state.currentLevel >= static_cast<int>(data.levelSettings.size())) {
      return false;
    }

    const auto& levelSettings = data.levelSettings[state.currentLevel];
    gf::Log::debug("Level Settings: %d constraints %d movies\n", levelSettings.constraintCount, levelSettings.movieCount);
    state.movieLevel = computeLevel(data.movieDatabase, levelSettings.constraintCount, levelSettings.movieCount, random);
    state.currentMovie = 0;
    ++state.currentLevel;
    return true;
  }

}
