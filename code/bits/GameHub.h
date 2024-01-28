#ifndef MM_GAME_HUB_H
#define MM_GAME_HUB_H

#include <gf/GameManager.h>

#include "AudioController.h"
#include "AudioManager.h"
#include "CommonScene.h"
#include "DebriefScene.h"
#include "GameData.h"
#include "GameOverScene.h"
#include "GameState.h"
#include "StartScene.h"
#include "ConstraintListScene.h"
#include "TheaterScene.h"

namespace mm {

  struct GameHub : gf::GameManager {
    GameHub();

    void startNewShift();
    void endShift();

    AudioManager audioResources;
    AudioController sounds;

    GameData data;
    GameState state;

    CommonScene common;
    StartScene start;
    ConstraintListScene listFirst;
    TheaterScene theater;
    ConstraintListScene listRecall;
    DebriefScene debrief;
    GameOverScene gameOver;
  };


}


#endif // MM_GAME_HUB_H
