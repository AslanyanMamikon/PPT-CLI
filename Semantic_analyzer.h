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
	SemanticAnalyzer(){}
	SemanticResult analize(const CommandNode& node) {
		if (node.cmd == "add") {
			if (node.object != "slide") return { false, "suppeted: add slide" };


			if (node.flags.count("-pos")) {
				if (!validatePositions(node.flags.at("-pos"))) return { false, "invalid -pos value" };
			}
			
			return { true, "" };

		}
		else if (node.cmd == "remove") {

			if (node.object != "slide") return { false, "suppeted: remove slide" };
			if (node.flags.count("-pos")) {
				if (!validatePositions(node.flags.at("-pos"))) return { false, "invalid -pos value" };
			}
			return { true, "" };
		}
	}




	static bool validatePositions(const std::string& s) {
		std::string token;
		for (size_t i = 0;i <= s.size(); ++i) {
			if (i == s.size() || s[i] == ',') {
				if (token.empty()) return false;
				if (!isNumber(token)) return false;



			}
			else if (!isspace((unsigned char)s[i])) token.push_back(s[i]);
		}
		return true;
	}


	static std::vector<int> parserPosition(const std::string& s) {
		std::vector<int> out;
		std::string token;
		for (size_t i = 0; i < s.size(); ++i) {
			if (i == s.size() || s[i] == ',') {
				if (!token.empty()) {
					out.push_back(stoi(token));
					token.clear();
				}
			}
			else if (!isspace((unsigned char)s[i])) token.push_back(s[i]);
		}
		return out;
	}

private:
	static bool isNumber(const std::string& t) {
		if (t.empty()) return false;
		for (char c : t)
			if (!isdigit((unsigned char)c)) return false;
		return true;
	}

};



#endif // !SEMANTIC_ANALYZER_H_
