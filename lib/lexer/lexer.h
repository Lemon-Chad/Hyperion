//
// Created by Jack Smith on 3/28/23.
//

#ifndef HYPERION_LEXER_H
#define HYPERION_LEXER_H

#include <vector>

namespace hyperion {

    const char* KEYWORDS[] = {
            "if",
            "els",
            "fun",
            "cls",
            "let",
            "val",
            "nll",
            "for",
            "while",
            "do",
    };

    typedef enum {
        TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH,

        TOKEN_INT, TOKEN_FLOAT,

        TOKEN_KEYWORD, TOKEN_IDENTIFIER,
    } TokenType;

    typedef struct {
        TokenType type;
        const char* start;
        int length;
        int line;
    } Token;

    class Lexer {
    public:
        Lexer(char* text) {
            this->text = text;
            this->index = -1;
            this->line = 0;
            this->len = strlen(text);
            this->current = ' ';
            this->advance();
        }

        std::vector<Token> lex() {
            while (index < len) {
                if (isdigit(current)) {
                    make_number();
                } else if (isalpha(current)) {
                    make_identifier();
                } else {
                    Token token;

                    token.start = &current;
                    token.length = 1;
                    token.line = line;

                    switch (current) {
                        case '+':
                            token.type = TOKEN_PLUS;
                            break;
                        case '-':
                            token.type = TOKEN_MINUS;
                            break;
                    }
                    tokens.push_back(token);
                }
                advance();
            }
            return tokens;
        }

    private:
        char* text;
        std::vector<Token> tokens;
        int index;
        int line;
        size_t len;
        char current;

        void advance() {
            index++;
            current = text[index];
        }

        char peek(int dist) {
            return text[index + dist];
        }

        void make_number() {

        }

        void make_identifier() {

        }
    };

} // hyperion_lexer

#endif //HYPERION_LEXER_H
