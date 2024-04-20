#ifndef ALPHA_RING_NATIVE_INFO_H
#define ALPHA_RING_NATIVE_INFO_H


enum class eEntry : int {
    actor = 1,
    players = 2,
    prop_ref = 5,
    object = 7,
    clump = 14,
    lights = 24,
    time = 25,
    vocalization_records = 27,
    recycling_group = 28,
    effect_location = 29,
    swarm = 32,
    device_groups = 33,
    flocks = 38,
    tracking = 41,
    widget = 42,
    objectives = 43,
    leaf_system = 45,
    sim_gamestate_entities = 48,
    dynamic_firing_points = 49,
    havok_proxies = 50,
    effect_geometry_sample = 57,
    antenna = 60,
    impact_arrarys = 66,
    tracking_hs_thread = 68,
    loopobjects = 71,
    det_hs_thread = 74,
    object_activation_regions = 76,
    recorded_animations = 79,
    list_object_reference = 82,
    cluster_collideable_object_refe = 94,
    collideable_object_cluster_refe = 95,
    cluster_noncollideable_object_r = 99,
};

class ICNativeInfo {
public:
    virtual bool setModuleAddress(__int64 hModule) = 0;
    virtual __int64 getModuleAddress() = 0;
    virtual __int64 getEntryAddress(int index) = 0;
};

extern ICNativeInfo* g_pICNativeInfo;
inline ICNativeInfo* NativeInfo() { return g_pICNativeInfo; }


#endif //ALPHA_RING_NATIVE_INFO_H
