#include "expr.cpp"
#include <string>
#include <string.h>


class Interpreter : public Visitor
{
    public:
        string VisitLiteralExpr(Literal *expr) override
        {
            cout << "Entered VisitLiteralExpr: " << expr->value << endl;
            //cout << "Expr.value: " << expr->value << endl;
            return expr->value;
        }

        string VisitGroupingExpr(Grouping *expr) override
        {
            cout << "Entered VisitGroupingExpr" << endl;
            return eval(expr->expression);
        }

        string VisitUnaryExpr(Unary *expr) override
        {
            cout << "Entered VisitUnaryExpr" << endl;
            string r = eval(expr->right);

            if (expr->op.tokenType() == "MINUS") return r;
            else if (expr->op.tokenType() == "BANG") return notTrue(r);

            return "";      
        }

        string VisitBinaryExpr(Binary *expr) override
        {
            cout << "Entered VisitBinaryExpr" << endl;
            string l = eval(expr->left);
            string r = eval(expr->right);
            
            //
            cout << "   " << l << expr->op.tokenLiteral() << r << endl; 
            //

            if(expr->op.tokenType() == "MINUS") return to_string(stod(l) - stod(r));
            else if(expr->op.tokenType() == "SLASH"){  return to_string(stod(l) / stod(r));}
            else if(expr->op.tokenType() == "STAR"){  return to_string(stod(l) * stod(r));}
            else if(expr->op.tokenType() == "PLUS"){
                if(isDouble(l,r)) return to_string(stod(l) + stod(r));
                else if(isString(l,r)) return l.append(r);
            } 
            else if(expr->op.tokenType() == "GREATER"){  return compare(l, r, ">");} 
            else if(expr->op.tokenType() == "GREATER_EQUAL"){  return compare(l, r, ">=");} 
            else if(expr->op.tokenType() == "LESS"){  return compare(l, r, "<");} 
            else if(expr->op.tokenType() == "LESS_EQUAL"){  return compare(l, r, "<=");} 
            else if(expr->op.tokenType() == "BANG_EQUAL"){  return compare(l, r, "!=");} 
            else if(expr->op.tokenType() == "EQUAL_EQUAL"){ cout << "       Entered E_E" << endl;  return compare(l, r, "==");} 
            
            return "";
        }

        void interpret(Expr* expr)
        {
            try {
                string value = eval(expr);
                cout << "Eval: " <<  value << endl;
            } catch (...) {
                cout << "Error in interpreter" << endl;
            }
        }

    private:
        string eval(Expr *expr)
        {
            cout << "Entered eval" << endl;
            return expr->Accept(this);
        }

        string notTrue(string s)
        {
            if (s == "") return "true";
            if (s == "true") return "false";
            if (s == "false") return "true";
            return "false";

        }

        bool isDouble(string one, string two)
        {
            for (int i = 0; i < one.length(); i++)
            {
                if (isdigit(one[i])) continue;
                else return false;
            }
            for (int i = 0; i < two.length(); i++)
            {
                if (isdigit(two[i])) continue;
                else return false;
            }

            return true;
        }

        bool isString(string one, string two)
        {
            if(isDouble(one, two)) return false;
            return true;
        }

//left to do. Equal and Unequal for null

        string compare(string one, string two, string op)
        {   
            if(isString(one, two)) return compareString(one, two, op);
            if (op ==">")
            {   if(stod(one) > stod(two)) 
                    return "true"; 
                return "false";
            }
            else if (op ==">=")
            {   if(stod(one) >= stod(two)) 
                    return "true"; 
                return "false";
            }
            else if (op == "<")
            {   if(stod(one) < stod(two)) 
                    return "true"; 
                return "false";
            }
            else if (op == "<=")
            {   if(stod(one) <= stod(two)) 
                    return "true"; 
                return "false";
            }
            else if (op == "!=")
            {   if(stod(one) != stod(two))  
                    return "true"; 
                return "false";
            }
            else if (op == "==")
            {   if(stod(one) == stod(two)) 
                    return "true"; 
                return "false";
            }
            
            return "false";
        }

        string compareString(string one, string two, string op)
        {
            if (op ==">")
            {   if((one) > (two)) 
                    return "true"; 
                return "false";
            }
            else if (op ==">=")
            {   if((one) >= (two)) 
                    return "true"; 
                return "false";
            }
            else if (op == "<")
            {   if((one) < (two)) 
                    return "true"; 
                return "false";
            }
            else if (op == "<=")
            {   if((one) <= (two)) 
                    return "true"; 
                return "false";
            }
            else if (op == "!=")
            {   if((one) != (two))  
                    return "true"; 
                return "false";
            }
            else if (op == "==")
            {   if((one) == (two)) 
                    return "true"; 
                return "false";
            }
            
            return "false";
        }
};