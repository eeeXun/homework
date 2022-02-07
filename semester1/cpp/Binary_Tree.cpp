#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* pLeft;
    Node* pRight;
};

int insertToTree(Node* p, int n)
{
    if (n < p->value) {
        if (p->pLeft != NULL)
            insertToTree(p->pLeft, n);
        else {
            Node* f = new Node;
            p->pLeft = f;
            f->value = n;
            f->pLeft = NULL;
            f->pRight = NULL;
            return 0;
        }
    } else if (n > p->value) {
        if (p->pRight != NULL)
            insertToTree(p->pRight, n);
        else {
            Node* f = new Node;
            p->pRight = f;
            f->value = n;
            f->pLeft = NULL;
            f->pRight = NULL;
            return 0;
        }
    }
}
void printTree(Node* p)
{
    if (p != NULL) {
        printTree(p->pLeft);
        cout << p->value << " ";
        printTree(p->pRight);
    }
}

int main()
{
    int n;
    cin >> n;
    Node* p = new Node;
    if (n == 0) {
        return 0;
    } else {
        p->value = n;
        p->pLeft = NULL;
        p->pRight = NULL;
    }
    while (cin >> n && n > 0) {
        insertToTree(p, n);
    }
    printTree(p);
}
