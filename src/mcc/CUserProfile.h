#pragma once

struct CUserProfile {
    bool SubtitleSetting; // 0x0
    bool SubtitleSizeSetting; // 0x1
    bool SubtitleBackgroundSetting; // 0x2
    bool SubtitleShadowColorSetting; // 0x3
    bool DialogueColorStyleSetting; // 0x4
    bool DialogueColorSetting; // 0x5
    bool DialoguePaletteSetting; // 0x6
    bool SpeakerSetting; // 0x7
    bool SpeakerColorStyleSetting; // 0x8
    bool SpeakerColorSetting; // 0x9
    bool SpeakerPaletteSetting; // 0xA
    bool SubtitleFontSetting; // 0xB
    float SubtitleBackgroundOpacitySetting; // 0xC
    float SubtitleShadowOpacitySetting; // 0x10
    int FOVSetting; // 0x14
    int VehicleFOVSetting; // 0x18
    bool CrosshairLocation; // 0x1C
    bool LookControlsInverted; // 0x1D
    bool MouseLookControlsInverted; // 0x1E
    bool VibrationDisabled; // 0x1F
    bool ImpulseTriggersDisabled; // 0x20
    bool AircraftControlsInverted; // 0x21
    bool MouseAircraftControlsInverted; // 0x22
    bool AutoCenterEnabled; // 0x23
    bool CrouchLockEnabled; // 0x24
    bool MKCrouchLockEnabled; // 0x25
    bool ClenchProtectionEnabled; // 0x26
    bool UseFemaleVoice; // 0x27
    int HoldToZoom; // 0x28
    int PlayerModelPrimaryColorIndex; // 0x2C
    int PlayerModelSecondaryColorIndex; // 0x30
    int PlayerModelTertiaryColorIndex; // 0x34
    bool UseEliteModel; // 0x38
    bool LockMaxAspectRatio; // 0x39
    bool un; // 0x3A
    bool UsersSkinsEnabled; // 0x3B
    int PlayerModelPermutation; // 0x3C
    int HelmetIndex; // 0x40
    int LeftShoulderIndex; // 0x44
    int RightShoulderIndex; // 0x48
    int ChestIndex; // 0x4C
    int WristIndex; // 0x50
    int UtilityIndex; // 0x54
    int ArmsIndex; // 0x58
    int LegsIndex; // 0x5C
    int BackpackIndex; // 0x60
    int SpartanBodyIndex; // 0x64
    int SpartanArmorEffectIndex; // 0x68
    int KneesIndex; // 0x6C
    int VisorColorIndex; // 0x70
    int EliteHelmetIndex; // 0x74
    int EliteLeftShoulderIndex; // 0x78
    int EliteRightShoulderIndex; // 0x7C
    int EliteChestIndex; // 0x80
    int EliteArmsIndex; // 0x84
    int EliteLegsIndex; // 0x88
    int EliteArmorIndex; // 0x8C
    int EliteArmorEffectIndex; // 0x90
    int VoiceIndex; // 0x94
    int PlayerModelPrimaryColor; // 0x98
    int PlayerModelSecondaryColor; // 0x9C
    int PlayerModelTertiaryColor; // 0xA0
    int SpartanPose; // 0xA4
    int ElitePose; // 0xA8

    char buffer[0x100]; // 0xAC

    wchar_t ServiceTag[4]; // 0x1AC
    bool OnlineMedalFlasher; // 0x1B4
    bool VerticalLookSensitivity; // 0x1B5
    bool HorizontalLookSensitivity; // 0x1B6
    bool LookAcceleration; // 0x1B7
    float LookAxialDeadZone; // 0x1B8
    float LookRadialDeadZone; // 0x1BC
    float ZoomLookSensitivityMultiplier; // 0x1C0
    float VehicleLookSensitivityMultiplier; // 0x1C4
    bool ButtonPreset; // 0x1C8
    bool StickPreset; // 0x1C9
    bool LeftyToggle; // 0x1CA
    bool FlyingCameraTurnSensitivity; // 0x1CB
    bool FlyingCameraPanning; // 0x1CC
    bool FlyingCameraSpeed; // 0x1CD
    bool FlyingCameraThrust; // 0x1CE
    bool TheaterTurnSensitivity; // 0x1CF
    bool TheaterPanning; // 0x1D0
    bool TheaterSpeed; // 0x1D1
    bool TheaterThrust; // 0x1D2
    bool MKTheaterTurnSensitivity; // 0x1D3
    bool MKTheaterPanning; // 0x1D4
    bool MKTheaterSpeed; // 0x1D5
    bool MKTheaterThrust; // 0x1D6
    bool SwapTriggersAndBumpers; // 0x1D7
    bool UseModernAimControl; // 0x1D8
    bool UseDoublePressJumpToJetpack; // 0x1D9
    bool DualWieldInverted; // 0x1DA
    bool ControllerDualWieldInverted; // 0x1DB
    bool ControllerHornetControlJoystick; // 0x1DC
    bool ControllerBansheeTrickButtonsSwapped; // 0x1DD
    bool ColorCorrection; // 0x1DE
    bool EnemyPlayerNameColor; // 0x1DF
    bool GameEngineTimer; // 0x1E0

    char buffer2[0x12F]; // 0x1E1

    bool GameSpecific; // 0x310
    char un2[0x100 - 1]; // 0x311
    float MouseSensitivity; // 0x410
    bool MouseSmoothing; // 0x414
    bool MouseAcceleration; // 0x415
    __int16 PixelPerfectHudScale; // 0x416
    int MouseAccelerationMinRate; // 0x418
    int MouseAccelerationMaxAccel; // 0x41C
    int MouseAccelerationScale; // 0x420
    int MouseAccelerationExp; // 0x424
    int KeyboardMouseButtonPreset; //? 0x428

    char buffer3[0x630]; // 0x42C

    int MasterVolume; // 0xA5C
    int MusicVolume; // 0xA60
    int SfxVolume; // 0xA64

    char buffer4[0xC]; // 0xA68

    float Brightness; // 0xA74

    char buffer5[0x3C]; // 0xA78

    int ColorBlindMode; // 0xAB4
    int ColorBlindStrength; // 0xAB8
    int ColorBlindBrightness; // 0xABC
    int ColorBlindContrast; // 0xAC0
    int RemasteredHUDSetting; // 0xAC4
    int HUDScale; // 0xAC8
};

static_assert(sizeof(CUserProfile) == 0xACC);