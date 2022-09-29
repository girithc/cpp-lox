#include <iostream>
#include <sstream>
#include <string>

#include "tokenType.cpp"

using namespace std;

class Token {

    private:

    TokenType ttype;
    string lexeme;
    string literal;
    int line;


    public:

    Token()
    {
        this->lexeme = "";
        this->literal = "";
        line = 0;
    }


    Token(TokenType ttype, string lexeme, string literal, int line)
    {
        this->ttype = ttype;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;

        return ;
    }

    string toString()
    {
        stringstream sstr;
        sstr << enum_str[this->ttype] << " -- " << this->lexeme << " -- " << this->literal 
        << " -- " << this->line;
        return sstr.str();
    }

    string tokenType()
    {
        return enum_str[this->ttype];
    }
    string tokenLiteral()
    {
        return this->lexeme;
    }

};