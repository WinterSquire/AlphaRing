#ifndef ALPHA_RING_MODULE_H
#define ALPHA_RING_MODULE_H

#include "../base.h"

class Module {
public:
    Module();
    Module(const char* fileName, const char* moduleName, const char* version);
    bool loadModule(const char* fileName, const char* moduleName, const char* version);
    uint64_t getAddress(const char* name);
    std::string toString();

private:
    std::string m_name;
    std::string m_version;
    std::unordered_map<std::string, uint64_t> m_address;

};

#endif //ALPHA_RING_MODULE_H
