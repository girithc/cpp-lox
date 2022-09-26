#include "tokenType.cpp"
#include <string>
#include <iterator>

using namespace std;


class Parser {
    private:
    
    list<Token> tokens;
    int current = 0;

    string equality()
    {
        string expr = comparison();

        while(match(BANG_EQUAL, EQUAL_EQUAL))
        {
            Token operator = previous();
            string right = comparison();
            right = 
        }
    }

    string expression()
    {
        return equality();
    }

    public:

    void Parser(list<Token> t)
    {
        tokens = t;
    }
    
};