#ifndef __CORE_INIT_CPP__
#define __CORE_INIT_CPP__

#include "../header/core.hpp"
#include "../../utils/os/restart.cpp"

namespace core {

    void terminalHandler::init(){

        m_running = true;
        m_defaultSystemCMD = false;

        if(IsRunAsAdmin()){
            m_termianlprivilege_level = ADMIN;
        }

        initstaticcommand();
        initdynamiccommand();
    }

    void terminalHandler::initstaticcommand (){

        m_staticcommand[0] = StaticCommand(
            "Quit",
            Command_Type::STATIC,
            "1.0.0",
            [this](const StaticExeStruct& a){
                this->m_running  = false;
            }
        );

        m_staticcommand[1] = StaticCommand(
            "Restart",
            Command_Type::STATIC,
            "1.0.0",
            [this](const StaticExeStruct& a){
                Utils::OS::restart();
            }
        );

        m_staticcommand[2] = StaticCommand(
            "Include",
            Command_Type::STATIC,
            "1.0.0",
            [this](const StaticExeStruct& a){
                if(a.data.size() != 2){
                    Utils::ErrorHandle::ErrorDisplay("Too Many Arg for \'Include\' Command.");
                    return;
                }
            }
        );

        m_staticcommand[3] = StaticCommand(
            "System",
            Command_Type::STATIC,
            "1.0.0",
            [this](const StaticExeStruct& a){
                if(a.data.size() != 1){
                    Utils::ErrorHandle::ErrorDisplay("Too Many Arg in \'System\' Command.");
                    return;
                }
                m_defaultSystemCMD = true;
                std::cout<<"Default Cmd Online.\n";
            }
        );

        m_staticcommand[4] = StaticCommand(
            "Normal",
            Command_Type::STATIC,
            "1.0.0",
            [this](const StaticExeStruct& a){
                if(a.data.size() != 1){
                    Utils::ErrorHandle::ErrorDisplay("Too Many Arg in \'Normal\' Command.");
                    return;
                }
                m_defaultSystemCMD = false;
                std::cout<<"Custom Cmd Online.\n";
            }
        );

    }

    void terminalHandler::dynamiccommand(const Json::Value& data){
        for (const auto &key : data.getMemberNames()) {
            const Json::Value &value = data[key];

            // later version < or > include.
            if (m_umapdynamiccommand.find(key) == m_umapdynamiccommand.end()) {
                try{
                    m_umapdynamiccommand[key] = DynamicCommand(value,key);
                }catch(const std::exception& e){
                    Utils::ErrorHandle::ErrorDisplay(e.what());
                }
            }
        }
    }

    void terminalHandler::initdynamiccommand (){
        Json::Value data;
        Utils::FileOperation::ReadJson(data,m_JsonFileFordynamic);
        dynamiccommand(data);
    }

}
#endif