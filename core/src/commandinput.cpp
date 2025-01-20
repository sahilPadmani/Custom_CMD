#ifndef __COMMANDINPUT_CPP__
#define __COMMANDINPUT_CPP__

#include "../header/commandinput.hpp"

namespace core {

    inputStyle::inputStyle(const std::vector<std::string>& command_set)
    :m_commandset{begin(command_set),end(command_set)}{
    }

    std::string inputStyle::InputFromUser()const{
        // auto dllfile = m_dllInputstyle.getHmodule();

        // std::string Inputcommand = GetDataFromDll(dllfile, "ReadInputFromUser", "Input Dll File.");

        // return std::move(Inputcommand);
        return " ";
    }

    bool inputStyle::insertCommand(const std::string& newcommand){
        if(m_commandset.find(newcommand) != m_commandset.end())
            return false;
        m_commandset.emplace(newcommand);
        return true;
    }
}
#endif