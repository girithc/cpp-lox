#include <string>
#include <unordered_map>
#include <iterator>
#include "token.cpp"

using namespace std;

class Environment
{
    public:
        Environment* enclosing;
        Environment();
        Environment(Environment* e);
        void define(string name, string value);
        string getItem(Token name);
        void assign(Token name, string value);
    private:
        unordered_map <string, string> valueMap;

};

Environment::Environment()
{
    enclosing = NULL;
}

Environment::Environment(Environment* e)
{
    enclosing = e;
}

void
Environment::define(string name, string value)
{
    //cout << "Entered define{" << name << "," << value << "}" << endl;
    valueMap.insert({{name, value}});
}

string
Environment::getItem(Token name)
{
    //cout << "Enter getItem:" << name.tokenLiteral() << endl;
    if(valueMap.find(name.tokenLiteral()) != valueMap.end())
    {
        //cout << "Found " << endl;
        return valueMap[name.tokenLiteral()];
    } 
    if (enclosing) return enclosing->getItem(name);

    throw invalid_argument("Environment error");
}

void
Environment::assign(Token name, string value)
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