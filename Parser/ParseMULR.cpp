//
//  ParseMULR.cpp
//  MULR
//
//  Created by David Edwards on 7/13/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//
/**
 enum TOKEN_TYPE {
 LPAREN, RPAREN, END_OF_FILE, ID, SEMICOLON, COLON, HASHTAG,
 LBRACE, RBRACE, LBRACKET, RBRACKET, EQUALS, STAR, PLUS,
 NOT, PHPVAR, COMMA, OR, AND, MINUS, ARROW, GREATER_THAN, GTEQ,
 LESS_THAN, LTEQ, MODULO, HAT, DOT, INTEGER, FLOAT
 };
 */

#include "ParseMULR.hpp"
#include <iostream>
#include <set>
using namespace std;

ParseMULR::ParseMULR(vector<Token*> in, vector<char> raw) {
    feed = feed->getInstance();
    feed->setTokens(in);
    regworker = new RegExp();
    tokens = in;
	
	this->raw = raw;
}

void ParseMULR::executeParse() {
    
    set<string> functiondefs;
    
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens.at(i)->type == PHPVAR) {
            functiondefs.insert(tokens.at(i)->literal_text);
        }
    }
    
    parseHeader();
    
    start = parse_function();
    
    Token * t = feed->getToken();
    
    while (t->type != END_OF_FILE) {
        feed->ungetToken(t);
        functions.push_back(parse_function());
        t = feed->getToken();
    }
	
	if (match(start)) {
		cout<<"YES"<<endl;
	} else {
		cout<<"NO"<<endl;
	}
	
}

bool ParseMULR::match(TerminalRule * entry) {
	
	node * temp = entry->expression->starting;
	
	vector<node*> decision;
	
	bool retFlag = false;
	
	
	vector<char> mem;
	vector<node*> beginLoop;
	
	vector<vector<char>> loopMem;
	
	vector<branch*> branchStack;
	
	branch * treeBranch = new branch;
	treeBranch->altRoute = NULL;
	treeBranch->loop = false;
	bool tret = false;
	
	while (1) {
		stringstream ss;
		string target;
		char mychar=raw.back();
		ss << mychar;
		ss >> target;
		
		if (temp->label1 != NULL && temp->label1->type == EPSILON) {
			if (temp->neighbor2 != NULL && temp->label2 != NULL) {
				branchStack.push_back(treeBranch);
				treeBranch = new branch;
				treeBranch->loop = temp->loop;
				treeBranch->altRoute = temp->neighbor2;
			}
			temp = temp->neighbor1;
			
		} else if (temp->label1 == NULL) {
			if (mychar == '\$') { //this is assuming EOF is the follow of this rule (but it's not always the case)
				return true;
			} else {
				if (treeBranch->altRoute != NULL) {
					while (!treeBranch->consumed.empty()) {
						raw.push_back(treeBranch->consumed.back());
						treeBranch->consumed.pop_back();
					}
					temp = treeBranch->altRoute;
					treeBranch->altRoute = NULL;
				} else if (!branchStack.empty()) {
					
					
					while (!treeBranch->consumed.empty()) {
						raw.push_back(treeBranch->consumed.back());
						treeBranch->consumed.pop_back();
					}
					
					
					while (!branchStack.empty()) {
						treeBranch = branchStack.back();
						branchStack.pop_back();
						
						if (!treeBranch->loop && treeBranch->altRoute != NULL) {
							while (!treeBranch->consumed.empty()) {
								raw.push_back(treeBranch->consumed.back());
								treeBranch->consumed.pop_back();
							}
						} else if (!treeBranch->loop) {
							while (!treeBranch->consumed.empty()) {
								raw.push_back(treeBranch->consumed.back());
								treeBranch->consumed.pop_back();
							}
						}
						if (treeBranch->altRoute != NULL) {
							temp = treeBranch->altRoute;
							tret = true;
							break;
						}
					}
					if (!tret) {
						return false;
					} else {
						tret = false;
					}
				} else {
					return false;
				}
			}
			
		} else if (temp->label1->literal_text == target) {
			treeBranch->consumed.push_back(mychar);
			raw.pop_back();
			temp = temp->neighbor1;
		} else if (temp->label1->literal_text != target) {
			
			if (treeBranch->altRoute != NULL) {
				while (!treeBranch->consumed.empty()) {
					raw.push_back(treeBranch->consumed.back());
					treeBranch->consumed.pop_back();
				}
				temp = treeBranch->altRoute;
				treeBranch = branchStack.back();
				branchStack.pop_back();
			} else if (!branchStack.empty()) {
				
				while (!treeBranch->consumed.empty()) {
					raw.push_back(treeBranch->consumed.back());
					treeBranch->consumed.pop_back();
				}
				
				while (!branchStack.empty()) {
					treeBranch = branchStack.back();
					branchStack.pop_back();
					while (!treeBranch->consumed.empty()) {
						raw.push_back(treeBranch->consumed.back());
						treeBranch->consumed.pop_back();
					}
					if (treeBranch->altRoute != NULL) {
						temp = treeBranch->altRoute;
						tret = true;
						break;
					}
				}
				if (!tret) {
					return false;
				} else {
					tret = false;
				}	
			} else {
				return false;
			}
		}
	}
	
}

void ParseMULR::parseHeader() {
    Token * t = feed->getToken();
    if (t->type != KEYWORD) {
        cerr<<"MULR expected at first token"<<endl;
        exit(1);
    }
    t = feed->getToken();
    if (t->type != SEMICOLON) {
        cerr<<"expected SEMICOLON after MULR"<<endl;
        exit(1);
    }
}

TerminalRule * ParseMULR::parse_function() {
    
    regex * reg_ex;
    Token * t = feed->getToken();
    string name = t->literal_text;
    if (t->type != PHPVAR) {
        cerr<<"Start rule must be in the form $[a-z0-9]+"<<endl;
        exit(1);
    } else {
        t = feed->getToken();
        if (t->type != COLON) {
            cerr<<"<"<<t->line_no<<","<<t->start_position<<">: "
            <<"Expected COLON after start symbol"<<endl;
            exit(1);
        } else {
            reg_ex = regworker->parse_regex();
            t = feed->getToken();
            if (t->type != SEMICOLON) {
                cerr<<"<"<<t->line_no<<","<<t->start_position<<">: "
                <<"Expected SEMICOLON got: \'"<<t->literal_text<<"\'"<<endl;
                exit(1);
            }
            TerminalRule * term = new TerminalRule;
            term->expression = reg_ex;
            term->name = name;
            return term;
        }
    }
    
}

