//
//  ParseMULR.hpp
//  MULR
//
//  Created by David Edwards on 7/13/18.
//  Copyright © 2018 David Edwards. All rights reserved.
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
	bool match(TerminalRule * entry);
	std::vector<char> raw;
public:
	ParseMULR(std::vector<Token*> in, std::vector<char> raw);
    ~ParseMULR();
	void executeParse();
};
#endif /* ParseMULR_hpp */
