#ifndef TOKEN_H
#define TOKEN_H

#include <string>


enum class TokenType {
 
    PLUS,       // +
    MINUS,      // -
    STAR,       // *
    SLASH,      // /
    EQUAL,      // =
    SEMICOLON,  // ;
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE,     // }
    COMMA,
    DOT,

    
    IDENTIFIER, 
    NUMBER,     
    
    // Keywords
    VAR,        // var 
    IF,         // if
    WHILE,      // while
    DEFER,      // defer (trasher)
    PRINT,      // print (ekrana basmak icin)

  
    END_OF_FILE
};


struct Token {
    TokenType type;
    std::string text; 
    int line;         // Which line 
};

#endif