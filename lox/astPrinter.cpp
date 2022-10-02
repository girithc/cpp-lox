#include "expr.cpp"
#include <string>
#include <sstream>


class AstPrinter : public Visitor
{
    public:
    

    string print(Expr* expr)
    {   cout << "Entered print" << endl;
        return expr->Accept(this);}

    string VisitBinaryExpr(Binary* expr) override
    {
        stringstream ss;
        ss << "( ";
        ss << expr->op.tokenLiteral();
        ss << expr->left->Accept(this);
        ss << expr->right->Accept(this);
        ss << " )";
        //expr->Accept(this);
        return ss.str();
    }

    string VisitGroupingExpr(Grouping* expr) override
    {
        //cout << "Entered visitG" << endl;
        stringstream ss;
        ss << "( ";
        ss << "Group ";
        ss << expr->expression->Accept(this);
        ss << " )";
        return ss.str();
        }

    string VisitLiteralExpr(Literal* expr) override
    {
        //if (expr->value == "NIL") return "NIL";
        
        return expr->value;
    }

    string VisitUnaryExpr(Unary* expr) override
    {
        stringstream ss;
        ss << "( ";
        ss << expr->op.tokenLiteral();
        ss << expr->right->Accept(this);
        ss << " )";
        return ss.str();
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
    cout << "Done building Bazuka" << endl;
    cout << AstPrt.print(expression);
}