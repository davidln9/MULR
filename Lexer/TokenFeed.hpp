//
//  TokenFeed.hpp
//  MULR
//	Open Source Software
//

#ifndef TokenFeed_hpp
#define TokenFeed_hpp

#include <stdio.h>
#include "MULRLexer.hpp"

class TokenFeed { //this is a singleton
private:
    std::vector<Token*> input;
    TokenFeed();
    TokenFeed(TokenFeed const&);
    TokenFeed& operator=(TokenFeed const&);
    static TokenFeed* instance;
public:
    TokenFeed * getInstance();
    Token * getToken();
    void ungetToken(Token *t);
    void setTokens(std::vector<Token*> input);
};

#endif /* TokenFeed_hpp */
