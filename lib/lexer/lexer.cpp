//
// Created by Jack Smith on 3/28/23.
//

#include "lexer.h"

namespace hyperion {
    std::string get_token_value(Token tok) {
        char val[tok.length];
        memcpy(val, tok.start, tok.length);
        return val;
    }
} // hyperion_lexer