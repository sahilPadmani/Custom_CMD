#ifndef PRINT_H
#define PRINT_H
#include <iostream>
#include <json/json.h>
#ifdef __cplusplus
extern "C"
{
#endif
    struct CommandParemeterData {
        char** strings;    // Array of C-style strings
        int* sizes;        // Array of sizes corresponding to each string
        size_t count;      // Number of strings
    };
    __declspec(dllexport) const char* GetJsonData(){
        Json::Value root;

        root["Name"] = "print";
        root["Privilege_Level"] = 1;
        root["Version"] = "1.1.0";
        root["InputMethod"] = 2;
        root["ExecuteType"] = 1;
        root["DllFilePath"] = "./dllfile/Print.dll";

        static std::string strformat_json_data = Json::writeString(Json::StreamWriterBuilder(), root);
        return strformat_json_data.c_str();
    }
    __declspec(dllexport) void __cdecl CommandMain(const CommandParemeterData* Printed_Line)
    {
        if (Printed_Line->count > 0 && Printed_Line->strings != nullptr) {
            std::cout << Printed_Line->strings[1] << '\n';
        }
    }
#ifdef __cplusplus
}
#endif
#endif