#ifndef _ERRORHANDLER_
#define _ERRORHANDLER_
#include <string>
#include <stdio.h>
namespace Utils {
    namespace ErrorHandle {
        static void ErrorDisplay(const std::string& error){
            printf_s("Error : %s \n",error.c_str());
        }
    }
}

#endif