//
//  PDA.hpp
//  MULR
//
//  Created by David Edwards on 7/26/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#ifndef PDA_hpp
#define PDA_hpp

#include <stdio.h>
#include <vector>
#include "DFA.h"
#include "Regulator.hpp"

class PDABuilder {
  
public:
    PDABuilder(TerminalRule * start, std::vector<TerminalRule*> functions);
    regex * constructPDA();
private:
    TerminalRule * start;
    std::vector<TerminalRule*> functions;
    regex * lookupFunction(std::string function);
    void convertToPDA(regex * in);
};

#endif /* PDA_hpp */
