#include "Log.h"

#include "spdlog.h"

#include "common.h"

namespace AlphaRing::Log {
    std::shared_ptr<spdlog::logger> default_logger;

    bool Init() {
        bool result = AllocConsole();
        assertm(result, "failed to allocate console");

        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);

        default_logger = std::make_shared<spdlog::logger>(
                "default",
                std::move(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>())
        );

        spdlog::register_logger(default_logger);

        return true;
    }

    bool Shutdown() {
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        FreeConsole();

        return true;
    }
}
