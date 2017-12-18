#ifndef QUAKE2_MOD_H
#define QUAKE2_MOD_H

#include "q2includewrapper.h"

typedef enum {
    FROZEN_TIME_BOOST,
    FROZEN_TIME_BOOST_GUNSHOT
} superhot_pickup_t;


typedef struct {
    qboolean is_player_moving;
    qboolean (*on_update)(edict_t *ent, usercmd_t *ucmd);

    qboolean (*should_allow_update_on)(edict_t *ent);

    void (*on_pickup)(superhot_pickup_t type, edict_t *ent);
} mod;
typedef void (firefunc_t)(edict_t*);
extern edict_t *player;

extern mod superhot;

#endif //QUAKE2_MOD_H
