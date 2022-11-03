#include "testParserAndInterpreter.cpp"
#include <string>

/*
class Waffles {
  eat() {
    return "eating Waffles";
  }
  make() {
    print "making Waffles";
  }
}

print Waffles;
var foodItem = Waffles();
print foodItem;
foodItem.make();
print foodItem.eat();




class Thing {
  getCallback() {
    fun localFunction() {
      print this;
    }
    return localFunction;
  }
}

var callback = Thing().getCallback();
callback();
*/
void testRegularClass()
{
    //cout << "Enter testIfStatement()" << endl;
    ofstream testFile;
    testFile.open("test/testRegularClass.txt");


    string code = "class Waffles {";
    code.append("\n");
    code.append("  eat() {");
    code.append("\n");
    //code2.append("  eat() {");
    code.append("    return \"eating Waffles\";");
    code.append("\n");
    //code2.append("    return \"eating Waffles\";");
    code.append("  }");
    code.append("\n");
    code.append("make() {");
    code.append("\n");
    code.append("    print \"making Waffles\";");
    code.append("\n");
    code.append(" }}");
    code.append("\n");
    //code2.append("sayHi(\"Girith\", \"Choudhary\", \"m\");");
    code.append("print Waffles;");
    code.append("\n");
    code.append("var foodItem = Waffles();");
    code.append("\n");
    code.append("print foodItem;");
    code.append("\n");
    code.append("foodItem.make();");
    code.append("\n");
    code.append("print foodItem.eat();");
    code.append("\n");
    
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());
    //cout << code << endl << endl;
    string lox = "lox>";
    cout << "testRegularClass()" << endl;

    Scanner scanner(code);
    list<Token> testTokens = scanner.scanTokens();

    Parser parser(testTokens);
    list<Stmt*> stmts = parser.parse();

    Interpreter* interpreter = new Interpreter();
    interpreter->interpret(stmts);

    testFile.close();

    cout.rdbuf(oldCout);
    ifstream rdFile;
    ofstream wrFile;

    string line;
    rdFile.open("test/testRegularClass.txt");
    wrFile.open("test/testClassesAndMethods.txt");


    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    //cout << "Hello World" << line << endl;
        
    getline(rdFile, line);
    assert(line.substr(lox.length()) == "Waffles,loxClass");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(Waffles, loxClass)" << endl;

    getline(rdFile, line);
    assert(line.substr(lox.length()) == "Waffles <instance>");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(Waffles <instance>)" << endl;

    getline(rdFile, line);
    //cout << line << endl;
    assert(line.substr(lox.length()) == "making Waffles");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(making Waffles)" << endl;

    getline(rdFile, line);
    assert(line.substr(lox.length()) == "eating Waffles");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(eating Waffles)" << endl;

    
    wrFile << endl << endl;
    rdFile.close();
    remove("test/testRegularClass.txt");

}

/*
class Memory {
  getLocation() {
    fun localMemory() {
      print this;
    }
    return localMemory;
  }
}

var location = Memory().getLocation();
location();
*/
void testClassThis()
{
    //cout << "Enter testIfStatement()" << endl;
    ofstream testFile;
    testFile.open("test/testClassThis.txt");

    string code;
    code.append("\n");
    code.append("class Memory {");
    code.append("\n");
    //code2.append("  eat() {");
    code.append("  getLocation() {");
    code.append("\n");
    //code2.append("    return \"eating Waffles\";");
    code.append("    fun localMemory() {");
    code.append("\n");
    code.append("      print this;");
    code.append("\n");
    code.append("    }");
    code.append("\n");
    code.append("    return localMemory;");
    code.append("\n");
    //code2.append("sayHi(\"Girith\", \"Choudhary\", \"m\");");
    code.append(" }}");
    code.append("\n");
    code.append("var location = Memory().getLocation();");
    code.append("\n");
    code.append("location();");
    code.append("\n");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());

    
    cout << "testClassThis()" << endl;

    Scanner scanner(code);
    list<Token> testTokens = scanner.scanTokens();

    Parser parser(testTokens);
    list<Stmt*> stmts = parser.parse();

    Interpreter* interpreter = new Interpreter();
    interpreter->interpret(stmts);

    testFile.close();

    cout.rdbuf(oldCout);
    ifstream rdFile;
    ofstream wrFile;

    string line;
    rdFile.open("test/testClassThis.txt");
    wrFile.open("test/TestClassesAndMethods.txt", ios_base::app);

    string lox = "lox>";

    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    string memory = "0x";
    getline(rdFile, line);
    assert(line.substr(lox.length()).find(memory) != string::npos);
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(0x This (ClassMemory))" << endl;

        
   

    rdFile.close();
    remove("test/testClassThis.txt");

}
void testClassesAndMethods()
{
    //cout << "Enter testIfStatement()" << endl;
    testRegularClass();
    testClassThis();
}