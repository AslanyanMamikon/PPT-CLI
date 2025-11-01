#include "Argument.h"

void ArgumentValidator::addInfo(const ArgumentInfo& info)
{
    infos[info.name] = info;
}

void ArgumentValidator::validate(const std::unordered_map<std::string, std::string>& flags) const
{
    for (const auto& [name, info] : infos) {
        auto it = flags.find(name);

        if (info.required && it == flags.end()) {
            throw CommandValidationException("Missing required flag: " + name);
        }

        if (it == flags.end()) continue;// -----------------------------

        const std::string& value = it->second;
        switch (info.type) {
        case ArgumentType::Integer:
            if (!isInteger(value))
                throw CommandValidationException("Flag " + name + " expects an integer");
            break;
        case ArgumentType::Float:
            if (!isFloat(value))
                throw CommandValidationException("Flag " + name + " expects a float");
            break;
        case ArgumentType::Enum:
            if (std::find(info.allowedValues.begin(), info.allowedValues.end(), value) == info.allowedValues.end())
                throw CommandValidationException("Flag " + name + " invalid value: " + value);
            break;
        default:
            break;
        }
    }
}

bool ArgumentValidator::isInteger(const std::string& s)
{
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
bool ArgumentValidator::isFloat(const std::string& s)
{
    bool dotSeen = false;
    for (char c : s) {
        if (c == '.') {
            if (dotSeen) return false;
            dotSeen = true;
        }
        else if (!isdigit(c)) return false;
    }
    return true;
}