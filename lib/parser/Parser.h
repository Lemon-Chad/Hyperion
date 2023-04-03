//
// Created by Jack Smith on 3/28/23.
//

#ifndef HYPERION_PARSER_H
#define HYPERION_PARSER_H

#include <vector>
#include "../lexer/lexer.h"
#include "Node.h"
#include <functional>

namespace hyperion {

    class Parser {
    public:
        explicit Parser(Token tokens[], size_t length) : tokens(tokens), current(nullptr) {
            index = -1;
            len = length;

            advance();
        }

        std::vector<Node*> parse() {
            std::vector<Node*> nodes;
            while (index < len && current->type != TOKEN_EOF) {
                nodes.push_back(expression());
                while (current->type == TOKEN_NEWLINE) {
                    advance();
                }
            }
            return nodes;
        }
    private:
        Token* tokens;
        int index;
        size_t len;
        Token* current;

        Node* expression() {
            return barithmetic();
        }

        Node* barithmetic() {
            return binop({ TOKEN_PLUS, TOKEN_MINUS, },
                         [this] -> Node* { return this->carithmetic(); });
        }

        Node* carithmetic() {
            return binop({ TOKEN_STAR, TOKEN_SLASH, },
                   [this] -> Node* { return this->parens(); });
        }

        Node* parens() {
            if (current->type == TOKEN_LPAREN) {
                consume(TOKEN_LPAREN, "(");
                Node* node = expression();
                consume(TOKEN_RPAREN, ")");
                return node;
            } else {
                return atom();
            }
        }

        Node* binop(const std::vector<TokenType>& ops, const std::function<Node*()>& func) {
            Node* lhs = func();
            while (std::find(ops.begin(), ops.end(), current->type) != ops.end()) {
                Token* op = consume();
                Node* rhs = func();
                lhs = new BinOpNode(lhs, rhs, op->type);
            }
            return lhs;
        }

        Node* atom() {
            // Since we only have numbers for now.
            if (current->type != TOKEN_FLOAT && current->type != TOKEN_INT)
                consume(TOKEN_FLOAT, "a number");
            std::string val = get_token_value(current);
            bool is_float = val.find('.', 0) != std::string::npos;
            Node* node = new NumberNode(val, is_float);
            advance();
            return node;
        }

        Token* consume(TokenType type, const std::string& expected) {
            Token* tok = current;
            if (tok->type != type) {
                fprintf(stderr, "%d:%d | Expected '%s', got '%s'.",
                        tok->line + 1, tok->line_index + 1,
                        expected.c_str(), get_token_value(tok).c_str());
                exit(0);
            }
            advance();
            return tok;
        }

        Token* consume() {
            Token* tok = current;
            advance();
            return tok;
        }

        Token* peek(int dist) {
            return &tokens[index + dist];
        }

        void advance() {
            current = &tokens[++index];
        }
    };

} // hyperion

#endif //HYPERION_PARSER_H
