#ifndef MM_GAME_HUB_H
#define MM_GAME_HUB_H

#include <gf/GameManager.h>

#include "CommonScene.h"
#include "GameData.h"
#include "GameState.h"
#include "StartScene.h"
#include "ConstraintListScene.h"
#include "TheaterScene.h"

namespace mm {

  struct GameHub : gf::GameManager {
    GameHub();

    GameData data;
    GameState state;

    CommonScene common;
    StartScene start;
    ConstraintListScene listFirst;
    TheaterScene theater;
    ConstraintListScene listRecall;
  };


}


#endif // MM_GAME_HUB_H
