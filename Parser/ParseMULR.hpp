//
//  ParseMULR.hpp
//  MULR
//	Open Source Software
//

#ifndef ParseMULR_hpp
#define ParseMULR_hpp

#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "MULRLexer.hpp"
#include "TokenFeed.hpp"
#include "RegExp.hpp"
#include "DFA.h"
#include "PDABuilder.hpp"
#include "SetGenerator.h"
#include <set>

typedef struct statement {
	statement * next;
} statement;

class ParseMULR {
private:
    std::vector<Token*> tokens;
    TokenFeed *feed;
    RegExp * regworker;
    void ungetToken(Token t);
    TerminalRule * parse_function();
	std::vector<TerminalRule*> functions;
    void parseHeader();
//    bool alreadyVisited(std::vector<node*> visited, node* n);
    bool alreadyDecided(std::vector<int> d, int i);
	TerminalRule * start;
	
	std::vector<int> debug_stack;
	bool match(TerminalRule * entry);
	std::vector<char> raw;
	statement * execution;
public:
	ParseMULR(std::vector<Token*> in, std::vector<char> raw);
    ~ParseMULR();
	void executeParse();
};
#endif /* ParseMULR_hpp */
