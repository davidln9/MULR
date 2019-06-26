//
//  DFA.h
//  MULR
//	Open Source Software
//

#ifndef DFA_h
#define DFA_h
#include <string>
#include <set>
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
	std::set<std::string> first;
	std::set<std::string> follow;
	std::set<std::string> between;
	std::set<struct LHS*> affected;
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
	bool tryRecursion;
} branch;

typedef struct fbranch {
	TerminalRule * f;
	node * altRoute;
	node * stopAt;
} followBranch;

typedef struct firstBr {
	node * altRoute;
	bool addFirst;
} firstBranch;


typedef struct node {
    struct label * label1;
    struct label * label2;
    struct node * neighbor1;
    struct node * neighbor2;
	bool loop;
} node;
#endif /* DFA_h */
