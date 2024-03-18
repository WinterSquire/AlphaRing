#include "Console.h"

#include "Function.h"

bool Console::Execute(const char *name, const Arg &arg) {
    auto func = Function::getFunction(name);
    if (func == nullptr) return false;
    return (*func)(arg);
}
