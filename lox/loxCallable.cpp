#include <string>
#include "stmt.cpp"

using namespace std;

class Interpreter;

class LoxCallable
{
    public:
        virtual ~LoxCallable(){};
        virtual string Call(Interpreter* interpreter, 
                            list<string> args){return "";};
        virtual string arity(){return "";};
};