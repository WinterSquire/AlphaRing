#include "Arg.h"

#include "Common.h"

Arg::Arg() {
    m_nArgc = 0;
}

Arg::Arg(int argc, const char **argv) : Arg() {
    int index = 0;
    size_t size = 0;

    while (size < COMMAND_MAX_LENGTH && index < argc && index < COMMAND_MAX_ARGC) {
        m_ppArgv[index] = m_pArgvBuffer + size;
        size += String::Copy(m_pArgvBuffer + size, COMMAND_MAX_LENGTH - size, argv[index]);
        ++size; // '\0'
        ++index;
    }

    m_nArgc = index;
}

Arg::Arg(std::initializer_list<const char *> argv) {
    int index = 0;
    size_t size = 0;

    while (size < COMMAND_MAX_LENGTH && index < argv.size() && index < COMMAND_MAX_ARGC) {
        m_ppArgv[index] = m_pArgvBuffer + size;
        size += String::Copy(m_pArgvBuffer + size, COMMAND_MAX_LENGTH - size, *(argv.begin() + index));
        ++size; // '\0'
        ++index;
    }

    m_nArgc = index;
}

int Arg::size() const {
    return m_nArgc;
}

const char *Arg::operator[](int index) const {
    if (index < 0 || index >= m_nArgc) return nullptr;
    return m_ppArgv[index];
}
