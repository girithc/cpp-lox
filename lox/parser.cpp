
#include "interpreter.cpp"

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

/*
program        → statement* EOF ;
statement      → exprStmt
               | printStmt ;
exprStmt       → expression ";" ;
printStmt      → "print" expression ";" ;

program        → declaration* EOF ;
declaration    → varDecl
               | statement ;
statement      → exprStmt
               | printStmt ;
*/
class Parser{

    public:
    Parser(list<Token> t);

    list<Stmt*> parse()
    {
        list<Stmt*> stmtList;
        while(isNotEnd())
        {
            stmtList.push_back(declaration());
        }
        return stmtList;
    }

    private:
        //variables
        list<Token> tokens;
        int current = 0;

        //helper
        Token getToken(int index);
        Token peek(); 
        void advanceToken();
        bool isNotEnd();
        bool check(TokenType t);
        bool match(list<TokenType> types);

        //parsing expression
        Expr* equality();
        Expr* expression();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* primary();
        Expr* assignment();
        Expr* logicOr();
        Expr* logicAnd();

        //parsing stmt
        Stmt* statement();
        Stmt* ifStatement();
        Stmt* printStatement();
        Stmt* whileStatement();
        Stmt* forStatement();
        Stmt* expressionStatement();

        Stmt* declaration();
        Stmt* varDeclaration();
        list<Stmt*> block();


        //panic mode
        Token consume(TokenType t, string message);
        string error(Token t, string message);
        void synchronize();
};

Parser::Parser(list<Token> t)
{
    tokens = t;
}

Expr* 
Parser::expression()
{
    return assignment();
}

Stmt* 
Parser::declaration()
{
    try
    {
        cout << "Entered declaration()" << endl;
        list<TokenType> tt;
        tt.push_back(VAR);
        if (match(tt)) return varDeclaration();
        return statement();
    }
    catch(...)
    {
        throw invalid_argument("Parser error");
    }   
}

Stmt* 
Parser::varDeclaration()
{
    cout << "   Entered varDeclaration()" << endl;
    Token n = consume(IDENTIFIER, "Expect a variable name. ");
    Expr* init = NULL;

    list<TokenType> token_types;
    token_types.push_back(EQUAL);

    if(match(token_types)) init = expression();

    Token m = consume(SEMICOLON, "Expect ';' after a variable name. ");
    return new Var(n, init);
}

Stmt*
Parser::statement()
{
    list<TokenType> t1,t2, t3, t4, t5;

    t5.push_back(FOR);
    if(match(t5)) return forStatement();

    t1.push_back(IF);
    if(match(t1)) return ifStatement();

    t2.push_back(PRINT);
    if(match(t2)) return printStatement();

    t3.push_back(WHILE);
    if(match(t3)) return whileStatement();

    t4.push_back(LEFT_BRACE);
    if(match(t4)) return new Block(block());
   
    return expressionStatement();
}

Stmt*
Parser::forStatement()
{
    consume(LEFT_PAREN, "Expect '(' after a 'for'");
    Stmt* init;
    list<TokenType> t1, t2;
    t1.push_back(SEMICOLON);
    t2.push_back(VAR);

    //FOR(int i = 0; i < 10; i++)
    if(match(t1)) init = NULL;
    else if(match(t2)) init = varDeclaration();
    else init  = expressionStatement();

    //condition
    Expr* condition = NULL;
    if(!check(SEMICOLON)) condition = expression();
    consume(SEMICOLON, "Expect ';' after for loop condition" );

    //for loop increment
    Expr* increment = NULL;
    if(!check(RIGHT_PAREN)) increment = expression();
    consume(RIGHT_PAREN, "Expect ')' after a for clause" );
    
    //body
    Stmt* body = statement();

    //increment var
    if(increment)
    {
        list<Stmt*> stmts;
        stmts.push_back(body);
        stmts.push_back(new Expression(increment));

        body = new Block(stmts);
    }

    //check condition
    if(!condition) condition = new Literal("true");
    body = new While(condition, body);
    
    if(init) 
    {
        list<Stmt*> stmts;
        stmts.push_back(init);
        stmts.push_back(body);
        
        body = new Block(stmts);
    }



    return body;
}

