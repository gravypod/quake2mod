#include "mod.h"

#define MIN_NUM_FROZEN_FRAMES 1
#define MAX_NUM_FROZEN_FRAMES 1000

#define MIN_FRAME_TIME 0.009f
#define MAX_FRAME_TIME 0.1f

#define CLAMP(value, mi, ma) \
    (((value) < (mi) ? (mi) : ((value) > (ma) ? (ma) : (value))))

int frozen_frames;
int frozen_frames = 0;
edict_t *player = NULL;

float SUPERHOT_frametime = 0.1f;


qboolean on_update(edict_t *ent, usercmd_t *ucmd) {

    if (!player)
        player = ent;

    //qboolean last_moving = superhot.is_player_moving;
    // Detect if the player is currently moving
    superhot.is_player_moving = (qboolean) ((ucmd->forwardmove != 0 ||
                                             ucmd->sidemove != 0 ||
                                             ucmd->upmove != 0) || (player->health < 0));


    if (superhot.is_player_moving && (!frozen_frames || !frozen_frames--)) {
        if (frozen_frames) {
            frozen_frames--;
        } else {
            SUPERHOT_frametime = 0.1f;
            player->client->quad_framenum = 0;
        }
    } else {
        SUPERHOT_frametime = 0.0f;
    }

    ent->client->ps.stats[STAT_HEALTH_ICON] = (short) gi.imageindex("i_fixme");
    ent->client->ps.stats[STAT_HEALTH] = (short) ((SUPERHOT_frametime / 0.1f) * 100);

    return true;
}

qboolean should_allow_update_on(edict_t *ent) {
    if (ent->client)
        return true;

    return (qboolean) (frozen_frames == 0);
}

void on_pickup(superhot_pickup_t type, edict_t *ent) {
    static int called = 0;
    static int frozen_time_boost = 500;


    if (player->client->quad_framenum < level.framenum)
        player->client->quad_framenum = level.framenum;

    switch (type) {
        case FROZEN_TIME_BOOST:
            gi.centerprintf(player, "SUPERHOT:  Picked up (%d) frozen frames (#%d)", frozen_time_boost, called);
            called++;
            frozen_frames += frozen_time_boost;
            player->client->quad_framenum += frozen_time_boost;
            break;
        case FROZEN_TIME_BOOST_GUNSHOT:
            gi.centerprintf(player, "SUPERHOT: Frozen Time Boost Kill");
            frozen_frames += 100;
            // Blue frozen-frames tint
            player->client->quad_framenum += 100;
            break;
    }
}

mod superhot = {
        .is_player_moving = false,
        .on_update = on_update,
        .should_allow_update_on = should_allow_update_on,
        .on_pickup = on_pickup
};