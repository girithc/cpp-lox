#include "expr.cpp"


class Interpreter : public Visiter
{
    public:
        void visitLiteralExpr(Literal *expr) override
        {
            cout << "Expr.value: " << expr->value << endl;
        }

        void visitGroupingExpr(Grouping *expr)
        {
            evaluate(expr->expression);
        }

        void visitUnaryExpr(Unary *expr)
        {
            evaluate(expr->right);

            if (expr->op.tokenType() == "MINUS")
            else if (expr->op.tokenType() == "BANG")       
        }

    private:
        void evaluate(Expr *expr)
        {
            expr->Accept(this);
        }
};