Stmt* 
Parser::whileStatement()
{
    consume(LEFT_PAREN, "Expect '(' after a 'while'");
    Expr* condition = expression();

    consume(RIGHT_PAREN, "Expect ')' after a condition" );

    Stmt* body = statement();
    return new While(condition, body);
}

Stmt*
Parser::ifStatement()
{
    consume(LEFT_PAREN, "Expect '(' after an 'if'");
    Expr* condition = expression();

    consume(RIGHT_PAREN, "Expect ')' after an if condition" );

    Stmt* ifBranch = statement();
    Stmt* elseBranch = NULL;

    list<TokenType> t;
    t.push_back(ELSE);
    
    if(match(t)) elseBranch = statement();

    return new If(condition, ifBranch, elseBranch);
}

Stmt* 
Parser::printStatement()
{
    Expr* expr = expression();
    consume(SEMICOLON,"Expect ';' after value.");
    return new Print(expr);
}

Stmt*
Parser::expressionStatement()
{
    Expr* expr = expression();
    consume(SEMICOLON,"Expect ';' after expression.");
    return new Expression(expr);
}

list<Stmt*>
Parser::block()
{
    list<Stmt*> s;
    while(!check(RIGHT_BRACE) && isNotEnd())
    {
        s.push_back(declaration());
    }
    consume(RIGHT_BRACE, "Expect '}' after a block.");
    return s;
}

Expr* 
Parser::assignment()
{
    //Expr* expr = equality();
    Expr* expr = logicOr();

    list<TokenType> token_types;
    token_types.push_back(EQUAL);

    if (match(token_types))
    {
        Token e = getToken(current-1); 
        cout << "Token in assignment: " << e.tokenLiteral() << endl;
        Expr* v = assignment();
        if(dynamic_cast<const Variable*>(expr) != nullptr)
        {
            Variable *vr = dynamic_cast< Variable*>(expr);
            Token n = vr->name;
            cout << "Token for Assign: " << n.tokenLiteral() << endl;
            return new Assign(n, v);
        }

        throw invalid_argument("Error in Variable casting on Expr. Location: assignment() " );
    }
    return expr;
}

Expr*
Parser::logicOr() // like Binary
{
    Expr *expr = logicAnd();

    list<TokenType> t;
    t.push_back(OR);

    while(match(t))
    {
        Token op = getToken(current-1);
        Expr *r = logicAnd();
        expr = new Logical(expr, op, r);
    }

    return expr;
}

Expr*
Parser::logicAnd()
{
    Expr* expr = equality();

    list<TokenType> t;
    t.push_back(AND);

    while(match(t))
    {
        Token op = getToken(current-1);
        Expr *r = equality();
        expr = new Logical(expr, op, r);
    }

    return expr;
}

