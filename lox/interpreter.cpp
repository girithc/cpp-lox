#include "stmt.cpp"
#include <string>
#include <string.h>
#include <list>
#include <iterator>
#include <unordered_map>
#include <stdexcept>
#include <any>

class Interpreter;
class Environment;
class LoxCallable
{
    public:
        virtual ~LoxCallable(){};
        virtual string Call(Interpreter* interpreter, 
                            list<string> args){return "";};
        virtual int arity(){return 0;};
        virtual string toString(){return "";};
};
class LoxFunction : public LoxCallable
{
    private:
        any returnValue;
        
    public:
        Function* declaration;
        LoxFunction(Function* d);
        string Call(Interpreter* interpreter, list<string> args) override;
        int arity() override;
        string toString() override;
};
class Environment
{
    public:
        Environment* enclosing;
        Environment();
        Environment(Environment* e);
        void define(string name, string value);
        void defineLoxFunction(string name, LoxFunction* value);
        string getItem(Token name);
        LoxFunction* getLoxFunction(string name);
        void assign(Token name, string value);
    private:
        unordered_map <string, string> valueMap;
        unordered_map <string, LoxFunction*> valueMapLoxFunction;

};
class ReturnRunTime : public runtime_error
{
    public:
        Token t;
        string returnValue;
        ReturnRunTime(string val):runtime_error(val){returnValue = val; }
        ReturnRunTime(Token t, string message);
};

class Interpreter : public Visitor, VisitorStmt
{
    public:
        string VisitLiteralExpr(Literal *expr) override;
        string VisitLogicalExpr(Logical* expr) override;
        string VisitGroupingExpr(Grouping *expr) override;
        string VisitUnaryExpr(Unary *expr) override;
        string VisitVariableExpr(Variable* expr) override;
        string VisitAssignExpr(Assign* expr) override;
        string VisitBinaryExpr(Binary *expr) override;
        string VisitCallExpr(Call* expr) override;

        string VisitExpressionStmt(Expression* stmt) override;
        string VisitFunctionStmt(Function* stmt) override;
        string VisitWhileStmt(While* stmt) override;
        string VisitIfStmt(If* stmt) override;
        string VisitPrintStmt(Print* stmt) override;
        string VisitReturnStmt(Return* stmt) override;
        string VisitVarStmt(Var* stmt) override;
        string VisitBlockStmt(Block* stmt) override;
        
        void interpret(list<Stmt*> stmts);
        void executeBlock(list<Stmt*> s, Environment* e);
        Environment *globals = new Environment();

    private:
        Environment *env = globals;
        string eval(Expr *expr);
        string notTrue(string s);
        string compare(string one, string two, string op);
        string compareString(string one, string two, string op);

        void execute(Stmt* stmt);
        bool isDouble(string one, string two);
        bool isString(string one, string two);

        void checkNumberOperand(Token op, any operand);
        void checkNumberOperandMulti(Token op, any l, any r);

};

LoxFunction::LoxFunction(Function* d)
{
    declaration = d;
}
string LoxFunction::Call(Interpreter* interpreter, list<string> args)
{
    cout << "Enter LoxFunction::Call" << endl;
    Environment *env = new Environment(interpreter->globals);

    list<Token>::iterator iParams = declaration->params.begin();
    list<string>::iterator iArgs = args.begin();
    for (int i = 0; i < declaration->params.size(); i++)
    {
        env->define((*iParams).tokenLiteral(), (*iArgs));
        iParams++;
        iArgs++;
    }

    try
    { 
        cout << "Executing Function block" << endl;
        interpreter->executeBlock(declaration->body, env);
    }
    catch(ReturnRunTime* r)
    {
        cout << "Found Return Value" << endl;
        cout << "   " << r->returnValue << endl;
        return r->returnValue;
        exit(1);
    }
    
    //interpreter->executeBlock(declaration->body, env);
    
    

    return "";
}
string LoxFunction::toString(){ return "<fn " + declaration->name.tokenLiteral() + ">";}
int LoxFunction::arity(){ return declaration->params.size();}


