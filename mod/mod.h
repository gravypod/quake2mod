#ifndef QUAKE2_MOD_H
#define QUAKE2_MOD_H

#include "q2includewrapper.h"

typedef enum {
    FROZEN_TIME_BOOST
} superhot_pickup_t;


typedef struct {
    qboolean is_player_moving;
    void (*set_player_moving)(qboolean);
    qboolean (*on_update)(edict_t *ent, usercmd_t *ucmd);

    qboolean (*should_allow_update_on)(edict_t *ent);

    void (*add_frozen_frames)(int num_frames);

    void (*on_pickup)(superhot_pickup_t type, edict_t *ent);
} mod;

extern mod superhot;

#endif //QUAKE2_MOD_H
