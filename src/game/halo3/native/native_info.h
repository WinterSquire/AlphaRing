#ifndef ALPHA_RING_NATIVE_INFO_H
#define ALPHA_RING_NATIVE_INFO_H


enum class eEntry : int {
    actor = 0x1,
    players = 0x2,
    prop_ref = 0x5,
    loop_actors = 0x6,
    object = 0x7,
    players_action = 0x8,
    map = 0x9,
    clump = 0x14,
    time = 25,
    message = 0x1E,
    lights = 0x24,
    physics_constants = 0x26,
    vocalization_records = 0x27,
    recycling_group = 0x28,
    effect_location = 0x29,
    cameras = 0x31,
    swarm = 0x32,
    device_groups = 0x33,
    render = 0x34,
    flocks = 0x38,
    tracking = 0x41,
    widget = 0x42,
    objectives = 0x43,
    chud = 0x44,
    leaf_system = 0x45,
    sim_gamestate_entities = 0x48,
    dynamic_firing_points = 0x49,
    havok_proxies = 0x50,
    effect_geometry_sample = 0x57,
    antenna = 0x60,
    impact_arrarys = 0x66,
    tracking_hs_thread = 0x68,
    loopobjects = 0x71,
    det_hs_thread = 0x74,
    object_activation_regions = 0x76,
    recorded_animations = 0x79,
    list_object_reference = 0x82,
    cluster_collideable_object_refe = 0x94,
    collideable_object_cluster_refe = 0x95,
    cluster_noncollideable_object_r = 0x99,
    cameras_data = 0xAF,
};

class ICNativeInfo {
public:
    virtual bool setModuleAddress(__int64 hModule) = 0;
    virtual __int64 getModuleAddress() = 0;
    virtual __int64 getEntryAddress(eEntry entry) = 0;
    virtual __int64 getEntryAddress(int index) = 0;

};

extern ICNativeInfo* g_pICNativeInfo;
inline ICNativeInfo* NativeInfo() { return g_pICNativeInfo; }


#endif //ALPHA_RING_NATIVE_INFO_H
