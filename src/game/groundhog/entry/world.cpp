#include "game/groundhog/native.h"

#include "common.h"
#include <queue>
#include <mutex>

#include "groundhog.h"

namespace GroundHog::Entry::World {
    std::mutex tasks_mutex;
    std::queue<std::function<void()>> tasks;

    void AddTask(const std::function<void()>& func) {
        std::unique_lock<std::mutex> lock(tasks_mutex);
        tasks.push(func);
    }

    void ExecuteTask() {
        std::function<void()> func = nullptr;

        std::unique_lock<std::mutex> lock(tasks_mutex);
        if (!tasks.empty()) { func = tasks.front();tasks.pop();}
        lock.unlock();

        if (func != nullptr) func();
    }

    void Prologue() {
        ExecuteTask();
    }

    void Epilogue() {

    }

    GroundHogEntry(entry, OFFSET_GROUNDHOG_PF_WORLD, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
