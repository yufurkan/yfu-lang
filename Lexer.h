#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <map>
#include "Token.h"

class Lexer {
private:

    std::vector<Token> tokens;
    std::string source; 
    int pos = 0;        
    int line = 1;      
    int current=0;
    int start=0;
   
    std::map<std::string, TokenType> keywords;
    
    char peek();    
    bool isAtEnd();
    char advance();     
    void addToken(TokenType type); 
    void addToken(TokenType type, std::string text);
    
   
    void scanToken();      
    void string();          
    void number();           
    void identifier();

public:
    // Constructor
 Lexer(const std::string& source);

    std::vector<Token> tokenize();
};

#endif