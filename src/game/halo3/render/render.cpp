#include "render.h"

#include "../native/native.h"

class CRender : public ICRender {
public:
    chud_flag_t *getChud() override;
    render_flag_t *getRender() override;
    wireframe_flag_t *getWireframe() override;

    wireframe_flag_t m_wireframe_flag;

    static CRender s_instance;
};

CRender CRender::s_instance;
ICRender* g_pICRender = &CRender::s_instance;

chud_flag_t *CRender::getChud() {
    return (chud_flag_t*)(NativeInfo()->getEntryAddress((int)eEntry::chud) + 0x144);
}

render_flag_t *CRender::getRender() {
    return (render_flag_t*)NativeInfo()->getEntryAddress((int)eEntry::render);
}

wireframe_flag_t *CRender::getWireframe() {
    return &m_wireframe_flag;
}
