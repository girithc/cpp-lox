
#include "token.cpp"
#include <list>
#include <string.h>

using namespace std;

class Expr;
class Assign : public Expr;
class Binary : public Expr;
class Call : public Expr;
class Get : public Expr;
class Grouping : public Expr;
class Literal : public Expr;
class Logical : public Expr;
class Set : public Expr;
class Super : public Expr;
class This : public Expr;
class Unary : public Expr;
class Variable : public Expr;

template<typename R> 
class Visitor
{
    public:
        ~Visitor() {}
        virtual R VisitAssignExpr(Assign *expr) = 0;
        virtual R VisitBinaryExpr(Binary *expr) = 0;
        virtual R VisitCallExpr(Call *expr) = 0;
        virtual R VisitGetExpr(Get *expr) = 0;
        virtual R VisitGroupingExpr(Grouping *xpr) = 0;
        virtual R VisitLiteralExpr(Literal *expr) = 0;
        virtual R VisitLogicalExpr(Logical *expr) = 0;
        virtual R VisitSetExpr(Set *expr) = 0;
        virtual R VisitSuperExpr(Super *expr) = 0;
        virtual R VisitThisExpr(This *expr) = 0;
        virtual R VisitUnaryExpr(Unary *expr) = 0;
        virtual R VisitVariableExpr(Variable *expr) = 0;
};


class Expr 
{
    public:
        virtual ~Expr(){}
        template <typename R> R sudo_accept(Visitor<R> *visitor){}
        //{accept(visitor);}
        template <typename R> virtual void accept(Visitor<R> *visitor);
};


class Assign : public Expr
{
    public:
        Token name;
        Expr value;

        Assign(Token n, Expr v)
        {
            name = n;
            value = v;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
          return visitor->VisitAssignExpr(this);
        }
};

class Binary : public Expr
{
    public:
        Expr left;
        Token operator;
        Expr right;

        Binary(Expr l, Token op, Expr r)
        {
            left = l;
            right = r;
            operator = op;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitBinaryExpr(this);
        }
};

class Call : public Expr
{
    public:
        Expr callee;
        Token paren;
        list<Expr> arguments;

        Call(Expr c, Token p, list<Expr> as)
        {
            callee = c;
            paren = p;
            arguments = as;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitCallExpr(this);
        }

};

class Get : public Expr
{
    public:
        Expr object;
        Token name;

        Get(Expr o, Token n)
        {
            object = 0;
            name = m;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitGetExpr(this);
        }

};

class Grouping : public Expr
{
    public:
        Expr expression;

        Grouping(Expr e)
        {
            expression = e;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitGroupingExpr(this);
        }

};

class Literal : public Expr
{
    public:
        string value;

        Literal(string v)
        {
            value = v;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitLiteralExpr(this);
        }

};

class Logical : public Expr
{
    public:
        Expr left;
        Token operator;
        Expr right;

        Logical(Expr l, Token op, Expr r)
        {
            left = l;
            operator = op;
            right = r;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitLogicalExpr(this);
        }

};

class Set : public Expr
{
    public:
        Expr object;
        Token name;
        Expr value;

        Set(Expr o, Token n, Expr v)
        {
            object = o;
            name = n;
            value = v;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override
        {
            return visitor->VisitSetExpr(this);
        }

};

class Super : public Expr
{
    public:
        Token keyword;
        Token method;

        Super(Token k, Token m)
        {
            keyword = k;
            method = m;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitSuperExpr(this);
        }

};

class This : public Expr
{
    public:
        Token keyword;

        This(Token k)
        {
            keyword = k;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitThisExpr(this);
        }

};

class Unary : public Expr
{
    public:
        Token operator;
        Expr right;

        Unary(Token o, Expr r)
        {
            operator = o;
            right = r;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitUnaryExpr(this);
        }

};

class Variable : public Expr
{
    public:
        Token name;

        Variable(Token n)
        {
            name = n;
        }

        template <typename R> R sudo_accept(Visitor<R> *visitor) override        
        {
            return visitor->VisitVariableExpr(this);
        }

};