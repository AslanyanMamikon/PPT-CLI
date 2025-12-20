#include "Parser.h"
#include "CommandFactory.h"
#include <cctype>
#include <algorithm>

const ParserState Parser::transitionTable[][6] = {
    //                WORD              FLAG              NUMBER            STRING            END               UNKNOWN
    /* START     */ { ParserState::COMMAND, ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
    /* COMMAND   */ { ParserState::OBJECT,  ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
    /* OBJECT    */ { ParserState::ARG,     ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
    /* FLAG      */ { ParserState::FLAG_VALUE, ParserState::FLAG, ParserState::FLAG_VALUE, ParserState::FLAG_VALUE, ParserState::END, ParserState::ERROR },
    /* FLAG_VALUE*/ { ParserState::ARG,     ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
    /* ARG       */ { ParserState::ARG,     ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
    /* ERROR     */ { ParserState::ERROR,   ParserState::ERROR, ParserState::ERROR, ParserState::ERROR, ParserState::ERROR, ParserState::ERROR }
};

Parser::Parser(std::istream& stream)
    : tz(stream), exitFlagPtr(nullptr), editorPtr(nullptr) {
}

std::string Parser::toLower(const std::string& s)
{
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return out;
}

std::unique_ptr<ICommand> Parser::parse(bool* exitFlag, Editor* editor)
{
    exitFlagPtr = exitFlag;
    editorPtr = editor;
    errorMsg.clear();

    std::string cmd;
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

    ParserState state = ParserState::START;
    std::string currentFlag;

    while (!tz.eof()) {
        const Token& tok = tz.getToken();

        int stateIdx = static_cast<int>(state);
        int tokenIdx = static_cast<int>(tok.type);

        ParserState next = transitionTable[stateIdx][tokenIdx];

        if (next == ParserState::ERROR) {
            errorMsg = "Unexpected token '" + tok.text + "' in state " +
                std::to_string(stateIdx);
            return nullptr;
        }

        state = next;

        switch (state) {
        case ParserState::COMMAND:
            if (tok.type == TokenType::WORD) {
                cmd = toLower(tok.text);
            }
            break;

        case ParserState::OBJECT:
            if (tok.type == TokenType::WORD) {
                object = toLower(tok.text);
            }
            break;

        case ParserState::FLAG:
            if (tok.type == TokenType::FLAG) {
                currentFlag = tok.text;
                flags[currentFlag] = "";
            }
            break;

        case ParserState::FLAG_VALUE:
            flags[currentFlag] = tok.text;
            currentFlag.clear();
            break;

        case ParserState::ARG:
            args.push_back(tok.text);
            break;

        case ParserState::END:
            break;

        default:
            break;
        }

        if (tok.type == TokenType::END) {
            break;
        }
    }

    if (cmd.empty()) {
        errorMsg = "No command found";
        return nullptr;
    }

    try {
        return CommandFactory::createCommand(cmd, object, flags, args, exitFlagPtr, editorPtr);
    }
    catch (const CommandValidationException& e)
    {
        errorMsg = e.what();
        return nullptr;
    }
}