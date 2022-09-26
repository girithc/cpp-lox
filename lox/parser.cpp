#include "token.cpp"
#include "expression.cpp"

#include <string>
#include <iterator>
#include <list>

using namespace std;


class Parser {

    private:
    
    list<Token> tokens;
    int current = 0;

    Token previous()
    {
        list<Token>::iterator i = tokens.begin;
        advance(i, current-1);
        return *i;
    }

    Token peek() 
    {
        list<Token>::iterator i = tokens.begin;
        advance(i, current);
        return *i;
    }

    bool isNotEnd()
    {
        return !(peek(type) == TokenEOF);
    }

    Token advanceToken() 
    {
        if(isNotEnd()) current += 1;
        return previous();
    }

    bool check(TokenType type)
    {
        if(isNotEnd())
        {
            return (peek().type == type);
        }
        return false;
    }

    bool match(TokenType[] types)
    {
        for (TokenType t: types)
        {
            if(check(type))
            {
                advanceToken();
                return true;
            }
        }
        return false;
    }

    Expr equality()
    {
        Expr expr = comparison();

        while(match(BANG_EQUAL, EQUAL_EQUAL))
        {
            Token operator = previous();
            Expr right = comparison();
            Expr tempExpr(expr, operator, right);
            right = tempExpr.binary();
        }
    }

    Expr expression()
    {
        return equality();
    }

    public:

    void Parser(list<Token> t)
    {
        tokens = t;
    }
    
};