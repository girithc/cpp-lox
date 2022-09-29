#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;


class GenerateAst
{
    private:

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

    void defineVisitor(ofstream& writeFile, string baseName
                        list<string> types)
    {

    }

    void defineType(ofstream& writeFile,  string baseName, 
                    string className, string fieldList)
    {
        writeFile << "  class " << className << ": "
        << "public " << baseName << " {" << endl;

        //Constructor
        writeFile << "      " << className << " (" <<
                fieldList << ") {";

        //Parameter store - fields
        list<string> fields = tokenizeString(fieldList, ',');
        for (const string & i: fields)
        {
            string name = is.substr(i.find(" ")+1)
            writeFile << "      this." 
            << name << " = " << name << ";" << endl;
        }

        writeFile << "      }" << endl;

        for (const string & i: fields)
        {
            writeFile << "      " << i << ";" << endl;
        }
        writeFile << endl;
    }

    void defineAst(string outputDir, string baseName, list<string> types)
    {
        string path = outputDir;
        path.append("/");
        path.append(baseName);
        path.append(".cpp");

        ofstream writeFile;
        writeFile.open(path);

        writeFile << "#include <string>" << endl;
        writeFile << "using namespace std;" << endl;

        writeFile << "class " << baseName << "{" << endl;
        
        //AST Class
        writeFile << "  public:" << endl;

        for (const string & i: types)
        {
            string className = i.substr(0, i.find(':')); //= i->name.substr(0, ":");
            string fields = i.substr(i.find(':')+1);
            defineType(writeFile, baseName, className, fields);
            
            //cout << className << "//" << fields << endl;
        }


        defineVisitor(writeFile, baseName, types);

        writeFile << "}" << endl;

    }
    
    public:
    int main(int argc, char** argv) 
    {
        if(argc != 1)
        {
            cout << "Usage: generate_ast <output directory>" << endl;
            exit(1);
        }
        string outputDir(argv[0]);

        list<string> typeOfExpression;
        typeOfExpression.push_back("Unary    :Token operator,Expr right");
        typeOfExpression.push_back("Literal  :Object value");
        typeOfExpression.push_back("Grouping :Expr expression");
        typeOfExpression.push_back("Binary   :Expr left,Token operator,Expr right");
        
        defineAst(outputDir, "Expr", typeOfExpression);
        }
};

