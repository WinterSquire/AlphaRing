#ifndef ALPHA_RING_MODULE_H
#define ALPHA_RING_MODULE_H

#include "../os/FileVersion.h"

#include <unordered_map>

class Module{
public:
    Module();
    Module(const char* fileName, const char* moduleName, const char* version);
    bool loadModule(const char* fileName, const char* moduleName, const char* version);
    uint64_t getAddress(const char* name);
    string toString();

private:
    string m_name;
    string m_version;
    std::unordered_map<string, uint64_t> m_address;
};

#endif //ALPHA_RING_MODULE_H
