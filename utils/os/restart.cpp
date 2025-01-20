#ifndef _UTILS_RESTART_APPLICATION_
#define _UTILS_RESTART_APPLICATION_
#include <iostream>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Utils {
    namespace OS {

#ifdef _WIN32
        // Restart App
        void restart() {

        char szPath[MAX_PATH];
        GetModuleFileNameA(NULL, szPath, MAX_PATH);

        // Create a new process
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        MessageBoxA(NULL, "     Restart the Process :)       ", "System Restart",
                    MB_OK | MB_ICONINFORMATION);

        if (CreateProcessA(szPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si,
                            &pi)) {
            // Close process and thread handles
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

            ExitProcess(0);
        }

        // Handle error

        MessageBoxA(NULL, "Failed to restart the process", "Error",
                    MB_OK | MB_ICONERROR);
        }
#elif  __linux__
        void restart() {
            char path[1024];

            // Get the path of the current executable
            ssize_t count = readlink("/proc/self/exe", path, sizeof(path));
            if (count == -1 || count == sizeof(path)) {
                std::cerr << "Failed to determine executable path." << std::endl;
                return;
            }

            path[count] = '\0'; // Null-terminate the path

            // Restart the application
            if (execl(path, path, nullptr) == -1) {
                std::cerr << "Failed to restart application on Linux." << std::endl;
            }
        }
#endif
    }
}
#endif