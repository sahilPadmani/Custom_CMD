#ifndef __COMMAND_CPP__
#define __COMMAND_CPP__

#include <vector>
#include <string>
#include "../../utils/common/version.cpp"

namespace CommandHandle {
    namespace InitCommand {
        enum Command_Type{
            SYSTEM,
            DYNAMIC,
            STATIC
        };

        struct BasicExeStruct{
            const std::vector<std::string>& data;
            explicit BasicExeStruct(const std::vector<std::string>& exedata):data(exedata){}
        };

        using Version = Utils::version;

        class Command {
            protected:
                std::string m_name;
                Command_Type m_type;
                Version m_version;

            public:
                Command() = default;

                Command(
                    const std::string& commandname,
                    const Command_Type& type,
                    const std::string& version)
                    : m_name(commandname), m_type(type), m_version(version)
                {}

                virtual ~Command() {}

                Command(const Command& other)
                    : m_name(other.m_name), m_type(other.m_type), m_version(other.m_version)
                {}

                Command& operator=(const Command& other) {
                    if (this == &other) {
                        return *this;
                    }
                    
                    m_name = other.m_name;
                    m_type = other.m_type;
                    m_version = other.m_version;

                    return *this;
                }

                Command(Command&& other) noexcept
                    : m_name(std::move(other.m_name)),
                    m_type(std::move(other.m_type)),
                    m_version(std::move(other.m_version))
                {}

                Command& operator=(Command&& other) noexcept {
                    if (this == &other) {
                        return *this;
                    }

                    m_name = std::move(other.m_name);
                    m_type = std::move(other.m_type);
                    m_version = std::move(other.m_version);

                    return *this;
                }

                inline const std::string& getCommandName() const {
                    return m_name;
                }

                inline const Command_Type& getType() const {
                    return m_type;
                }
        };
    }
}

#endif