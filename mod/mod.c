#include "mod.h"


void player_moving(qboolean moving)
{
    superhot.is_player_moving = moving;
}

mod superhot = {
        .is_player_moving = false,
        .set_player_moving = player_moving
};