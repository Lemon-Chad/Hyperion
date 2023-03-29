//
// Created by Jack Smith on 3/28/23.
//

#include "lexer.h"

namespace hyperion {
    std::string get_token_value(Token* tok) {
        char val[tok->length];
        memcpy(val, tok->start, tok->length);
        return val;
    }

    std::string show_token(Token* tok) {
        switch (tok.type) {
            case TOKEN_EOF:
                return "EOF";
            case TOKEN_LPAREN:
                return "(";
            case TOKEN_NEWLINE:
                return "\\n";
            case TOKEN_LONGARROW:
                return "==>";
            case TOKEN_PLUS:
                return "+";
            case TOKEN_IDENTIFIER:
            case TOKEN_FLOAT:
            case TOKEN_INT:
            case TOKEN_KEYWORD:
                return get_token_value(tok);
            case TOKEN_SEMICOLON:
                return ";";
            case TOKEN_DOUBLEEQ:
                return "==";
            case TOKEN_EQ:
                return "=";
            case TOKEN_MINUS:
                return "-";
            case TOKEN_RPAREN:
                return ")";
            case TOKEN_SLASH:
                return "/";
            case TOKEN_STAR:
                return "*";
        }
    }
} // hyperion_lexer