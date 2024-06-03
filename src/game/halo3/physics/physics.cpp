#include "physics.h"

static Halo3::Physics::BumpPossession_t s_data;

Halo3::Physics::BumpPossession_t *Halo3::Physics::BumpPossession() {
    return &s_data;
}
