#ifndef ALPHA_RING_ACTORS_H
#define ALPHA_RING_ACTORS_H


struct actor_t {
    bool enable_ai;
};

class ICActor {
public:
    virtual actor_t* getActor() = 0;
};


#endif //ALPHA_RING_ACTORS_H
