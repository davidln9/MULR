//
//  TokenChecker.hpp
//  MULR
//
//  Created by David Edwards on 7/15/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

/*
 
 lkjljljljljljl
 
 */

#ifndef TokenChecker_hpp
#define TokenChecker_hpp

#include <stdio.h>
#include "MULRLexer.hpp"
#include "TokenBuilder.hpp"
using namespace std;

class TokenChecker {
public:
    bool checkInput(vector<Token*> &input, TokenBuilder builder, char ch, string &id_String, string &int_string, string &float_string, Token *t, bool &scanForId, bool &scanForPHP, bool &checkForArrow, bool &checkForGTEQ, bool &checkForLTEQ, bool &parsingInt, bool &parsingFloat, int &position, int &line_number, int &token_id, CHECK_TYPE ctype, bool comment, bool inSingleQuote, bool inDoubleQuote, string &singleQuoteString, string &doubleQuoteString, string &commentString);
private:
    
};

#endif /* TokenChecker_hpp */
