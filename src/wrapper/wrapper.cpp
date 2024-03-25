#include "module_definition.h"

#include "WtsApi32.h"

ModuleDefinition module{
    WRAPPER_DLL_NAME,
    {
            "WTSRegisterSessionNotification",
            "WTSUnRegisterSessionNotification",
            "WTSQueryUserToken",
            "WTSQuerySessionInformationW",
            "WTSFreeMemory"
    }
};

extern "C" {
#pragma comment(linker, "/EXPORT:WTSRegisterSessionNotification=WTSRegisterSessionNotificationWrapper")
BOOL __stdcall WTSRegisterSessionNotificationWrapper(HWND hWnd, DWORD dwFlags) {
    return ((BOOL (__stdcall *)(HWND, DWORD)) module.GetFunc(0))(hWnd, dwFlags);
}

#pragma comment(linker, "/EXPORT:WTSUnRegisterSessionNotification=WTSUnRegisterSessionNotificationWrapper")
BOOL __stdcall WTSUnRegisterSessionNotificationWrapper(HWND hWnd) {
    return ((BOOL (__stdcall *)(HWND)) module.GetFunc(1))(hWnd);
}

#pragma comment(linker, "/EXPORT:WTSQueryUserToken=WTSQueryUserTokenWrapper")
BOOL __stdcall WTSQueryUserTokenWrapper(ULONG SessionId, PHANDLE phToken) {
    return ((BOOL (__stdcall *)(ULONG, PHANDLE)) module.GetFunc(2))(SessionId, phToken);
}

#pragma comment(linker, "/EXPORT:WTSQuerySessionInformationW=WTSQuerySessionInformationWWrapper")
BOOL __stdcall WTSQuerySessionInformationWWrapper(HANDLE hServer, DWORD SessionId, WTS_INFO_CLASS WTSInfoClass,
                                                  LPWSTR *ppBuffer, DWORD *pBytesReturned) {
    return ((BOOL (__stdcall *)(HANDLE, DWORD, WTS_INFO_CLASS, LPWSTR *, DWORD *))
                module.GetFunc(3)) (hServer, SessionId, WTSInfoClass, ppBuffer, pBytesReturned);
}

#pragma comment(linker, "/EXPORT:WTSFreeMemory=WTSFreeMemoryWrapper")
void __stdcall WTSFreeMemoryWrapper(PVOID pMemory) {
    return ((void (__stdcall *)(PVOID)) module.GetFunc(4))(pMemory);
}
}