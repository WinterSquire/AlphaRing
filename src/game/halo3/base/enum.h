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

enum eGameEvent : unsigned int
{
    GAMEEVENT_GAME_SAVE = 1,
    GAMEEVENT_GAME_SAVE_NO_TIMEOUT,
    GAMEEVENT_GAME_SAVE_IMMEDIATE,
    GAMEEVENT_GAME_SAVE_CINEMATIC_SKIP
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
