#include "mod.h"

#define MIN_NUM_FROZEN_FRAMES 1
#define MAX_NUM_FROZEN_FRAMES 1000

#define MIN_FRAME_TIME 0.009f
#define MAX_FRAME_TIME 0.1f

#define CLAMP(value, mi, ma) \
    (((value) < (mi) ? (mi) : ((value) > (ma) ? (ma) : (value))))

int frozen_frames = 100;
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

/*
    frozen_frames = CLAMP(
            frozen_frames + (superhot.is_player_moving ? -5 : 1),
            MIN_NUM_FROZEN_FRAMES, MAX_NUM_FROZEN_FRAMES
    );
*/

    if (superhot.is_player_moving && (!frozen_frames || !frozen_frames--)) {
        if (frozen_frames) {
            frozen_frames--;
        } else {
            SUPERHOT_frametime = 0.1f;
        }
    } else {
        SUPERHOT_frametime = 0.0f;
    }

    //ent->client->ps.stats[STAT_HEALTH_ICON] = gi.imageindex('i_fixme');
    ent->client->ps.stats[STAT_HEALTH] = (int) (SUPERHOT_frametime / 0.1f) * 100;


    //double suggested_frame_time = /*0.1f - */(pow(0.1f, frozen_frames>>1));

/*
    double suggested_frame_time = 0.1f;

    if (frozen_frames >= 1 && frozen_frames < 100)
        suggested_frame_time = 0.1f;
    if (frozen_frames >= 100 && frozen_frames < 200)
        suggested_frame_time = 0.05f;
    if (frozen_frames >= 200 && frozen_frames < 300)
        suggested_frame_time = 0.04f;
    if (frozen_frames >= 300 && frozen_frames < 400)
        suggested_frame_time = 0.03f;
    if (frozen_frames >= 400 && frozen_frames < 500)
        suggested_frame_time = 0.02f;
    if (frozen_frames >= 500 && frozen_frames < 600)
        suggested_frame_time = 0.01f;
    if (frozen_frames >= 600 && frozen_frames < 700)
        suggested_frame_time = 0.009f;
    if (frozen_frames >= 700 && frozen_frames < 800)
        suggested_frame_time = 0.008f;
    if (frozen_frames >= 800 && frozen_frames < 900)
        suggested_frame_time = 0.007f;
    if (frozen_frames >= 900)
        suggested_frame_time = 0.006f;
*/



    //if (suggested_frame_time < MIN_FRAME_TIME)
    //    SUPERHOT_frametime = MIN_FRAME_TIME;
    //else if (suggested_frame_time > MAX_FRAME_TIME)
    //    SUPERHOT_frametime = MAX_FRAME_TIME;
    //else
    //SUPERHOT_frametime = (float) suggested_frame_time;

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

    called++;

    switch (type) {
        case FROZEN_TIME_BOOST:
            gi.centerprintf(player, "SUPERHOT:  Added (%d) frames (%d times)", frozen_time_boost, called);
            frozen_frames += frozen_time_boost;
            break;
    }
}

mod superhot = {
        .is_player_moving = false,
        .on_update = on_update,
        .should_allow_update_on = should_allow_update_on,
        .on_pickup = on_pickup
};