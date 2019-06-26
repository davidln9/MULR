//
//  TokenBuilder.hpp
//  MULR
//	Open Source Software
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
