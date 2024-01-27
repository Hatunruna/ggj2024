#include "GameHub.h"

#include "config.h"

namespace mm {

  GameHub::GameHub()
  : GameManager("Game", { GAME_DATADIR })
  , start(*this)
  , listFirst(*this, ConstraintListType::First)
  , theater(*this)
  , listRecall(*this, ConstraintListType::Recall)
  {
    pushScene(start);
  }

}
