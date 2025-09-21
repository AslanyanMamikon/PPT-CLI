#ifndef SEMANTIC_ANALYZER_H_
#define SEMANTIC_ANALYZER_H_

#include <iostream>
#include "Parser.h"

struct SemanticResult {
	bool ok;
	std::string message;
};

class SemanticAnalyzer {
public:
	SemanticAnalyzer() {}


	SemanticResult analize(const CommandNode& node);
	static bool validatePositions(const std::string& s);
	static std::vector<int> parserPosition(const std::string& s);

private:
	static bool isNumber(const std::string& t);
};

#endif // !SEMANTIC_ANALYZER_H_
