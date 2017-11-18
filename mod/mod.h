#ifndef QUAKE2_MOD_H
#define QUAKE2_MOD_H

#include "../q_shared.h"

typedef struct {
    qboolean is_player_moving;
    void (*set_player_moving)(qboolean);
} mod;

extern mod superhot;

#endif //QUAKE2_MOD_H
