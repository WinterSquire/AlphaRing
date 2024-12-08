#ifndef ALPHA_RING_TYPE_H
#define ALPHA_RING_TYPE_H

#include "./math.h"

#define NONE -1
#define MAX_LOCAL_PLAYERS 4
#define MAX_ONLINE_PLAYERS 16

typedef unsigned short Index;
typedef unsigned int INDEX;
typedef unsigned int t_Player;
typedef unsigned int Datum;
typedef unsigned int StringID;

template<typename T>
struct entity_manager_t {
    char m_name[0x20];             // 0x0
    __int32 m_max;                 // 0x20
    __int32 m_sizeof;              // 0x24
    __int32 m_un1;                 // 0x28
    __int32 m_signature;           // 0x2C
    __int32 m_un2[2];              // 0x30
    unsigned __int16 m_next_index; // 0x3A
    __int16 m_un3;                 // 0x3A
    __int32 m_capacity;            // 0x3C
    __int32 m_size;                // 0x40
    unsigned __int16 m_next_id;    // 0x44
    __int16 m_un4;                 // 0x46
    __int64 m_data;                // 0x48

    inline bool isValid(__int16 index) const { return index >= 0 && index < m_size && index < m_max; }
    inline T* get(__int16 index) const { return (T*)(m_data + (__int64)m_sizeof * (__int16)index); }
    inline __int32 INDEX(__int16 index) const { return ((__int32)(*(__int16*)(m_data + index * m_sizeof)) << 16) | index;}
};

struct TagRef
{
    __int32 name;
    __int64 un;
    Datum datum;
};
struct TagBlock
{
    __int32 count;
    __int32 memory_address;
    __int32 un;
};

struct NavPoint
{
    INDEX object = -1;
    unsigned int widget[4]{0x00000000,0xFFFFFFFF,0x00000000,0x00000000};
    float opacity = 1.0f;
    __int16 v1[6]{0,0,0,0,0,0};
    Vector3 position;
};

// https://github.com/XboxChaos/Assembly/blob/a9650c010fc6bb8e7d0ea01afe3a024619e4db95/src/Blamite/Util/CharConstant.cs#L9
class CharConstant {
public:
    int magic;
public:
    static const char* ConvertToString(int constant, char s[5]) {
        int index = 4;
        while (constant > 0) {
            index--;
            s[index] = (char) (constant & 0xFF);
            constant >>= 8;
        }
        s[4] = '\0';
        if (index == 4) return "";
        else return s;
    }

    const char* ToString(char s[5]) {return CharConstant::ConvertToString(magic, s);}
};

namespace COLOR3
{
    static float PureRed = 0xFF0000;
    static float PureGreen = 0x00FF00;
    static float PureBlue = 0x0000FF;
    static float Grey = 0xCCCCCC;

    inline __int32 HSVtoRGB(int hue, int saturation, int value) {
        double r, g, b;
        double h = hue / 60.0;
        double s = saturation / 255.0;
        double v = value / 255.0;
        int i = (int)h;
        double f = h - i;
        double p = v * (1 - s);
        double q = v * (1 - s * f);
        double t = v * (1 - s * (1 - f));
        switch (i) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            case 5:
            default:
                r = v;
                g = p;
                b = q;
                break;
        }
        int red = (int)(r * 255.0);
        int green = (int)(g * 255.0);
        int blue = (int)(b * 255.0);
        return ((red << 16) | (green << 8) | blue);
    }
}

#endif //ALPHA_RING_TYPE_H
