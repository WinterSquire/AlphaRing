#ifndef TINYXML2_TEST_FUNCTION_H
#define TINYXML2_TEST_FUNCTION_H

#include "Arg.h"

#include <unordered_map>
#include <string>

typedef void ( *func_t )( const Arg &arg );

class Function {
public:
    Function(func_t func, const char* name, const char* info);

    bool operator() (const Arg& arg);
    static Function* getFunction(const char* name);

private:
    static std::unordered_map<std::string, Function*> s_function_map;

    func_t m_func;
    const char* m_name;
    const char* m_info;
};


#endif //TINYXML2_TEST_FUNCTION_H