Environment::Environment()
{
    enclosing = NULL;
}
Environment::Environment(Environment* e)
{
    enclosing = e;
}
void Environment::define(string name, string value)
{
    cout << "env> Entered define{" << name << "," << value << "}" << endl;
    valueMap.insert({{name, value}});
}
void Environment::defineLoxFunction(string name, LoxFunction* value)
{
    //cout << "Entered define{" << name << "," << value << "}" << endl;
    string l= "loxFunction";
    define(name,l);
    cout << name << " " << value << endl;
    valueMapLoxFunction.insert({{name, value}});
    cout << name << " " << valueMapLoxFunction[name] << endl;;
}
string Environment::getItem(Token name)
{
    //cout << "Enter getItem:" << name.tokenLiteral() << endl;
    if(valueMap.find(name.tokenLiteral()) != valueMap.end())
    {
        //cout << "Found " << endl;
        if(valueMap[name.tokenLiteral()]=="loxFunction") return name.tokenLiteral()+","+"loxFunction";
        return valueMap[name.tokenLiteral()];
    } 
    if (enclosing) return enclosing->getItem(name);

    throw invalid_argument("Environment error");
}
LoxFunction* Environment::getLoxFunction(string name)
{
    //cout << "Enter getItem:" << name.tokenLiteral() << endl;
    if(valueMapLoxFunction.find(name) != valueMapLoxFunction.end())
    {
        //cout << "Found " << endl;
        return valueMapLoxFunction[name];
    } 
    if (enclosing) return enclosing->getLoxFunction(name);

    throw invalid_argument("Environment error");
}
void Environment::assign(Token name, string value)
{
    //cout << "Entered env Assign" << endl;
    if(valueMap.find(name.tokenLiteral()) != valueMap.end())
    {
        //cout << "Changing key value in map: " << value << endl;
        unordered_map <string, string>::iterator i = valueMap.find(name.tokenLiteral());
        i->second = value;
        return;
    }

    if (enclosing)
    {
        enclosing->assign(name, value);
        return;
    }
    throw invalid_argument("Undefined variable " + name.tokenLiteral() + ".");
}

