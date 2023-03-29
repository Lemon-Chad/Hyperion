#include "../lib/lexer/lexer.h"
#include "../lib/parser/Parser.h"

static char* read_file(const char* path) {
    FILE* file = std::fopen(path, "rb");
    if (file == nullptr) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(file_size + 1);
    if (buffer == nullptr) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char **argv) {
    switch (argc) {
        case 0:
        case 1: {
            printf("Enter a filename to compile it!");
            break;
        }
        case 2: {
            char *text = read_file(argv[1]);
            hyperion::Lexer lexer = hyperion::Lexer(text);
            std::vector<hyperion::Token> toks = lexer.lex();

            for (hyperion::Token tok: toks) {
                if (tok.type == hyperion::TOKEN_EOF) {
                    break;
                }
                std::string val = hyperion::get_token_value(&tok);
                printf("['%s', %u]", tok.type == hyperion::TOKEN_NEWLINE ? "\\n" : val.c_str(), tok.type);
            }

            printf("\n");

            hyperion::Parser parser = hyperion::Parser(&toks[0], toks.size());
            std::vector<hyperion::Node*> nodes = parser.parse();

            for (hyperion::Node* node: nodes) {
                printf("%s, ", node->show().c_str());
            }

            break;
        }
        default: {
            fprintf(stderr, "Too many arguments, I don't know what to do!");
            exit(0);
        }
    }
    return 0;
}
