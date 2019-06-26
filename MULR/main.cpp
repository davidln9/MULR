//
//  main.cpp
//  MULR
//	Open Source Software
//

#include <iostream>
#include <fstream>
#include "TokenWriter.hpp"
#include "ParseMULR.hpp"
#include "Validator.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    //cout << "Hello, World!\n";
    ifstream grammar;
	ifstream input;
    bool parse;
    if (argc < 2) {
        cerr<<"Error: Missing input file"<<endl;
        exit(1);
    } else if (argc == 3) {
        grammar.open(argv[2]);
		input.open(argv[1]);
        parse = false;
	} else {
		cerr<<"usage: grammar_file input_file"<<endl;
		exit(1);
	}
	
	vector<char> raw_input;
	char ch;
	
	while (input>>skipws>>ch) {
		raw_input.push_back(ch);
	}
	
	raw_input.push_back('\$');
	
	for (size_t i = 0; i < raw_input.size(); i++) {
		cout<<"input char: "<<raw_input.at(i)<<endl;
	}
	
	vector<char> sortedIn;
	
	while (!raw_input.empty()) {
		sortedIn.push_back(raw_input.back());
		raw_input.pop_back();
	}
	
	input.close();
    
    vector<Token*> sortedTokens;
    MULRLexer * lexer = new MULRLexer(grammar);
    vector<Token*> tokens = lexer->getTokens();
    grammar.close();
    
//    validator *v = new validator(tokens);
//    v->checkFunctions();
    
    while (!tokens.empty()) {
        sortedTokens.push_back(tokens.back());
        tokens.pop_back();
    }
//    TokenWriter *writer = new TokenWriter(sortedTokens);
//    writer->writeTokens();
    
//    program * sets = new program(sortedTokens);
//    vector<terminals*> myTokens;
//    vector<myRules*> rule;
//
//    sets->parseInput(myTokens, rule);
//    vector<first*> firsts = sets->doFirst(rule, myTokens);
//
//    for (size_t i = 0; i < firsts.size(); i++) {
//        if (!firsts.at(i)->term) {
//            cout<<"FIRST("<<firsts.at(i)->t->literal_text<<") = { ";
//            for (size_t j = 0; j < firsts.at(i)->symbols.size(); j++) {
//                cout<<firsts.at(i)->symbols.at(j)->t->literal_text;
//                if (j < (firsts.at(i)->symbols.size() - 1))
//                    cout<<", ";
//            }
//            cout<<" }\n";
//        }
//    }
	
    ParseMULR *parser = new ParseMULR(sortedTokens, sortedIn);
    parser->executeParse();
    
    while (!sortedTokens.empty()) {
        delete sortedTokens.back();
        sortedTokens.pop_back();
    }
//    writer->~TokenWriter();
    
    return 0;
}
