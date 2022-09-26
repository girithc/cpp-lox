#include "token.cpp"
#include <string>

using namespace std;

class Expr()
{
    private:

    Expr* leftExpr;
    Expr* rightExpr;
    Token operator;

    public:

    void Expr()
    {

    }

    void Expr(Expr left, Token op, Expr right)
    {
        *leftExpr = left;
        operator = op;
        *rightExpr = right;
    }

    Expr binary()
    {
        Expr* result;

        return *result;
    }
}