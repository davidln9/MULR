//
//  DFA.h
//  MULR
//
//  Created by David Edwards on 7/19/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#ifndef DFA_h
#define DFA_h
#include <string>
#include <vector>

enum labelType {
    TERMINAL, NON_TERMINAL, EPSILON
};

typedef struct regex {
    struct node * starting;
    struct node * accepting;
} regex;

typedef struct LHS {
    std::string name;
    regex * expression;
	std::vector<char> first;
	std::vector<char> follow;
} TerminalRule;


typedef struct label {
    labelType type;
    std::string literal_text;
    std::string pop_symbol;
    std::string push_symbol;
    
} label;

typedef struct branch {
	std::vector<char> consumed;
	bool loop;
	node * altRoute;
} branch;


typedef struct node {
    struct label * label1;
    struct label * label2;
    struct node * neighbor1;
    struct node * neighbor2;
	bool loop;
} node;
#endif /* DFA_h */
