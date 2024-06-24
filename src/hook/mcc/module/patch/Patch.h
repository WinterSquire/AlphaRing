#pragma once

#include <string>
#include <vector>
#include <initializer_list>

struct Patch {
public:
    template<size_t size>
    Patch(const char* name, const char* desc, __int64 offset, const char (&src)[size], bool enabled = false)
    : m_dst(nullptr), m_name(name), m_desc(desc), m_offset(offset), m_data(src, src+size), m_backup(src, src+size), m_enabled(enabled) {}

    Patch(const char* name, const char* desc, __int64 offset, const std::vector<__int8>& src, bool enabled = false)
    : m_dst(nullptr), m_name(name), m_desc(desc), m_offset(offset), m_data(src), m_backup(src), m_enabled(enabled) {}

    ~Patch() {
        setState(false);
    };

    static bool apply(void *dst, const void *src, size_t size, void *backup = nullptr);

    inline bool setState(bool state) {
        if (m_enabled == state) return false;
        m_enabled = state;
        return apply();
    }

    inline bool apply() {
        if (m_enabled)
            return apply(m_dst, m_data.data(), m_data.size(), m_backup.data());
        else
            return apply(m_dst, m_backup.data(), m_backup.size());
    }

    inline void update(__int64 hModule) {m_dst = (void*)(hModule + m_offset);}
    inline const char* name() const {return m_name.c_str();}
    inline const char* desc() const {return m_desc.c_str();}
    inline bool have_desc() const {return !m_desc.empty();}
    inline bool enabled() {return m_enabled;}

private:
    void* m_dst;
    __int64 m_offset;
    std::string m_name;
    std::string m_desc;
    std::vector<__int8> m_data;
    std::vector<__int8> m_backup;
    bool m_enabled;

};

class PatchSet {
public:
    PatchSet() = default;
    ~PatchSet() = default;

    PatchSet(std::initializer_list<Patch> embed_patches) : m_embed_patches(), m_patches() {
        for (auto patch : embed_patches)
            m_embed_patches.push_back(new Patch(patch));
    }

    inline void clear() {
        for (auto patch : m_patches)
            delete patch;
        m_patches.clear();
    }

    inline void apply() {
        for (auto &patch : m_embed_patches)
            patch->apply();
        for (auto &patch : m_patches)
            patch->apply();
    }

    inline void update(__int64 hModule) {
        for (auto &patch : m_embed_patches)
            patch->update(hModule);
        for (auto &patch : m_patches)
            patch->update(hModule);
    }

    inline void add(Patch* patch) {
        m_patches.push_back(patch);
    }

    inline std::vector<Patch*>& embed_patches() {return m_embed_patches;}
    inline std::vector<Patch*>& patches() {return m_patches;}

private:
    std::vector<Patch*> m_embed_patches;
    std::vector<Patch*> m_patches;

};