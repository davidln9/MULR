//
//  TokenBuilder.cpp
//  MULR
//
//  Created by David Edwards on 7/15/18.
//  Copyright © 2018 David Edwards. All rights reserved.
//

#include "TokenBuilder.hpp"

Token * TokenBuilder::buildToken(string ch, int &position, int &id, int line, TOKEN_TYPE type) {
    
    Token * t = new Token;
    t->type = type;
    t->start_position = position;
    position += ch.length()-1;
    t->end_position = position;
    position++;
    t->literal_text = ch;
    t->line_no = line;
    id++;
    t->token_id = id;
    
    return t;
}
