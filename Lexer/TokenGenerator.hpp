//
//  TokenGenerator.hpp
//  MULR
//
//  Created by David Edwards on 7/14/18.
//  Copyright © 2018 David Edwards. All rights reserved.
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
