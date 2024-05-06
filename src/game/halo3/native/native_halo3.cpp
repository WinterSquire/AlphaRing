#include "native_halo3.h"

class CHalo3 : public ICHalo3 {
public:
    CNativeInfo *NativeInfo() override {return &m_nativeInfo;}

    static CHalo3 s_instance;

private:
    CNativeInfo m_nativeInfo;

};

CHalo3 CHalo3::s_instance;
ICHalo3* g_pICHalo3 = &CHalo3::s_instance;
