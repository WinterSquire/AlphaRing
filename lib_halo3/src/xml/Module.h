#ifndef TINYXML2_TEST_MODULE_H
#define TINYXML2_TEST_MODULE_H

#include "../base.h"
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

#endif //TINYXML2_TEST_MODULE_H
