#include "Module.h"

#include <iostream>

#include "tinyxml2.h"

using namespace tinyxml2;

Module::Module() {

}

Module::Module(const char *fileName, const char *moduleName, const char *version) {
    loadModule(fileName, moduleName, version);
}

bool Module::loadModule(const char *fileName, const char *moduleName, const char *version) {
    XMLDocument doc;
    doc.LoadFile(fileName);

    auto root_element = doc.RootElement();

    if (root_element == nullptr) return false;

    auto module_element = root_element->FirstChildElement();
    while (module_element) {
        if (module_element->Attribute("name", moduleName)
        && module_element->Attribute("version", version))
            break;
        module_element = module_element->NextSiblingElement();
    }

    if (module_element == nullptr) return false;

    m_name = moduleName;
    m_version = version;
    m_address.clear();

    auto address_element = module_element->FirstChildElement();
    while (address_element) {
        auto name = address_element->Attribute("name");
        auto offset = address_element->Attribute("offset");

        m_address.emplace(name, std::stoull(offset, nullptr, 16));

        address_element = address_element->NextSiblingElement();
    }

    return true;
}

uint64_t Module::getAddress(const char *name) {
    auto result = m_address.find(name);
    if (result == m_address.end()) return 0;
    return result->second;
}

string Module::toString() {
    string result {
        "Name: " + m_name + '\n' +\
        "Version: " + m_version + '\n'
    };

    for (auto key: m_address) {
        result.append(string(key.first + ' ' + std::to_string(key.second) + '\n'));
    }

    return result;
}
