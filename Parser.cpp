#include "Parser.h"
#include <cctype>

std::string Parser::toLower(const std::string& s) {
	std::string out = s;
	for (char& c : out) {
		c = tolower((unsigned char)c);
	}
	return out;
}
/*
bool Parser::parse(CommandNode& node, std::string& err) {
	if (tz.eof()) {
		err = "empty input";
		return false;
	}

	Token t = tz.next();
	if (t.type != TokenType::WORD) {
		err = "expected command word";
		return false;
	}

	node.cmd = toLower(t.text);

	if (tz.eof()) return true;

	Token t2 = tz.peek();
	if (t2.type == TokenType::WORD) {
		node.object = toLower(tz.next().text);
	}

	while (!tz.eof()) {
		Token tok = tz.next();
		if (tok.type == TokenType::FLAG) {
			std::string flag = tok.text;

			Token la = tz.peek();
			if (la.type == TokenType::STRING ||
				la.type == TokenType::WORD ||
				la.type == TokenType::NUMBER) {
				Token valueTok = tz.next();
				node.flags[flag] = valueTok.text;
			}
			else {
				node.flags[flag] = "";
			}
		}
		else if (tok.type == TokenType::NUMBER) {
			node.positionArgs.push_back(tok.text);
		}
		else if (tok.type == TokenType::STRING || tok.type == TokenType::WORD) {
			node.args.push_back(tok.text);
		}
		else {
			// Ignore END token
		}
	}
	return true;
}
	
*/


CharCategory Parser::categorizeChar(char c) {
	if (std::isalpha(c)) return CharCategory::ALPHA;
	if (std::isdigit(c)) return CharCategory::DIGIT;
	if (c == '-') return CharCategory::DASH;
	if (c == '"' || c == '\'') return CharCategory::QUOTE;
	if (std::isspace(c)) return CharCategory::SPACE;
	return CharCategory::OTHER;
}


ParserState Parser::getNextState(ParserState currentState, CharCategory category) {
	switch (currentState) {
	case ParserState::START:
		switch (category) {
		case CharCategory::ALPHA: return ParserState::COMMAND;
		case CharCategory::SPACE: return ParserState::START;
		default: return ParserState::ERROR;
		}
		
	case ParserState::COMMAND:
		switch (category) {
		case CharCategory::ALPHA:
		case CharCategory::DIGIT:
		case CharCategory::OTHER: return ParserState::COMMAND;
		case CharCategory::SPACE: return ParserState::OBJECT;
		case CharCategory::DASH: return ParserState::FLAG;
		case CharCategory::QUOTE: return ParserState::ARG;
		default: return ParserState::ERROR;
		}
		
	case ParserState::OBJECT:
		switch (category) {
		case CharCategory::ALPHA:
		case CharCategory::DIGIT:
		case CharCategory::OTHER: return ParserState::OBJECT;
		case CharCategory::SPACE: return ParserState::ARG;
		case CharCategory::DASH: return ParserState::FLAG;
		case CharCategory::QUOTE: return ParserState::ARG;
		default: return ParserState::ERROR;
		}
		
	case ParserState::FLAG:
		switch (category) {
		case CharCategory::ALPHA:
		case CharCategory::DIGIT:
		case CharCategory::DASH:
		case CharCategory::OTHER: return ParserState::FLAG;
		case CharCategory::SPACE: return ParserState::FLAG_VALUE;
		case CharCategory::QUOTE: return ParserState::FLAG_VALUE;
		default: return ParserState::ERROR;
		}
		
	case ParserState::FLAG_VALUE:
		switch (category) {
		case CharCategory::ALPHA:
		case CharCategory::DIGIT:
		case CharCategory::QUOTE:
		case CharCategory::OTHER: return ParserState::FLAG_VALUE;
		case CharCategory::SPACE: return ParserState::ARG;
		case CharCategory::DASH: return ParserState::FLAG;
		default: return ParserState::ERROR;
		}
		
	case ParserState::ARG:
		switch (category) {
		case CharCategory::ALPHA:
		case CharCategory::DIGIT:
		case CharCategory::SPACE:
		case CharCategory::QUOTE:
		case CharCategory::OTHER: return ParserState::ARG;
		case CharCategory::DASH: return ParserState::FLAG;
		default: return ParserState::ERROR;
		}
		
	default:
		return ParserState::ERROR;
	}
}


