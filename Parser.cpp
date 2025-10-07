#include "Parser.h"
#include <cctype>

std::string Parser::toLower(const std::string& s) {
	std::string out = s;
	for (char& c : out) {
		c = tolower((unsigned char)c);
	}
	return out;
}

const ParserState Parser::transitionTable[][6] = {
	//							WORD          FLAG			      NUMBER		   STRING			  END			     UNKNOWN
	/* START  */ { ParserState::COMMAND, ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
	/* COMMAND*/ { ParserState::OBJECT, ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
	/* OBJECT */ { ParserState::OBJECT,  ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
	/* FLAG   */ { ParserState::FLAG_VALUE, ParserState::FLAG, ParserState::FLAG_VALUE, ParserState::FLAG_VALUE, ParserState::END, ParserState::ERROR },
	/* FLAG_VAL*/{ ParserState::ARG,   ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
	/* ARG    */ { ParserState::ARG,   ParserState::FLAG, ParserState::ARG, ParserState::ARG, ParserState::END, ParserState::ERROR },
};

bool Parser::parseDFA(CommandNode& node, std::string& err) {
	node.cmd.clear();
	node.object.clear();
	node.flags.clear();
	node.args.clear();
	node.positionArgs.clear();

	ParserState state = ParserState::START;
	std::string currentWord;
	std::string currentFlag;
	std::string currentValue;

	while (!tz.eof())
	{
		const Token& tok = tz.getToken();

		ParserState next = transitionTable[(int)state][(int)tok.type];
		if (next == ParserState::ERROR)
		{
			err = "Unexpected token '" + tok.text + "' in state " + std::to_string((int)state);
			return false;
		}
		
		state = next;
		
		switch (state)
		{
		case ParserState::COMMAND:
			if (tok.type == TokenType::WORD)
				node.cmd = toLower(tok.text);
			break;

		case ParserState::OBJECT:
			if (tok.type == TokenType::WORD)
				node.object = toLower(tok.text);
			break;

		case ParserState::FLAG:
			if (tok.type == TokenType::FLAG)
			{
				currentFlag = tok.text;
				node.flags[currentFlag] = "";
			}
			break;

		case ParserState::FLAG_VALUE:
			node.flags[currentFlag] = tok.text;
			currentFlag.clear();
			break;

		case ParserState::ARG:
			if (tok.type == TokenType::NUMBER)
				node.positionArgs.push_back(tok.text);
			else
				node.args.push_back(tok.text);
			break;

		default:
			break;
		}

		if (tok.type == TokenType::END)
			break;
	}

	if (node.cmd.empty())
	{
		err = "No command found";
		return false;
	}
	return true;
}
