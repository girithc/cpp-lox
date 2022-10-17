




class LoxFunction : public LoxCallable
{
    public:
        LoxFunction(Function* d)
        {
            declaration = d;
        }

        string Call(Interpreter* interpreter, 
                    list<string> args)
        {
            
        }


    private:
        Function* declaration;



};