//
//  TokenWriter.cpp
//  MULR
//	Open Source Software
//

#include "TokenWriter.hpp"
using namespace std;

TokenWriter::TokenWriter(vector<Token*> tokens) {
    this->tokens = tokens;
}

TokenWriter::~TokenWriter() {
    while (!tokens.empty()) {
        Token *t = tokens.back();
        delete t;
        tokens.pop_back();
    }
}
void TokenWriter::writeTokens() {
    string ttype;
    for (size_t i = 0; i < tokens.size(); i++) {
        
        switch (tokens.at(i)->type) {
            case LPAREN:
                ttype = "LPAREN";
                break;
            case RPAREN:
                ttype = "RPAREN";
                break;
            case ID:
                ttype = "ID";
                break;
            case SEMICOLON:
                ttype = "SEMICOLON";
                break;
            case COLON:
                ttype = "COLON";
                break;
            case HASHTAG:
                ttype = "HASHTAG";
                break;
            case LBRACE:
                ttype = "LBRACE";
                break;
            case RBRACE:
                ttype = "RBRACE";
                break;
            case LBRACKET:
                ttype = "LBRACKET";
                break;
            case RBRACKET:
                ttype = "RBRACKET";
                break;
            case EQUALS:
                ttype = "EQUALS";
                break;
            case STAR:
                ttype = "STAR";
                break;
            case PLUS:
                ttype = "PLUS";
                break;
            case NOT:
                ttype = "NOT";
                break;
            case PHPVAR:
                ttype = "PHPVAR";
                break;
            case COMMA:
                ttype = "COMMA";
                break;
            case OR:
                ttype = "OR";
                break;
            case AND:
                ttype = "AND";
                break;
            case MINUS:
                ttype = "MINUS";
                break;
            case ARROW:
                ttype = "ARROW";
                break;
            case GREATER_THAN:
                ttype = "GREATER_THAN";
                break;
            case GTEQ:
                ttype = "GREQ";
                break;
            case LESS_THAN:
                ttype = "LESS_THAN";
                break;
            case LTEQ:
                ttype = "LTEQ";
                break;
            case MODULO:
                ttype = "MODULO";
                break;
            case HAT:
                ttype = "HAT";
                break;
            case DOT:
                ttype = "DOT";
                break;
            case INTEGER:
                ttype = "INTEGER";
                break;
            case FLOAT:
                ttype = "FLOAT";
                break;
            case NEWLINE:
                ttype = "NEWLINE";
                break;
            case TAB:
                ttype = "TAB";
                break;
            case QUESTION:
                ttype = "QUESTION";
                break;
            case ESCAPE_CHAR:
                ttype = "ESCAPE_CHAR";
                break;
            case WS:
                ttype = "WS";
                break;
            case AMPERSAND:
                ttype = "AMPERSAND";
                break;
            case KEYWORD:
                ttype = "KEYWORD";
                break;
            case COMMENT:
                ttype = "COMMENT";
                break;
            case SINGLE_QUOTE_STRING:
                ttype = "SINGLE_QUOTE_STRING";
                break;
            case DOUBLE_QUOTE_STRING:
                ttype = "DOUBLE_QUOTE_STRING";
                break;
        }
        
        if (tokens.at(i)->start_position == tokens.at(i)->end_position) {
            cout<<"{TOKEN["<<tokens.at(i)->token_id<<"]"<<"<"<<tokens.at(i)->line_no<<","<<tokens.at(i)->start_position<<">"
                <<", TYPE: "<<ttype<<", LITERAL_TEXT: \'"<<tokens.at(i)->literal_text<<"\'}"<<endl;
        } else {
            cout<<"{TOKEN["<<tokens.at(i)->token_id<<"]"<<"<"<<tokens.at(i)->line_no<<","<<tokens.at(i)->start_position<<","
                <<tokens.at(i)->end_position<<">"<<", TYPE: "<<ttype<<", LITERAL_TEXT: \'"<<tokens.at(i)->literal_text
                <<"\'}"<<endl;
        }
    }
}
