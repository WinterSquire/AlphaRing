#ifndef ALPHA_RING_EOBJECTTYPE_H
#define ALPHA_RING_EOBJECTTYPE_H

enum eObjectType : unsigned int {
    OBJECTTYPE_BIPED,
    OBJECTTYPE_VEHICLE,
    OBJECTTYPE_WEAPON,
    OBJECTTYPE_EQUIPMENT,
    OBJECTTYPE_TERMINAL,
    OBJECTTYPE_PROJECTILE,
    OBJECTTYPE_SCENERY,
    OBJECTTYPE_MACHINE,
    OBJECTTYPE_CONTROL,
    OBJECTTYPE_SOUNDSCENERY,
    OBJECTTYPE_CRATE,
    OBJECTTYPE_CREATURE,
    OBJECTTYPE_GIANT,
    OBJECTTYPE_EFFECTSCENERY
};

static const char* eObjectTypeName[] =
{
        "biped",
        "vehicle",
        "weapon",
        "equipment",
        "terminal",
        "projectile",
        "scenery",
        "machine",
        "control",
        "soundscape",
        "crate",
        "creature",
        "giant",
        "effect scenery"
};

#endif //ALPHA_RING_EOBJECTTYPE_H
