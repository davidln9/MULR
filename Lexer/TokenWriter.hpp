//
//  TokenWriter.hpp
//  MULR
//	Open Source Software
//

#ifndef TokenWriter_hpp
#define TokenWriter_hpp

#include <stdio.h>
#include <iostream>
#include "MULRLexer.hpp"

class TokenWriter {
private:
    std::vector<Token*> tokens;
public:
    ~TokenWriter();
    TokenWriter(std::vector<Token*> tokens);
    void writeTokens();
};
#endif /* TokenWriter_hpp */
