
#include <string.h>

using namespace std;


class ExprNode
{
    public:

        string value;
        ExprNode *left;
        ExprNode *right;

        ExprNode()
        {
            left = nullptr;
            right = nullptr;
        }

        ExprNode(string v)
        {
            value = v;
            left = nullptr;
            right = nullptr;
        }

        ExprNode(ExprNode *l, string m, ExprNode* r)
        {
            value = m;
            left = l;
            right = r;
        }
};



