#include "basic_widget.h"

namespace Halo3::Entry::World {extern void AddTask(const std::function<void()>& func);}

void BasicWidget::setState(const std::function<void()>& func) {
    Halo3::Entry::World::AddTask(func);
}
