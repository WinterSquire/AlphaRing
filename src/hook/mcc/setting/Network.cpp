#include "Network.h"

network_setting_t g_networkSetting;

void network_setting_t::set_url(HINTERNET hConnect, LPCWSTR url) {
    if (!b_enable_capture) return;
    std::lock_guard<std::mutex> lock(mutex);
    map_url[hConnect] = url;
}

bool network_setting_t::set_header(HINTERNET hRequest, LPCWSTR header) {
    char buffer[1024*1024];

    if (!b_enable_capture) return false;

    std::lock_guard<std::mutex> lock(mutex);
    auto it = map_request.find(hRequest);
    if (it == map_request.end()) return false;

    sprintf(buffer, "Header: %ls", header);
    it->second->headers = buffer;

    return true;
}

bool network_setting_t::set_body(HINTERNET hRequest, LPCVOID lpBuffer, DWORD dwNumberOfBytes) {
    char buffer[1024*1024];

    if (!b_enable_capture) return false;

    std::lock_guard<std::mutex> lock(mutex);

    auto it = map_request.find(hRequest);
    if (it == map_request.end()) return false;

    sprintf(buffer, "%.*s", dwNumberOfBytes, (char*)lpBuffer);
    it->second->body = std::string(buffer);

    return true;
}

bool network_setting_t::set_response(HINTERNET hRequest, LPCVOID lpBuffer, DWORD dwNumberOfBytes) {
    char buffer[1024*1024];

    if (!b_enable_capture) return false;

    std::lock_guard<std::mutex> lock(mutex);
    auto it = map_request.find(hRequest);
    if (it == map_request.end()) return false;

    sprintf(buffer, "%.*s", dwNumberOfBytes, (char*)lpBuffer);

    it->second->response = std::string(buffer);

    return true;
}

void network_setting_t::clear() {
    std::lock_guard<std::mutex> lock(mutex);

    for (auto request: request_list) {
        delete request;
    }

    map_url.clear();
    map_request.clear();
    request_list.clear();
}

void network_setting_t::add(HINTERNET hRequest, HINTERNET hConnect, LPCWSTR method, LPCWSTR path) {
    char buffer[1024*1024];

    if (!b_enable_capture) return;

    std::lock_guard<std::mutex> lock(mutex);

    sprintf(buffer, "%ls", method);

    auto str_method = std::string(buffer);

    sprintf(buffer, "%ls%ls", map_url[hConnect].c_str(), path);

    auto str_url = std::string(buffer);

    auto new_request = new RequestInfo {
            map_url[hConnect].length(),
            std::move(str_method),
            std::move(str_url),
            "",
            "",
            ""
    };

    map_request[hRequest] = new_request;
    request_list.emplace_back(new_request);
}

void network_setting_t::execute(network_setting_t::invoke_type invoke) {
    std::lock_guard<std::mutex> lock(mutex);
    invoke(request_list);
}
