#ifndef ALPHA_RING_ACTORS_H
#define ALPHA_RING_ACTORS_H


struct actor_t {
    bool enable_ai;
};

class ICActor {
public:
    virtual actor_t* getActor() = 0;
};

extern ICActor* g_pICActor;
inline ICActor* Actor() {return g_pICActor;}


#endif //ALPHA_RING_ACTORS_H
