#include "CPatchSet.h"

void CPatchSet::clear() {
    for (auto patch : m_patches) {
        patch->setState(false);
        delete patch;
    }
    m_patches.clear();
}

void CPatchSet::apply() {
    for (auto patch : m_embed_patches)
        if (patch->enabled())
            patch->apply();

    for (auto patch : m_patches)
        if (patch->enabled())
            patch->apply();
}

void CPatchSet::update(__int64 hModule) {
    this->hModule = hModule;
}

void CPatchSet::add(const char *name, const char *desc, __int64 offset, const std::vector<__int8> &src, bool enabled) {
    auto patch = new CPatch(name, desc, offset, src, enabled);
    patch->setParent(this);
    m_patches.push_back(patch);
}
