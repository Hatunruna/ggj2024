#include "GameHub.h"

#include "config.h"

namespace mm {

  GameHub::GameHub()
  : GameManager("Game", { GAME_DATADIR })
  , common(*this)
  , start(*this)
  , listFirst(*this, ConstraintListType::First)
  , theater(*this)
  , listRecall(*this, ConstraintListType::Recall)
  {
    std::vector<gf::Ref<gf::Scene>> scenes;
    scenes.push_back(common);
    scenes.push_back(start);

    pushScenes(scenes);
  }

}
