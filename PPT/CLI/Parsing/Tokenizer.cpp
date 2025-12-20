#include "Tokenizer.h"
#include <cctype>


Tokenizer::Tokenizer(std::istream& st) : stream(st), bufPos(0), bufEnd(0), atEnd(false) { }

bool Tokenizer::eof() const { return atEnd; }

char Tokenizer::nextChar()
{
	if (bufPos >= bufEnd)
	{
		stream.read(buffer, BUFFER_SIZE);
		bufEnd = static_cast<size_t>(stream.gcount());
		bufPos = 0;
		if (bufEnd == 0)
		{
			atEnd = true;
			return '\0';
		}
	}
	return buffer[bufPos++];
}

const Token& Tokenizer::getToken()
{
	const Token& tok = current;
	advance();
	return tok;
}


void Tokenizer::advance()
{
    if (atEnd) {
        current = { TokenType::END, "" };
        return;
    }

    char c;
    do {
        c = nextChar();
        if (atEnd) {
            current = { TokenType::END, "" };
            return;
        }
    } while (isspace(static_cast<unsigned char>(c)));

    if (c == '-') {
        std::string flag(1, c);
        while (!atEnd) {
            char peek = nextChar();
            if (atEnd || isspace(static_cast<unsigned char>(peek))) {
                if (!atEnd) bufPos--;
                break;
            }
            flag.push_back(peek);
        }
        current = { TokenType::FLAG, flag };
        return;
    }

    if (isdigit(static_cast<unsigned char>(c))) {
        std::string num(1, c);
        while (!atEnd) {
            char peek = nextChar();
            if (isdigit(static_cast<unsigned char>(peek)) || peek == '.') {
                num.push_back(peek);
            }
            else {
                bufPos--;
                break;
            }
        }
        current = { TokenType::NUMBER, num };
        return;
    }

    if (isalpha(static_cast<unsigned char>(c))) {
        std::string word(1, c);
        while (!atEnd) {
            char peek = nextChar();
            if (isalnum(static_cast<unsigned char>(peek)) || peek == '_' || peek == '.') {
                word.push_back(peek);
            }
            else {
                bufPos--;
                break;
            }
        }
        current = { TokenType::WORD, word };
        return;
    }

    if (c == '"') {
        std::string str;
        while (!atEnd) {
            c = nextChar();
            if (c == '"' || atEnd) break;
            str.push_back(c);
        }
        current = { TokenType::STRING, str };
        return;
    }

    current = { TokenType::UNKNOWN, std::string(1, c) };
}