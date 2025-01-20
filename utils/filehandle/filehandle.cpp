#ifndef _FILEHANDLE_
#define _FILEHANDLE_

#include <fstream>
#include <json/json.h>

namespace Utils {
    namespace FileOperation {
        static void ReadJson(Json::Value& data, const std::string& filepath) {
            std::ifstream file(filepath, std::ifstream::binary);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + filepath);
            }

            file >> data;
            // file.close(); RAII
        }
        static void WriteJson(const Json::Value& data, const std::string& filepath) {
            std::ofstream file(filepath, std::ofstream::binary);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file for writing: " + filepath);
            }

            Json::StreamWriterBuilder writer;
            std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
            jsonWriter->write(data, &file);
            // file.close(); RAII
        }
    }
}

#endif