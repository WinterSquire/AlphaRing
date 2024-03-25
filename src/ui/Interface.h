#ifndef ALPHA_RING_INTERFACE_H
#define ALPHA_RING_INTERFACE_H

#include "../core/System.h"

class Interface : public System {
public:
    eStatus initialize() override;
    eStatus shutdown() override;
};

static Interface sInterface;

#endif //ALPHA_RING_INTERFACE_H
