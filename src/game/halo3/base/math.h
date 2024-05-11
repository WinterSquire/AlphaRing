#ifndef ALPHA_RING_MATH_H
#define ALPHA_RING_MATH_H

#define M_PI 3.14159265358979323846

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
    inline void operator = (const Vector3& v){x = v.x; y = v.y; z = v.z;}
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

class Degree2 : public Vector2 {
public :
    inline void SetDegree(float yaw, float pitch) { x = yaw * M_PI / 180.0f;y = pitch * M_PI / 180.0f;}
};

class Radian3;

class Degree3: public Vector3 {
public:
    Degree3(float x = 0, float y = 0, float z = 0) : Vector3(x,y,z) {}

    operator Radian3();
    void operator =(const Radian3& other);
};

class Radian3 : public Vector3 {
public:
    Radian3(float x = 0, float y = 0, float z = 0) : Vector3(x,y,z) {}

    operator Degree3();
    void operator =(const Degree3& other);
};


#endif //ALPHA_RING_MATH_H
