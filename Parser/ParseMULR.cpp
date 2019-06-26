//
//  ParseMULR.cpp
//  MULR
//	Open Source Software
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
#include "BranchChars.hpp"
#include <iostream>
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
	
	start->follow.insert("\$");
	
	//build FIRST and FOLLOW sets
	SetGenerator * sets = new SetGenerator(functions);
	sets->generateFirsts(start);
	
	cout<<"FIRST(START): {";
	std::set<string>:: iterator it;
	for (it = start->first.begin(); it != start->first.end(); ++it) {
		cout<<*it;
		
		if (it != start->first.end()) {
			cout<<", ";
		}
	}
	cout<<"}"<<endl;
	
	for (size_t i = 0; i < functions.size(); i++) {
		cout<<"FIRST("<<functions.at(i)->name<<"): {";
		
		if (functions.at(i)->first.size() == 0) {
			sets->generateFirsts(functions.at(i));
			cout<<"DEBUG_S"<<endl;
		}
		for (it = functions.at(i)->first.begin(); it != functions.at(i)->first.end(); ++it) {
			cout<<*it;
			
			if (it != functions.at(i)->first.end()) {
				cout<<", ";
			}
		}
		cout<<"}"<<endl;
	}
	
	sets->generateFollow(start);
	
	
	
	cout<<"FOLLOW(START): {";
	for (it = start->follow.begin(); it != start->follow.end(); ++it) {
		cout<<*it;
		if (it != start->follow.end()) {
			cout<<", ";
		}
	}
	cout<<"}"<<endl;
	
	for (size_t i = 0; i < functions.size(); i++) {
		cout<<"FOLLOW("<<functions.at(i)->name<<"): {";
		
		for (it = functions.at(i)->follow.begin(); it != functions.at(i)->follow.end(); ++it) {
			cout<<*it;
			if (it != functions.at(i)->follow.end()) {
				cout<<", ";
			}
		}
		cout<<"}"<<endl;
	}
	
	cout<<"BETWEEN(START): {";
	for (it = start->between.begin(); it != start->between.end(); ++it) {
		cout<<*it<<", ";
	}
	cout<<"}"<<endl;
	
	for (size_t i = 0; i < functions.size(); i++) {
		cout<<"BETWEEN("<<functions.at(i)->name<<"): {";
		
		for (it = functions.at(i)->between.begin(); it != functions.at(i)->between.end(); ++it) {
			cout<<*it<<", ";
		}
		cout<<"}"<<endl;
	}
	
	execution = NULL;
	if (match(start)) {
		cout<<"YES"<<endl;
	} else {
		cout<<"NO"<<endl;
	}
	
}

