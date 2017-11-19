#include "mod.h"


void player_moving(qboolean moving) {
    superhot.is_player_moving = moving;
}

qboolean on_update(edict_t *ent, usercmd_t *ucmd) {
    qboolean last_moving = superhot.is_player_moving;
    superhot.set_player_moving((qboolean) (ucmd->forwardmove != 0 || ucmd->sidemove != 0 || ucmd->upmove != 0));

    if (last_moving != superhot.is_player_moving) {
        gi.centerprintf(ent, "Moving changed");
    }

    return true;
}

qboolean should_allow_update_on(edict_t *ent) {
    if (ent->client)
        return true;
    
    return superhot.is_player_moving;
}

mod superhot = {
        .is_player_moving = false,
        .set_player_moving = player_moving,
        .on_update = on_update,
        .should_allow_update_on = should_allow_update_on
};