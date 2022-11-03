

Instructions to run the program

run command to generate executeable a.out: g++ lox/lox.cpp  -std=c++17.
run command: ./a.out sample/s2.lox

Procedure to run a lox file:
Put the .lox file in the sample folder
run the command: ./a.out sample/filename.lox

Testing

command to test Scanner: ./a.out scanner
command to test Parser and Interpreter: ./a.out interpreter or ./a.out parser 
command to test Lox Functions: ./a.out function
command to test Lox Classes and Methods: ./a.out class
command to test all of the above together: ./a.out all


Test Case results are in the test folder.
testScanner.txt has the test cases for the scanner
testParserAndInterpreter.txt has the test cases for the parser and interpreter
testFunctions.txt has the test cases for lox Functions
testClassesAndMethods.txt has the test cases for the lox Classes and Methods

About the Lox interpreter:

This lox interpreter is written in c++.
All the computations of the lox interpreter is done in the lox folder.
This lox interpreter is based on the lox interpreter shown in the book craftinginterpreters.

This lox interpreter does not support inheritance.
