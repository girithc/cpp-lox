#include "stmt.cpp"
#include <string>
#include <string.h>
#include <list>
#include <iterator>

class Interpreter;
class LoxCallable
{
    public:
        virtual ~LoxCallable(){};
        virtual string Call(Interpreter* interpreter, 
                            list<string> args){return "";};
        virtual string arity(){return "";};
};
class LoxFunction : public LoxCallable
{
    private:
        Function* declaration;
    public:
        LoxFunction(Function* d)
        {
            declaration = d;
        }

        string Call(Interpreter* interpreter, list<string> args);
};


string
LoxFunction::Call(Interpreter* interpreter, list<string> args)
{
    return "abc";
}

class Interpreter : public Visitor, VisitorStmt
{
    public:
        string VisitLiteralExpr(Literal *expr) override
        {
            //cout << "Entered VisitLiteralExpr: " << expr->value << endl;
            //cout << "Expr.value: " << expr->value << endl;
            return expr->value;
        }

        string VisitLogicalExpr(Logical* expr) override
        {
            string l = eval(expr->left);

            if(expr->op.tokenType() == "OR")
            {
                if(notTrue(l) == "false") return l;
            }
            else
            {
                if(notTrue(l) == "true") return l;
            }

            return eval(expr->right);
        }

        string VisitGroupingExpr(Grouping *expr) override
        {
            //cout << "Entered VisitGroupingExpr" << endl;
            return eval(expr->expression);
        }

        string VisitUnaryExpr(Unary *expr) override
        {
            //cout << "Entered VisitUnaryExpr" << endl;
            string r = eval(expr->right);

            if (expr->op.tokenType() == "MINUS") return r;
            else if (expr->op.tokenType() == "BANG") return notTrue(r);

            return "";      
        }

        string VisitVariableExpr(Variable* expr) override
        {
            //cout << "Entered VisitVariableExpr: " << expr->name.tokenLiteral() << endl;
            return env->getItem(expr->name);
        }


        string VisitAssignExpr(Assign* expr) override
        {
            //cout << "Entered VisitAssignExpr" << endl;
            string v = eval(expr->value);
            //cout << "   new Value: " << v << endl;
            env->assign(expr->name, v);
            return "";
        }

        string VisitBinaryExpr(Binary *expr) override
        {
            //cout << "Entered VisitBinaryExpr" << endl;
            string l = eval(expr->left);
            string r = eval(expr->right);
            
            //
            //cout << "   " << l << expr->op.tokenLiteral() << r << endl; 
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
            else if(expr->op.tokenType() == "LESS"){   return compare(l, r, "<");} 
            else if(expr->op.tokenType() == "LESS_EQUAL"){  return compare(l, r, "<=");} 
            else if(expr->op.tokenType() == "BANG_EQUAL"){  return compare(l, r, "!=");} 
            else if(expr->op.tokenType() == "EQUAL_EQUAL"){   return compare(l, r, "==");} 
            
            return "";
        }

        string VisitCallExpr(Call* expr) override
        {
            string callee = eval(expr->callee);
            list<string> args;

            list<Expr*>::iterator i;
            for (i = expr->arguments.begin(); 
            i != expr->arguments.end(); i++)
            {
                args.push_back(eval(*i));
            }


            LoxCallable* function;
            //return function.call(this, arguments);

            return function->Call(this,args);
        }

        string VisitExpressionStmt(Expression* stmt) override
        {
            string e = eval(stmt->expression);
            return "";
        }
        
        string VisitWhileStmt(While* stmt) override
        {
            //cout << "Entered VisitWhileStmt" << endl;
            int i = 0;
            while(notTrue(eval(stmt->condition)) == "false")
            {
                //cout << "       ";
                execute(stmt->body);
                //i++;
                //if(i > 4) exit(1);
            }
                
            
            return "";
        }

        string VisitIfStmt(If* stmt) override
        {
            //cout << "Enter if statement()" << endl;
            if(notTrue(eval(stmt->condition)) == "false")
            {
                //cout << "   Enter ifBranch" << endl;
                execute(stmt->ifBranch);
            }

            else if(stmt->elseBranch)
                execute(stmt->elseBranch);
        
            return "";
        }

        string VisitPrintStmt(Print* stmt) override
        {
            //cout << "   Entered VisitPrintStmt" << endl;
            string v = eval(stmt->expression);
            cout  << v << endl;
            
            return "";
        }

        string VisitVarStmt(Var* stmt) override
        {
            //cout << "Entered VisitVarStmt " << endl;
            string v = "";
            if(stmt->intializer)
            {   v = eval(stmt->intializer);} 

            env->define(stmt->name.tokenLiteral(), v);
            return "";
        }

        string VisitBlockStmt(Block* stmt) override
        {
            executeBlock(stmt->stmts, new Environment(env));
            //list<Stmt*> s = stmt->stmts;
            //Environment *envtemp = env;
           
            return "";
        }
        

        void interpret(list<Stmt*> stmts)
        {
            try {
                //string value = eval(expr);
                //cout << "Eval: " <<  value << endl;
                list<Stmt*>::iterator i;
                int counter = 0;
                for (i = stmts.begin(); i != stmts.end(); i++)
                {
                    counter++;
                    //cout << "c: " << counter << endl;
                    execute(*i);
                }

            } catch (...) {
                cout << "Error in interpreter" << endl;
            }
        }

        void executeBlock(list<Stmt*> s, Environment* e)
        {

            Environment* prev = env;
                try
                {
                    env = e;
                    list<Stmt*>::iterator i;
                    for (i = s.begin(); i != s.end(); i++)
                    {
                        execute(*i);
                    }
                }
                catch(exception e)
                {
                    std::cerr << e.what() << '\n';
                }
            env = prev;
            return;
        }

    private:
        Environment *env = new Environment();
        
        void execute(Stmt* stmt)
        {
            //cout << "   Entered execute" << endl;
            string r = stmt->Accept(this);
        }

        string eval(Expr *expr)
        {
            //cout << "Entered eval" << endl;
            return expr->Accept(this);
        }

        string notTrue(string s)
        {
            //cout << "notTrue (" << s << ")" << endl;
            if (s == "")
            {   
                //cout <<  "  " << s << "is true" << endl; 
                return "true"; 
            }
            if (s == "true") 
            {
                //cout <<  "  " << s << "is false" << endl; 
                return "false"; 
            }
            if (s == "false" || s == "NIL") 
            {
                //cout <<  "  " << s << "is true" << endl; 
                return "true"; 
            }

            return "false";

        }

        bool isDouble(string one, string two)
        {
            //cout << "      checking string one" << one;
            for (int i = 0; i < one.length(); i++)
            {
                if (isdigit(one[i])) continue;
                else if(one[i] =='.' && isdigit(one[i+1])) continue;
                else return false;
            }
            //cout << "      checking string two" << two;
            for (int i = 0; i < two.length(); i++)
            {
                 
                if (isdigit(two[i])) continue;
                else if(one[i] =='.' && isdigit(one[i+1])) continue;
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
            if(isString(one, two))
            {//cout << "        isString" << endl; 
                return compareString(one, two, op);}
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
            {   //cout << "           LEss" << endl;
                if(stod(one) < stod(two)) 
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