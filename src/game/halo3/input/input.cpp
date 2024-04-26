#include "input.h"

#include "../native/native.h"

class CInput : public ICInput {
public:
    void enableInput(bool value) override;

    static CInput s_instance;
};

CInput CInput::s_instance;
ICInput* g_pICInput = &CInput::s_instance;

void CInput::enableInput(bool value) {
    *(bool*)(NativeInfo()->getModuleAddress() + 0x20AC061) = value;
}
