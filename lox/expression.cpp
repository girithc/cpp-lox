#include "token.cpp"
#include <string>

using namespace std;

struct exprNode
{
    string value;
    exprNode *left;
    exprNode *right;
};

class ExprTree()
{
    exprNode *head;

    void ExprTree()
    {
        head = NULL;
    }

    void insert(string v, exprNode* e)
    {
        
    }
};