#include "render.h"

#include "../native/native.h"

class CRender : public ICRender {
public:
    render_flags_t *getRenderFlags() override;

    static CRender s_instance;
};

CRender CRender::s_instance;
ICRender* g_pICRender = &CRender::s_instance;

render_flags_t *CRender::getRenderFlags() {return (render_flags_t*)(NativeInfo()->getEntryAddress((int)eEntry::render) + 0x144);}
