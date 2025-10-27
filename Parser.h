#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Tokenizer.h"
#include "ICommand.h"

enum class ParserState {
    START,
    COMMAND,
    OBJECT,
    FLAG,
    FLAG_VALUE,
    ARG,
    ERROR,
    END
};

class Parser {
public:
    explicit Parser(std::istream& stream);

    std::unique_ptr<ICommand> parse();

    const std::string& getError() const { return errorMsg; }

private:
    Tokenizer tz;
    std::string errorMsg;

private:
    static std::string toLower(const std::string& s);
    //static const ParserState transitionTable[7][7];
    static const ParserState transitionTable[static_cast<int>(ParserState::END) + 1][static_cast<int>(TokenType::UNKNOWN) + 1];
};

#endif // PARSER_H_