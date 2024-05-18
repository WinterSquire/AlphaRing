#include "../native.h"

#include "common.h"
#include <queue>
#include <mutex>

#include "halo3odst.h"

namespace Halo3ODST::Entry::World {
    std::mutex tasks_mutex;
    std::queue<std::function<void()>> tasks;

    void ExecuteTask() {
        std::function<void()> func = nullptr;

        std::unique_lock<std::mutex> lock(tasks_mutex);
        if (!tasks.empty()) { func = tasks.front();tasks.pop();}
        lock.unlock();

        if (func != nullptr) func();
    }

    void AddTask(const std::function<void()>& func) {
        std::unique_lock<std::mutex> lock(tasks_mutex);
        tasks.push(func);
    }

    void Prologue() {
        ExecuteTask();
    }

    void Epilogue() {

    }

    Halo3ODSTEntry(entry, OFFSET_HALO3ODST_PF_WORLD, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
