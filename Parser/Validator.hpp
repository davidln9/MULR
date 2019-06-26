//
//  Validator.hpp
//  MULR
//	Open Source Software
//

#ifndef Validator_hpp
#define Validator_hpp

#include <stdio.h>
#include "MULRLexer.hpp"

class validator {
private:
    std::vector<Token*> functions;
    std::vector<Token*> tokens;
    std::vector<Token*> getFunctions();
public:
    void checkFunctions();
    validator(std::vector<Token*> tokens);
};
#endif /* Validator_hpp */
