//refer appendix 2 to start
#include <list>
#include <string>

#include "expr.cpp"

using namespace std;

class VisitorStmt;
class Stmt
{
    public:
        virtual ~Stmt(){};
        virtual string Accept(VisitorStmt *visitor){ return "";}
};

class Block;
class Class;
class Expression;
class Function;
class If;
class Print;
class Return;
class Var;
class While;

class VisitorStmt : public Stmt 
{
    public:
        ~VisitorStmt(){}
        virtual string VisitBlockStmt(Block* stmt){return "";};
        virtual string VisitClassStmt(Class* stmt){return "";};
        virtual string VisitExpressionStmt(Expression* stmt){return "";};
        virtual string VisitFunctionStmt(Function* stmt){return "";};
        virtual string VisitIfStmt(If* stmt){return "";};
        virtual string VisitPrintStmt(Print* stmt){return "";};
        virtual string VisitReturnStmt(Return* stmt){return "";};
        virtual string VisitVarStmt(Var* stmt){return "";};
        virtual string VisitWhileStmt(While* stmt){return "";};
};

class Block : public Stmt
{
    public:
        list<Stmt*> stmts;

        Block(list<Stmt*> s)
        {
            stmts = s;
        }

        string Accept(VisitorStmt *visitor)
        {
            return visitor->VisitBlockStmt(this);
        }
};

class Class : public Stmt 
{
    public:
        Token name;
        //Variable* superclass;
        list<Function*> methods;

    Class(Token n, list<Function*> m)
    {
        name = n;
        //superclass = s;
        methods = m;
    }

    string Accept(VisitorStmt* visitor)
    {
        return visitor->VisitClassStmt(this);
    }
};

class Expression : public Stmt
{
    public:
        Expr* expression;

        Expression(Expr* e)
        {
            expression = e;
        }

        string Accept(VisitorStmt* visitor)
        {
            return visitor->VisitExpressionStmt(this);
        }
};

class Function : public Stmt
{
    public:
        Token name;
        list<Token> params;
        list<Stmt*> body;

        Function(Token n, list<Token> p, list<Stmt*> b)
        {
            name = n;
            params = p;
            body = b;
        }

        string Accept(VisitorStmt* visitor)
        {
            return visitor->VisitFunctionStmt(this);
        }
};

class If : public Stmt
{
    public:
        Expr* condition;
        Stmt* ifBranch;
        Stmt* elseBranch;

    If(Expr* c, Stmt* tb, Stmt* eb)
    {
        condition = c;
        ifBranch = tb;
        elseBranch = eb;
    }

    string Accept(VisitorStmt* visitor)
    {
        return visitor->VisitIfStmt(this);
    }
};

class Print : public Stmt
{
    public:
        Expr* expression;

        Print(Expr* e)
        {
            expression = e;
        }

        string Accept(VisitorStmt* visitor)
        {
            return visitor->VisitPrintStmt(this);
        }
};

class Return : public Stmt
{
    public:
        Token keyword;
        Expr* value;

        Return(Token k, Expr* v)
        {
            keyword = k;
            value = v;
        }

        string Accept(VisitorStmt* visitor)
        {
            return visitor->VisitReturnStmt(this);
        }
};

class Var : public Stmt 
{
    public:
        Token name;
        Expr* init;

        Var(Token n, Expr* i)
        {
            name = n;
            init = i;
        }

        string Accept(VisitorStmt* visitor)
        {
            return visitor->VisitVarStmt(this);
        }
};


class While : public Stmt
{
    public:
        Expr* condition;
        Stmt* body;

        While(Expr* c, Stmt* b)
        {
            condition = c;
            body = b;
        }

        string Accept(VisitorStmt* visitor)
        {
            return visitor->VisitWhileStmt(this);
        }
};
