//
//  TokenChecker.cpp
//  MULR
//
//  Created by David Edwards on 7/15/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#include "TokenChecker.hpp"
#include <iostream>
//#define COMMENT_MODE 1

bool TokenChecker::checkInput(vector<Token*> &input, TokenBuilder builder, char ch, string &id_String, string &int_string, string &float_string, Token *t, bool &scanForId, bool &scanForPHP, bool &checkForArrow, bool &checkForGTEQ, bool &checkForLTEQ, bool &parsingInt, bool &parsingFloat, int &position, int &line_number, int &token_id, CHECK_TYPE ctype, bool comment, bool inSingleQuote, bool inDoubleQuote, string &singleQuoteString, string &doubleQuoteString, string &commentString) {
    
    bool breakout = false;
    
    
    switch (ctype) {
        case DOT_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForId) {
                t = builder.buildToken(id_String, position, token_id, line_number, ID);
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                if (!comment)
                    t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                else
                    t = builder.buildToken(id_String, position, token_id, line_number, COMMA);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (parsingInt) { //this int just became a float (notice that floats must start with an int [ex: 0.3 .3 is not a float
                parsingFloat = true; //but a dot and an int
                parsingInt = false;
                float_string = int_string + ".";
                int_string = "";
                breakout = true;
            } else if (parsingFloat) { //this float just got cut off by a '.' (I don't care about syntax in the lexer though)
                parsingFloat = false;
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                float_string = "";
            }
            break;
        case STANDARD_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForId) {
                if (id_String == "MULR") {
                    t = builder.buildToken(id_String, position, token_id, line_number, KEYWORD);
                } else {
                    t = builder.buildToken(id_String, position, token_id, line_number, ID);
                }
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                int_string = "";
                input.push_back(t);
                parsingInt = false;
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                float_string = "";
            }
            break;
		case QUOTE_TYPE:
			if (inSingleQuote) {
//				singleQuoteString+=ch;
				return true;
			} else if (inDoubleQuote) {
//				doubleQuoteString+=ch;
				return true;
			} else if (comment) {
				commentString+=ch;
				return true;
			}
			if (scanForId) {
				if (id_String == "MULR") {
					t = builder.buildToken(id_String, position, token_id, line_number, KEYWORD);
				} else {
					t = builder.buildToken(id_String, position, token_id, line_number, ID);
				}
				input.push_back(t);
				scanForId = false;
				id_String = "";
			} else if (scanForPHP) {
				t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
				input.push_back(t);
				scanForPHP = false;
				id_String = "";
			} else if (checkForArrow) {
				t = builder.buildToken("-", position, token_id, line_number, MINUS);
				input.push_back(t);
				checkForArrow = false;
			} else if (checkForGTEQ) {
				t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
				input.push_back(t);
				checkForGTEQ = false;
			} else if (checkForLTEQ) {
				t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
				input.push_back(t);
				checkForLTEQ = false;
			} else if (parsingInt) {
				t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
				int_string = "";
				input.push_back(t);
				parsingInt = false;
			} else if (parsingFloat) {
				t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
				input.push_back(t);
				float_string = "";
			}
			break;
        case ARROW_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForId) {
                t = builder.buildToken(id_String, position, token_id, line_number, ID);
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("->", position, token_id, line_number, ARROW);
                input.push_back(t);
                checkForArrow = false;
                breakout = true;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                input.push_back(t);
                parsingInt = false;
                int_string = "";
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                parsingFloat = false;
                float_string = "";
            }
            break;
        case NUMERIC_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForId || scanForPHP) {
                id_String += ch;
                breakout = true;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (checkForArrow) { //this is a negative number
                checkForArrow = false;
                int_string = "-";
            } else if (parsingFloat) {
                float_string += ch;
                breakout = true;
            }
            break;
        case DEFAULT_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForPHP || scanForId) {
                id_String += ch;
                breakout = true;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                input.push_back(t);
                parsingInt = false;
                int_string = "";
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                parsingFloat = false;
                float_string = "";
            }
            break;
        case EQUALS_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForId) {
                t = builder.buildToken(id_String, position, token_id, line_number, ID);
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">=", position, token_id, line_number, GTEQ);
                input.push_back(t);
                checkForGTEQ = false;
                breakout = true;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<=", position, token_id, line_number, LTEQ);
                input.push_back(t);
                checkForLTEQ = false;
                breakout = true;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                int_string = "";
                input.push_back(t);
                parsingInt = false;
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                float_string = "";
            }
            break;
        case EOF_TYPE: {
            if (comment) {
                if (COMMENT_MODE == 1) {
                    t = builder.buildToken(commentString, position, token_id, line_number, COMMENT);
                    input.push_back(t);
                    commentString = "";
                }
            } else if (inSingleQuote) {
                cerr<<"UNFINISHED SINGLE QUOTE STRING FOUND EOF"<<endl;
                exit(1);
            } else if (inDoubleQuote) {
                cerr<<"UNFINISHED DOUBLE QUOTE STRING FOUND EOF"<<endl;
                exit(1);
            }
            if (scanForId) {
                t = builder.buildToken(id_String, position, token_id, line_number, ID);
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                int_string = "";
                input.push_back(t);
                parsingInt = false;
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                float_string = "";
            }
            break;
        }
        case NEWLINE_TYPE: {
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return true;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return true;
            } else if (comment) {
                if (commentString.at(1) == '/' && COMMENT_MODE == 1) {
                    t = builder.buildToken(commentString, position, token_id, line_number, COMMENT);
                    input.push_back(t);
                }
                else if (commentString.at(1) == '*')
                    return true;
                
                return false;
            }
            if (scanForId) {
                t = builder.buildToken(id_String, position, token_id, line_number, ID);
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                int_string = "";
                input.push_back(t);
                parsingInt = false;
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                float_string = "";
            }
            break;
        }
        case ESCAPE_TYPE:
            if (inSingleQuote) {
                singleQuoteString+=ch;
                return false;
            } else if (inDoubleQuote) {
                doubleQuoteString+=ch;
                return false;
            } else if (comment) {
                commentString+=ch;
                return true;
            }
            if (scanForId) {
                t = builder.buildToken(id_String, position, token_id, line_number, ID);
                input.push_back(t);
                scanForId = false;
                id_String = "";
            } else if (scanForPHP) {
                t = builder.buildToken(id_String, position, token_id, line_number, PHPVAR);
                input.push_back(t);
                scanForPHP = false;
                id_String = "";
            } else if (checkForArrow) {
                t = builder.buildToken("-", position, token_id, line_number, MINUS);
                input.push_back(t);
                checkForArrow = false;
            } else if (checkForGTEQ) {
                t = builder.buildToken(">", position, token_id, line_number, GREATER_THAN);
                input.push_back(t);
                checkForGTEQ = false;
            } else if (checkForLTEQ) {
                t = builder.buildToken("<", position, token_id, line_number, LESS_THAN);
                input.push_back(t);
                checkForLTEQ = false;
            } else if (parsingInt) {
                t = builder.buildToken(int_string, position, token_id, line_number, INTEGER);
                int_string = "";
                input.push_back(t);
                parsingInt = false;
            } else if (parsingFloat) {
                t = builder.buildToken(float_string, position, token_id, line_number, FLOAT);
                input.push_back(t);
                float_string = "";
            }
            break;
        default:
            cerr<<"UKNOWN CHECK TYPE"<<endl;
            break;
    }
    
    
    return breakout;
}
