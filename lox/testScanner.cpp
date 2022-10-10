
#include "testParserAndInterpreter.cpp"
#include <iostream>
#include <cassert>
#include <string>
#include <iterator>
#include <fstream>

using namespace std;


void testDeclaration()
    {
        ofstream testFile;
        testFile.open("test/testScannerResult.txt");

        string code = "var a = \"Declared\";";
        code.append("a = 4;");
        Scanner scanner(code);
        list<Token> testTokens = scanner.scanTokens();
        
        list<Token>::iterator testItr;
        testItr = testTokens.begin();

        testFile << "testDeclaration()" << endl;
    
        assert(testItr->tokenType() == "VAR");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "EQUAL");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "STRING");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "SEMICOLON");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "EQUAL");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "NUMBER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "SEMICOLON");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testFile << endl << endl;
        testFile.close();
    }

void testIfElseAndComparison()
{
        ofstream testFile;
        testFile.open("test/testScannerResult.txt", ios_base::app);

        string code = "if (a<b) {";
        code.append("  print a/b;");
        code.append("} else {");
        code.append("  print a*b;");
        code.append("}");
        Scanner scanner(code);
        list<Token> testTokens = scanner.scanTokens();
        
        list<Token>::iterator testItr;
        testItr = testTokens.begin();

        testFile << "testIfElseAndComparison()" << endl;

        assert(testItr->tokenType() == "IF");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "LEFT_PAREN");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "LESS");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "RIGHT_PAREN");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;
        
        assert(testItr->tokenType() == "LEFT_BRACE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "PRINT");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "SLASH");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "SEMICOLON");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "RIGHT_BRACE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "ELSE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "LEFT_BRACE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "PRINT");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "STAR");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "IDENTIFIER");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "SEMICOLON");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "RIGHT_BRACE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        
        testFile << endl << endl;
        testFile.close();
         
}

void testWhileAndBool()
{
        ofstream testFile;
        testFile.open("test/testScannerResult.txt",  ios_base::app);

        string code = "while (true and false){ // comment";
        code.append("\n");
        code.append(" return true or false;}");
        
        Scanner scanner(code);
        list<Token> testTokens = scanner.scanTokens();
        
        list<Token>::iterator testItr;
        testItr = testTokens.begin();

        testFile << "testWhileAndBool()" << endl;

        assert(testItr->tokenType() == "WHILE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "LEFT_PAREN");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "TRUE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "AND");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "FALSE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "RIGHT_PAREN");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "LEFT_BRACE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "RETURN");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "TRUE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "OR");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "FALSE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "SEMICOLON");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        testItr ++;

        assert(testItr->tokenType() == "RIGHT_BRACE");
        testFile << "Test passed: " << testItr->tokenLiteral() << "="  << testItr->tokenType() << endl;
        
        testFile << endl << endl;
        testFile.close();
}




void testScanner()
    {
        
        cout << "Enter test scanner" << endl;
        testDeclaration();
        testIfElseAndComparison();
        testWhileAndBool();

        
        
        //testIfElseAndComparison();
        //testWhileAndBool();
        //testIfElse();
        //testWhile();
        //testBoolean();

    }

