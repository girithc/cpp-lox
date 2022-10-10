#include "scanner.cpp"
#include <iostream>
#include <cassert>
#include <string>
#include <iterator>
#include <fstream>

using namespace std;

/*
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
    ofstream testFile;
    testFile.open("test/testIf.txt");

    string code = "var a = 1;";
    code.append("if ( a < 1) print \"a is less than 1\" ;");
    code.append("else print \"a is greater than 1\";");
    code.append("if(true) print \"yes\" or nil;");
    code.append("if(!nil) print true and false;");

    cout.rdbuf(testFile.rdbuf());

    cout << "testIfStatement()" << endl;

    Scanner scanner(code);
    list<Token> testTokens = scanner.scanTokens();

    Parser parser(testTokens);
    list<Stmt*> stmts = parser.parse();

    Interpreter* interpreter = new Interpreter();
    interpreter->interpret(stmts);

    testFile.close();

    ifstream rdFile;
    rdFile.open("test/testIf.txt");

    


}

void testWhileStatement()
{
    ofstream testFile;
    testFile.open("test/testWhile.txt");
    //input file
    string code = "var a = 4; var i = 8;";
    code.append("while ( a < i) { ");
    code.append("print a; a = a+1; }");
    code.append("print a;");

    cout.rdbuf(testFile.rdbuf());

    cout << "testWhileStatement()" << endl;

    Scanner scanner(code);
    list<Token> testTokens = scanner.scanTokens();

    Parser parser(testTokens);
    list<Stmt*> stmts = parser.parse();

    Interpreter* interpreter = new Interpreter();
    interpreter->interpret(stmts);

    testFile.close();
}

void testForStatement()
{
    ofstream testFile;
    testFile.open("test/testFor.txt");

    string code = "var i = 4;";
    code.append("for (var a = 0; a<i; a=a+1)");
    code.append("{print a;}");

    cout.rdbuf(testFile.rdbuf());

    cout << "testForStatement()" << endl;

    Scanner scanner(code);
    list<Token> testTokens = scanner.scanTokens();

    Parser parser(testTokens);
    list<Stmt*> stmts = parser.parse();

    Interpreter* interpreter = new Interpreter();
    interpreter->interpret(stmts);

    testFile.close();
}




void testParserAndInterpreter()
{
    cout << "Enter testParserAndInterpreter()" << endl;
    testIfStatement();
    testWhileStatement();
    testForStatement();
}