void Parser::processStateAction(ParserState state, char c, CommandNode& node, 
	std::string& currentWord, std::string& currentFlag, std::string& currentValue) {
	
	switch (state) {
	case ParserState::COMMAND:
		if (!std::isspace(c)) {
			currentWord += c;
		} else {
			node.cmd = toLower(currentWord);
			currentWord.clear();
		}
		break;
		
	case ParserState::OBJECT:
		if (!std::isspace(c)) {
			currentWord += c;
		} else {
			node.object = toLower(currentWord);
			currentWord.clear();
		}
		break;
		
	case ParserState::FLAG:
		if (c == '-') {
			if (!currentFlag.empty()) {
				node.flags[currentFlag] = "";
				currentFlag.clear();
			}
			currentFlag = c;
		} else if (!std::isspace(c)) {
			currentFlag += c;
		} else {
			node.flags[currentFlag] = "";
			currentFlag.clear();
		}
		break;
		
	case ParserState::FLAG_VALUE:
		if (std::isspace(c)) {
			if (!currentFlag.empty() && !currentValue.empty()) {
				node.flags[currentFlag] = currentValue;
				currentFlag.clear();
				currentValue.clear();
			}
		} else {
			currentValue += c;
		}
		break;
		
	case ParserState::ARG:
		if (std::isspace(c)) {
			if (!currentWord.empty()) {
				if (std::isdigit(currentWord[0])) {
					node.positionArgs.push_back(currentWord);
				} else {
					node.args.push_back(currentWord);
				}
				currentWord.clear();
			}
		} else {
			currentWord += c;
		}
		break;
		
	default:
		break;
	}
}

bool Parser::parseDFA(CommandNode& node, std::string& err) {
	node.cmd.clear();
	node.object.clear();
	node.flags.clear();
	node.args.clear();
	node.positionArgs.clear();

	std::string input;
	Tokenizer tempTz = tz;

	while (!tempTz.eof()) {
		Token t = tempTz.next();
		if (t.type != TokenType::END) {
			input += t.text + " ";
		}
	}

	if (!input.empty() && input.back() == ' ') {
		input.pop_back();
	}
	
	if (input.empty()) {
		err = "empty input";
		return false;
	}
	
	ParserState currentState = ParserState::START;
	std::string currentWord;
	std::string currentFlag;
	std::string currentValue;
	
	for (size_t i = 0; i < input.length(); ++i) {
		char c = input[i];
		CharCategory category = categorizeChar(c);
		ParserState nextState = getNextState(currentState, category);
		
		if (nextState == ParserState::ERROR) {
			err = "Invalid character '" + std::string(1, c) + "' at position " + 
				  std::to_string(i) + " in state " + 
				  std::to_string(static_cast<int>(currentState));
			return false;
		}
		
		processStateAction(nextState, c, node, currentWord, currentFlag, currentValue);
		currentState = nextState;
	}
	
	if (!currentWord.empty()) {
		if (currentState == ParserState::COMMAND) {
			node.cmd = toLower(currentWord);
		} else if (currentState == ParserState::OBJECT) {
			node.object = toLower(currentWord);
		} else if (std::isdigit(currentWord[0])) {
			node.positionArgs.push_back(currentWord);
		} else {
			node.args.push_back(currentWord);
		}
	}
	
	if (!currentFlag.empty()) {
		node.flags[currentFlag] = currentValue;
	}
	
	if (node.cmd.empty()) {
		err = "No command found";
		return false;
	}
	
	return true;
}