#include "testClassesAndMethods.cpp"
#include <string>

/*
fun sayHi(first, last, middle) {
  print "Hi "+first+" "+middle+". "+last;
}
sayHi("Girith", "Choudhary", "m");

fun factorial(n) {
  if(n==0) return 1;
  return n * factorial(n-1);
}

for (var i = 0; i <= 4; i = i + 1) {
  print "factorial of (" + i +") = " +factorial(i);
}
*/
void testRegularFunction()
{
    //cout << "Enter testIfStatement()" << endl;
    ofstream testFile;
    testFile.open("test/testRegularFunctions.txt");

    string code2; 

    string code = "fun sayHi(first, last, middle) {";
    code2 = code;
    code.append("print \"Hi \"+first+\" \"+middle+\". \"+last;");
    code2.append("\n");
    code2.append("print \"Hi \"+first+\" \"+middle+\". \"+last;");
    code.append("}");
    code2.append("\n");
    code2.append("}");
    code.append("sayHi(\"Girith\", \"Choudhary\", \"m\");");
    code2.append("\n");
    code2.append("sayHi(\"Girith\", \"Choudhary\", \"m\");");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());
    //cout << code << endl << endl;

    cout << "testRegularFunction()" << endl;

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
    rdFile.open("test/testRegularFunctions.txt");
    wrFile.open("test/testFunctions.txt");

    string lox = "lox>";

    wrFile << code2 << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    //cout << "Hello World" << line << endl;
        
    getline(rdFile, line);
    assert(line.substr(lox.length()) == "Hi Girith m. Choudhary");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(Hi Girith m. Choudhary)" << endl;

    wrFile << endl << endl;
    rdFile.close();
    remove("test/testRegularFunctions.txt");

}

/*
fun factorial(n) {
  if(n==0) return 1;
  return n * factorial(n-1);
}

for (var i = 0; i <= 4; i = i + 1) {
  print "factorial of (" + i +") = " +factorial(i);
}
*/
void testRecursiveFunction()
{
    //cout << "Enter testIfStatement()" << endl;
    ofstream testFile;
    testFile.open("test/testRecursiveFunctions.txt");

    string code2;
    string code = "fun factorial(n) {";
    code2 = code;
    code.append("  if(n==0) return 1;");
    code2.append("\n");
    code2.append("  if(n==0) return 1;");
    code.append("  return n * factorial(n-1);");
    code2.append("\n");
    code2.append("  return n * factorial(n-1);");
    code.append("}");
    code2.append("\n");
    code2.append("}");
    code.append("for (var i = 0; i <= 4; i = i + 1) {");
    code2.append("\n");
    code2.append("for (var i = 0; i <= 4; i = i + 1) {");
    code.append("  print factorial(i);");
    code2.append("\n");
    code2.append("  print factorial(i);");
    code.append("}");
    code2.append("\n");
    code2.append("}");
    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());

    
    cout << "testRecursiveFunction()" << endl;

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
    rdFile.open("test/testRecursiveFunctions.txt");
    wrFile.open("test/testFunctions.txt", ios_base::app);

    string lox = "lox>";

    wrFile << code2 << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;
        
    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("1"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = " << "(1)" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("1"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = " << "(1)" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("2"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = " << "(2)" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("6"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = " << "(6)" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("24"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = " << "(24)" << endl;

    rdFile.close();
    remove("test/testRecursiveFunctions.txt");

}


void testFunctions()
{
    //cout << "Enter testIfStatement()" << endl;
    testRegularFunction();
    testRecursiveFunction();
}