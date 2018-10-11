//
//  MULRLexer.cpp
//  MULR
//
//  Created by David Edwards
//  Open Source Software
//

#include "MULRLexer.hpp"
#include "TokenGenerator.hpp"
#include <iostream>
#include <fstream>
using namespace std;

MULRLexer::MULRLexer(ifstream &in) {
    this->in = &in;
}

MULRLexer::~MULRLexer() {
    
}

vector<Token*> MULRLexer::getTokens() {
    
    vector<Token*> tokens;
    vector<char> raw_input;
    char ch;
    
    while (*in>>noskipws>>ch) {
        raw_input.push_back(ch);
    }
    if (in->eof()) {
        raw_input.push_back('\b');
    }
    TokenGenerator * generator = new TokenGenerator(raw_input);
    tokens = generator->getTokens();
    delete generator;
    
    for (size_t i = 0; i < tokens.size(); i++) {
        cout<<"Token[" << i << "]: " << tokens.at(i)->type<<": "<<tokens.at(i)->literal_text<<endl;
    }
    return tokens;
    

}
