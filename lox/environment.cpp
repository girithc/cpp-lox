#include <string>
#include <unordered_map>
#include "token.cpp"

using namespace std;

class Environment
{
    public:
        void define(string name, string value);
        string getItem(Token name);
    private:
        unordered_map <string, string> valueMap;
};

void
Environment::define(string name, string value)
{
    cout << "Entered define{" << name << "," << value << "}" << endl;
    valueMap.insert({{name, value}});
}

string
Environment::getItem(Token name)
{
    cout << "Enter getItem:" << name.tokenLiteral() << endl;
    if(valueMap.find(name.tokenLiteral()) != valueMap.end())
    {
        cout << "Found " << endl;
        return valueMap[name.tokenLiteral()];
    } 
     throw invalid_argument("Environment error");
}