//
//  TokenWriter.hpp
//  MULR
//
//  Created by David Edwards on 7/18/18.
//  Copyright © 2018 David Edwards. All rights reserved.
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
