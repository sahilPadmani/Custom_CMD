#ifndef __DLLGUARD_CPP__
#define __DLLGUARD_CPP__

#include <string>
#include <cstring>
#include <stdexcept>
#include "../../definecommand/dynamiccommand.cpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace CommandHandle {
    namespace ExeCommand {
        namespace Dynamic {

            class DllGuard {
            public:
                explicit DllGuard(const std::string& dllfilepath) {
#ifdef _WIN32
                    DllFilehandle = LoadLibraryA(dllfilepath.c_str());
#else
                    DllFilehandle = dlopen(dllfilepath.c_str(), RTLD_NOW);   
#endif
                    if (!DllFilehandle) {
                        throw std::runtime_error("Failed to load DLL: " + dllfilepath);
                    }
                }

                ~DllGuard() {
                    if (DllFilehandle) {
#ifdef _WIN32
                        FreeLibrary(DllFilehandle);
#else
                        dlclose(DllFilehandle);
#endif
                    }
                }

#ifdef _WIN32
                inline HMODULE getHmodule()const{
                    return DllFilehandle;
                }
#else
                inline void* getHmodule() const {
                    return DllFilehandle;
                }
#endif

            private:
#ifdef _WIN32
                HMODULE DllFilehandle;
#else
                void* DllFilehandle;
#endif
            };

            class ParameterMemoryGuard{
                public:
                explicit ParameterMemoryGuard(const std::vector<std::string>& data){
                    Data.strcount = data.size();
                    Data.strings = new char*[Data.strcount];
                    Data.strsize = new int[Data.strcount];

                    for (size_t i = 0; i < Data.strcount; ++i) {
                        size_t len = data[i].size();
                        Data.strsize[i] = static_cast<int>(len);
                        Data.strings[i] = new char[len + 1]; // +1 for null terminator
                        strcpy_s(Data.strings[i], len + 1, data[i].c_str());
                    }
                }

                ~ParameterMemoryGuard() {
                    for (size_t i = 0; i < Data.strcount; ++i) {
                        delete[] Data.strings[i];
                    }

                    // Free the arrays
                    delete[] Data.strings;
                    delete[] Data.strsize;
                }

                const InitCommand::DLLParameter* getSafeData()const{
                    return &Data;
                }

                private:
                    InitCommand::DLLParameter Data;
            };

            class ReturnGuard;
        }
    }
}

#endif