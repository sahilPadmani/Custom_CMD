#ifndef _PROSTRING_
#define _PROSTRING_

#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <string>
#include <algorithm>

namespace Utils {
    namespace StrFun {
        using std::string;
        bool isValidNumber(const string &s) {
            return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
        }

        void trim(std::string& str) {
            // Remove leading spaces
            str.erase(0, str.find_first_not_of(" \t\n\r"));

            // Remove trailing spaces
            str.erase(str.find_last_not_of(" \t\n\r") + 1);
        }

        inline std::vector<char> split(const string &str) {
            return {str.begin(), str.end()};
        }

        std::vector<string> split(const string& str , const char& delimiter){
            std::vector<string> vector_str;

            std::istringstream iss(str);
            string token;

            while (std::getline(iss, token, delimiter)) {
                if (!token.empty()) {
                    vector_str.emplace_back(token);
                }
            }

            return vector_str;
        }
    
        std::vector<string> split_enter_tab_space(const string& str){
            std::vector<string> vector_str;
            std::istringstream iss(str);
            string token;

            while (iss >> token) {
                vector_str.emplace_back(token);
            }

            return vector_str;
        }

        string join(const std::vector<string>& vector_str , const char& delimiter = ' '){
            std::ostringstream oss;
            for(int i = 0 ; i < vector_str.size() ; ++i ){
                if( i > 0)
                    oss << delimiter;
                oss <<vector_str[i];
            }
            return oss.str();
        }

        std::vector<string> splitString_into2(const string& str){
            std::vector<string> vec_2_str(2);
            std::istringstream iss(str);
            iss >> vec_2_str[0];

            std::getline(iss,vec_2_str[1]);
            trim(vec_2_str[1]);
            return vec_2_str;
        }
    }
}
#endif