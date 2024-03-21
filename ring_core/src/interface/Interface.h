#ifndef ALPHA_RING_INTERFACE_H
#define ALPHA_RING_INTERFACE_H

#include "../system/System.h"

class Interface : public System {
public:
    eStatus initialize() override;
    eStatus shutdown() override;
};

static Interface sInterface;

#endif //ALPHA_RING_INTERFACE_H
