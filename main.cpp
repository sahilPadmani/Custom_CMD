#include "core/src/core.cpp"
int main(){
    core::terminalHandler terminal;
    
    while(terminal.IsRunning()){
        try{
            std::cout << terminal.getCurrentWorkingDirectory()<<'>';
            std::string command;
            std::getline(std::cin,command);
            terminal.runcommand(command);

        }catch(const std::exception& e){
            Utils::ErrorHandle::ErrorDisplay(e.what());
            return 1;
        }
    }
    return 0;
}