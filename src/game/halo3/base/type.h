#ifndef ALPHA_RING_TYPE_H
#define ALPHA_RING_TYPE_H


#define NONE -1
#define M_PI 3.14159265358979323846

typedef unsigned short Index;
typedef unsigned int INDEX;
typedef unsigned int t_Player;
typedef unsigned int Datum;
typedef unsigned int StringID;

class Vector2
{
public :
    float x = 0,y = 0;
    Vector2(float x = 0, float y = 0) : x(x), y(y){}
    inline void operator = (float v){x = v; y = v;}
    inline void operator = (Vector2& v){x = v.x; y = v.y;}
    inline bool operator == (Vector2& v){return x == v.x && y == v.y;}
    inline Vector2 operator + (const float f) const {return Vector2(x+f,y+f);}
};

class Vector3
{
public :
    float x = 0,y = 0,z = 0;
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z){}
    inline void operator = (float v){x = v; y = v; z = v;}
    inline void operator = (Vector3& v){x = v.x; y = v.y; z = v.z;}
    inline bool operator == (Vector3& v){return x == v.x && y == v.y && z == v.z;}
    inline Vector3 operator + (const float f) const {return Vector3(x+f,y+f,z+f);}
};

class Vector4
{
public :
    float x = 0,y = 0,z = 0,w = 0;
    Vector4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w){}
    inline void operator = (float v){x = v; y = v; z = v; w = v;}
    inline void operator = (Vector4& v){x = v.x; y = v.y; z = v.z; w = v.w;}
    inline bool operator == (Vector4& v){return x == v.x && y == v.y && z == v.z && w == v.w;}
    inline Vector4 operator + (const float f) const {return Vector4(x+f,y+f,z+f,w+f);}
};

class Degree2 : public Vector2
{
public :
    inline void SetDegree(float yaw, float pitch) { x = yaw * M_PI / 180.0f;y = pitch * M_PI / 180.0f;}
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

template<typename T>
struct entity_manager_t {
    char m_name[0x20];  // 0x0
    __int32 m_un0;      // 0x20
    __int32 m_sizeof;   // 0x24
    __int32 m_un1[5];   // 0x28
    __int32 m_capacity; // 0x3C
    __int32 m_size;     // 0x40
    __int32 m_un2;      // 0x44
    __int64 m_data;     // 0x48

    inline T* get(__int16 index) const { return (T*)(m_data + (__int64)m_sizeof * (__int16)index); }
    inline __int32 INDEX(__int16 index) const { return ((__int32)((__int16)(m_data + index * m_sizeof)) << 16) | index;}
};

#endif //ALPHA_RING_TYPE_H
