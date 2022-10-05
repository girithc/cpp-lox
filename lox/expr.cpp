
#include <iostream>
#include <list>
#include <string.h>
#include <string>


#include "token.cpp"

using namespace std;


class Visitor;
class Expr 
{
    public:
        virtual ~Expr(){};
        virtual string Accept(Visitor *visitor){return "";};
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
        virtual string VisitAssignExpr(Assign *expr) {return "";};
        virtual string VisitBinaryExpr(Binary *expr) {return "";};
        virtual string VisitCallExpr(Call *expr){return "";} ;
        virtual string VisitGetExpr(Get *expr) {return "";};
        virtual string VisitGroupingExpr(Grouping *xpr) {return "";};
        virtual string VisitLiteralExpr(Literal *expr) {return "";};
        virtual string VisitLogicalExpr(Logical *expr) {return "";};
        virtual string VisitSetExpr(Set *expr) {return "";};
        virtual string VisitSuperExpr(Super *expr) {return "";};
        virtual string VisitThisExpr(This *expr) {return "";};
        virtual string VisitUnaryExpr(Unary *expr) {return "";};
        virtual string VisitVariableExpr(Variable *expr) {return "";};
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

        string Accept(Visitor *visitor)        
        {   return visitor->VisitAssignExpr(this);
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

        string Accept(Visitor *visitor)       
        {   return visitor->VisitBinaryExpr(this);
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

        string Accept(Visitor *visitor)       
        {   return visitor->VisitCallExpr(this);
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

        string Accept(Visitor *visitor)        
        {   return visitor->VisitGetExpr(this);}

};


class Grouping : public Expr
{
    public:
        Expr* expression;
        Grouping(Expr* e){   expression = e;}
        string Accept(Visitor *visitor)        
        {   return visitor->VisitGroupingExpr(this);}
};


class Literal : public Expr
{
    public:
        string value;
        Literal(string v)
        {   value = v;}
        string Accept(Visitor *visitor)       
        {   return visitor->VisitLiteralExpr(this);}
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

        string Accept(Visitor *visitor)       
        {   return visitor->VisitLogicalExpr(this);}

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

        string Accept(Visitor *visitor)
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

        string Accept(Visitor *visitor)       
        {   return visitor->VisitSuperExpr(this);}

};


class This : public Expr
{
    public:
        Token keyword;

        This(Token k)
        {   keyword = k;}

        string Accept(Visitor *visitor)        
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

        string Accept(Visitor *visitor)        
        {   return visitor->VisitUnaryExpr(this);}

};


class Variable : public Expr
{
    public:
        Token name;

        Variable(Token n)
        {   name = n;}

        string Accept(Visitor *visitor)      
        {   return visitor->VisitVariableExpr(this);}

};





