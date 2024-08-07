#pragma once

#define OFFSET_HALO3_PF_DRAW_STRUCTURE 0x27FDB4
#define OFFSET_HALO3_PF_DRAW_MODEL 0x2B51E0
#define OFFSET_HALO3_PF_ENGINE 0xB2A20
#define OFFSET_HALO3_PF_WORLD 0xEEDD4
#define OFFSET_HALO3_PF_MAP 0x42EF8
#define OFFSET_HALO3_PF_RENDER 0x1851EC

#define OFFSET_HALO3_PF_BUMP 0x37F438

#define OFFSET_HALO3_PF_COOP_JOIN 0x11DF8
#define OFFSET_HALO3_PF_OBJECT_CHANGE_COLOR 0x28B5B0

#define OFFSET_HALO3_PF_PLAYER_PUSH_MESSAGE 0x2D4884
#define OFFSET_HALO3_PF_PLAYER_POSSESS 0xE33FC
#define OFFSET_HALO3_PF_PLAYERS_CONTROL_CAMERA 0x131078

#define OFFSET_HALO3_PV_TAG_NAMES 0xA48148
#define OFFSET_HALO3_PV_ENABLE_INPUT 0x20AC061
#define OFFSET_HALO3_PV_GLOBAL_VARIABLE 0x2D3DD70
#define OFFSET_HALO3_PV_OBJECT_INFOS 0x814050

struct halo3_teb_data_definition {
    void* zero;
    void* actor;
    void* players;
    int current_tread;
    int padding;
    void* game_engine_globals;
    void* prop_ref;
    void* ai_globals;
    void* object;
    void* players_globals;
    void* game_globals;
    void* squad;
    void* scripted_camera_globals;
    void* effect;
    void* prop;
    void* un;
    void* command_scripts;
    int tag_resource_cache_paging;
    int padding2;
    void* halo_interpolation; // frame interpolation data
    void* cinematic_new_globals;
    void* render_texture_globals;
    void* clump;
    void* cinematic_globals;
    void* object_globals;
    void* breakable_surface_breakable_surface_globals;
    void* player_control_globals;
    void* game_time_globals;
    void* joint_state;
    void* campaign_meta_game_globals;
    void* object_broadphase;
    void* effect_event;
    void* chud_persistent_user_data1;
    void* object_looping_sounds;
    void* player_effects;
    void* player_training_globals;
    void* player_mapping_globals;
    void* gamestate_timing_samples;
    void* lights;
    void* scripted_exposure_globals;
    void* physics_constants;
    void* vocalization_records;
    void* recycling_group;
    void* effect_location;
    void* un1;
    void* chud_cortana_effect;
    void* impacts;
    void* game_sound_globals;
    void* object_early_movers;
    void* cached_object_render_states;
    void* game_allegiance_globals;
    void* director_globals;
    void* swarm;
    void* device_groups;
    void* rasterizer_game_states;
    void* game_save_globals;
    void* recycling_volumes;
    void* hs_runtime_globals;
    void* flocks;
    void* object_scripting;
    void* effect_counts;
    void* squad_group;
    void* cloth;
    void* particle_system;
    void* impact_globals;
    void* breakable_surface_set_broken_events;
    void* main_timing;
    void* tracking;
    void* widget;
    void* objectives;
    void* chud_persistent_user_data2;
    void* leaf_system;
    void* damage_globals;
    void* local_game_engine_globals;
    void* sim_gamestate_entities;
    void* dynamic_firing_points;
    void* DOF_globals;
    void* beam_system;
    void* light_volume_system;
    void* particle_location;
    void* contrail_system;
    void* un2;
    void* scenario_interpolator_globals;
    void* havok_proxies;
    void* ai_player_state_globals;
    void* particle_emitter;
    void* game_sound_scripted_impulses;
    void* decal_system;
    void* rumble;
    void* effect_geometry_sample;
    void* object_schedule_globals;
    void* c_particle_emitter_gpu;
    void* object_list_header;
    void* decal_counts;
    void* hs_globals;
    void* swarm_spawner;
    void* screen_effect;
    void* muffin;
    void* antenna;
    void* lights_globals;
    void* c_particle_emitter_gpu_s_row;
    void* beam_location;
    void* light_volume_location;
    void* contrail_location;
    void* impact_arrarys;
    void* s_structure_seam_globals;
    void* tracking_hs_thread;
    void* render_timing_samples;
    void* rasterizer;
    void* interaction_ripples;
    void* particles;
    void* non_det_hs_thread;
    void* beam;
    void* light_volume;
    void* contrail;
    void* objects;
    void* c_beam_gpu;
    void* c_light_volume_gpu;
    void* det_hs_thread;
    void* ai_reference_frame;
    void* object_activation_regions;
    void* c_contrail_gpu_s_row;
    void* c_contrail_gpu;
    void* recorded_animations;
    void* c_beam_gpu_s_row;
    void* c_light_volume_gpu_s_row;
    void* hue_saturation_control;
    void* contrail_profile;
    void* decal;
    void* place_holder;
    void* object_name_list;
    void* campaign_objectives;
    void* list_object_reference;
    void* kill_trigger_volume_state;
    void* sound_classes;
    void* vocalization_timers;
    void* effect_lightprobes;
    void* game_sound_player_effects_globals;
    void* bink_game_state;
    void* effect_messaging_queue;
    void* director_scripting;
    void* chud_widgets0;
    void* chud_widgets1;
    void* chud_widgets2;
    void* chud_widgets3;
    void* un3;
    void* object_messaging_queue;
    void* decal_messaging_queue;
    void* havok_gamestate;
    void* player_control_globals_deterministic;
    void* cluster_collideable_object_reference;
    void* collideable_object_cluster_reference;
    void* place_holder2;
    void* spawner_globals;
    void* observer_gamestate_globals;
    void* cluster_noncollideable_object_reference;
    void* noncollideable_object_cluster_reference;
    void* place_holder3;
    void* un4;
    void* object_placement_globals;
    void* c_particle_emitter_gpu1;
    void* c_particle_emitter_gpu2;
    void* c_particle_emitter_gpu4;
    void* c_particle_emitter_gpu3;
    void* render_game_globals;
    void* soft_surface_globals;
    void* cluster_light_reference;
    void* light_cluster_reference;
    void* place_holder4;
    void* OBJ_Render_Data;
    void* cinematic_light_globals;
    void* visibility_active_portals;
    void* random_math;
    void* task_records;
    void* fp_orientations;
    void* fp_weapons;
    void* deterministic_game_sound_globals;
    void* observer_globals;
    void* nondet_light_data;
    void* render_object;
};