Expr* 
Parser::equality()
{
    cout << "Equality -->";
    Expr* expr = comparison();
    
    //exit(1);
    list<TokenType> tt;
    tt.push_back(BANG_EQUAL);
    tt.push_back(EQUAL_EQUAL);

    while(match(tt))
    {
        cout << "   enter equality match " << endl;
        Token op = getToken(current-1);
        cout << "   Operator:" << op.tokenLiteral() << endl;  

        
        Expr* r = comparison();
        
        //exit(1);
        cout << "   creating Binary" << endl;
        expr = new Binary(expr, op, r);
        //string temp = e;
        //e = "";
        //e.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr* 
Parser::comparison()
{
    cout << "Comparison -->";

    Expr* expr = term();
    
    list<TokenType> tt;
    tt.push_back(GREATER);
    tt.push_back(GREATER_EQUAL);
    tt.push_back(LESS);
    tt.push_back(LESS_EQUAL);

    while(match(tt))
    {
        Token op = getToken(current-1);
        Expr* r = term();
        
        expr = new Binary(expr, op, r);
        //string temp = c;
        //c = "";
        //c.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr* 
Parser::term()
{
    cout << "Term -->";
    Expr* expr = factor();
    
    list<TokenType> tt;
    tt.push_back(MINUS);
    tt.push_back(PLUS);

    while(match(tt))
    {
        Token op = getToken(current-1);
        Expr* r = factor();
        
        expr = new Binary(expr, op, r);
        //string temp = t;
        //t = "";
        //t.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr*
Parser::factor()
{
    cout << "Factor -->";
    Expr* expr = unary();
    
    list<TokenType> tt;
    tt.push_back(SLASH);
    tt.push_back(STAR);

    while(match(tt))
    {
        Token op = getToken(current-1);
        Expr* r = unary();
        
        expr = new Binary(expr, op, r);
        //string temp = f;
        //f = "";
        //f.append(temp + "," + op.tokenLiteral() + "," + r);
    }
    
    return expr;
}

Expr*
Parser::unary()
{
    cout << "Unary -->";
    list<TokenType> tt;
    tt.push_back(BANG);
    tt.push_back(MINUS);

    while(match(tt))
    {   
        cout << "match Unary" << endl;
        Token op = getToken(current-1);
        Expr* r = unary();
        
        return new Unary(op, r);
        // return (op.tokenLiteral() + "," + r);
    }
    
    return primary();
}

Expr*
Parser::primary()
{
    cout << "Primary" << endl;
    list<TokenType> t1, t2, t3, t4, t5;
    
    t1.push_back(FALSE);
    if(match(t1)){cout << " False" << endl; return new Literal("FALSE");}

    t2.push_back(TRUE);
    if(match(t2)){cout << " True" << endl; return new Literal("TRUE");}

    t3.push_back(NIL);
    if(match(t3)) {cout << " NIL" << endl; return new Literal("NIL");}

    list<TokenType> tt;
    tt.push_back(NUMBER);
    tt.push_back(STRING);
    if(match(tt))
    {
        cout << "   matched NUMBER/STRING: " << endl; 
        cout << "   Current:" << this->current << endl;
        Token temp = getToken(current-1);
        //cout << " --" << temp.tokenLiteral() <<"--" << (current-1) << endl;
        return new Literal(temp.tokenLiteral());
    }

    t4.push_back(IDENTIFIER);
    if(match(t4)) return new Variable(getToken(current-1));
    
    t5.push_back(LEFT_PAREN);
    if(match(t5))
    {
        cout << "   matched LEFT_PAREN" << endl;
        cout << "   Current:" << this->current << endl<< endl;

        Expr* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression" );
        return new Grouping(expr);
    }

    throw error(peek(), "Expect expression");
}

bool 
Parser::match(list<TokenType> tt)
{
    //cout << "   Enter match()" << endl;
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
    if (isNotEnd()) return peek().tokenType() == enum_str[t];
    
    return false;
}

void
Parser::advanceToken()
{
    cout << "   Enter advanceToken()" << endl;
    if(isNotEnd())
    {
        this->current += 1;
    }
    else {
        cout << "isEnd" << endl;
    } 
}

bool 
Parser::isNotEnd()
{
    if (peek().tokenType() == "TokenEOF") return false;
    return true;
}

Token 
Parser::peek()
{
    //cout << "   Enter peek()" << endl;
    list<Token>::iterator i;
    int tokenIndexCounter = 0;
    for (i = tokens.begin(); i != tokens.end(); i++)
    {
        if(tokenIndexCounter == this->current)
        {
            //cout << "       current: " << current << endl;
            return *i;
        }
        tokenIndexCounter += 1;
    }
    cout << "       not found" << endl;
    return Token();
}

Token 
Parser::getToken(int index)
{   
    cout << "   Entered getToken(" << index << ")" << endl;
    list<Token>::iterator i;
    int tokenIndexCounter = 0;
    for (i = tokens.begin(); i != tokens.end(); i++)
    {
        if(current == 0)
        {
            return *i;
        }
        
        if(tokenIndexCounter == (index))
        {
            cout << "       return = " << (*i).tokenLiteral() << endl;
            return *i;
        }
        tokenIndexCounter += 1;
    }
     

    return Token();
}

// panic mode

Token
Parser::consume(TokenType t, string message)
{
    if (check(t))
    {
        Token token = getToken(current);
        advanceToken();
        return token;
    } 

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
      if (getToken(current-1).tokenType() == "SEMICOLON") return;

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

