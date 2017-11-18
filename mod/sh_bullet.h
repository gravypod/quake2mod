//
// Created by gravypod on 11/18/17.
//

#ifndef QUAKE2_SH_BULLET_H
#define QUAKE2_SH_BULLET_H

#include "q2includewrapper.h"


void fire_superhot_bullet (edict_t *self,
                           vec3_t start,
                           vec3_t dir,
                           int damage,
                           int speed,
                           float damage_radius,
                           int radius_damage);

#endif //QUAKE2_SH_BULLET_H
