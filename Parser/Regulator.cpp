//
//  Regulator.cpp
//  MULR
//	Open Source Software
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
