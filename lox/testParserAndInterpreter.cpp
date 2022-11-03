#include "scanner.cpp"
#include <iostream>
#include <cassert>
#include <string>
#include <string.h>
#include <iterator>
#include <fstream>

using namespace std;

/*
testCases 

var i = 1;
  for (var a = 0; i < 3; a=a+1) {
    i =a;
    print a;
  }
  
  print i;

var a = 1;
while(a > 0)
{
  a = i;
  i = i -1;
  print a;

}

if ( a < 1) print "a is less than 1: a =" + a;
else print "a is greater than 1";
*/

void testIfStatement()
{
    //cout << "Enter testIfStatement()" << endl;
    ofstream testFile;
    testFile.open("test/testIf.txt");

    string code = "var a = 1;";
    code.append("if ( a < 1) print \"a is less than 1\" ;");
    code.append("\n");
    code.append("else print \"a is greater than 1\";");
    code.append("\n");
    code.append("if(true) print \"yes\" or nil;");
    code.append("\n");
    code.append("if(!nil) print true and false;");
    code.append("\n");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());

    cout << "testIfStatement()" << endl;

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
    rdFile.open("test/testIf.txt");
    wrFile.open("test/testParserAndInterpreter.txt");

    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    string lox = "lox>";

    getline(rdFile, line);
    assert(line.substr(lox.length()) == "a is greater than 1");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(a is greater than 1)" << endl;


    getline(rdFile, line);
    assert(line.substr(lox.length()) == "yes");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(yes)" << endl;

    getline(rdFile, line);
    assert(line.substr(lox.length()) == "FALSE");
    wrFile << "Test passed: (" << line.substr(lox.length()) << ") = " << "(FALSE)" << endl << endl;

    rdFile.close();
    remove("test/testIf.txt");


}

void testWhileStatement()
{
    ofstream testFile;
    testFile.open("test/testWhile.txt");
    //input file
    string code = "var a = 4; var i = 8;";
    code.append("\n");
    code.append("while ( a < i) { ");
    code.append("\n");
    code.append("print a; a = a+1; }");
    code.append("\n");
    code.append("print a;");
    code.append("\n");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());

    cout << "testWhileStatement()" << endl;

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
    rdFile.open("test/testWhile.txt");
    wrFile.open("test/testParserAndInterpreter.txt", ios_base::app);

    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;

    string lox = "lox>";
    
    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("4"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("4") << ")" << endl;


    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("5"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("5") << ")" << endl;


    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("6"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("6") << ")" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("7"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("7") << ")" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("8"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("8") << ")" << endl << endl;


    rdFile.close();
    remove("test/testWhile.txt");
}

void testForStatement()
{
    ofstream testFile;
    testFile.open("test/testFor.txt");

    string code = "var i = 4;";
    code.append("\n");
    code.append("for (var a = 0; a<i; a=a+1)");
    code.append("\n");
    code.append("{print a;}");
    code.append("\n");

    streambuf* oldCout = cout.rdbuf();
    cout.rdbuf(testFile.rdbuf());

    cout << "testForStatement()" << endl;
    

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
    rdFile.open("test/testFor.txt");
    wrFile.open("test/testParserAndInterpreter.txt", ios_base::app);

    string lox = "lox>";

    wrFile << code << endl << endl;

    getline(rdFile, line);
    wrFile << line << endl;
    
    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("0"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("0") << ")" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("1"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("1") << ")" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("2"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("2") << ")" << endl;

    getline(rdFile, line);
    assert(stod(line.substr(lox.length())) == stod("3"));
    wrFile << "Test passed: (" << stod(line.substr(lox.length())) << ") = (" << stod("3") << ")" << endl << endl;

    rdFile.close();
    remove("test/testFor.txt");
}




void testParserAndInterpreter()
{
    //cout << "Enter testParserAndInterpreter()" << endl;
    testIfStatement();
    testWhileStatement();
    testForStatement();
}