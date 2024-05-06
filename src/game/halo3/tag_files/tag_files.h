#pragma once

#include "../base/base.h"

class ICTagFiles {
public:
    virtual const char* getTagName(__int16 index) = 0;
};

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

struct ITagGroup
{
    CharConstant Magic;
    CharConstant ParentMagic;
    CharConstant GrandparentMagic;
    StringID Description;
};

struct TagElement
{
    __int16 tag_group_index;
    __int16 datum_index_salt;
    __int32 memory_address;
};

