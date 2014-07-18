#ifndef NORDICARTS_RANDGAME_H
#define NORDICARTS_RANDGAME_H

#include "./includes.h"
#include "./Game/Game.h"

namespace NordicArts {
    enum GameState {
        GS_INTRO,
        GS_MENU,
        GS_PAUSED_MENU,
        GS_GAME,
        GS_QUIT,
        GS_NUM_GAME_STATES,
    };
};

#endif
