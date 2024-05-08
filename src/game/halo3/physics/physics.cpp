#include "physics.h"

#include "../native/native.h"

class CPhysics : public ICPhysics {
public:
    physics_constant_t *PhysicsConstant() override;

    bump_possession_setting_t *BumpPossessionSetting() override;

    static CPhysics instance;
    
private:
    bump_possession_setting_t m_bumpPossessionSetting;

};

CPhysics CPhysics::instance;
ICPhysics* g_pHalo3ICPhysics = &CPhysics::instance;

physics_constant_t *CPhysics::PhysicsConstant() {
    return (physics_constant_t*)NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_PHYSICS_CONSTANTS);
}

bump_possession_setting_t *CPhysics::BumpPossessionSetting() {
    return &m_bumpPossessionSetting;
}
