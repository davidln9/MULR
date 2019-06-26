//
//  RegExp.hpp
//  MULR
//	Open Source Software
//

#ifndef RegExp_hpp
#define RegExp_hpp

#include <stdio.h>
#include <vector>
#include "TokenFeed.hpp"
#include "DFA.h"
#include <set>

class RegExp {
public:
    RegExp();
    regex * parse_regex();
	regex * parse_regex_concat();
	std::set<Token*> getTerminals();
private:
    std::vector<int> parenStack;
    TokenFeed * feed;
	std::set<Token*> terminals;
};
#endif /* RegExp_hpp */
