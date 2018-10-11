//
//  PDA.cpp
//  MULR
//
//  Created by David Edwards on 7/26/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#include "PDABuilder.hpp"
#include "ParseMULR.hpp"
#include <iostream>
using namespace std;

PDABuilder::PDABuilder(TerminalRule * start, vector<TerminalRule*> functions) {
    this->start = start;
    this->functions = functions;
}


regex * PDABuilder::constructPDA() {
    
    convertToPDA(start->expression);
    
    for (size_t i = 0; i < functions.size(); i++) {
        convertToPDA(functions.at(i)->expression);
    }
    
    node * temp = start->expression->starting;
    vector<node*> droppedVals;
    vector<node*> visited;
    
    bool n1, n2;
    
    vector<node*> decisionPt;
    
    while (1) {
        visited.push_back(temp);
        n1 = false;
        n2 = false;
        if (temp->neighbor1 != NULL) {
            n1 = true;
        }
        if (temp->neighbor2 != NULL) {
            n2 = true;
        }
        if (n1 && n2) {
            decisionPt.push_back(temp);
        }
        
        if (n1) {
            if (temp->label1->type == NON_TERMINAL && temp->label1->literal_text == start->name) {
                droppedVals.push_back(temp->neighbor1);
                temp->neighbor1 = start->expression->starting->neighbor1;
                temp->label1->type = EPSILON;
                temp->label1->pop_symbol = "_";
                temp->label1->push_symbol = start->name;
                temp = droppedVals.back();
            } else if (temp->label1->type == NON_TERMINAL) {
                regex * gr = lookupFunction(temp->label1->literal_text);
                droppedVals.push_back(temp->neighbor1);
                temp->neighbor1 = gr->starting;
                temp->label1->type = EPSILON;
                temp->label1->push_symbol = temp->label1->literal_text;
                temp->label1->pop_symbol = "_";
                
                transition * tr = new transition;
                tr->neighbor = temp;
                tr->label = new label;
                tr->label->type = EPSILON;
                tr->label->pop_symbol = start->name;
                tr->label->push_symbol = "_";
                gr->accepting->optRet->transition.push_back(tr);
                temp = droppedVals.back();
            } else if (temp->label1->type == EPSILON && temp->label1->pop_symbol == "$") {
                while (!droppedVals.empty()) {
                    
                    transition * t = new transition;
                    t->neighbor = droppedVals.back();
                    t->label = new label;
                    t->label->type = EPSILON;
                    t->label->pop_symbol = start->name;
                    t->label->push_symbol = "_";
                    temp->optRet->transition.push_back(t);
                    
                    droppedVals.pop_back();
                }
                if (!decisionPt.empty()) {
                    temp = decisionPt.back()->neighbor2;
                    decisionPt.pop_back();
                } else {
                    temp = temp->neighbor1;
                }
            } else {
                temp = temp->neighbor1;
            }
        } else if (!decisionPt.empty()) {
            temp = decisionPt.back()->neighbor2;
            decisionPt.pop_back();
        } else {
            break;
        }
        
    }
    return NULL;
}

regex * PDABuilder::lookupFunction(string function) {
    
    for (size_t i = 0; i < functions.size(); i++) {
        if (functions.at(i)->name == function) {
            return functions.at(i)->expression;
        }
    }
    
    cerr<<"Reference to undefined function: "<<function<<endl;
    exit(1);
    return NULL;
}

void PDABuilder::convertToPDA(regex* in) { //adds a new start and accept state with stack symbols
    
    node * start = new node;
    start->label1 = new label;
    start->label1->type = EPSILON;
    start->label1->pop_symbol = "_";
    start->label1->push_symbol = "$";
    start->neighbor1 = in->starting;
    start->neighbor2 = NULL;
    start->label2 = NULL;
    
    in->starting = start;
    
    node * end = new node;
    end->label1 = NULL;
    end->label2 = NULL;
    end->neighbor1 = NULL;
    end->neighbor2 = NULL;
    in->accepting->optRet = new retCall;
    in->accepting->neighbor1 = end;
    in->accepting->label1 = new label;
    in->accepting->label1->type = EPSILON;
    in->accepting->label1->push_symbol = "_";
    in->accepting->label1->pop_symbol = "$";
    
    end->optRet = new retCall;
    in->accepting = end;
    
//    regex * R1 = new regex;
//    R1->starting = start;
//    R1->accepting = end;
//    return R1;
    
}
