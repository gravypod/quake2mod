#ifndef QUAKE2_MOD_H
#define QUAKE2_MOD_H

#include "q2includewrapper.h"
typedef struct {
    qboolean is_player_moving;
    void (*set_player_moving)(qboolean);
    qboolean (*on_update)(edict_t *ent, usercmd_t *ucmd);
} mod;

extern mod superhot;

#endif //QUAKE2_MOD_H
