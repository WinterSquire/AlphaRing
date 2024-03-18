#ifndef ALPHA_RING_ARG_H
#define ALPHA_RING_ARG_H

#include <initializer_list>

class Arg
{
public:
    Arg();
    Arg(int argc, const char **argv);
    Arg(std::initializer_list<const char*> argv);

    int size() const;
    const char *operator[]( int index ) const;	// Gets at arguments

private:
    enum
    {
        COMMAND_MAX_ARGC = 64,
        COMMAND_MAX_LENGTH = 512,
    };

    int		m_nArgc;
    char	m_pArgvBuffer[ COMMAND_MAX_LENGTH ];
    const char*	m_ppArgv[ COMMAND_MAX_ARGC ];
};

#endif //ALPHA_RING_ARG_H
