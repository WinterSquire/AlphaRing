#ifndef ALPHA_RING_NATIVE_FUNC_H
#define ALPHA_RING_NATIVE_FUNC_H


class ICNativeFunc {
public:
    // Main Thread
    virtual bool pushMsg(int player_index, const char* msg, int type = 2) = 0;

    // Render Thread
    virtual __int64 draw(__int64 drawType, unsigned int count, void *data, unsigned int size) = 0;

    virtual __int64 draw_line(void *data, unsigned int line_count, unsigned int vertex_size);
};

extern ICNativeFunc* g_pICNativeFunc;
inline ICNativeFunc* NativeFunc() { return g_pICNativeFunc; }


#endif //ALPHA_RING_NATIVE_FUNC_H
