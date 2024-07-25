#include "CUserProfile.h"

#include "CGameEngine.h"

#include "imgui.h"
#include <cstdio>

void CUserProfile::ImGuiContext() {
    bool result = false;
    char buffer[1024];

    result |= ImGui::Checkbox("SubtitleSetting", &SubtitleSetting);
    result |= ImGui::Checkbox("SubtitleSizeSetting", &SubtitleSizeSetting);
    result |= ImGui::Checkbox("SubtitleBackgroundSetting", &SubtitleBackgroundSetting);
    result |= ImGui::Checkbox("SubtitleShadowColorSetting", &SubtitleShadowColorSetting);
    result |= ImGui::Checkbox("DialogueColorStyleSetting", &DialogueColorStyleSetting);
    result |= ImGui::Checkbox("DialogueColorSetting", &DialogueColorSetting);
    result |= ImGui::Checkbox("DialoguePaletteSetting", &DialoguePaletteSetting);
    result |= ImGui::Checkbox("SpeakerSetting", &SpeakerSetting);
    result |= ImGui::Checkbox("SpeakerColorStyleSetting", &SpeakerColorStyleSetting);
    result |= ImGui::Checkbox("SpeakerColorSetting", &SpeakerColorSetting);
    result |= ImGui::Checkbox("SpeakerPaletteSetting", &SpeakerPaletteSetting);
    result |= ImGui::Checkbox("SubtitleFontSetting", &SubtitleFontSetting);
    result |= ImGui::InputFloat("SubtitleBackgroundOpacitySetting", &SubtitleBackgroundOpacitySetting);
    result |= ImGui::InputFloat("SubtitleShadowOpacitySetting", &SubtitleShadowOpacitySetting);
    result |= ImGui::InputInt("FOVSetting", &FOVSetting);
    result |= ImGui::InputInt("VehicleFOVSetting", &VehicleFOVSetting);
    result |= ImGui::Checkbox("CrosshairLocation", &CrosshairLocation);
    result |= ImGui::Checkbox("LookControlsInverted", &LookControlsInverted);
    result |= ImGui::Checkbox("MouseLookControlsInverted", &MouseLookControlsInverted);
    result |= ImGui::Checkbox("VibrationDisabled", &VibrationDisabled);
    result |= ImGui::Checkbox("ImpulseTriggersDisabled", &ImpulseTriggersDisabled);
    result |= ImGui::Checkbox("AircraftControlsInverted", &AircraftControlsInverted);
    result |= ImGui::Checkbox("MouseAircraftControlsInverted", &MouseAircraftControlsInverted);
    result |= ImGui::Checkbox("AutoCenterEnabled", &AutoCenterEnabled);
    result |= ImGui::Checkbox("CrouchLockEnabled", &CrouchLockEnabled);
    result |= ImGui::Checkbox("MKCrouchLockEnabled", &MKCrouchLockEnabled);
    result |= ImGui::Checkbox("ClenchProtectionEnabled", &ClenchProtectionEnabled);
    result |= ImGui::Checkbox("UseFemaleVoice", &UseFemaleVoice);
    result |= ImGui::InputInt("HoldToZoom", &HoldToZoom);
    result |= ImGui::InputInt("PlayerModelPrimaryColorIndex", &PlayerModelPrimaryColorIndex);
    result |= ImGui::InputInt("PlayerModelSecondaryColorIndex", &PlayerModelSecondaryColorIndex);
    result |= ImGui::InputInt("PlayerModelTertiaryColorIndex", &PlayerModelTertiaryColorIndex);
    result |= ImGui::Checkbox("UseEliteModel", &UseEliteModel);
    result |= ImGui::Checkbox("LockMaxAspectRatio", &LockMaxAspectRatio);
    result |= ImGui::Checkbox("UsersSkinsEnabled", &UsersSkinsEnabled);
    result |= ImGui::InputInt("PlayerModelPermutation", &PlayerModelPermutation);
    result |= ImGui::InputInt("HelmetIndex", &HelmetIndex);
    result |= ImGui::InputInt("LeftShoulderIndex", &LeftShoulderIndex);
    result |= ImGui::InputInt("RightShoulderIndex", &RightShoulderIndex);
    result |= ImGui::InputInt("ChestIndex", &ChestIndex);
    result |= ImGui::InputInt("WristIndex", &WristIndex);
    result |= ImGui::InputInt("UtilityIndex", &UtilityIndex);
    result |= ImGui::InputInt("ArmsIndex", &ArmsIndex);
    result |= ImGui::InputInt("LegsIndex", &LegsIndex);
    result |= ImGui::InputInt("BackpackIndex", &BackpackIndex);
    result |= ImGui::InputInt("SpartanBodyIndex", &SpartanBodyIndex);
    result |= ImGui::InputInt("SpartanArmorEffectIndex", &SpartanArmorEffectIndex);
    result |= ImGui::InputInt("KneesIndex", &KneesIndex);
    result |= ImGui::InputInt("VisorColorIndex", &VisorColorIndex);
    result |= ImGui::InputInt("EliteHelmetIndex", &EliteHelmetIndex);
    result |= ImGui::InputInt("EliteLeftShoulderIndex", &EliteLeftShoulderIndex);
    result |= ImGui::InputInt("EliteRightShoulderIndex", &EliteRightShoulderIndex);
    result |= ImGui::InputInt("EliteChestIndex", &EliteChestIndex);
    result |= ImGui::InputInt("EliteArmsIndex", &EliteArmsIndex);
    result |= ImGui::InputInt("EliteLegsIndex", &EliteLegsIndex);
    result |= ImGui::InputInt("EliteArmorIndex", &EliteArmorIndex);
    result |= ImGui::InputInt("EliteArmorEffectIndex", &EliteArmorEffectIndex);
    result |= ImGui::InputInt("VoiceIndex", &VoiceIndex);
    result |= ImGui::InputInt("PlayerModelPrimaryColor", &PlayerModelPrimaryColor);
    result |= ImGui::InputInt("PlayerModelSecondaryColor", &PlayerModelSecondaryColor);
    result |= ImGui::InputInt("PlayerModelTertiaryColor", &PlayerModelTertiaryColor);
    result |= ImGui::InputInt("SpartanPose", &SpartanPose);
    result |= ImGui::InputInt("ElitePose", &ElitePose);

    /*
     * Assault Rifle: Object: 13 Skin: 1281
     * */

    if (ImGui::CollapsingHeader("Skins")) {
        if (ImGui::Button("Reset")) {
            memset(Skins, -1, sizeof(Skins));
            result = true;
        }

        for (int i = 0; i < 32; ++i) {
            sprintf(buffer, "Skin %d", i);
            if (ImGui::TreeNode(buffer)) {
                result |= ImGui::InputInt("Object", &Skins[i].object);
                result |= ImGui::InputInt("Skin", &Skins[i].skin);
                ImGui::TreePop();
            }
        }
    }

    // ServiceTag is ignored as it's a wchar_t array

    result |= ImGui::Checkbox("OnlineMedalFlasher", &OnlineMedalFlasher);
    result |= ImGui::Checkbox("VerticalLookSensitivity", &VerticalLookSensitivity);
    result |= ImGui::Checkbox("HorizontalLookSensitivity", &HorizontalLookSensitivity);
    result |= ImGui::Checkbox("LookAcceleration", &LookAcceleration);
    result |= ImGui::InputFloat("LookAxialDeadZone", &LookAxialDeadZone);
    result |= ImGui::InputFloat("LookRadialDeadZone", &LookRadialDeadZone);
    result |= ImGui::InputFloat("ZoomLookSensitivityMultiplier", &ZoomLookSensitivityMultiplier);
    result |= ImGui::InputFloat("VehicleLookSensitivityMultiplier", &VehicleLookSensitivityMultiplier);
    result |= ImGui::Checkbox("ButtonPreset", &ButtonPreset);
    result |= ImGui::Checkbox("StickPreset", &StickPreset);
    result |= ImGui::Checkbox("LeftyToggle", &LeftyToggle);
    result |= ImGui::Checkbox("FlyingCameraTurnSensitivity", &FlyingCameraTurnSensitivity);
    result |= ImGui::Checkbox("FlyingCameraPanning", &FlyingCameraPanning);
    result |= ImGui::Checkbox("FlyingCameraSpeed", &FlyingCameraSpeed);
    result |= ImGui::Checkbox("FlyingCameraThrust", &FlyingCameraThrust);
    result |= ImGui::Checkbox("TheaterTurnSensitivity", &TheaterTurnSensitivity);
    result |= ImGui::Checkbox("TheaterPanning", &TheaterPanning);
    result |= ImGui::Checkbox("TheaterSpeed", &TheaterSpeed);
    result |= ImGui::Checkbox("TheaterThrust", &TheaterThrust);
    result |= ImGui::Checkbox("MKTheaterTurnSensitivity", &MKTheaterTurnSensitivity);
    result |= ImGui::Checkbox("MKTheaterPanning", &MKTheaterPanning);
    result |= ImGui::Checkbox("MKTheaterSpeed", &MKTheaterSpeed);
    result |= ImGui::Checkbox("MKTheaterThrust", &MKTheaterThrust);
    result |= ImGui::Checkbox("SwapTriggersAndBumpers", &SwapTriggersAndBumpers);
    result |= ImGui::Checkbox("UseModernAimControl", &UseModernAimControl);
    result |= ImGui::Checkbox("UseDoublePressJumpToJetpack", &UseDoublePressJumpToJetpack);
    result |= ImGui::Checkbox("DualWieldInverted", &DualWieldInverted);
    result |= ImGui::Checkbox("ControllerDualWieldInverted", &ControllerDualWieldInverted);
    result |= ImGui::Checkbox("ControllerHornetControlJoystick", &ControllerHornetControlJoystick);
    result |= ImGui::Checkbox("ControllerBansheeTrickButtonsSwapped", &ControllerBansheeTrickButtonsSwapped);
    result |= ImGui::Checkbox("ColorCorrection", &ColorCorrection);
    result |= ImGui::Checkbox("EnemyPlayerNameColor", &EnemyPlayerNameColor);
    result |= ImGui::InputInt("GameEngineTimer", &GameEngineTimer);

    // LoadoutSlots
    if (ImGui::CollapsingHeader("LoadoutSlots")) {
        for (int i = 0; i < 5; ++i) {
            sprintf(buffer, "LoadoutSlot %d", i);
            if (ImGui::TreeNode(buffer)) {
                result |= ImGui::InputInt("TacticalPackageIndex", &LoadoutSlots[i].TacticalPackageIndex);
                result |= ImGui::InputInt("SupportUpgradeIndex", &LoadoutSlots[i].SupportUpgradeIndex);
                result |= ImGui::InputInt("PrimaryWeaponIndex", &LoadoutSlots[i].PrimaryWeaponIndex);
                result |= ImGui::InputInt("SecondaryWeaponIndex", &LoadoutSlots[i].SecondaryWeaponIndex);
                result |= ImGui::InputInt("PrimaryWeaponVariantIndex", &LoadoutSlots[i].PrimaryWeaponVariantIndex);
                result |= ImGui::InputInt("SecondaryWeaponVariantIndex", &LoadoutSlots[i].SecondaryWeaponVariantIndex);
                result |= ImGui::InputInt("EquipmentIndex", &LoadoutSlots[i].EquipmentIndex);
                result |= ImGui::InputInt("GrenadeIndex", &LoadoutSlots[i].GrenadeIndex);
                // Name is ignored as it's a wchar_t array
                ImGui::TreePop();
            }
        }
    }

    // CustomKeyboardMouseMappingV2 is ignored as it's used only for player0

    result |= ImGui::InputFloat("MouseSensitivity", &MouseSensitivity);
    result |= ImGui::Checkbox("MouseSmoothing", &MouseSmoothing);
    result |= ImGui::Checkbox("MouseAcceleration", &MouseAcceleration);

    int tmp = PixelPerfectHudScale;
    if (ImGui::InputInt("PixelPerfectHudScale", &tmp) && tmp >= 0 && tmp <= 0xFFFF) {
        PixelPerfectHudScale = static_cast<__int16>(tmp);
        result = true;
    }

    result |= ImGui::InputFloat("MouseAccelerationMinRate", &MouseAccelerationMinRate);
    result |= ImGui::InputFloat("MouseAccelerationMaxAccel", &MouseAccelerationMaxAccel);
    result |= ImGui::InputFloat("MouseAccelerationScale", &MouseAccelerationScale);
    result |= ImGui::InputFloat("MouseAccelerationExp", &MouseAccelerationExp);
    result |= ImGui::InputInt("KeyboardMouseButtonPreset", &KeyboardMouseButtonPreset);

    result |= ImGui::InputFloat("MasterVolume", &MasterVolume);
    result |= ImGui::InputFloat("MusicVolume", &MusicVolume);
    result |= ImGui::InputFloat("SfxVolume", &SfxVolume);
    result |= ImGui::InputFloat("Brightness", &Brightness);

    // WeaponDisplayOffset
    if (ImGui::CollapsingHeader("WeaponDisplayOffset")) {
        for (int i = 0; i < 5; ++i) {
            sprintf(buffer, "WeaponDisplayOffset %d", i);
            if (ImGui::TreeNode(buffer)) {
                result |= ImGui::InputFloat3("Offset", &WeaponDisplayOffset[i].x);
                ImGui::TreePop();
            }
        }
    }

    result |= ImGui::InputInt("ColorBlindMode", &ColorBlindMode);
    result |= ImGui::InputInt("ColorBlindStrength", &ColorBlindStrength);
    result |= ImGui::InputInt("ColorBlindBrightness", &ColorBlindBrightness);
    result |= ImGui::InputInt("ColorBlindContrast", &ColorBlindContrast);
    result |= ImGui::InputInt("RemasteredHUDSetting", &RemasteredHUDSetting);
    result |= ImGui::InputFloat("HUDScale", &HUDScale);

    if (result) {
        auto p_engine = GameEngine();
        if (p_engine) p_engine->load_setting();
    }
}
