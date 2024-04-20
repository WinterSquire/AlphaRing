#ifndef ALPHA_RING_LOCKEDRESOURCE_H
#define ALPHA_RING_LOCKEDRESOURCE_H

#include <mutex>

template<typename T>
class LockedResource {
public:
    LockedResource(std::mutex& mutex, T& resource) : m_lock(mutex), m_resource(resource) {}

    inline T& get() {return m_resource;}
private:
    T& m_resource;
    std::lock_guard<std::mutex> m_lock;
};


#endif //ALPHA_RING_LOCKEDRESOURCE_H
