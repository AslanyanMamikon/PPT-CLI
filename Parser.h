#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Tokenizer.h"

struct CommandNode {
	std::string cmd;
	std::string object;
	std::vector<std::string> positionArgs;
	std::unordered_map <std::string, std::string> flags;
	std::vector <std::string> args;
};

enum class ParserState {
	START,      // Initial state
	COMMAND,    // Parsing command word
	OBJECT,     // Parsing object name
	FLAG,       // Parsing flag name
	FLAG_VALUE, // Parsing flag value
	ARG,        // Parsing arguments
	ERROR,      // Error state
	END         // End state
};

class Parser {
public:
	
	Parser(std::istream& st) : stream(st), tz(stream) { }

	bool parseDFA(CommandNode& node, std::string& err);

private:
	std::istream& stream;
	Tokenizer tz;
	static std::string toLower(const std::string& s);
	
	static const ParserState transitionTable[static_cast<int>(ParserState::END) + 1][static_cast<int>(TokenType::UNKNOWN) + 1];

};

#endif // !PARSER_H_

