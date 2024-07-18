#pragma once

#include <string>
#include <vector>

namespace MCC::Network {
    struct RequestInfo {
        bool status;
        size_t url_length;
        std::string method;
        std::string url;
        std::string headers;
        std::string body;
        std::string response;
    };

    bool Initialize();
    void ImGuiContext();
}