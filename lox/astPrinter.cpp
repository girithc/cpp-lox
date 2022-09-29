#include "expr.cpp"
#include <string>
#include <sstream>

class AstPrinter : public Visitor<string>
{
    public:
    string parenthesize(string name, list<Expr> exprs)
    {
        stringstream ss;
        ss <<"(" ;
        ss << name;

        list<Expr>::iterator i;
        for (i = exprs.begin(); i != exprs.end(); i++)
        {
            ss << " ";
            ss << i->sudo_accept(this);
        }

        ss << ")";

        return ss.str();
    }

    string print(Expr expr)
    {
        return expr.sudo_accept(this);
    }

    string VisitBinaryExpr(Binary expr) override
    {
        list<Expr> exprs;
        exprs.push_back(expr.left);
        exprs.push_back(expr.right);
        return parenthesize(expr.op.tokenLiteral(), 
                            exprs);
    }

    string VisitGroupingExpr(Grouping expr) override
    {
        list<Expr> exprs;
        exprs.push_back(expr.expression);
        return parenthesize("group", exprs);
    }

    string VisitLiteralExpr(Literal expr) override
    {
        if (expr.value == "NIL") return "NIL";
        return expr.value;
    }

    string VisitUnaryExpr(Unary expr) override
    {
        list<Expr> exprs;
        exprs.push_back(expr.right);
        return parenthesize(expr.op.tokenLiteral(), exprs);
    }

};


int main()
{
    Expr expression = new Binary(
        new Unary(
            new Token(MINUS, "-", NULL, 1),
            new Literal(123)),
        new Token(STAR, "*", NULL, 1),
        new Grouping(
            new Literal(45.67)));

    cout << new AstPrinter().print(expression) << endl;
}