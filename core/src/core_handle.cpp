#ifndef __CORE_HANDLE_CPP__
#define __CORE_HANDLE_CPP__

#include "../header/core.hpp"

namespace core {

    void terminalHandler::handlesystemcommand(const std::string& command)const{
        system(command.c_str());
    }

    bool terminalHandler::handlestaticcommand(const std::vector<std::string>& splitcommand){
        for(auto& i: m_staticcommand){
            if(i.getCommandName() == splitcommand.at(0)){
                i.RunStaticCommand(StaticExeStruct(splitcommand));
                return true;
            }
        }
        return false;
    }

    bool terminalHandler::handleInput_type(std::vector<std::string>& splitcommand , const std::string& orignalcommand , int type){
        switch (type) {
            case Input_Method::TOKEN:
                break;
            case Input_Method::FULL_LINE:
                splitcommand = Utils::StrFun::splitString_into2(orignalcommand);
                break;
            case Input_Method::OTHER_COMMAND_OUTPUT:
                break;
            default:
                Utils::ErrorHandle::ErrorDisplay(splitcommand[0] + " Command Input Method Not Valied");
                return false;
        }
        return true;
    }
    
    void terminalHandler::handledynamiccommand (std::vector<std::string>& splitcommand , const std::string& orignalcommand){
        if(m_umapdynamiccommand.find(splitcommand.at(0)) == m_umapdynamiccommand.end()){
            Utils::ErrorHandle::ErrorDisplay(splitcommand[0] + " Command Not Found");
            return;
        }

        auto selectcommand = m_umapdynamiccommand.at(splitcommand[0]);

        if(!selectcommand.privilegeValid(this->m_termianlprivilege_level)){
            Utils::ErrorHandle::ErrorDisplay(splitcommand[0] + " Command Permission Not Valied");
            return;
        }

        if(handleInput_type(splitcommand , orignalcommand , selectcommand.getInputType())){

            auto exestruct = DynamicExeStruct(splitcommand,selectcommand.getDLLFilePath());
            CommandHandle::ExeCommand::Dynamic::DllLoadFileAndRunCommand(exestruct);

        }
    }

}
#endif
