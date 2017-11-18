#include "sh_bullet.h"



void blaster_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);

/*
=================
check_dodge

This is a support routine used when a client is firing
a non-instant attack weapon.  It checks to see if a
monster's dodge function should be called.
=================
*/
static void check_dodge (edict_t *self, vec3_t start, vec3_t dir, int speed)
{
    vec3_t	end;
    vec3_t	v;
    trace_t	tr;
    float	eta;

    // easy mode only ducks one quarter the time
    if (skill->value == 0)
    {
        if (random() > 0.25)
            return;
    }
    VectorMA (start, 8192, dir, end);
    tr = gi.trace (start, NULL, NULL, end, self, MASK_SHOT);
    if ((tr.ent) && (tr.ent->svflags & SVF_MONSTER) && (tr.ent->health > 0) && (tr.ent->monsterinfo.dodge) && infront(tr.ent, self))
    {
        VectorSubtract (tr.endpos, start, v);
        eta = (VectorLength(v) - tr.ent->maxs[0]) / speed;
        tr.ent->monsterinfo.dodge (tr.ent, self, eta);
    }
}


void superhot_bullet_touch (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
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
    /*
    else
    {
        JDK: No sprite for explode for bullets
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
     */


    // JdK Bullets don't ahve a radius damage
    // JDK T_RadiusDamage(ent, ent->owner, ent->radius_dmg, other, ent->dmg_radius, MOD_R_SPLASH);

    // JDK Remove explosions from bullets
    //gi.WriteByte (svc_temp_entity);
    //if (ent->waterlevel)
    //    gi.WriteByte (TE_ROCKET_EXPLOSION_WATER);
    //else
    //    gi.WriteByte (TE_ROCKET_EXPLOSION);
    //gi.WritePosition (origin);
    //gi.multicast (ent->s.origin, MULTICAST_PHS);

    // JDK send a blaster muzzle flash
    gi.WriteByte (svc_muzzleflash);
    gi.WriteShort (ent-g_edicts);
    gi.WriteByte (MZ_BLASTER);
    gi.multicast (ent->s.origin, MULTICAST_PVS);

    G_FreeEdict (ent);
}


void fire_superhot_bullet (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage)
{
    edict_t	*rocket;

    rocket = G_Spawn();
    VectorCopy (start, rocket->s.origin);
    VectorCopy (dir, rocket->movedir);
    vectoangles (dir, rocket->s.angles);
    VectorScale (dir, speed, rocket->velocity);
    rocket->movetype = MOVETYPE_FLYMISSILE;
    rocket->clipmask = MASK_SHOT;
    rocket->solid = SOLID_BBOX;
    rocket->s.effects |= EF_BLASTER; //EF_ROCKET;
    VectorClear (rocket->mins);
    VectorClear (rocket->maxs);
    rocket->s.modelindex = gi.modelindex ("models/objects/rocket/tris.md2");
    rocket->owner = self;
    rocket->touch = superhot_bullet_touch;
    rocket->nextthink = level.time + 8000/speed;
    rocket->think = G_FreeEdict;
    rocket->dmg = 999999;
    rocket->radius_dmg = radius_damage;
    rocket->dmg_radius = 1; //damage_radius;
    rocket->s.sound = gi.soundindex ("misc/lasfly.wav");
    // JDK: Bullets go PEW!
    // gi.soundindex ("weapons/rockfly.wav");
    rocket->classname = "rocket";

    if (self->client)
        check_dodge (self, rocket->s.origin, dir, speed);

    gi.linkentity (rocket);
}
