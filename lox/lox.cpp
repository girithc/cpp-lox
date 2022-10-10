#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include "testScanner.cpp"

//#include "scanner.cpp"

using namespace std;


class Lox 
{

        public:

        bool hadError = false;

        void runFile(string path)
        {
            ifstream fstream;
            fstream.open(path);
            string data;
            string srcCode;
            string newLine = "\n";
            cout << "Path >> " << path << endl;
            if(fstream.good())
            {
                //cout << endl << "File Data: " << endl;
                while (!fstream.eof()) 
                {
                    getline(fstream, data);
                    //cout << fdata << endl ;
                    srcCode.append(data);
                    srcCode.append(newLine);
                }
                //cout << srcCode << endl ;
                run(srcCode);
            }
            else
            {
                cout << "Failed to open file: " << path << endl; 
            }

            if (hadError) exit(65);

        }

        void runPrompt()
        {
            //running code
            string srcCode;
            string lineCode;
            cout << "> ";
            while(cin >> lineCode)
            {
                srcCode.append(lineCode);
            }
            run(lineCode);
            hadError = false;
        }


        void run(string code)
        {
            
            Scanner scanner (code);
            
            list<Token> tokens = scanner.scanTokens();
            //exit(1);
            list<Token>::iterator itr;
            
            int tokenCounter = 0;
            //exit(1);
            for (itr = tokens.begin(); itr != tokens.end(); itr++ )
            {
                //cout << " Token Counter : " << tokenCounter << endl;
                cout << itr->tokenType() << endl;

                tokenCounter++;
            }

            Parser parser(tokens);
            cout << endl << "---- Start Parse ----" << endl;
            //Expr* expr = parser.parse();
            list<Stmt*> stmts = parser.parse();
            cout << "---- Parse ended ----" << endl << endl;

            Interpreter* interpreter = new Interpreter();

            cout << "---- Start Interpreter ----" << endl;
            interpreter->interpret(stmts);
            cout << "---- Interpreter ended ----" << endl << endl;
            exit(1);
        }

        void error(int line, string message)
        {
            report(line, "", message);
        }

        void report(int line, string where, string message)
        {
            cout << "Error:" <<  " [line " << line <<  "] Error" <<  where << ": " 
                    << message;
            hadError = true;
        }
};

    int main(int argc, char** argv)
    {   
        Lox lox;
        if (argc == 2 && strcmp(argv[1],"scanner")==0)
        {
            cout << "Testing Scanner..." << endl; 
            testScanner();
        } 
        else if (argc == 2 && strcmp(argv[1],"parser")==0)
        {
            //testScanner();
            cout << "Testing Interpreter and Parser..." << endl;
            testParserAndInterpreter();
        } 
        else if (argc == 2 && strcmp(argv[1],"interpreter")==0)
        {
            //testScanner();
            cout << "Testing Interpreter and Parser..." << endl;
            testParserAndInterpreter();
        } 
        else if (argc > 2)
        {
            cout << "Usage: jlox [script]";
            cout << argc << endl;
            exit(64);
        } 
        else if (argc == 2)
        {
            lox.runFile(argv[1]);
        }
        else
        {
            lox.runPrompt();
        }
}