#include "render.h"

#include "../native/native.h"

class CRender : public ICRender {
public:
    chud_flag_t *getChudFlag() override;
    render_flag_t *getRender() override;
    wireframe_flag_t *getWireframe() override;
    chud_t *getChud() override;
    split_screen_t* getSplitScreen() override;

    wireframe_flag_t m_wireframe_flag;

    static CRender s_instance;
};

CRender CRender::s_instance;
ICRender* g_pHalo3ICRender = &CRender::s_instance;

chud_flag_t *CRender::getChudFlag() {
    return (chud_flag_t*)(NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_CHUD) + 0x144);
}

render_flag_t *CRender::getRender() {
    return (render_flag_t*)NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_RENDER);
}

wireframe_flag_t *CRender::getWireframe() {
    return &m_wireframe_flag;
}

chud_t *CRender::getChud() {
    return (chud_t*)NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_MESSAGE);
}

split_screen_t* CRender::getSplitScreen() {
    return (split_screen_t*)NativeHalo3()->NativeInfo()->getEntryAddress(OFFSET_HALO3_V_ENTRY_SPLIT_SCREEN);
}
