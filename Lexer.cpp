#include "Lexer.h"
#include <iostream>
#include <cctype>
#include <vector>


Lexer::Lexer(const std::string& source) {
    this->source = source;
    this->start = 0;
    this->current = 0;
    this->line = 1;


    
    keywords["var"] = TokenType::VAR;
    keywords["if"] = TokenType::IF;
    keywords["while"] = TokenType::WHILE;
    keywords["defer"] = TokenType::DEFER;

    keywords["print"] = TokenType::PRINT; 
}

// is it end of code
bool Lexer::isAtEnd() {
    return current >= source.length();
}

char Lexer::peek(){
    if(current>=source.length()) return '\0';
    return source[current];
}

void Lexer::identifier(){
    while (isalnum(peek())) advance();


    std::string text = source.substr(start, current - start);
    TokenType type;

    if (keywords.find(text) != keywords.end()) {
        type = keywords[text];
    } else {
        type = TokenType::IDENTIFIER; 
    }
    
    addToken(type);
}


void Lexer::addToken(TokenType type) {

    std::string text = source.substr(start, current - start);
    tokens.push_back({type, text, line});
}

void Lexer::number(){
    
 
    while (isdigit(peek())) advance();
   if (peek() == '.' && isdigit(source[current + 1])) {
        advance(); 


        while (isdigit(peek())) advance();
    }

    if (peek() == '.') {
        std::cerr << "ERROR: Multiple points in a numerical expression! Line: " << line << std::endl;
        
        return; 
    }

    addToken(TokenType::NUMBER);
        
    

}

char Lexer::advance() {
    return source[current++];
}

std::vector<Token> Lexer::tokenize(){

   

    while (!isAtEnd()){
        start = current;
        scanToken();
    }

    tokens.push_back({TokenType::END_OF_FILE, "", line});
    
    return tokens;
}

void Lexer::scanToken() {
    char c = advance(); //current++

    switch (c) {
        case '(': addToken(TokenType::LPAREN); break;
        case ')': addToken(TokenType::RPAREN); break;
        case '{': addToken(TokenType::LBRACE); break;
        case '}': addToken(TokenType::RBRACE); break;
        case ',': addToken(TokenType::COMMA); break; // will add token.h
        case '.': addToken(TokenType::DOT); break;   // will add token.h
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;


        case '=':
            // If there is also an = sign it means == Equals.
            // Otherwise it just means = Assignment.

            // For now, we'll keep it simple and return future for it
            addToken(TokenType::EQUAL); 
            break;

            //Checikng comment line
        case '/':
            // İf next character is / it is a comment line
            if (peek() == '/') {
                // forward until line ends
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH); // Dividing symbl
            }
            break;

        // Space, Tab
        case ' ':
        case '\r':
        case '\t':

            break;

        case '\n': 
            line++; 
            break;

        default:
            if (isdigit(c)) {
                number();
            }
            // Character? or _
            else if (isalpha(c)) {
                identifier();
            }
            else {
                std::cerr << "Undefinded character: " << c << " line: " << line << std::endl;
            }
            break;
    }
}