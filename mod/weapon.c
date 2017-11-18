
#include "q2includewrapper.h"
#include "sh_bullet.h"

extern qboolean is_quad;
extern qboolean is_silenced;

static void P_ProjectSource (gclient_t *client, vec3_t point, vec3_t distance, vec3_t forward, vec3_t right, vec3_t result)
{
    vec3_t	_distance;

    VectorCopy (distance, _distance);
    if (client->pers.hand == LEFT_HANDED)
        _distance[1] *= -1;
    else if (client->pers.hand == CENTER_HANDED)
        _distance[1] = 0;
    G_ProjectSource (point, _distance, forward, right, result);
}

void Superhot_Weapon_Fire (edict_t *ent)
{
    vec3_t	offset, start;
    vec3_t	forward, right;
    int		damage;
    float	damage_radius;
    int		radius_damage;

    damage = 100 + (int)(random() * 20.0);
    radius_damage = 120;
    damage_radius = 120;
    if (is_quad)
    {
        damage *= 4;
        radius_damage *= 4;
    }

    AngleVectors (ent->client->v_angle, forward, right, NULL);

    VectorScale (forward, -2, ent->client->kick_origin);
    ent->client->kick_angles[0] = -1;

    VectorSet(offset, 8, 8, ent->viewheight-8);
    P_ProjectSource (ent->client, ent->s.origin, offset, forward, right, start);
    // Original Line: fire_rocket (ent, start, forward, damage, 650, damage_radius, radius_damage);
    fire_superhot_bullet(ent, start, forward);

    // send muzzle flash
    gi.WriteByte (svc_muzzleflash);
    gi.WriteShort (ent-g_edicts);
    gi.WriteByte (MZ_BLASTER | is_silenced);
    gi.multicast (ent->s.origin, MULTICAST_PVS);

    ent->client->ps.gunframe++;

    PlayerNoise(ent, start, PNOISE_WEAPON);

    if (! ( (int)dmflags->value & DF_INFINITE_AMMO ) )
        ent->client->pers.inventory[ent->client->ammo_index]--;
}


void Superhot_Weapon_Blaster (edict_t *ent)
{
    static int	pause_frames[]	= {19, 32, 0};
    static int	fire_frames[]	= {5, 0};

    Weapon_Generic (ent, 4, 8, 52, 55, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_Shotgun (edict_t *ent)
{
    static int	pause_frames[]	= {22, 28, 34, 0};
    static int	fire_frames[]	= {8, 9, 0};

    Weapon_Generic (ent, 7, 18, 36, 39, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_SuperShotgun (edict_t *ent)
{

    static int	pause_frames[]	= {29, 42, 57, 0};
    static int	fire_frames[]	= {7, 0};

    Weapon_Generic (ent, 6, 17, 57, 61, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_Machinegun (edict_t *ent)
{
    static int	pause_frames[]	= {23, 45, 0};
    static int	fire_frames[]	= {4, 5, 0};

    Weapon_Generic (ent, 3, 5, 45, 49, pause_frames, fire_frames, Superhot_Weapon_Fire);
}
void Superhot_Weapon_Chaingun (edict_t *ent)
{

    static int	pause_frames[]	= {38, 43, 51, 61, 0};
    static int	fire_frames[]	= {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 0};

    Weapon_Generic (ent, 4, 31, 61, 64, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_HyperBlaster (edict_t *ent)
{
    static int	pause_frames[]	= {0};
    static int	fire_frames[]	= {6, 7, 8, 9, 10, 11, 0};

    Weapon_Generic (ent, 5, 20, 49, 53, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_RocketLauncher (edict_t *ent)
{
    static int	pause_frames[]	= {25, 33, 42, 50, 0};
    static int	fire_frames[]	= {5, 0};

    Weapon_Generic (ent, 4, 12, 50, 54, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_GrenadeLauncher (edict_t *ent)
{
    static int	pause_frames[]	= {34, 51, 59, 0};
    static int	fire_frames[]	= {6, 0};

    Weapon_Generic (ent, 5, 16, 59, 64, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_Railgun (edict_t *ent)
{
    static int	pause_frames[]	= {56, 0};
    static int	fire_frames[]	= {4, 0};

    Weapon_Generic (ent, 3, 18, 56, 61, pause_frames, fire_frames, Superhot_Weapon_Fire);
}

void Superhot_Weapon_BFG (edict_t *ent)
{
    static int	pause_frames[]	= {39, 45, 50, 55, 0};
    static int	fire_frames[]	= {9, 17, 0};

    Weapon_Generic (ent, 8, 32, 55, 58, pause_frames, fire_frames, Superhot_Weapon_Fire);
}