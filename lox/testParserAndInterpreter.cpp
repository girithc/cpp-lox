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
    testFile.open("test/testParserAndScannerResult.txt");
    testFile.close();
}

void testWhileStatement()
{
    ofstream testFile;
    testFile.open("test/testParserAndScannerResult.txt", ios_base::app);
    testFile.close();
}

void testForStatement()
{
    ofstream testFile;
    testFile.open("test/testParserAndScannerResult.txt", ios_base::app);
    testFile.close();
}




void testParserAndInterpreter()
{
    cout << "Enter testParserAndInterpreter()" << endl;
    testIfStatement();
    testWhileStatement();
    testForStatement();
}