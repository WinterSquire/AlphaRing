#include "Function.h"

std::unordered_map<std::string, Function*> Function::s_function_map;

Function::Function(func_t func, const char *name, const char *info) : m_func(func), m_name(name), m_info(info) {
//    s_function_map.emplace(name, this);
}

bool Function::operator()(const Arg &arg) {
    if (m_func == nullptr) return false;
    m_func(arg);
    return true;
}

Function *Function::getFunction(const char *name) {
    auto result = s_function_map.find(name);
    return result == s_function_map.end() ? nullptr : result->second;
}
