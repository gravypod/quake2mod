#include "mod.h"

int frozen_frames = 0;
edict_t *player = NULL;

float SUPERHOT_frametime = 0.1f;


void player_moving(qboolean moving) {
    superhot.is_player_moving = moving;
}

qboolean on_update(edict_t *ent, usercmd_t *ucmd) {

    if (!player)
        player = ent;

    // Detect if the player is currently moving
    qboolean moving = (qboolean) (ucmd->forwardmove != 0 || ucmd->sidemove != 0 || ucmd->upmove != 0);

    // If they die allow them to see respawn menu
    if (player->health < 0)
        moving = true;

    // IF the player is moving subtract from frozen frames
    if (moving) {
        //superhot.add_frozen_frames(-3);
        frozen_frames = 0;
    } else {
        superhot.add_frozen_frames(1);
    }

    superhot.set_player_moving(moving);

    SUPERHOT_frametime = 0.1f / (frozen_frames > 0 ? frozen_frames : 1);

    return true;
}

qboolean should_allow_update_on(edict_t *ent) {
    if (ent->client)
        return true;
    
    return (qboolean) (frozen_frames == 0);
}

void add_frozen_frames(int num_frames) {
    frozen_frames += num_frames;
    if (frozen_frames < 0)
        frozen_frames = 0;
}

void on_pickup(superhot_pickup_t type, edict_t *ent) {
    static int called = 0;
    called++;
    switch (type) {
        case FROZEN_TIME_BOOST:
            gi.centerprintf(player, "SUPERHOT: 100 extra frozen frames (%d)", called);
            superhot.add_frozen_frames(100);
            break;
    }
}

mod superhot = {
        .is_player_moving = false,
        .set_player_moving = player_moving,
        .on_update = on_update,
        .should_allow_update_on = should_allow_update_on,
        .add_frozen_frames = add_frozen_frames,
        .on_pickup = on_pickup
};