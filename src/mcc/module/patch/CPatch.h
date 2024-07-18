#pragma once

#include <string>
#include <vector>

class CPatchSet;

class CPatch {
public:
    // size - 1 to exclude '\0'
    template<size_t size>
    CPatch(const char* name, const char* desc, __int64 offset, const char (&src)[size], bool enabled = false)
            : m_name(name), m_desc(desc), m_offset(offset), m_data(src, src+size-1), m_backup(src, src+size-1), m_enabled(enabled) {}

    CPatch(const char* name, const char* desc, __int64 offset, const std::vector<__int8>& src, bool enabled = false)
            : m_name(name), m_desc(desc), m_offset(offset), m_data(src), m_backup(src), m_enabled(enabled) {}

    bool apply();
    bool setState(bool state);
    void setParent(CPatchSet* parent) {m_parent = parent;}

    inline const char* name() const {return m_name.c_str();}
    inline const char* desc() const {return m_desc.c_str();}
    inline bool have_desc() const {return !m_desc.empty();}
    inline bool enabled() {return m_enabled;}

    static bool apply(void *dst, const void *src, size_t size, void *backup = nullptr);

private:
    CPatchSet* m_parent;
    __int64 m_offset;
    std::string m_name;
    std::string m_desc;
    std::vector<__int8> m_data;
    std::vector<__int8> m_backup;
    bool m_enabled;

};