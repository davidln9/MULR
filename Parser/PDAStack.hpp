//
//  PDAStack.hpp
//  MULR
//
//  Created by David Edwards on 7/26/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#ifndef PDAStack_hpp
#define PDAStack_hpp

#include <stdio.h>
#include <vector>
#include <string>

class PDAStack {
public:
    PDAStack(std::vector<std::string> stack);
    void push(std::string);
    std::string pop();
private:
    std::vector<std::string> stack;
};

#endif /* PDAStack_hpp */
