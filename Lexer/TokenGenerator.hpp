//
//  TokenGenerator.hpp
//  MULR
//	Open Source Software
//

#ifndef TokenGenerator_hpp
#define TokenGenerator_hpp

#include <stdio.h>
#include <iostream>
#include "MULRLexer.hpp"
#include "TokenChecker.hpp"
using namespace std;

class TokenGenerator {
private:
    vector<char> raw;
public:
    TokenGenerator(vector<char> raw);
    ~TokenGenerator();
    vector<Token*> getTokens();
};

#endif /* TokenGenerator_hpp */
