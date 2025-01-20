#ifndef __STATICCOMMAND_CPP__
#define __STATICCOMMAND_CPP__

#include <functional>
#include "../../utils/errorhandler/error.cpp"
#include "command.cpp"


namespace CommandHandle {
    namespace InitCommand {

        struct StaticExeStruct : public BasicExeStruct{
            StaticExeStruct(const std::vector<std::string>& exedata)
                :BasicExeStruct(exedata){   
            }
        };

        class StaticCommand : public Command {
            public:
                StaticCommand() = default;
                ~StaticCommand() = default;

                explicit StaticCommand(
                    const std::string& commandname,
                    const Command_Type& type,
                    const std::string& version,
                    std::function<void(const StaticExeStruct&)> exefunction)
                : Command(commandname, type, version), m_exeFunction(std::move(exefunction)) {}

                StaticCommand(const StaticCommand& other)
                    : Command(other), m_exeFunction(other.m_exeFunction) {}

                StaticCommand(StaticCommand&& other) noexcept
                    : Command(std::move(other)), m_exeFunction(std::move(other.m_exeFunction)) {}

                StaticCommand& operator=(const StaticCommand& other) {
                    if (this != &other) {
                        Command::operator=(other);
                        m_exeFunction = other.m_exeFunction;
                    }
                    return *this;
                }

                StaticCommand& operator=(StaticCommand&& other) noexcept {
                    if (this != &other) {
                        Command::operator=(std::move(other));
                        m_exeFunction = std::move(other.m_exeFunction);
                    }
                    return *this;
                }

                void RunStaticCommand(const StaticExeStruct& data) {
                    if (!m_exeFunction) {
                        Utils::ErrorHandle::ErrorDisplay(getCommandName() + " execution function not set!");
                        return;
                    }
                    m_exeFunction(data);
                }

            private:
                std::function<void(const StaticExeStruct&)> m_exeFunction;
        };
    }
}

#endif