//
//  Regulator.cpp
//  MULR
//
//  Created by David Edwards on 7/27/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#include "Regulator.hpp"

using namespace std;

Regulator::Regulator() {
    
}

bool Regulator::alreadyVisited(vector<node *> visited, node* n) {
    
    for (int i = 0; i < visited.size(); i++) {
        if (visited.at(i) == n) {
            return true;
        }
    }
    
    return false;
}
