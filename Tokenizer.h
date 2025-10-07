#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <string>
#include <iostream>

constexpr size_t BUFFER_SIZE = 1024;

enum class TokenType {
	WORD,
	FLAG,
	NUMBER,
	STRING,
	END,
	UNKNOWN
};

struct Token {
	TokenType type;
	std::string text;
	Token(TokenType t = TokenType::END, std::string s = "") :
		type(t), text(std::move(s)) {
	}
};

class Tokenizer {
public:
	explicit Tokenizer(std::istream& st);

	const Token& getToken();
	bool eof() const;

private:
	std::istream& stream;
	Token current;

	char buffer[BUFFER_SIZE];
	size_t bufPos;
	size_t bufEnd;
	bool atEnd;

	void advance();
	char nextChar();
};

#endif // !TOKENIZER_H_