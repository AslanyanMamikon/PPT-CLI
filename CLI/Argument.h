#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "ICommand.h"

enum class ArgumentType {
    String,
    Integer,
    Float,
    Enum
};

struct ArgumentInfo {
    std::string name;
    ArgumentType type;
    bool required;
    std::vector<std::string> allowedValues;
};

/*
ArgumentInfo layoutFlag = {
    "-layout", 
    ArgumentType::Enum, 
    false, 
    {"title", "blank", "content"}
};
*/

class ArgumentValidator {
public:
    void addInfo(const ArgumentInfo& info);
    void validate(const std::unordered_map<std::string, std::string>& flags) const;

private:
    std::unordered_map<std::string, ArgumentInfo> infos;

    static bool isInteger(const std::string& s);
    static bool isFloat(const std::string& s);
};

#endif // !ARGUMENT_H_
