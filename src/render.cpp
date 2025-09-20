#include "render.h"
#include "rasterizer.h"
#include "player.h"

#include "input.h"
#include "string_table.h"
#include "player_customization.h"

#include <cassert>

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>

#define IMGUI_CHECKBOX(object, property) \
	ImGui::Checkbox(#property, &object.property)

using namespace libmcc;

static struct {
	int game;
	unsigned long long id;
	char tag[5];
	char name[0x20];

	t_skin_list skin_list;
	t_gamepad_mapping gamepad_mapping;
	t_keyboard_mouse_mapping keyboard_mosue_mapping;

	libmcc::s_player_profile source;
} g_player_profile_interface_global;

void render_page1();
void render_page2();

void 
render_main() {
	constexpr auto main_window_flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse;

	static int page_index = 0;
	auto io = &ImGui::GetIO();
	auto context = ImGui::GetCurrentContext();

	// setup main window
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io->DisplaySize);

	// render main window
	ImGui::Begin("AR", 0, main_window_flags);

	if (ImGui::BeginMenuBar()) {
		const char* page_names[]{
			"Basics",
			"Profile",
		};

		for (int i = 0; i < _countof(page_names); ++i) {
			bool selected = page_index == i;
			if (ImGui::MenuItem(page_names[i], NULL, &selected)) page_index = i;
		}

		ImGui::EndMenuBar();
	}

	switch (page_index) {
	case 0: render_page1(); break;
	case 1: render_page2(); break;
	default: break;
	}

	ImGui::End();

	// handle window movement
	do {
		static bool is_moving = false;

		if (context->MovingWindow) {
			if (is_moving) break;
			is_moving = true;
			ReleaseCapture();
			SendMessage(g_rasterizer_global.wnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
		else {
			if (!is_moving) break;
			is_moving = false;
			SetCapture(g_rasterizer_global.wnd);
		}
	} while (false);
}

static void 
render_page1() {
	static int players = 1;
	auto io = &ImGui::GetIO();
	auto context = ImGui::GetCurrentContext();

	ImGui::InputInt("Players", &players);

	if (ImGui::BeginTabBar("Config")) {
		char buffer[] = "Player X";

		for (int i = 0; i < 4; ++i) {
			buffer[7] = '0' + i;

			if (ImGui::BeginTabItem(buffer)) {
				ImGui::Text(buffer);

				ImGui::EndTabItem();
			}
		}

		ImGui::EndTabBar();
	}
}

#define PROFILE_CHECKBOX(property) IMGUI_CHECKBOX(profile, property)

static void 
render_page2() {
	// render functions
	auto render_profile_control_layouy_km = [](
		unsigned char size_list[k_control_mapping_group_count],
		unsigned char action_list[k_game_abstract_button_count],
		int button_list[k_game_abstract_button_count][2],
		const char* global_action_group_name_list[],
		const char* global_action_name_list[],
		const char* global_button_name_list[]
	) {
		for (int i = 0; i < k_control_mapping_group_count; ++i) {
			auto size = size_list[i];

			if (!size ||
				!ImGui::TreeNode(global_action_group_name_list[i])) continue;

			if (ImGui::BeginTable(global_action_group_name_list[i], 3)) {
				for (int j = 0; j < size; ++j) {
					ImGui::TableNextRow();
					auto action = action_list[j];

					ImGui::TableSetColumnIndex(0);
					ImGui::Text(global_action_name_list[action]);

					ImGui::TableSetColumnIndex(1);
					if (ImGui::Button("")) {
						// set primary key
					}

					ImGui::TableSetColumnIndex(2);
					if (ImGui::Button("")) {
						// set secondary key
					}
				}
				ImGui::EndTable();
			}

			ImGui::TreePop();

			action_list += size;
		}		
	};

	auto render_profile_control_km = [](libmcc::s_player_profile& profile) {
		PROFILE_CHECKBOX(mouse_look_controls_inverted);
		PROFILE_CHECKBOX(mouse_aircraft_controls_inverted);
		PROFILE_CHECKBOX(mouse_look_controls_inverted);
		PROFILE_CHECKBOX(mouse_look_controls_inverted);
		PROFILE_CHECKBOX(mouse_look_controls_inverted);
	};

	auto render_profile_control_gamepad = [](libmcc::s_player_profile& profile) {
		/*
		// control
        bool mk_crouch_lock_enabled; // 0x25
        bool vertical_look_sensitivity; // 0x1B5
        bool horizontal_look_sensitivity; // 0x1B6
        bool look_acceleration; // 0x1B7
        float look_axial_dead_zone; // 0x1B8
        float look_radial_dead_zone; // 0x1BC
        float zoom_look_sensitivity_multiplier; // 0x1C0
        float vehicle_look_sensitivity_multiplier; // 0x1C4
        bool button_preset; // 0x1C8
        bool stick_preset; // 0x1C9
        bool lefty_toggle; // 0x1CA
        bool flying_camera_turn_sensitivity; // 0x1CB
        bool flying_camera_panning; // 0x1CC
        bool flying_camera_speed; // 0x1CD
        bool flying_camera_thrust; // 0x1CE
        bool theater_turn_sensitivity; // 0x1CF
        bool theater_panning; // 0x1D0
        bool theater_speed; // 0x1D1
        bool theater_thrust; // 0x1D2
        bool mk_theater_turn_sensitivity; // 0x1D3
        bool mk_theater_panning; // 0x1D4
        bool mk_theater_speed; // 0x1D5
        bool mk_theater_thrust; // 0x1D6
        bool swap_triggers_and_bumpers; // 0x1D7
        bool use_modern_aim_control; // 0x1D8
        bool use_double_press_jump_to_jetpack; // 0x1D9
        bool dual_wield_inverted; // 0x1DA
        bool controller_dual_wield_inverted; // 0x1DB
        bool controller_hornet_control_joystick; // 0x1DC
        bool controller_banshee_trick_buttons_swapped; // 0x1DD
        float mouse_sensitivity; // 0x410
        bool mouse_smoothing; // 0x414
        bool mouse_acceleration; // 0x415
        float mouse_acceleration_min_rate; // 0x418
        float mouse_acceleration_max_accel; // 0x41C
        float mouse_acceleration_scale; // 0x420
        float mouse_acceleration_exp; // 0x424
        int keyboard_mouse_button_preset; // 0x428
		*/
		PROFILE_CHECKBOX(auto_center_enabled);
		PROFILE_CHECKBOX(look_controls_inverted);
		PROFILE_CHECKBOX(aircraft_controls_inverted);
		PROFILE_CHECKBOX(vibration_disabled);
		PROFILE_CHECKBOX(crouch_lock_enabled);
		PROFILE_CHECKBOX(impulse_triggers_disabled);
		PROFILE_CHECKBOX(hold_to_zoom);
		PROFILE_CHECKBOX(clench_protection_enabled);
	};

	auto render_profile_control_layout_gamepad = [](
		unsigned char size_list[k_control_mapping_group_count],
		unsigned char action_list[k_game_abstract_button_count],
		unsigned char button_list[k_game_abstract_button_count],
		const char* global_action_group_name_list[],
		const char* global_action_name_list[],
		const char* global_button_name_list[]
	) {
		for (int i = 0; i < k_control_mapping_group_count; ++i) {
			auto size = size_list[i];

			if (!size||
				!ImGui::TreeNode(global_action_group_name_list[i])) continue;

			for (int j = 0; j < size; ++j) {
				auto action = action_list[j];
				auto button = static_cast<int>(button_list[action]);

				if (!ImGui::Combo(
					global_action_name_list[action],
					&button,
					global_button_name_list,
					k_abstract_gamepad_button_count
				))
					continue;

				button_list[action] = button;
			}

			ImGui::TreePop();

			action_list += size;
		}
	};

	auto render_profile_video = [](libmcc::s_player_profile* profile) {		
		ImGui::Checkbox("lock_max_aspect_ratio", &profile->lock_max_aspect_ratio);
		ImGui::InputFloat("Brightness", &profile->brightness);
		ImGui::InputFloat("HUD Scale", &profile->hud_scale);
		ImGui::InputInt("FOV", &profile->fov_setting);
		ImGui::InputInt("Vehicle FOV", &profile->vehicle_fov_setting);
	};

	auto render_profile_audio = [](libmcc::s_player_profile* profile) {
		ImGui::InputFloat("Master Volume", &profile->master_volume);
		ImGui::InputFloat("Music Volume", &profile->music_volume);
		ImGui::InputFloat("SFX Volume", &profile->sfx_volume);
	};

	auto render_profile_display_offset = [](float offsets[5][3], const char* names[5]) {
		for (int i = 0; i < 5; ++i) {
			ImGui::InputFloat3(names[i], offsets[i]);
		}
	};

	auto render_profile_gameplay = [](libmcc::s_player_profile* profile) {
		ImGui::Checkbox("Crosshair Location", &profile->crosshair_location);
	};

	auto render_profile_customization = [](libmcc::s_player_profile* profile) {
		ImGui::Checkbox("Use female voice", &profile->use_female_voice);
		ImGui::Checkbox("Use elite model", &profile->use_elite_model);
		ImGui::Checkbox("Users skins enabled", &profile->users_skins_enabled);

		ImGui::InputInt("Player Model primary color", &profile->player_model_primary_color_index);
		ImGui::InputInt("Player model secondary color", &profile->player_model_secondary_color_index);
		ImGui::InputInt("Player model tertiary color", &profile->player_model_tertiary_color_index);
		ImGui::InputInt("Player model permutation", &profile->player_model_permutation);
	};

	auto render_profile_customization_categories = [](
		const unsigned char size_list[k_customizable_type_count],
		const unsigned char item_list[],
		const int skin_range_list[][2],
		int skin_list[],
		const int global_skin_list[],
		const char* global_armor_name_list[],
		const char* global_weapon_vehicle_name_list[],
		const char* global_skin_name_list[],
		const char* global_category_name_list[]
	) {
		for (int i = 0; i < k_customizable_type_count; ++i) {
			auto size = size_list[i];

			if (!size ||
				!ImGui::TreeNode(global_category_name_list[i])) 
					continue;

			for (int j = 0; j < size; ++j) {
				auto item = item_list[j];
				auto skin = skin_list[j];
				auto item_name = i == 0 ? global_armor_name_list[item] : global_weapon_vehicle_name_list[item];
				auto skin_name = (skin < 0 || skin >= k_customization_item_count) ? NULL : global_skin_name_list[skin];

				if (!ImGui::BeginCombo(item_name, skin_name)) continue;

				for (int k = skin_range_list[j][0]; k < skin_range_list[j][1]; ++k) {
					auto skin_item = global_skin_list[k];
					bool selected = skin == skin_item;

					if (!ImGui::Selectable(global_skin_name_list[skin_item], &selected))
						continue;

					skin_list[j] = skin_item;
					break;
				}

				ImGui::EndCombo();
			}

			ImGui::TreePop();

			item_list += size;
			skin_list += size;
			skin_range_list += size;
		}
	};	

	// local variables
	auto io = &ImGui::GetIO();
	auto context = ImGui::GetCurrentContext();
	auto global = &g_player_profile_interface_global;

	// layout
	if (ImGui::BeginCombo("Name", global->name)) {

		ImGui::EndCombo();
	}

	ImGui::InputInt2("ID", (int*)&global->id);
	ImGui::InputText("Tag", global->tag, 5);

	ImGui::Combo("Game", &global->game, k_game_titles, k_game_count);

	ImGui::Button("New");
	ImGui::SameLine();
	ImGui::Button("Delete");
	ImGui::SameLine();
	ImGui::Button("Apply");
	ImGui::SameLine();
	ImGui::Button("Cancel");

	if (ImGui::CollapsingHeader("Control")) {
		if (ImGui::TreeNode("Keyboard & Mouse")) {
			if (ImGui::TreeNode("Layout")) {

				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Gamepad")) {
			if (ImGui::TreeNode("Layout")) {

				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}

	if (ImGui::CollapsingHeader("Customization")) {
		auto game_customization_global = 
			g_customization_global.game_customization_globals + global->game;

		render_profile_customization(&global->source);

		render_profile_customization_categories(
			game_customization_global->sizes,
			game_customization_global->items,
			game_customization_global->skins,
			global->skin_list,
			g_customization_global.skins,
			k_customizable_armor_names,
			k_customizable_weapon_vehicle_names,
			k_customization_item_names,
			k_customizable_type_names
		);
	}

	if (ImGui::CollapsingHeader("Video")) {
		render_profile_video(&global->source);
	}

	if (ImGui::CollapsingHeader("Audio")) {
		render_profile_audio(&global->source);
	}

	if (ImGui::CollapsingHeader("Gameplay")) {
		render_profile_gameplay(&global->source);	
		if (ImGui::TreeNode("Weapon Display Offse")) {
			render_profile_display_offset(
				reinterpret_cast<float(*)[3]>(&global->source.weapon_display_offset),
				k_display_offset_weapon_type_names
			);
			ImGui::TreePop();
		}
	}

	if (ImGui::CollapsingHeader("Misc")) {

	}
}