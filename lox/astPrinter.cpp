#include "expr.cpp"
#include <string>
#include <sstream>


class AstPrinter : public Visitor
{
    public:
    

    void print(Expr* expr)
    {   expr->Accept(this);}

    void VisitBinaryExpr(Binary* expr) override
    {
        list<Expr*> exprs;
        exprs.push_back(expr->left);
        exprs.push_back(expr->right);
    }

    void VisitGroupingExpr(Grouping* expr) override
    {
        list<Expr*> exprs;
        exprs.push_back(expr->expression);
    }

    void VisitLiteralExpr(Literal* expr) override
    {
        //if (expr->value == "NIL") return "NIL";
        cout << expr->value << endl;
    }

    void VisitUnaryExpr(Unary* expr) override
    {
        list<Expr*> exprs;
        exprs.push_back(expr->right);
    }

};


int main()
{
    Token a(MINUS, "-", "", 1);
    Token b(STAR, "*", "", 1);

    
    Unary* u = new Unary(a, new Literal("123"));
    Grouping* g = new Grouping(new Literal("45"));
    
    Expr* expression = new Binary(u,b,g);

    //cout << new AstPrinter<string>().print(expression) << endl;

    AstPrinter AstPrt;


    cout << "Done building" << endl;
    AstPrt.print(expression);
}