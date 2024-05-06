#include "input.h"

#include "../native/native.h"

class CInput : public ICInput {
public:
    void enableInput(bool value) override;

    static CInput s_instance;
};

CInput CInput::s_instance;
ICInput* g_pHalo3ICInput = &CInput::s_instance;

void CInput::enableInput(bool value) {
    *(bool*)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PV_ENABLE_INPUT) = value;
}
