#ifndef ALPHA_RING_BASIC_WIDGET_H
#define ALPHA_RING_BASIC_WIDGET_H

#include "imgui/imgui.h"
#include <functional>

class BasicWidget {
public:
    BasicWidget(const char* name) : m_name(name) {}
    static void setState(const std::function<void()>& func);

    inline const char* name() {return m_name;}
    virtual void render() = 0;
    virtual void update() = 0;

private:
    const char* m_name;

};


#endif //ALPHA_RING_BASIC_WIDGET_H
