//
//  MULRLexer.hpp
//  MULR
//	Open Source Software
//

#ifndef MULRLexer_hpp
#define MULRLexer_hpp

#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#define PYTHON_MODE 0 //sends WS, TAB, and NEWLINE to parser
#define COMMENT_MODE 0 //sends COMMENTS to parser

enum TOKEN_TYPE {
    LPAREN, RPAREN, ID, SEMICOLON, COLON, HASHTAG,
    LBRACE, RBRACE, LBRACKET, RBRACKET, EQUALS, STAR, PLUS,
    NOT, PHPVAR, COMMA, OR, AND, MINUS, ARROW, GREATER_THAN, GTEQ,
    LESS_THAN, LTEQ, MODULO, HAT, DOT, INTEGER, FLOAT, NEWLINE, TAB,
    QUESTION, ESCAPE_CHAR, WS, AMPERSAND, KEYWORD, COMMENT,
    SINGLE_QUOTE_STRING, DOUBLE_QUOTE_STRING, END_OF_FILE
};

enum CHECK_TYPE {
    STANDARD_TYPE, EQUALS_TYPE, NUMERIC_TYPE, DOT_TYPE, ARROW_TYPE, DEFAULT_TYPE, EOF_TYPE, NEWLINE_TYPE, ESCAPE_TYPE, QUOTE_TYPE
};

typedef struct Token {
    int line_no;
    std::string literal_text;
    TOKEN_TYPE type;
    int token_id;
    int start_position;
    int end_position;
}Token;

class MULRLexer {
private:
    std::ifstream *in;
public:
    MULRLexer(std::ifstream &in);
    ~MULRLexer();
    std::vector<Token*> getTokens();
};

#endif /* MULRLexer_hpp */
