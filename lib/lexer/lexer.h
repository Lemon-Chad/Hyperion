//
// Created by Jack Smith on 3/28/23.
//

#ifndef HYPERION_LEXER_H
#define HYPERION_LEXER_H

#include <vector>
#include <string>

namespace hyperion {

    const std::string KEYWORDS[] = {
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

        TOKEN_NEWLINE, TOKEN_SEMICOLON,

        TOKEN_EQ, TOKEN_DOUBLEEQ, TOKEN_LONGARROW,
    } TokenType;

    typedef struct {
        TokenType type;
        const char* start;
        size_t length;
        int line;
    } Token;

    class Lexer {
    public:
        explicit Lexer(char* text) {
            this->text = text;
            this->index = -1;
            this->line = 0;
            this->line_index = -1;
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
                } else if (iswspace(current) && current != '\n') {
                    advance();
                } else {
                    // This is for symbols, like +, -, =>, etc.
                    Token token;

                    token.start = text + index;
                    token.length = 1;
                    token.line = line;
                    symbol_type(&token);

                    tokens.push_back(token);
                }
            }
            return tokens;
        }

    private:
        char* text;
        std::vector<Token> tokens;
        size_t index;
        size_t len;
        int line;
        int line_index;
        char current;

        void advance() {
            index++;
            line_index++;
            current = text[index];
        }

        // Sets the type for the token
        // Used for symbols, like +, -, =>, etc.
        void symbol_type(Token* token) {
            switch (current) {
                case '+':
                    token->type = TOKEN_PLUS;
                    advance();
                    break;
                case '-':
                    token->type = TOKEN_MINUS;
                    advance();
                    break;
                case '*':
                    token->type = TOKEN_STAR;
                    advance();
                    break;
                case '/':
                    token->type = TOKEN_SLASH;
                    advance();
                    break;
                case '\n':
                    token->type = TOKEN_NEWLINE;
                    line++;
                    line_index = 0;
                    advance();
                    break;
                case ';':
                    token->type = TOKEN_SEMICOLON;
                    advance();
                    break;
                case '=':
                    token->type = TOKEN_EQ;
                    advance();
                    if (current == '=') {
                        token->type = TOKEN_DOUBLEEQ;
                        advance();
                        token->length++;
                        if (current == '>') {
                            token->type = TOKEN_LONGARROW;
                            advance();
                            token->length++;
                        }
                    }
                    break;
                default:
                    fprintf(stderr, "%d:%d | Unrecognized character \'%c\'.\n", line + 1, line_index + 1, current);
                    exit(0);
            }
        }

        char peek(int dist) {
            return text[index + dist];
        }

        // Creates a number token and
        // adds it to the list of tokens
        void make_number() {
            bool is_float = false;
            size_t length = 0;
            int ln = line;
            do {
                length++;
                advance();

                if (current == '.' && !is_float) {
                    is_float = true;
                    length++;
                    advance();
                }
            } while (isdigit(current));

            Token token{
                is_float ? TOKEN_FLOAT : TOKEN_INT,
                text + index - length,
                length,
                ln,
            };

            tokens.push_back(token);
        }

        // Creates an identifier/keyword token
        // and adds it to the list of tokens
        void make_identifier() {
            size_t length = 0;
            int ln = line;
            do {
                length++;
                advance();
            } while (isalnum(current));

            char identc[length];
            strncpy(identc, text + index - length, length);
            std::string ident = identc;

            bool is_keyword = std::find(std::begin(KEYWORDS), std::end(KEYWORDS), ident) != std::end(KEYWORDS);

            Token token{
                    is_keyword ? TOKEN_KEYWORD : TOKEN_IDENTIFIER,
                    text + index - length,
                    length,
                    ln,
            };

            tokens.push_back(token);
        }
    };

} // hyperion_lexer

#endif //HYPERION_LEXER_H
