//
//  Regulator.hpp
//  MULR
//
//  Created by David Edwards on 7/27/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#ifndef Regulator_hpp
#define Regulator_hpp

#include <stdio.h>
#include <vector>
#include "DFA.h"

class Regulator {
public:
    Regulator();
    bool alreadyVisited(std::vector<node*> visited, node* n);
private:
};

#endif /* Regulator_hpp */
