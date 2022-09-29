
#include "token.cpp"
#include <iostream>
#include <list>
#include <string.h>

using namespace std;


class Visitor;
class Expr 
{
    public:
        virtual ~Expr(){};
        virtual void Accept(Visitor *visitor){};
        //{accept(visitor);}s
        //virtual void accept(Visitor<R> *visitor);
};
class Assign;
class Binary;
class Call;
class Get;
class Grouping;
class Literal;
class Logical;
class Set;
class Super;
class This;
class Unary;
class Variable;

class Visitor : public Expr
{
    public:
        ~Visitor() {}
        virtual void VisitAssignExpr(Assign *expr) {};
        virtual void VisitBinaryExpr(Binary *expr) {};
        virtual void VisitCallExpr(Call *expr){}; ;
        virtual void VisitGetExpr(Get *expr) {};;
        virtual void VisitGroupingExpr(Grouping *xpr) {};
        virtual void VisitLiteralExpr(Literal *expr) {};
        virtual void VisitLogicalExpr(Logical *expr) {};
        virtual void VisitSetExpr(Set *expr) {};
        virtual void VisitSuperExpr(Super *expr) {};
        virtual void VisitThisExpr(This *expr) {};
        virtual void VisitUnaryExpr(Unary *expr) {};
        virtual void VisitVariableExpr(Variable *expr) {};
};




class Assign : public Expr
{
    public:
        Token name;
        Expr* value;

        Assign(Token n, Expr* v)
        {
            name = n;
            value = v;
        }

        void Accept(Visitor *visitor)        
        {   visitor->VisitAssignExpr(this);
        }
};


class Binary : public Expr
{
    public:
        Expr* left;
        Token op;
        Expr* right;

        Binary(Expr* l, Token o, Expr* r)
        {   left = l;
            right = r;
            op = o;
        }

        void Accept(Visitor *visitor)       
        {   visitor->VisitBinaryExpr(this);
        }
};


class Call : public Expr
{
    public:
        Expr* callee;
        Token paren;
        list<Expr*> arguments;

        Call(Expr* c, Token p, list<Expr*> as)
        {   callee = c;
            this->paren = p;
            arguments = as;
        }

        void Accept(Visitor *visitor)       
        {   visitor->VisitCallExpr(this);
        }

};


class Get : public Expr
{
    public:
        Expr* object;
        Token name;

        Get(Expr* o, Token n)
        {   object = o;
            name = n;
        }

        void Accept(Visitor *visitor)        
        {   visitor->VisitGetExpr(this);}

};


class Grouping : public Expr
{
    public:
        Expr* expression;
        Grouping(Expr* e){   expression = e;}
        void Accept(Visitor *visitor)        
        {   visitor->VisitGroupingExpr(this);}
};


class Literal : public Expr
{
    public:
        string value;
        Literal(string v)
        {   value = v;}
        void Accept(Visitor *visitor)       
        {   visitor->VisitLiteralExpr(this);}
};


class Logical : public Expr
{
    public:
        Expr* left;
        Token op;
        Expr* right;

        Logical(Expr* l, Token op, Expr* r)
        {   left = l;
            this->op = op;
            right = r;
        }

        void Accept(Visitor *visitor)       
        {   visitor->VisitLogicalExpr(this);}

};

class Set : public Expr
{
    public:
        Expr* object;
        Token name;
        Expr* value;

        Set(Expr* o, Token n, Expr* v)
        {   object = o;
            name = n;
            value = v;
        }

        void Accept(Visitor *visitor)
        {   return visitor->VisitSetExpr(this);}

};


class Super : public Expr
{
    public:
        Token keyword;
        Token method;

        Super(Token k, Token m)
        {   keyword = k;
            method = m;
        }

        void Accept(Visitor *visitor)       
        {   visitor->VisitSuperExpr(this);}

};


class This : public Expr
{
    public:
        Token keyword;

        This(Token k)
        {   keyword = k;}

        void Accept(Visitor *visitor)        
        {   return visitor->VisitThisExpr(this);}

};


class Unary : public Expr
{
    public:
        Token op;
        Expr* right;

        Unary(Token o, Expr* r)
        {   op = o;
            right = r;}

        void Accept(Visitor *visitor)        
        {   visitor->VisitUnaryExpr(this);}

};


class Variable : public Expr
{
    public:
        Token name;

        Variable(Token n)
        {   name = n;}

        void Accept(Visitor *visitor)      
        {   visitor->VisitVariableExpr(this);}

};





