#include "Lexer.h"
#include <iostream>


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
    if(current>=source.lenght()) retunr "\0";
    return source[current];
}

char Lexer::advance() {
    return source[current++];
}


void Lexer::addToken(TokenType type) {

    std::string text = source.substr(start, current - start);
    tokens.push_back({type, text, line});
}

char Lexer::advance() {
    return source[current++];
}

std::vector<Token> Lexer::tokenize(){
    vector<Token> tokens;
    while (!isAtEnd()){
        start = current;
        scanToken();
    }
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

        case '\n': b:
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