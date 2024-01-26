#include "GameHub.h"

#include "config.h"

namespace mm {

  GameHub::GameHub()
  : GameManager("Game", { GAME_DATADIR })
  , start(*this)
  , theater(*this)
  {
    pushScene(start);
  }

}
