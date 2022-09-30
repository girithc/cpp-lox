#include "expr.cpp"
#include <string>
#include <sstream>


class AstPrinter : public Visitor
{
    public:
    

    void print(Expr* expr)
    {   cout << "Entered print" << endl;
        expr->Accept(this);}

    void VisitBinaryExpr(Binary* expr) override
    {
        cout << "( ";
        cout << expr->op.tokenLiteral();
        expr->left->Accept(this);
        expr->right->Accept(this);
        cout << " )";
        //expr->Accept(this);
    }

    void VisitGroupingExpr(Grouping* expr) override
    {
        //cout << "Entered visitG" << endl;
        cout << "( ";
        cout << "Group ";
        expr->expression->Accept(this);
        cout << " )";
    }

    void VisitLiteralExpr(Literal* expr) override
    {
        //if (expr->value == "NIL") return "NIL";
        
        cout << expr->value;
    }

    void VisitUnaryExpr(Unary* expr) override
    {
        cout << "( ";
        cout << expr->op.tokenLiteral();
        expr->right->Accept(this);
        cout << " )";
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