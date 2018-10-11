//
//  TokenBuilder.hpp
//  MULR
//
//  Created by David Edwards on 7/15/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#ifndef TokenBuilder_hpp
#define TokenBuilder_hpp

#include <stdio.h>
#include "MULRLexer.hpp"
using namespace std;

class TokenBuilder {
private:
public:
    Token* buildToken(string ch, int &position, int &id, int line, TOKEN_TYPE type);
private:
};

#endif /* TokenBuilder_hpp */
