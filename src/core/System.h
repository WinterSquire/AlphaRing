#ifndef ALPHA_RING_SYSTEM_H
#define ALPHA_RING_SYSTEM_H


class System {
public:
    enum eStatus {
        SYS_OK,
        SYS_ERROR,
    };

    virtual eStatus initialize() = 0;
    virtual eStatus shutdown() = 0;
};


#endif //ALPHA_RING_SYSTEM_H
