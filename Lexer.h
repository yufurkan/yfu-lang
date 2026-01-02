#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
private:


    std::string source; 
    int pos = 0;        
    int line = 1;      


    char current();    
    char peek();        
    void advance();     
    void addToken(TokenType type); 
    void addToken(TokenType type, std::string text);
    
   
   void scanToken();      
    void string();          
    void number();           
    void identifier();

public:
    // Constructor
    Lexer(std::string src) : source(src) {}
    

    std::vector<Token> tokenize();
};

#endif