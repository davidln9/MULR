//
//  RegExp.cpp
//  MULR
//	Open Source Software
//

#include "RegExp.hpp"
#include <iostream>
using namespace std;
RegExp::RegExp() {
    feed = feed->getInstance();
}

//exp -> ; (empty)
//exp -> (exp)[*+?]? exp
//exp -> exp[*+?]? exp (concatenate)
//exp -> exp[*+?]? | exp (or)
//exp -> id

regex * RegExp::parse_regex_concat() {
	
	Token * t = feed->getToken();
	if (t->type == SINGLE_QUOTE_STRING || t->type == DOUBLE_QUOTE_STRING || t->type == PHPVAR || t->type == ID) {
		node * start = new node;
		node * end = new node;
		start->label1 = new label;
		if (t->type == PHPVAR) {
			start->label1->type = NON_TERMINAL;
			terminals.insert(t);
		} else {
			start->label1->type = TERMINAL;
		}
		start->label1->literal_text = t->literal_text;
		
		start->neighbor1 = end;
		start->neighbor2 = NULL;
		start->label2 = NULL;
		
		end->neighbor1 = NULL;
		end->neighbor2 = NULL;
		end->label1 = NULL;
		end->label2 = NULL;
		regex * r = new regex;
		r->starting = start;
		r->accepting = end;
		return r;
	}
	
	return NULL;
}

set<Token*> RegExp::getTerminals() {
	return this->terminals;
}

regex * RegExp::parse_regex() {
	Token * t = feed->getToken();
	
	regex * R1 = new regex;
	node * starts = new node;
	node * ends = new node;
	starts->loop = false;
	ends->loop = false;
	ends->label1 = NULL;
	ends->label2 = NULL;
	ends->neighbor1 = NULL;
	ends->neighbor2 = NULL;
	
	starts->label1 = new label;
	starts->label1->type = EPSILON;
	starts->neighbor1 = ends;
	
	starts->neighbor2 = NULL;
	starts->label2 = NULL;
	
	R1->starting = starts;
	R1->accepting = ends;
	
	while (t->type != SEMICOLON) {
		if (t->type == ID || t->type == PHPVAR || t->type == SINGLE_QUOTE_STRING || t->type == DOUBLE_QUOTE_STRING) {
			feed->ungetToken(t);
			regex * temp = parse_regex_concat();
			
			t = feed->getToken();
			
			if (t->type == PLUS || t->type == STAR || t->type == QUESTION) {
				node * node1 = new node;
				node * node2 = new node;
				
				node1->loop = false;
				node2->loop = false;
				
				node2->neighbor1 = NULL;
				node2->neighbor2 = NULL;
				node2->label1 = NULL;
				node2->label2 = NULL;
				
				node1->label1 = new label;
				node1->label1->type = EPSILON;
				node1->neighbor1 = temp->starting;
				
				if (t->type == STAR || t->type == QUESTION) { // an option to bypass neighbor1
					node1->label2 = new label;
					node1->label2->type = EPSILON;
					node1->neighbor2 = node2;
				} else {
					node1->neighbor2 = NULL;
					node1->label2 = NULL;
				}
				
				temp->accepting->neighbor1 = node2;
				temp->accepting->label1 = new label;
				temp->accepting->label1->type = EPSILON;
				
				if (t->type == STAR || t->type == PLUS) { //the loop feature
					temp->accepting->neighbor2 = temp->starting;
					temp->accepting->loop = true;
					temp->accepting->label2 = new label;
					temp->accepting->label2->type = EPSILON;
				} else {
					temp->accepting->neighbor2 = NULL;
					temp->accepting->label2 =  NULL;
				}
				temp->accepting = node2;
				temp->starting = node1;
				t = feed->getToken();
			}
			
			R1->accepting->neighbor1 = temp->starting;
			
			R1->accepting->label1 = new label;
			R1->accepting->label1->type = EPSILON;
			R1->accepting = temp->accepting;
		} else if (t->type == OR) {
			regex * R2 = parse_regex();
			node * start = new node;
			node * end = new node;
			
			start->loop = false;
			end->loop = false;
			
			end->label1 = NULL;
			end->label2 = NULL;
			end->neighbor1 = NULL;
			end->neighbor2 = NULL;
			
			start->label1 = new label;
			start->label2 = new label;
			start->label1->type = EPSILON;
			start->label2->type = EPSILON;
			
			start->neighbor1 = R1->starting;
			start->neighbor2 = R2->starting;
			
			R1->accepting->label1 = new label;
			R1->accepting->label1->type = EPSILON;
			R1->accepting->neighbor1 = end;
			R1->accepting->neighbor2 = NULL;
			
			R1->starting = start;
			R1->accepting = end;
			
			R2->accepting->label1 = new label;
			R2->accepting->label1->type = EPSILON;
			R2->accepting->neighbor1 = end;
			
			t = feed->getToken();
			
		} else if (t->type == LPAREN) {
			regex * temp = parse_regex();
			t = feed->getToken();
			if (t->type == RPAREN) {
				
				t = feed->getToken();
				if (t->type == PLUS || t->type == STAR || t->type == QUESTION) {
					node * node1 = new node;
					node * node2 = new node;
					
					node1->loop = false;
					node2->loop = false;
					
					node2->neighbor1 = NULL;
					node2->neighbor2 = NULL;
					node2->label1 = NULL;
					node2->label2 = NULL;
					
					node1->label1 = new label;
					node1->label1->type = EPSILON;
					node1->neighbor1 = temp->starting;
					
					if (t->type == STAR || t->type == QUESTION) { // an option to bypass neighbor1
						node1->label2 = new label;
						node1->label2->type = EPSILON;
						node1->neighbor2 = node2;
					} else {
						node1->neighbor2 = NULL;
						node1->label2 = NULL;
					}
					
					temp->accepting->neighbor1 = node2;
					temp->accepting->label1 = new label;
					temp->accepting->label1->type = EPSILON;
					
					if (t->type == STAR || t->type == PLUS) { // the loop feature
						temp->accepting->neighbor2 = temp->starting;
						temp->accepting->loop = true;
						temp->accepting->label2 = new label;
						temp->accepting->label2->type = EPSILON;
					} else {
						temp->accepting->neighbor2 = NULL;
						temp->accepting->label2 =  NULL;
					}
					temp->accepting = node2;
					temp->starting = node1;
					t = feed->getToken();
				}
				
				R1->accepting->neighbor1 = temp->starting;
				R1->accepting->label1 = new label;
				R1->accepting->label1->type = EPSILON;
				
				R1->accepting = temp->accepting;
				
			} else {
				cerr<<"Expected RPAREN"<<endl;
				exit(32);
				return NULL;
			}
		} else if (t->type == RPAREN) {
			feed->ungetToken(t);
			return R1;
		}
	}
	
	feed->ungetToken(t);
	return R1;
}
