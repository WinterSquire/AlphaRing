#include "math.h"

Degree3::operator Radian3() {return Radian3(x * M_PI / 180.0f, y * M_PI / 180.0f, z * M_PI / 180.0f);}

void Degree3::operator=(const Radian3 &other) {x = other.x, y = other.y, z = other.z;}

Radian3::operator Degree3()  { return Degree3(x * 180.0f / M_PI, y * 180.0f / M_PI, z * 180.0f / M_PI);}

void Radian3::operator=(const Degree3 &other) {x = other.x, y = other.y, z = other.z;}
