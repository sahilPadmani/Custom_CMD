#ifndef __CORE_HPP__
#define __CORE_HPP__


#include <memory>
#include <array>
#include <unordered_map>
#include <mutex>
#include <json/json.h>

#include "../../utils/common/version.cpp"
#include "../../utils/filehandle/filehandle.cpp"
#include "../../utils/os/privilegelevel.cpp"

// #include "../../CommandHandler/definecommand/command.cpp"
#include "../../CommandHandler/definecommand/dynamiccommand.cpp"
#include "../../CommandHandler/definecommand/staticcommand.cpp"
#include "../../CommandHandler/execommand/dynamic/dllexe.cpp"

#include "../src/commandinput.cpp"

namespace core {

    using namespace CommandHandle::InitCommand;
    using namespace Utils::OS;

    class terminalHandler{
        public:
            explicit terminalHandler();
            std::string InputCommand()const;
            std::string getCurrentWorkingDirectory();
            bool IsRunning()const;
            void runcommand(const std::string&);

        private:
            inline static constexpr auto m_InputDllFile = "./defaultInput.dll";
            inline static constexpr auto m_JsonFileFordynamic = "./detail.command.json";
            
            bool m_running;
            bool m_defaultSystemCMD;
            char m_buffer[PATH_MAX];
            privilege_level m_termianlprivilege_level  = Utils::OS::USER;

            inputStyle m_inputmanage;

            // Restart , Quit , Include <Dll file> , System <-s/Opctional> , Normal ;
            // Restart work on applicaton not in VS code terminal ?
            std::array<StaticCommand,5> m_staticcommand;
            std::unordered_map<std::string,DynamicCommand> m_umapdynamiccommand;
            
            void init();
            void initstaticcommand();
            void initdynamiccommand();
            void dynamiccommand(const Json::Value&);

            void handlesystemcommand(const std::string&)const;
            bool handlestaticcommand(const std::vector<std::string>& );
            void handledynamiccommand(std::vector<std::string>& ,const std::string& );
            bool handleInput_type(std::vector<std::string>& , const std::string&  , int );
     
    };
}

#endif