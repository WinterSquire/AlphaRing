#pragma once

#include <string>
#include <windows.h>
#include <winhttp.h>
#include <unordered_map>

#include <mutex>

struct RequestInfo {
    size_t url_length;
    std::string method;
    std::string url;
    std::string headers;
    std::string body;
    std::string response;
};

struct network_setting_t {
    bool b_enable_capture;
    std::unordered_map<HINTERNET, std::wstring> map_url;
    std::unordered_map<HINTERNET, RequestInfo*> map_request;
    std::vector<RequestInfo*> request_list;
    std::mutex mutex;

    typedef void (*invoke_type)(std::vector<RequestInfo*>& requests);

    void add(HINTERNET hRequest, HINTERNET hConnect, LPCWSTR method, LPCWSTR path);
    void clear();
    void execute(invoke_type invoke);

    void set_url(HINTERNET hConnect, LPCWSTR url);
    bool set_header(HINTERNET hRequest, LPCWSTR header);
    bool set_body(HINTERNET hRequest, LPCVOID lpBuffer, DWORD dwNumberOfBytes);
    bool set_response(HINTERNET hRequest, LPCVOID lpBuffer, DWORD dwNumberOfBytes);
};

extern network_setting_t g_networkSetting;
inline network_setting_t* NetworkSetting() {return &g_networkSetting;};
