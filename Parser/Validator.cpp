//
//  Validator.cpp
//  MULR
//	Open Source Software
//

#include "Validator.hpp"
#include <iostream>
using namespace std;

validator::validator(vector<Token*> tokens) {
    this->tokens = tokens;
}

vector<Token*> validator::getFunctions() {
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens.at(i)->type == PHPVAR) {
            functions.push_back(tokens.at(i));
        }
    }
    
    return functions;
}

void validator::checkFunctions() {
    getFunctions();
    Token * temp;
    for (size_t i = 0; i < functions.size(); i++) {
        temp = functions.at(i);
        for (size_t j = i+1; j < functions.size(); j++) {
            if (temp->literal_text == functions.at(j)->literal_text) {
                cerr<<"Function redefinition ("<<temp->literal_text<<") at line: "<<functions.at(j)->line_no+1<<endl;
                exit(1);
            }
        }
    }
}
