
#include "Tokenizer.h"

void Tokenizer::skipSpace() {
	while (i < s.size() && isspace((unsigned char)s[i])) 
		++i;
}


void Tokenizer::advance() {
	skipSpace();
	if (i >= s.size()) {
		current = Token(TokenType::END, "");
		return;
	}

	char c = s[i];
	if (c == '"' || c == '\'') {
		char quote = c; ++i;
		std::string out;
		while (i < s.size() && s[i] != quote) {
			if (s[i] == '\\' && i + 1 < s.size()) {
				out += s[i + 1];
				i += 2;
			}
			else {
				out += s[i++];
			}
		}
		if (i < s.size() && s[i] == quote) ++i;
		current = Token(TokenType::STRING, out);
		return;
	}

	if (c == '-') {
		size_t j = i ;
		if (j < s.size() && (isalpha((unsigned char)s[j]) || s[j] == '-')) {
			std::string out;
			out += c;
			++j;
			while (j < s.size() && (isalnum((unsigned char)s[j]) || s[j] == '-' || s[j] == '.' || s[j] == '_')) {
				out += s[j++];
			}
			current = Token(TokenType::FLAG, out);
			i = j;
			return;
		}
	}

	if (isdigit((unsigned char)c)) {
		std::string out;
		size_t j = i;
		while (j < s.size() && (isdigit((unsigned char)s[j]) || s[j] == ',')) {
			out += s[j++];
		}
		current = Token(TokenType::NUMBER, out);
		i = j;
		return;
	}

	{
		std::string out;
		size_t j = i;
		while (j < s.size() && !isspace((unsigned char)s[j]) && s[j] != '"' && s[j] != '\'') {
			out += s[j++];
		}
		current = Token(TokenType::WORD, out);
		i = j;
		return;
	}
}
