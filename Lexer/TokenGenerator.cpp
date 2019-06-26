//
//  TokenGenerator.cpp
//  MULR
//	Open Source Software
//

#include "TokenGenerator.hpp"
using namespace std;

TokenGenerator::TokenGenerator(vector<char> raw) {
    this->raw = raw;
}

TokenGenerator::~TokenGenerator() {
    
}

vector<Token*> TokenGenerator::getTokens() {
    vector<Token*> input;
    char inputChar;
    size_t INPUT_CLOSE = raw.size()-1;
    
    string id_String = "";
    string int_string = "";
    string float_string = "";
    string commentString = "";
    string singleQuoteString = "";
    string doubleQuoteString = "";
    
    bool scanForId = false;
    bool scanForPHP = false;
    bool checkForArrow = false;
    bool checkForGTEQ = false;
    bool checkForLTEQ = false;
    bool parsingInt = false;
    bool parsingFloat = false;
    bool negative_number = false;
    
    bool line_comment = false;
    bool block_comment = false;
    
    int position = 0;
    int line_number = 0;
    int token_id = -1;
    bool inSingleQuote = false;
    bool inDoubleQuote = false;
    
    string stringChar = "";
    
    Token * t;
    TokenChecker checker;
    TokenBuilder builder;

    for (size_t i = 0; i < raw.size(); i++) {
        
        inputChar = raw.at(i);
        
        bool comment = line_comment || block_comment;
        switch (inputChar) {
            case '\"' :
                checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, QUOTE_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString);
                if (inDoubleQuote) {
                    inDoubleQuote = false;
//                    doubleQuoteString+="\"";
                    t = builder.buildToken(doubleQuoteString, position, token_id, line_number, DOUBLE_QUOTE_STRING);
                    input.push_back(t);
                    doubleQuoteString = "";
                } else {
                    inDoubleQuote = true;
//                    doubleQuoteString = "\"";
                }
                break;
            case '\'' :
                checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, QUOTE_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString);
                if (inSingleQuote) {
                    inSingleQuote = false;
//                    singleQuoteString+="\'";
                    t = builder.buildToken(singleQuoteString, position, token_id, line_number, SINGLE_QUOTE_STRING);
                    input.push_back(t);
                    singleQuoteString = "";
                } else {
                    inSingleQuote = true;
                }
                break;
            case '.' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, DOT_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken(".", position, token_id, line_number, DOT);
                input.push_back(t);
                break;
            case '*': //standard
				if (!checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
					
					t = builder.buildToken("*", position, token_id, line_number, STAR);
					input.push_back(t);
				}
				if (block_comment && i < INPUT_CLOSE && raw.at(i+1) == '/') {
					commentString+="/";
					if (COMMENT_MODE == 1) {
						t = builder.buildToken(commentString, position, token_id, line_number, COMMENT);
						input.push_back(t);
					}
					i++;
					block_comment = false;
					commentString = "";
					break;
				} else if (block_comment) {
					break;
				}
                break;
            case '#': //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("#", position, token_id, line_number, HASHTAG);
                input.push_back(t);
                break;
            case '!' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("!", position, token_id, line_number, NOT);
                input.push_back(t);
                break;
            case '(' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("(", position, token_id, line_number, LPAREN);
                input.push_back(t);
                break;
            case ')' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken(")", position, token_id, line_number, RPAREN);
                input.push_back(t);
                break;
            case ':' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken(":", position, token_id, line_number, COLON);
                input.push_back(t);
                break;
            case ';' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken(";", position, token_id, line_number, SEMICOLON);
                input.push_back(t);
                break;
            case '{' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("{", position, token_id, line_number, LBRACE);
                input.push_back(t);
                break;
            case '}' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("}", position, token_id, line_number, RBRACE);
                input.push_back(t);
                break;
            case '[' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("[", position, token_id, line_number, LBRACKET);
                input.push_back(t);
                break;
            case ']' : //standard
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("]", position, token_id, line_number, RBRACKET);
                input.push_back(t);
                break;
            case '$' : //standard (all LHS rules will be led with this symbol [ex; $rule -
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                scanForPHP = true;
                break;
            case '=' : //not standard (lteq and gteq might be affected
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, EQUALS_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("=", position, token_id, line_number, EQUALS);
                input.push_back(t);
                break;
            case '`' :
                cerr<<"INVALID TOKEN \'`\'"<<endl;
                exit(1);
                break;
            case '/' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                if (i < raw.size()-1 && raw.at(i+1) == '/') {
                    commentString+="//";
                    line_comment = true;
                    i++;
                    break;
                } else if (i < raw.size()-1 && raw.at(i+1) == '*') {
                    commentString+="/*";
                    block_comment = true;
                    i++;
                    break;
                }
                break;
            case '+' :
                if (!checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
					t = builder.buildToken("+", position, token_id, line_number, PLUS);
					input.push_back(t);
                }
				
                break;
            case ',' :
				if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken(",", position, token_id, line_number, COMMA);
                input.push_back(t);
                break;
            case '|' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("*", position, token_id, line_number, OR);
                input.push_back(t);
                break;
            case '&' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("&", position, token_id, line_number, AND);
                input.push_back(t);
                break;
            case '-' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
//                t = builder.buildToken("-", position, token_id, line_number, PHPVAR);
                checkForArrow = true;
//                parsingInt = true;
                negative_number = true;
                break;
            case '\\' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, ESCAPE_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                if (inDoubleQuote && i < INPUT_CLOSE && raw.at(i+1) == '\"') {
//                    doubleQuoteString+='\\';
                    doubleQuoteString+='\"';
                    i++;
                } else if (inDoubleQuote && i < INPUT_CLOSE && raw.at(i+1) == '\'') {
                    doubleQuoteString+='\'';
                    i++;
                } else if (inSingleQuote && i < INPUT_CLOSE && raw.at(i+1) == '\'') {
//                    singleQuoteString+='\\';
                    singleQuoteString+='\'';
                    i++;
                }
                break;
            case '@' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("@", position, token_id, line_number, AMPERSAND);
                input.push_back(t);
                break;
            case '\n' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NEWLINE_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    position = 0;
                    line_number++;
                    break;
                }
                if (line_comment) {
                    line_comment = false;
                }
                if (PYTHON_MODE == 1 && !block_comment) {
                    t = builder.buildToken("<NEWLINE>", position, token_id, line_number, NEWLINE);
                    input.push_back(t);
                }
                line_number++;
                position = 0;
                break;
            case '\t' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                if (PYTHON_MODE == 1) {
                    t = builder.buildToken("<TAB>", position, token_id, line_number, TAB);
                    input.push_back(t);
                }
                break;
            case '>' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, ARROW_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                checkForGTEQ = true;
                break;
            case '<' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                checkForLTEQ = true;
                break;
            case ' ' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                if (PYTHON_MODE == 1) {
                    t = builder.buildToken(" ", position, token_id, line_number, WS);
                    input.push_back(t);
                }
                break;
            case '0' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '1' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '2' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '3' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '4' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '5' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '6' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '7':
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '8':
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '9' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, NUMERIC_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                parsingInt = true;
                int_string += inputChar;
                break;
            case '%' :
				if (!checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
					t = builder.buildToken("%", position, token_id, line_number, MODULO);
					input.push_back(t);
				}
                break;
            case '^' :
				if (!checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
						t = builder.buildToken("^", position, token_id, line_number, HAT);
						input.push_back(t);
				}
				
                break;
            case '?' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, STANDARD_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                t = builder.buildToken("?", position, token_id, line_number, QUESTION);
                input.push_back(t);
                break;
            case '\b' :
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, EOF_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                
                break;
            default:
                if (checker.checkInput(input, builder, inputChar, id_String, int_string, float_string, t, scanForId, scanForPHP, checkForArrow, checkForGTEQ, checkForLTEQ, parsingInt, parsingFloat, position, line_number, token_id, DEFAULT_TYPE, comment, inSingleQuote, inDoubleQuote, singleQuoteString, doubleQuoteString, commentString)) {
                    break;
                }
                if (!scanForPHP) {
                    scanForId = true;
                }
                id_String += inputChar;
                break;
        }
    }
    return input;
}
