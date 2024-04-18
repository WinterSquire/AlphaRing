#ifndef ALPHA_RING_CONTEXT_H
#define ALPHA_RING_CONTEXT_H

struct Page {
    typedef void (*callback_t) ();

    int weight;
    const char* name;
    callback_t callback;

    Page(int weight, const char *name, callback_t callback);
};

#endif //ALPHA_RING_CONTEXT_H
