#pragma once

#include "spdlog/spdlog.h"

namespace AlphaRing::Log {
    extern std::shared_ptr<spdlog::logger> default_logger;

    bool Init();
    bool Shutdown();
}

#define LOG_INFO(...) AlphaRing::Log::default_logger->info(__VA_ARGS__)
#define LOG_ERROR(...) AlphaRing::Log::default_logger->error(__VA_ARGS__)
#define LOG_WARNING(...) AlphaRing::Log::default_logger->warn(__VA_ARGS__)
#define LOG_DEBUG(...) AlphaRing::Log::default_logger->debug(__VA_ARGS__)