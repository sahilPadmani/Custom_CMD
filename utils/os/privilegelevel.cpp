#ifndef _PRIVILEGELEVEL_
#define _PRIVILEGELEVEL_

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

namespace Utils {
    namespace OS {
        enum privilege_level {
            ADMIN = 0,
            USER = 1
        };

#ifdef _WIN32
        static bool IsRunAsAdmin() {
            BOOL isElevated = FALSE;
            HANDLE hToken = NULL;

            if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
                TOKEN_ELEVATION elevation;
                DWORD dwSize;
                if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize)) {
                    isElevated = elevation.TokenIsElevated;
                }
                CloseHandle(hToken);
            }
            return isElevated == TRUE;
        }
#elif __linux__
        static bool IsRunAsAdmin() {
            return geteuid() == 0;
        }
#endif
    }
}

#endif
