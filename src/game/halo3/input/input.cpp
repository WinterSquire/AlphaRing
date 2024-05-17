#include "input.h"

#include "../native/native.h"

class CH3Input : public ICH3Input {
public:
    void enableInput(bool value) override;

    static CH3Input s_instance;
};

CH3Input CH3Input::s_instance;
ICH3Input* g_pHalo3ICInput = &CH3Input::s_instance;

void CH3Input::enableInput(bool value) {
    *(bool*)(NativeHalo3()->NativeInfo()->getModuleAddress() + OFFSET_HALO3_PV_ENABLE_INPUT) = value;
}
