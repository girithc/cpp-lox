#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <iterator>

using namespace std;

list<string> tokenizeString(string listOfStrings, char buf)
    {
        stringstream ssList(listOfStrings);
        string listItem;
        list<string> res;

        while (!ssList.eof())
        {
            getline(ssList, listItem, buf);
            res.push_back(listItem);
        }
        return res;
    }

int main()
{
    list<string> types;
        types.push_back("Unary    :Token operator,Expr right");
        types.push_back("Literal  :Object value");
        types.push_back("Grouping :Expr expression");
        types.push_back("Binary   :Expr left,Token operator,Expr right");
    

    string className;
    string fields;
    for (const string & i: types)
    {
        className = i.substr(0, i.find(':')); //= i->name.substr(0, ":");
        fields = i.substr(i.find(':')+1);
            
        cout << fields << endl;
        list<string> fieldItems = tokenizeString(fields, ',');
        for (const string & j: fieldItems)
        {
            cout << "field Item: " ;
            cout << j.substr(j.find(" ")+1) << endl;
        }

        cout << endl << endl;
    }
}