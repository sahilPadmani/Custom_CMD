#ifndef __CORE_CPP__
#define __CORE_CPP__

#include "../header/core.hpp"
#include "core_init.cpp"
#include "core_handle.cpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

//public function
namespace core {

    using namespace CommandHandle::InitCommand;
    using namespace Utils::OS;

    std::string terminalHandler::getCurrentWorkingDirectory() {
    #ifdef _WIN32
        if (GetCurrentDirectoryA(PATH_MAX, m_buffer) == 0) {
            throw std::runtime_error("Failed to get current directory.");
        }
    #else
        if (getcwd(m_buffer, sizeof(m_buffer)) == nullptr) {
            throw std::runtime_error("Failed to get current directory.");
        }
    #endif
        return std::string(m_buffer);
    }

    terminalHandler::terminalHandler():m_inputmanage({m_InputDllFile}){
        init();
    }

    bool terminalHandler::IsRunning ()const{
        return m_running;
    }

    void terminalHandler::runcommand (const std::string& strcommand){
        auto splitcommand = Utils::StrFun::split_enter_tab_space(strcommand);

        if(handlestaticcommand(splitcommand))
            return;

        if(m_defaultSystemCMD){
            handlesystemcommand(strcommand);
            return ;
        }
        handledynamiccommand(splitcommand,strcommand);
    }

    std::string terminalHandler::InputCommand()const{
        return m_inputmanage.InputFromUser();
    }

}

#endif