#ifndef __EXEDYNAMIC_CPP__
#define __EXEDYNAMIC_CPP__

#include <json/json.h>
#include <list>
#include "dllguard.cpp"
#include "../../../utils/errorhandler/error.cpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace CommandHandle {
    namespace ExeCommand {
        namespace Dynamic {

            using DynamicExeStr = InitCommand::DynamicExeStruct;
            using namespace Utils::ErrorHandle;

            static bool DllLoadFileAndRunCommand(const DynamicExeStr& commanddata) {
                try {
                    DllGuard dllhandler{commanddata.dllfilepath};

#ifdef _WIN32
                    typedef void(__cdecl* DynamicDllMain)(const InitCommand::DLLParameter*);
                    DynamicDllMain dllmain = reinterpret_cast<DynamicDllMain>(GetProcAddress(dllhandler.getHmodule(), "CommandMain"));
#else
                    typedef void (*DynamicDllMain)(const InitCommand::DLLParameter*);
                    DynamicDllMain dllmain = reinterpret_cast<DynamicDllMain>(
                        dlsym(dllhandler.getHandle(), "CommandMain"));
#endif

                    if (!dllmain) {
                        throw std::runtime_error("Failed to find 'CommandMain' in DLL -> " + commanddata.dllfilepath);
                    }

                    ParameterMemoryGuard CommandParametrData_S{commanddata.data};

                    dllmain(CommandParametrData_S.getSafeData()); // Invoke the function
                    return true;

                } catch (const std::exception& e) {
                    ErrorDisplay(e.what());
                }
                return false;
            }

            static bool CommandsExecuter(const std::list<DynamicExeStr>& listCommand) {
                for (const auto& i : listCommand) {
                    if (!DllLoadFileAndRunCommand(i)) {
                        return false;
                    }
                }
                return true;
            }

            static std::string GetDataFromDll(
#ifdef _WIN32
                const HMODULE hmodule,
#else
                void* hmodule,
#endif
                const std::string& function_name,
                const std::string& dllfilepath) {

#ifdef _WIN32
                typedef const char*(__cdecl* DataFromDll)();
                DataFromDll fundata = reinterpret_cast<DataFromDll>(GetProcAddress(hmodule, function_name.c_str()));
#else
                typedef const char* (*DataFromDll)();
                DataFromDll fundata = reinterpret_cast<DataFromDll>(dlsym(hmodule, function_name.c_str()));
#endif

                if (!fundata) {
                    throw std::runtime_error("Failed to find '" + function_name + "' in DLL -> " + dllfilepath);
                }

                return std::string{fundata()};
            }

            static void GetJSONDataFromDllFile(const char* dllfilepath) {
                try {
                    DllGuard dllhandler{dllfilepath};

                    std::string data = GetDataFromDll(dllhandler.getHmodule(), "GetJsonData", dllfilepath);

                    Json::Value commanddata;
                    Json::CharReaderBuilder readerBuilder;
                    std::string errors;

                    std::istringstream jsonStringStream(data);

                    if (!Json::parseFromStream(readerBuilder, jsonStringStream, &commanddata, &errors)) {
                        throw std::runtime_error("parsing JSON: " + errors);
                        return;
                    }

                } catch (const std::exception& e) {
                    ErrorDisplay(e.what());
                }
            }

            static void GetJSONDataFromDllListExecuter(const std::list<std::string>& dllpath) {
                for (const auto& i : dllpath) {
                    GetJSONDataFromDllFile(i.c_str());
                }
            }

        }
    }
}

#endif
