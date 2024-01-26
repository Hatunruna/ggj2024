#ifndef MM_GAME_HUB_H
#define MM_GAME_HUB_H

#include <gf/GameManager.h>

#include "GameData.h"
#include "GameState.h"
#include "StartScene.h"
#include "TheaterScene.h"

namespace mm {

  struct GameHub : gf::GameManager {
    GameHub();

    GameData data;
    GameState state;

    StartScene start;
    TheaterScene theater;
  };


}


#endif // MM_GAME_HUB_H
