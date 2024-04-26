#ifndef ALPHA_RING_INPUT_H
#define ALPHA_RING_INPUT_H


class ICInput {
public:
    virtual void enableInput(bool value) = 0;

};

extern ICInput* g_pICInput;
inline ICInput* Input() {return g_pICInput;}

#endif //ALPHA_RING_INPUT_H
