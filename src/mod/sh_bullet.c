#include "sh_bullet.h"
#include "mod.h"

#define SUPERHOT_BULLET_THINK_INTERVAL ((float)0.01)
#define SUPERHOT_BULLET_SPEED 500 // 650
#define SUPERHOT_BULLET_DAMAGE 999999

int frozen_frames;

/**
 * Trigger's an entity's dodge logic if it exists
 *
 * @param self - The entity
 * @param start - Where the projectile is coming from
 * @param dir - direction the bullet is going
 * @param speed - speed of projectile
 */
void check_dodge(edict_t *self, vec3_t start, vec3_t dir, int speed) {
    vec3_t end;
    vec3_t v;
    trace_t tr;
    float eta;

    // easy mode only ducks one quarter the time
    if (skill->value == 0) {
        if (random() > 0.25)
            return;
    }
    VectorMA(start, 8192, dir, end);
    tr = gi.trace(start, NULL, NULL, end, self, MASK_SHOT);
    if ((tr.ent) && (tr.ent->svflags & SVF_MONSTER) && (tr.ent->health > 0) && (tr.ent->monsterinfo.dodge) &&
        infront(tr.ent, self)) {
        VectorSubtract (tr.endpos, start, v);
        eta = (VectorLength(v) - tr.ent->maxs[0]) / speed;
        tr.ent->monsterinfo.dodge(tr.ent, self, eta);
    }
}

void superhot_bullet_touch(edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf) {

    vec3_t		origin;
    int			n;

    if (other == ent->owner)
        return;

    if (surf && (surf->flags & SURF_SKY))
    {
        G_FreeEdict (ent);
        return;
    }

    if (ent->owner->client)
        PlayerNoise(ent->owner, ent->s.origin, PNOISE_IMPACT);

    // calculate position for the explosion entity
    VectorMA (ent->s.origin, -0.02, ent->velocity, origin);

    if (other->takedamage)
    {
        T_Damage (other, ent, ent->owner, ent->velocity, ent->s.origin, plane->normal, ent->dmg, 0, 0, MOD_ROCKET);
    }
    else
    {
        // don't throw any debris in net games
        if (!deathmatch->value && !coop->value)
        {
            if ((surf) && !(surf->flags & (SURF_WARP|SURF_TRANS33|SURF_TRANS66|SURF_FLOWING)))
            {
                n = rand() % 5;
                while(n--)
                    ThrowDebris (ent, "models/objects/debris2/tris.md2", 2, ent->s.origin);
            }
        }
    }

    T_RadiusDamage(ent, ent->owner, ent->radius_dmg, other, ent->dmg_radius, MOD_R_SPLASH);

    gi.WriteByte (svc_temp_entity);
    if (ent->waterlevel)
        gi.WriteByte (TE_ROCKET_EXPLOSION_WATER);
    else
        gi.WriteByte (TE_ROCKET_EXPLOSION);
    gi.WritePosition (origin);
    gi.multicast (ent->s.origin, MULTICAST_PHS);

    if (ent->is_special_bullet) {
        superhot.on_pickup(FROZEN_TIME_BOOST_GUNSHOT, NULL);
    }

    G_FreeEdict (ent);
}

/*void superhot_bullet_think(edict_t *self) {

    if (superhot.is_player_moving) {
        VectorScale(self->movedir, SUPERHOT_BULLET_SPEED, self->velocity);
    } else {
        VectorSet(self->velocity, 0, 0, 0);
    }

    // Cleanup the think
    if (self->nextthink < self->dmg_radius)
        self->think = superhot_bullet_think;
    else
        self->think = G_FreeEdict;

    self->nextthink = level.time + SUPERHOT_BULLET_THINK_INTERVAL;
}*/

edict_t *fire_superhot_bullet(edict_t *self, vec3_t start, vec3_t dir) {
    edict_t *rocket = G_Spawn();

    VectorCopy (start, rocket->s.origin);
    VectorCopy (dir, rocket->movedir);
    vectoangles(dir, rocket->s.angles);
    VectorScale(dir, SUPERHOT_BULLET_SPEED, rocket->velocity);
    VectorClear (rocket->mins);
    VectorClear (rocket->maxs);

    rocket->owner = self;
    rocket->touch = superhot_bullet_touch;

    // Setup think method
    rocket->nextthink = level.time + (8000000 / SUPERHOT_BULLET_SPEED); //SUPERHOT_BULLET_THINK_INTERVAL;
    rocket->think = G_FreeEdict; // superhot_bullet_think;

    // Set super hot rocket damage
    rocket->dmg = SUPERHOT_BULLET_DAMAGE;

    // Disable radius damage
    rocket->radius_dmg = 0;

    // Radius damage isn't used so I'm using this variable as the "max think time"
    // JDK: This variable was co-opted as a special counter.
    rocket->dmg_radius = level.time + (8000 / SUPERHOT_BULLET_SPEED);

    // Setup missle-specfic styling
    rocket->movetype = MOVETYPE_FLYMISSILE;
    rocket->clipmask = MASK_SHOT;
    rocket->solid = SOLID_BBOX;
    rocket->s.effects |= EF_BLASTER;
    rocket->s.sound = gi.soundindex("misc/lasfly.wav");
    rocket->s.modelindex = gi.modelindex("models/objects/rocket/tris.md2");
    rocket->classname = "rocket";

    if (self->client) {
        check_dodge(self, rocket->s.origin, dir, SUPERHOT_BULLET_SPEED);
    }

    gi.linkentity(rocket);
    return rocket;
}
