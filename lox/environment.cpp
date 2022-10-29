#include <string>
#include <unordered_map>
#include <iterator>
#include "token.cpp"

using namespace std;

class Environment1
{
    public:
        Environment1* enclosing;
        Environment1();
        Environment1(Environment1* e);
        void define(string name, string value);
        string getItem(Token name);
        void assign(Token name, string value);
    private:
        unordered_map <string, string> valueMap;

};
Environment1::Environment1()
{
    enclosing = NULL;
}
Environment1::Environment1(Environment1* e)
{
    enclosing = e;
}
void
Environment1::define(string name, string value)
{
    //cout << "Entered define{" << name << "," << value << "}" << endl;
    valueMap.insert({{name, value}});
}
string
Environment1::getItem(Token name)
{
    //cout << "Enter getItem:" << name.tokenLiteral() << endl;
    if(valueMap.find(name.tokenLiteral()) != valueMap.end())
    {
        //cout << "Found " << endl;
        return valueMap[name.tokenLiteral()];
    } 
    if (enclosing) return enclosing->getItem(name);

    throw invalid_argument("Environment1 error");
}

void
Environment1::assign(Token name, string value)
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