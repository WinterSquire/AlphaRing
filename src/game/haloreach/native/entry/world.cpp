#include "../native.h"

#include "common.h"
#include <queue>
#include <mutex>

namespace HaloReach::Entry::World {
    void Prologue(); void Epilogue();
    void ExecuteTask(); void AddTask(const std::function<void()>& func);
    std::queue<std::function<void()>> tasks; std::mutex tasks_mutex;
}

void HaloReach::Entry::World::Prologue() {
    ExecuteTask();
}

void HaloReach::Entry::World::Epilogue() {

}


void HaloReach::Entry::World::AddTask(const std::function<void()>& func) {
    std::unique_lock<std::mutex> lock(tasks_mutex);
    tasks.push(func);
}

void HaloReach::Entry::World::ExecuteTask() {
    std::function<void()> func = nullptr;

    std::unique_lock<std::mutex> lock(tasks_mutex);
    if (!tasks.empty()) { func = tasks.front();tasks.pop();}
    lock.unlock();

    if (func != nullptr) func();
}

