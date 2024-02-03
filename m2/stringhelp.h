#ifndef STRINGHELP_H
#define STRINGHELP_H

#include <string>

namespace m2 {

class StringHelp
{
public:
    static std::string toLower(const std::string &str);
    static std::string toUpper(const std::string &str);

    static std::string trimLeft(const std::string &str);
    static std::string trimRight(const std::string &str);
    static std::string trim(const std::string &str);

    static bool startsWith(const std::string &str, const std::string &prefix);
    static bool endsWith(const std::string &str, const std::string &suffix);

    static std::string toString(short value, int base, int width, char fill,
                                bool prefix);
    static std::string toString(unsigned short value, int base, int width,
                                char fill, bool prefix);
    static std::string toString(int value, int base, int width, char fill,
                                bool prefix);
    static std::string toString(unsigned int value, int base, int width,
                                char fill, bool prefix);
    static std::string toString(long long value, int base, int width, char fill,
                                bool prefix);
    static std::string toString(unsigned long long value, int base, int width,
                                char fill, bool prefix);
    static std::string toString(float value, int precision, int width);
    static std::string toString(double value, int precision, int width);
};

}// namespace m2

#endif//STRINGHELP_H