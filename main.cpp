#include <iostream>
#include <vector>
#include "Lexer.h"

int main() {
    // Test code
    std::string code = "var x = 10; print x;";

    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    for (const Token& token : tokens) {
        std::cout << "Tip: " << (int)token.type 
                  << " | Deger: " << token.text << std::endl;
    }

    return 0;
}