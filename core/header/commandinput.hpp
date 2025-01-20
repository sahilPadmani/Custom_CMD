#ifndef __COMMANDINPUT_HPP__
#define __COMMANDINPUT_HPP__

#include <unordered_set>

namespace core {
    using CommandHandle::ExeCommand::Dynamic::DllGuard;
    class inputStyle{
        public:
            ~inputStyle() = default;
            explicit inputStyle(const std::vector<std::string>& );
            std::string InputFromUser()const;

            bool insertCommand(const std::string& );
        private:
            std::unordered_set<std::string> m_commandset;
    };
}
#endif