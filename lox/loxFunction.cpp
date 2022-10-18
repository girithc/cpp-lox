#include "loxCallable.cpp"




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