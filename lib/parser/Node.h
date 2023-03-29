//
// Created by Jack Smith on 3/28/23.
//

#ifndef HYPERION_NODE_H
#define HYPERION_NODE_H

#include <string>
#include <format>
#include "../lexer/lexer.h"

namespace hyperion {

    typedef enum {
        AST_NUMBER, AST_BINOP, AST_UNARYOP,
    } NodeType;

    class Node {
    public:
        const NodeType type;
        explicit Node(NodeType type) : type(type) {}
        // When we start compiling, this virtual method will manifest
        // virtual void codegen() = 0;
        virtual std::string show() = 0;
    };

    class NumberNode: public Node {
    public:
        NumberNode(const char* val, const bool is_float) :
            Node(AST_NUMBER), is_float(is_float), val(val) {}
        std::string show() override {
            return val;
        }
    private:
        const bool is_float;
        const char* val;
    };

    class BinOpNode: public Node {
    public:
        BinOpNode(Node *left, Node *right, const TokenType op) :
            Node(AST_BINOP), left(left), right(right), op(op) {}
        std::string show() override {
            std::string ops = &op;
            std::string lhs = left->show();
            std::string rhs = right->show();

            return "(" + lhs + ops + rhs + ")";
        }
    private:
        Node *left;
        Node *right;
        const char op;
    };

    class UnaryOpNode: public Node {
    public:
        UnaryOpNode(Node *operand, const char op) :
                Node(AST_UNARYOP), operand(operand), op(op) {}
        std::string show() override {
            std::string ops = &op;
            std::string operands = operand->show();

            return "(" + ops + operands + ")";
        }
    private:
        Node *operand;
        const char op;
    };

} // hyperion

#endif //HYPERION_NODE_H