string Interpreter::VisitLiteralExpr(Literal *expr)
{
    cout << "Entered VisitLiteralExpr() " << expr->value << endl;
    //cout << "Expr.value: " << expr->value << endl;
    return expr->value;
}
string Interpreter::VisitLogicalExpr(Logical* expr) 
{
    cout << "Enter VisitLogicalExpr()" << endl;
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
string Interpreter::VisitGroupingExpr(Grouping *expr) 
{
    cout << "Entered VisitGroupingExpr" << endl;
    return eval(expr->expression);
}
string Interpreter::VisitUnaryExpr(Unary *expr) 
{
    cout << "Entered VisitUnaryExpr" << endl;
    string r = eval(expr->right);

    if (expr->op.tokenType() == "MINUS") return r;
    else if (expr->op.tokenType() == "BANG") return notTrue(r);

    return "";      
}
string Interpreter::VisitVariableExpr(Variable* expr) 
{
    cout << "Entered VisitVariableExpr: " << expr->name.tokenLiteral() << endl;
    return env->getItem(expr->name);
}
string Interpreter::VisitAssignExpr(Assign* expr) 
{
    cout << "Entered VisitAssignExpr" << endl;
    string v = eval(expr->value);
    //cout << "   new Value: " << v << endl;
    env->assign(expr->name, v);
    return "";
}
string Interpreter::VisitBinaryExpr(Binary *expr) 
{
    cout << "Entered VisitBinaryExpr" << endl;
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
string Interpreter::VisitCallExpr(Call* expr) 
{
    cout << "Enter VisitCallExpr()" << endl;
    string callee = eval(expr->callee);
    cout << "   Entered VisitCallExpr() again" << endl;
    LoxFunction* func;
    string returnFunc = "NIL";
    
    string lf = ",loxFunction";
    if(callee.find(lf) != string::npos)
    {
        string functionName = callee.substr(0, callee.find(','));
        func = env->getLoxFunction(functionName);
        list<string> args;

        list<Expr*>::iterator i;
        for (i = expr->arguments.begin(); 
        i != expr->arguments.end(); i++)
        {
            args.push_back(eval(*i));
        }
        cout << "function param: " ;
        cout << func->declaration->params.size() << endl;

        returnFunc = func->Call(this,args);
    }

    return returnFunc;
}
string Interpreter::VisitExpressionStmt(Expression* stmt) 
{
    cout << "Entered VisitExpressionStmt()" << endl;
    string e = eval(stmt->expression);
    return "";
}
string Interpreter::VisitFunctionStmt(Function* stmt) 
{
    cout << "Entered VisitFunctionStmt()" << endl;
    LoxFunction* loxFunc = new LoxFunction(stmt);
    cout << "   " << stmt->name.tokenLiteral() << endl;
    env->defineLoxFunction(stmt->name.tokenLiteral(), loxFunc);
    return "NIL";
}
string Interpreter::VisitWhileStmt(While* stmt) 
{
    cout << "Entered VisitWhileStmt" << endl;
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
string Interpreter::VisitIfStmt(If* stmt) 
{
    cout << "Enter VisitIfStatement()" << endl;
    if(notTrue(eval(stmt->condition)) == "false")
    {
        //cout << "   Enter ifBranch" << endl;
        execute(stmt->ifBranch);
    }

    else if(stmt->elseBranch)
        execute(stmt->elseBranch);

    return "";
}
string Interpreter::VisitPrintStmt(Print* stmt) 
{
    cout << "   Entered VisitPrintStmt" << endl;
    string v = eval(stmt->expression);
    cout  << "lox>" <<  v << endl;
    
    return "";
}
string Interpreter::VisitReturnStmt(Return* stmt)
{
    cout << "Enter VisitReturnStmt" << endl;
    string val = "";
    if(stmt) val = eval(stmt->value);

    throw new ReturnRunTime(val);
}
string Interpreter::VisitVarStmt(Var* stmt) 
{
    cout << "Entered VisitVarStmt " << endl;
    string v = "";
    if(stmt->init)
    {   v = eval(stmt->init);} 

    env->define(stmt->name.tokenLiteral(), v);
    return "";
}
string Interpreter::VisitBlockStmt(Block* stmt)
{
    cout << "Entered VisitBlockStmt " << endl;

    executeBlock(stmt->stmts, new Environment(env));
    //list<Stmt*> s = stmt->stmts;
    //Environment *envtemp = env;
    
    return "";
}
void Interpreter::interpret(list<Stmt*> stmts)
{
    try {
        //string value = eval(expr);
        //cout << "Eval: " <<  value << endl;
        cout << "Enter interpret()" << endl;
        list<Stmt*>::iterator i;
        int counter = 0;
        for (i = stmts.begin(); i != stmts.end(); i++)
        {
            
            cout << "executing " << "counter=" << counter << endl;
            execute(*i);
            counter++;
        }

    } catch (...) {
        cout << "Error in interpreter" << endl;
    }
}
void Interpreter::executeBlock(list<Stmt*> s, Environment* e)
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
            cout << "Exception in interpreter" << endl;
            std::cerr << e.what() << '\n';
        }
    env = prev;
    return;
}
void Interpreter::execute(Stmt* stmt)
{
    //cout << "   Entered execute" << endl;
    string r = stmt->Accept(this);
    cout << "Done executing " << endl << endl; 
}
string Interpreter::eval(Expr *expr)
{
    //cout << "Entered eval" << endl;
    return expr->Accept(this);
}
string Interpreter::notTrue(string s)
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
bool Interpreter::isDouble(string one, string two)
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
bool Interpreter::isString(string one, string two)
{
    if(isDouble(one, two)) return false;
    return true;
}
//left to do. Equal and Unequal for null
string Interpreter::compare(string one, string two, string op)
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
string Interpreter::compareString(string one, string two, string op)
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

