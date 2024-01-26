#ifndef XY_GAME_HUB_H
#define XY_GAME_HUB_H

#include <gf/GameManager.h>

#include "GameData.h"
#include "GameState.h"
#include "StartScene.h"
#include "TheaterScene.h"

namespace xy {

  struct GameHub : gf::GameManager {
    GameHub();

    GameData data;
    GameState state;

    StartScene start;
    TheaterScene theater;
  };


}


#endif // XY_GAME_HUB_H
