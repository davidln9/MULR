//
//  Regulator.hpp
//  MULR
//	Open Source Software
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
