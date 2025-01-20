#ifndef _VERSION_
#define _VERSION_

#include "prostring.cpp"
#include <array>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace Utils {

    class version {
    private:
        std::array<int, 3> m_VersionNumber{0, 0, 0};

    public:
        version() = default;

        ~version() = default;

        version(const version &other) : m_VersionNumber(other.m_VersionNumber) {}

        version &operator=(const version &other) {
            if (this != &other) {
                m_VersionNumber = other.m_VersionNumber;
            }
            return *this;
        }
        version(version &&other) noexcept : m_VersionNumber(std::move(other.m_VersionNumber)) {}

        version &operator=(version &&other) noexcept {
            if (this != &other) {
                m_VersionNumber = std::move(other.m_VersionNumber);
            }
            return *this;
        }

        explicit version(const std::string &version) {
            std::vector<std::string> ves_str = StrFun::split(version, '.');
            if (ves_str.size() != 3) {
                throw std::invalid_argument("Version string must have exactly three parts separated by dots.");
            }
            for (size_t i = 0; i < ves_str.size(); ++i) {
                if (!StrFun::isValidNumber(ves_str[i])) {
                    throw std::invalid_argument("Version string contains invalid number: " + ves_str[i]);
                }
                int num = std::stoi(ves_str[i]);
                if (num < 0) {
                    throw std::invalid_argument("Version parts must be greater than 0: " + ves_str[i]);
                }
                m_VersionNumber[i] = num;
            }
        }

        version &operator=(const std::string &versionStr) {
            *this = version(versionStr);
            return *this;
        }

        inline std::string getVersion() const {
            std::vector<std::string> vec_str(m_VersionNumber.size());
            
            std::transform(m_VersionNumber.begin(), m_VersionNumber.end(), std::back_inserter(vec_str),
                           [](const int &num) { return std::to_string(num); });
            return StrFun::join(vec_str, '.');
        }

        inline const bool operator<(const version &v2) const {
            for (size_t i = 0; i < m_VersionNumber.size(); ++i) {
                if (m_VersionNumber[i] != v2.m_VersionNumber[i]) {
                    return m_VersionNumber[i] < v2.m_VersionNumber[i];
                }
            }
            return false;
        }

        inline const bool operator>(const version &v2) const {
            return v2 < *this;
        }
    };

} // namespace Utils

#endif
