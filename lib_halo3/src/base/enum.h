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

enum eSkull : unsigned int
{
    //Primary
    SKULL_IRON,
    SKULL_BLACKEYE,
    SKULL_TOUGHLUCK,
    SKULL_CATCH,
    SKULL_FOG,
    SKULL_FAMINE,
    SKULL_THUNDERSTORM,
    SKULL_TILT,
    SKULL_MYTHIC,
    //Secondary
    SKULL_ASSASSIN,
    SKULL_BLIND,
    SKULL_COWBELL,
    SKULL_GRUNTBIRTHDAYPARTY,
    SKULL_IWHBYD,
    //etc
    SKULL_ACROPHOBIA,
    SKULL_BANDANA
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

enum eObjectType : unsigned int
{
    OBJECTTYPE_BIPED,
    OBJECTTYPE_VEHICLE,
    OBJECTTYPE_WEAPON,
    OBJECTTYPE_EQUIPMENT,
    OBJECTTYPE_TERMINAL,
    OBJECTTYPE_PROJECTILE,
    OBJECTTYPE_SCENERY,
    OBJECTTYPE_MACHINE,
    OBJECTTYPE_CONTROL,
    OBJECTTYPE_SOUNDSCENERY,
    OBJECTTYPE_CRATE,
    OBJECTTYPE_CREATURE,
    OBJECTTYPE_GIANT,
    OBJECTTYPE_EFFECTSCENERY
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

enum eEntryOffset : size_t //1.3073.0
{
    ENTRYOFFSET_ACTOR = 0x8,
    ENTRYOFFSET_PLAYER = 0x10,
    ENTRYOFFSET_PATCHEDRESOURCEDATA = 0x20,
    ENTRYOFFSET_OBJECT = 0x38,
    ENTRYOFFSET_ACTORLOOP = 0x30,
    ENTRYOFFSET_PLAYERACTION = 0x40,
    ENTRYOFFSET_MAP = 0x48,
    ENTRYOFFSET_SPEED = 0xC8, // 0x8 1.0/tick 0xC current tick 0x10 speed(float 1.0)
    ENTRYOFFSET_INFO = 0x110, // input,player INDEX ... local player
    ENTRYOFFSET_PHYSICS = 0x130, // Gravity ...
    ENTRYOFFSET_CAMERA = 0x188,
    ENTRYOFFSET_RENDER = 0x220, // Chud Light
    ENTRYOFFSET_CINEMATIC = 0x450
    //0x238 sim. gamestate entities
    //0x388 loopobjects
};

enum eGiveWeapon : unsigned int
{
    GIVEWEAPON_SPAWN,
    GIVEWEAPON_ADD,
    GIVEWEAPON_CLEAR,
    GIVEWEAPON_SHOW,
    GIVEWEAPON_DROP
};

#endif //ALPHA_RING_ENUM_H
