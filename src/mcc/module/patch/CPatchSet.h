#pragma once

#include "CPatch.h"

class CPatchSet {
public:
    CPatchSet() = default;
    ~CPatchSet() = default;

    CPatchSet(std::initializer_list<CPatch> embed_patches) : m_embed_patches(), m_patches() {
        for (const auto& patch : embed_patches) {
            auto new_patch = new CPatch(patch);
            new_patch->setParent(this);
            m_embed_patches.push_back(new_patch);
        }
    }

    void add(const char* name, const char* desc, __int64 offset, const std::vector<__int8>& src, bool enabled = false);
    void clear();

    void apply();
    void update(__int64 hModule);

    inline __int64 moduleAddress() {return hModule;}
    inline std::vector<CPatch*>& embed_patches() {return m_embed_patches;}
    inline std::vector<CPatch*>& patches() {return m_patches;}

private:
    __int64 hModule;
    std::vector<CPatch*> m_embed_patches;
    std::vector<CPatch*> m_patches;
};