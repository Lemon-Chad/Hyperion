cmake_minimum_required(VERSION 3.24)
project(Hyperion)

set(CMAKE_CXX_STANDARD 23)

add_executable(Hyperion src/main.cpp lib/lexer/lexer.cpp lib/lexer/lexer.h lib/parser/Parser.cpp lib/parser/Parser.h lib/parser/Node.cpp lib/parser/Node.h)
