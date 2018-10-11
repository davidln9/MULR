//
//  PDAStack.cpp
//  MULR
//
//  Created by David Edwards on 7/26/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#include "PDAStack.hpp"
using namespace std;

PDAStack::PDAStack(vector<string> stack) {
    this->stack = stack;
}

void PDAStack::push(string s) {
    stack.push_back(s);
}

string PDAStack::pop() {
    string s = stack.back();
    stack.pop_back();
    return s;
}


