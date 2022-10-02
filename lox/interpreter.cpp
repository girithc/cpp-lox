#include "expr.cpp"


class Interpreter : public Visiter
{
    public:
        string visitLiteralExpr(Literal *expr) override
        {
            //cout << "Expr.value: " << expr->value << endl;
            return expr->value;
        }

        string visitGroupingExpr(Grouping *expr)
        {
            return eval(expr->expression);
        }

        string visitUnaryExpr(Unary *expr)
        {
            string r = eval(expr->right);

            if (expr->op.tokenType() == "MINUS") return -(double)r;
            else if (expr->op.tokenType() == "BANG") return True(r);


            return "";      
        }

        string visitBinaryExpr(Binary *expr)
        {
            string l = eval(expr->left);
            string r = eval(expr->right);

            if(expr->op.tokenType() == "MINUS") return (string)((double)l - (double)r);
            else if(expr->op.tokenType() == "SLASH"){  return (string)((double)l / (double)r);}
            else if(expr->op.tokenType() == "STAR"){  return (string)((double)l * (double)r);}
            else if(expr->op.tokenType() == "PLUS"){
                if(isDouble(l,r)) return (string)((double)l + (double)r);
                else if(isString(l,r)) return l.append(r);
            }  
            return "";
        }

    private:
        string eval(Expr *expr)
        {
            return expr->Accept(this);
        }

        bool True(string s)
        {
            if (s == "") return false;
            if (s == "true" || s == "false") return (bool)s;
            return true;

        }
};