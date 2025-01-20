#ifndef __DYNAMICCOMMAND_CPP__
#define __DYNAMICCOMMAND_CPP__

#include "command.cpp"
#include "../../utils/os/privilegelevel.cpp"

namespace CommandHandle {
    namespace InitCommand {

        struct DLLParameter{
            char** strings;
            int* strsize;
            size_t strcount;
        };

        enum Input_Method {
            TOKEN = 1,                          // For commands where parts are separated and no spaces are included
            FULL_LINE = 2,                      
            OTHER_COMMAND_OUTPUT = 4            
        };

        enum Output_Method{
            PRINT = 1
        };

        struct DynamicExeStruct : public BasicExeStruct{ 
            const std::string& dllfilepath;
            DynamicExeStruct(const std::vector<std::string>& exedata,const std::string& dllpath)
                :BasicExeStruct(exedata),dllfilepath(dllpath){   
            }
        };

        // class InitDynamicCommand{
        //     const int& input_method ;
        //     const int& output_method ;
        //     const std::string& dllfilepath ;
        //     const Utils::OS::privilege_level& c_level ;

        // public:
        //     explicit InitDynamicCommand(
        //         const std::string& dllfilepath,
        //         const Utils::OS::privilege_level& c_level,
        //         const int& input_method , 
        //         const int& output_method
        //     ):{}
        // };

        using PrivilegeLevel = Utils::OS::privilege_level;

        constexpr auto NULL_DLL_FILE = "./NULL.DLL";

        class DynamicCommand : public Command {
            public:
                DynamicCommand() = default;

                explicit DynamicCommand(const Json::Value& data,const std::string& name){

                    m_privilegelevel = static_cast<PrivilegeLevel>(
                        data.get("Privilege_Level",PrivilegeLevel::USER).asInt()
                    );
                    m_version = data.get("Version","0.0.0").asString();
                    m_inputtype = data.get("InputMethod",Input_Method::TOKEN).asInt();
                    m_outputtype = data.get("ExecuteType",Output_Method::PRINT).asInt();
                    m_dllpath = data.get("DllFilePath",NULL_DLL_FILE).asString();
                    m_type = Command_Type::DYNAMIC;
                    m_name = name;
                }

                ~DynamicCommand()  = default;

                DynamicCommand(const DynamicCommand& other)
                    : Command(other),
                    m_dllpath(other.m_dllpath),
                    m_privilegelevel(other.m_privilegelevel),
                    m_inputtype(other.m_inputtype),
                    m_outputtype(other.m_outputtype)
                {}

                DynamicCommand& operator=(const DynamicCommand& other) {
                    if (this == &other) {
                        return *this;
                    }
                    
                    Command::operator=(other);
                    m_dllpath = other.m_dllpath;
                    m_privilegelevel = other.m_privilegelevel;
                    m_inputtype = other.m_inputtype;
                    m_outputtype = other.m_outputtype;

                    return *this;
                }

                DynamicCommand(DynamicCommand&& other) noexcept
                    : Command(std::move(other)),
                    m_dllpath(std::move(other.m_dllpath)),
                    m_privilegelevel(std::move(other.m_privilegelevel)),
                    m_inputtype(other.m_inputtype),
                    m_outputtype(other.m_outputtype)
                {
                    other.m_inputtype = 1;
                    other.m_outputtype = 1;
                }

                DynamicCommand& operator=(DynamicCommand&& other) noexcept {
                    if (this == &other) {
                        return *this;
                    }

                    Command::operator=(std::move(other));
                    m_dllpath = std::move(other.m_dllpath);
                    m_privilegelevel = std::move(other.m_privilegelevel);
                    m_inputtype = other.m_inputtype;
                    m_outputtype = other.m_outputtype;

                    
                    other.m_inputtype = 1;
                    other.m_outputtype = 1;

                    return *this;
                }

                inline const std::string& getDLLFilePath() const {
                    return m_dllpath;
                }

                inline bool privilegeValid(const PrivilegeLevel& app_level) const {
                    return (m_privilegelevel >= app_level);
                }

                inline int getInputType() const {
                    return m_inputtype;
                }

                inline const int& getOutputType() const {
                    return m_outputtype;
                }

            private:
                std::string m_dllpath;
                PrivilegeLevel m_privilegelevel;
                int m_inputtype;
                int m_outputtype;
        };
    }
}

#endif