bool ParseMULR::match(TerminalRule * entry) {
	
	node * temp = entry->expression->starting;
	
	vector<node*> decision;
	
	vector<char> mem;
	vector<node*> beginLoop;
	
	vector<vector<char>> loopMem;
	
	vector<branch*> branchStack;
	vector<branch*> recusiveBranchStack;
	
	branch * treeBranch = new branch;
	treeBranch->altRoute = NULL;
	treeBranch->loop = false;
	treeBranch->tryRecursion = false;
	bool tret = false;
	
	string tabs = "";
	
	for (size_t i = 0; i < debug_stack.size(); i++) {
		tabs+="\t";
	}
	
	while (1) {
		stringstream ss;
		string target;
		char mychar=raw.back();
		ss << mychar;
		ss >> target;
		
		cout<<tabs<<"DEBUG: TARGET: "<<target<<endl;

		
		if (temp->label1 != NULL && temp->label1->type == EPSILON) {
			if (temp->neighbor2 != NULL && temp->label2 != NULL) {
				branchStack.push_back(treeBranch);
				treeBranch = new branch;
				treeBranch->loop = temp->loop;
				treeBranch->altRoute = temp->neighbor2;
				treeBranch->tryRecursion = false;
			}
			temp = temp->neighbor1;
			
		} else if (temp->label1 == NULL) {
			
			bool found = false;
			set<string>:: iterator it;
			for (it = entry->follow.begin(); it != entry->follow.end(); ++it) {
				if (target == *it) {
					found = true;
					break;
				}
			}
			if (found) { //this is assuming EOF is the follow of this rule (but it's not always the case)
				if (mychar == '\$' && debug_stack.empty()) {
					raw.push_back(mychar);
				}
				BranchChars * b = BranchChars::getInstance();
				b->insertChars(treeBranch->consumed);
				delete treeBranch;
				while (!branchStack.empty()) {
					b->insertChars(branchStack.back()->consumed);
					delete branchStack.back();
					branchStack.pop_back();
				}
				return true;
			} else {
				bool doit = true;
				for (it = entry->between.begin(); it != entry->between.end(); ++it) {
					if (target == *it) {
						doit = false;
						treeBranch = recusiveBranchStack.back();
						temp = treeBranch->altRoute;
						recusiveBranchStack.pop_back();
						break;
					}
				}
				if (doit) {
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
					} else if (!recusiveBranchStack.empty()) {
						while (!treeBranch->consumed.empty()) {
							raw.push_back(treeBranch->consumed.back());
							treeBranch->consumed.pop_back();
						}
						treeBranch = recusiveBranchStack.back();
						temp = treeBranch->altRoute;
						recusiveBranchStack.pop_back();
					} else {
						while (!treeBranch->consumed.empty()) {
							raw.push_back(treeBranch->consumed.back());
							treeBranch->consumed.pop_back();
						}
						while (!branchStack.empty()) {
							while (!branchStack.back()->consumed.empty()) {
								raw.push_back(branchStack.back()->consumed.back());
								branchStack.back()->consumed.pop_back();
							}
							branchStack.pop_back();
						}
						return false;
					}
				}
			}
			
		} else if (temp->label1->literal_text == target) {
			treeBranch->consumed.push_back(mychar);
			cout<<tabs<<"DEBUG: CONSUMED: "<<raw.back()<<endl;
			raw.pop_back();
			temp = temp->neighbor1;
			
		} else if (temp->label1->type == NON_TERMINAL) {
			bool doit = true;
			if (temp->label1->literal_text == entry->name && !treeBranch->tryRecursion) { // save this for later maybe??
				if (treeBranch->altRoute != NULL) {
					node * t = new node;
					t->label1 = temp->label1;
					t->neighbor1 = temp->neighbor1;
					t->label2 = temp->label2;
					t->neighbor2 = temp->neighbor2;
//					node * t = temp;
					temp = treeBranch->altRoute;
					treeBranch = branchStack.back();
					branchStack.pop_back();
					branch * b = new branch;
					
					b->tryRecursion = true;
					b->altRoute = t;
					b->consumed = treeBranch->consumed;
					recusiveBranchStack.push_back(b);
					doit = false;
				} else if (!branchStack.empty()) {
					bool flag = false;
					while (!branchStack.empty()) {
						treeBranch = branchStack.back();
						branchStack.pop_back();
						if (treeBranch->altRoute != NULL) {
							temp = treeBranch->altRoute;
							branch * b = new branch;
							
							b->tryRecursion = true;
							b->altRoute = treeBranch->altRoute;
							b->consumed = treeBranch->consumed;
							recusiveBranchStack.push_back(b);
							flag = true;
							break;
						}
					}
					if (!flag) {
						cerr<<"BAD THINGS HAPPENING"<<endl;
						exit(5);
					} else {
						doit = false;
					}
				}
			}
			if (doit) {
				cout<<tabs<<"DEBUG: NON TERMINAL: "<<temp->label1->literal_text<<endl;
				// find the function that matches the label and parse it
				for (size_t i = 0; i < functions.size(); i++) {
					if (functions.at(i)->name == temp->label1->literal_text) {
						debug_stack.push_back(0);
						if (match(functions.at(i))) { // make program continue parsing
							cout<<tabs<<"DEBUG: SUCCESSFUL MATCH"<<endl;
							temp = temp->neighbor1;
							vector<char> consumed = BranchChars::getInstance()->getChars();
							for (size_t g = 0; g < consumed.size(); g++) {
								cout<<tabs<<"RECOVERED: "<<consumed.at(g)<<endl;
								treeBranch->consumed.push_back(consumed.at(g));
							}
							consumed.clear();
							break;
						} else { // recover
							
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
						debug_stack.pop_back();
					}
				}
			}
		} else if (temp->label1->literal_text != target) {
			
			cout<<tabs<<"MISS"<<endl;
			if (treeBranch->altRoute != NULL) {
				cout<<tabs<<"op1"<<endl;
				while (!treeBranch->consumed.empty()) {
					raw.push_back(treeBranch->consumed.back());
					treeBranch->consumed.pop_back();
				}
				temp = treeBranch->altRoute;
				treeBranch = branchStack.back();
				branchStack.pop_back();
			} else if (!branchStack.empty()) {
				cout<<tabs<<"op2"<<endl;
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
			} else if (!recusiveBranchStack.empty()) {
				cout<<tabs<<"op3"<<endl;
				treeBranch = recusiveBranchStack.back();
				recusiveBranchStack.pop_back();
				temp = treeBranch->altRoute;
			} else {
				cout<<tabs<<"op4"<<endl;
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

