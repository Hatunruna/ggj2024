#include "GameHub.h"

#include "config.h"

namespace xy {

  GameHub::GameHub()
  : GameManager("Game", { GAME_DATADIR })
  , state(random)
  , start(*this)
  , world(*this)
  , theater(*this)
  {
    pushScene(start);
  }

}
