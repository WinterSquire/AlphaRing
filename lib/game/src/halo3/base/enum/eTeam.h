#ifndef ALPHA_RING_ETEAM_H
#define ALPHA_RING_ETEAM_H

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

static const char* eTeamAIName[] =
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

static const char* eTeamColorName[] =
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

#endif //ALPHA_RING_ETEAM_H
