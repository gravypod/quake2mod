//
// Created by gravypod on 11/18/17.
//

#ifndef QUAKE2_Q2INCLUDEWRAPPER_H
#define QUAKE2_Q2INCLUDEWRAPPER_H

#include "../g_local.h"
#include "../m_player.h"

void Weapon_Generic (edict_t *ent,
                     int FRAME_ACTIVATE_LAST,
                     int FRAME_FIRE_LAST,
                     int FRAME_IDLE_LAST,
                     int FRAME_DEACTIVATE_LAST,
                     int *pause_frames,
                     int *fire_frames,
                     void (*fire)(edict_t *ent));

#endif //QUAKE2_Q2INCLUDEWRAPPER_H
