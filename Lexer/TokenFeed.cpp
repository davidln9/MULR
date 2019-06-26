//
//  TokenFeed.cpp
//  MULR
//	Open Source Software
//

#include "TokenFeed.hpp"
using namespace std;

TokenFeed * TokenFeed::instance = NULL;

TokenFeed * TokenFeed::getInstance() {
    if (instance == NULL) {
        instance = new TokenFeed;
    }
    return instance;
}

TokenFeed::TokenFeed() {
    
}

TokenFeed::TokenFeed(TokenFeed const&) {
    
}

void TokenFeed::setTokens(std::vector<Token *> input) {
    this->input = input;
}

Token * TokenFeed::getToken() {
    if (!input.empty()) {
        Token * t = (input.back());
        input.pop_back();
        return t;
    } else {
        Token * t = new Token;
        t->type = END_OF_FILE;
        return t;
    }
}

void TokenFeed::ungetToken(Token *t) {
    input.push_back(t);
}
