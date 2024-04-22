#ifndef ALPHA_RING_ENUM_H
#define ALPHA_RING_ENUM_H


enum eAction : unsigned int
{
    ACTION_ACTION = 0,
    ACTION_JUMP = 1,
    ACTION_ACCEPT = 2,
    ACTION_CANCEL = 3,
    ACTION_primary_trigger = 4,
    ACTION_grenade_trigger = 5,
    ACTION_MELEE = 6,
    ACTION_rotate_weapons = 7,
    ACTION_rotate_grenades = 9,
    ACTION_ZOOM = 0xA,
    ACTION_look_relative_up = 0xB,
    ACTION_vision_trigger = 0x15
};

enum eCameraMode : unsigned int
{
    CAMERAMODE_FOLLOWING,
    CAMERAMODE_ORBITING,
    CAMERAMODE_FLYING,
    CAMERAMODE_FP,
    CAMERAMODE_DEAD,
    CAMERAMODE_STATIC,
    CAMERAMODE_SCRIPTED,
    CAMERAMODE_AUTHORED,
    CAMERAMODE_SANDBOX
};

enum eFont : unsigned int
{
    FONT_Terminal,// Fixedsys, 9pt
    FONT_BodyText,// Conduit, 16pt
    FONT_Title,// Conduit, 32pt
    FONT_SuperLargeFont,// Conduit, 32pt
    FONT_LargeBodyText,// Conduit, 23pt
    FONT_SplitScreenHUDMessage,// Fixedsys, 9pt
    FONT_FullScreenHUDMessage,// Conduit, 18pt
    FONT_EnglishBodyText,// Larabie, 10pt
    FONT_HUDNumberText,// Conduit, 18pt
    FONT_SubtitleFont,// Conduit, 16pt
    FONT_MainMenuFont// Pragmata, 14pt
};

enum eVerticalJustification : unsigned int
{
    VerticalJustification_Default,
    VerticalJustification_Top,
    VerticalJustification_Center,
    VerticalJustification_Bottom
};

enum eHorizontalJustification : unsigned int
{
    HorizontalJustification_Left,
    HorizontalJustification_Right,
    HorizontalJustification_Center
};

enum eModelChoice : unsigned int
{
    MODELCHOICE_SP_MASTERCHIEF,
    MODELCHOICE_SP_DERVISH,
    MODELCHOICE_MP_MASTERCHIEF,
    MODELCHOICE_MP_ELITE,
    MODELCHOICE_COOP_ELITE,
    MODELCHOICE_MONITER
};

const static char* eObjectTypeName[] =
        {
                "biped",
                "vehicle",
                "weapon",
                "equipment",
                "terminal",
                "projectile",
                "scenery",
                "machine",
                "control",
                "soundscape",
                "crate",
                "creature",
                "giant",
                "effect scenery"
        };


enum eGameEvent : unsigned int
{
    GAMEEVENT_GAME_SAVE = 1,
    GAMEEVENT_GAME_SAVE_NO_TIMEOUT,
    GAMEEVENT_GAME_SAVE_IMMEDIATE,
    GAMEEVENT_GAME_SAVE_CINEMATIC_SKIP
};

enum eTeamColor : unsigned int
{
    TEAMCOLOR_RED,
    TEAMCOLOR_BLUE,
    TEAMCOLOR_GREEN,
    TEAMCOLOR_ORANGE,
    TEAMCOLOR_PURPLE,
    TEAMCOLOR_GOLD,
    TEAMCOLOR_BROWN,
    TEAMCOLOR_PINK,
    TEAMCOLOR_Grey
};

enum eTeamAI : unsigned int
{
    TEAMAI_DEFAULT,
    TEAMAI_PLAYER,
    TEAMAI_HUMAN,
    TEAMAI_COVENANT,
    TEAMAI_FLOOD,
    TEAMAI_SENTINEL,
    TEAMAI_HERETIC,
    TEAMAI_PROPHET,
    TEAMAI_GUILTY
};

const static char* eTeamAIName[] =
        {
                "Default",
                "Player",
                "Human",
                "Covenant",
                "Flood",
                "Sentinel",
                "Heretic",
                "Prophet",
                "Guilty"
        };

const static char* eTeamColorName[] =
        {
                "Red",
                "Blue",
                "Green",
                "Orange",
                "Purple",
                "Gold",
                "Brown",
                "Pink",
                "Grey"
        };

enum eGiveWeapon : unsigned int
{
    GIVEWEAPON_SPAWN,
    GIVEWEAPON_ADD,
    GIVEWEAPON_CLEAR,
    GIVEWEAPON_SHOW,
    GIVEWEAPON_DROP
};

enum eTlsArray : unsigned int{
    TLS_ACTOR = 0,
    TLS_OBJECT = 7,
};

#endif //ALPHA_RING_ENUM_H
