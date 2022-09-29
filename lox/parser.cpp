#include "token.cpp"
#include "expr.cpp"

#include <string>
#include <iterator>
#include <list>

using namespace std;
/*
expression     → equality ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;

*/
class Parser{

    public:
    Parser(list<Token> t);

    private:
    //variables
    list<Token> tokens;
    int current = 0;

    //helper
    Token previous();
    Token peek(); 
    Token advanceToken();
    bool isNotEnd();
    bool check(TokenType t);
    bool match(list<TokenType> types);

    //parsing expression
    Expr equality();
    Expr expression();
    Expr comparison();
    Expr term();
    Expr factor();
    Expr unary();
    Expr primary();

    //panic mode
    Token consume(TokenType t, string message);
    string error(Token t, string message);
    void synchronize();
};

Parser::Parser(list<Token> t)
{
    tokens = t;
}

Expr 
Parser::expression()
{
    return equality();
}

Expr 
Parser::equality()
{
    Expr expr = comparison();
    
    list<TokenType> tt;
    tt.push_back(BANG_EQUAL);
    tt.push_back(EQUAL_EQUAL);

    while(match(tt))
    {
        Token op = previous();
        Expr r = comparison();
        
        expr = new Binary(expr, op, r);
        //string temp = e;
        //e = "";
        //e.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr 
Parser::comparison()
{
    Expr expr = term();
    
    list<TokenType> tt;
    tt.push_back(GREATER);
    tt.push_back(GREATER_EQUAL);
    tt.push_back(LESS);
    tt.push_back(LESS_EQUAL);

    while(match(tt))
    {
        Token op = previous();
        Expr r = term();
        
        expr = new Binary(expr, op, r);
        //string temp = c;
        //c = "";
        //c.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr 
Parser::term()
{
    Expr expr = factor();
    
    list<TokenType> tt;
    tt.push_back(MINUS);
    tt.push_back(PLUS);

    while(match(tt))
    {
        Token op = previous();
        Expr r = factor();
        
        expr = new Binary(expr, op, r);
        //string temp = t;
        //t = "";
        //t.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr
Parser::factor()
{
    Expr expr = unary();
    
    list<TokenType> tt;
    tt.push_back(SLASH);
    tt.push_back(STAR);

    while(match(tt))
    {
        Token op = previous();
        Expr r = unary();
        
        expr = new Binary(expr, op, r);
        //string temp = f;
        //f = "";
        //f.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr
Parser::unary()
{
    list<TokenType> tt;
    tt.push_back(BANG);
    tt.push_back(MINUS);

    while(match(tt))
    {
        Token op = previous();
        Expr r = unary();
        
        return new Unary(op, r);
        // return (op.tokenLiteral() + "," + r);
    }
    
    return primary();
}

string
Parser::primary()
{
    list<TokenType> t1, t2, t3, t4;

    t1.push_back(FALSE);
    if(match(t1)) return new Literal("FALSE");

    t2.push_back(TRUE);
    if(match(t2)) return new Literal("FALSE");

    t3.push_back(NIL);
    if(match(t3)) return new Literal("NIL");

    list<TokenType> tt;
    tt.push_back(NUMBER);
    tt.push_back(STRING);
    if(match(tt)) return new Literal(previous().tokenLiteral());

    t4.push_back(LEFT_PAREN);
    if(match(t4))
    {
        Expr expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression" );
        return new Grouping(expr);
    }

    throw error(peek(), "Expect expression");
}

bool 
Parser::match(list<TokenType> tt)
{
    list<TokenType>::iterator i;
    for (i = tt.begin(); i != tt.end(); i++)
    {
        if(check(*i))
        {
            advanceToken();
            return true;
        }
    }
    return false;
}

bool
Parser::check(TokenType t)
{
    if (!isNotEnd()) return peek().tokenType() == enum_str[t];
    
    return false;
}

Token
Parser::advanceToken()
{
    if(isNotEnd()) current += 1;
    return previous();
}

bool 
Parser::isNotEnd()
{
    return peek().tokenType() == "TokenEOF";
}

Token 
Parser::peek()
{
    list<Token>::iterator i;
    int tokenIndexCounter = 0;
    for (i = tokens.begin(); i != tokens.end(); i++)
    {
        
        if(tokenIndexCounter == current)
        {
            return *i;
        }
        tokenIndexCounter += 1;
    }
}

Token 
Parser::previous()
{
    list<Token>::iterator i;
    int tokenIndexCounter = 0;
    for (i = tokens.begin(); i != tokens.end(); i++)
    {
        
        if(tokenIndexCounter == (current-1))
        {
            return *i;
        }
        tokenIndexCounter += 1;
    }
}


// panic mode

Token
Parser::consume(TokenType t, string message)
{
    if (check(t)) return advanceToken();

    throw error(peek(), message);
}


string 
Parser::error(Token t, string message)
{
   return "Error: " + message + " token: " + t.tokenLiteral();
}

void 
Parser::synchronize() {
    advanceToken();

    while (isNotEnd()) {
      if (previous().tokenType() == "SEMICOLON") return;

      /*  
      switch (peek().tokenType()) {
        case "CLASS":
        case "FUN":
        case "VAR":
        case "FOR":
        case "IF":
        case "WHILE":
        case "PRINT":
        case "RETURN":
          return;
      }*/

      advanceToken();
    }
  }


//test
int main()
{
    cout << "Hello World";
    string a = enum_str[BANG_EQUAL];
    
    
    cout <<endl << a;
}
