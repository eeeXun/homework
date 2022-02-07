#include <iostream>
using std::cin;
using std::cout;
using std::endl;

struct ListElement {
    int value; // value of an element
    ListElement* pNext; // Pointer to a list element
};

ListElement* addFront(ListElement* pList, int v);

void printList(ListElement* p);

int main()
{
    ListElement* pList = NULL;
    int n;
    while (cin >> n && n > 0) {
        pList = addFront(pList, n);
    }
    /*
pList = addFront(NULL, 5);
pList = addFront(pList, 4);
pList = addFront(pList, 3);
pList = addFront(pList, 2);
pList = addFront(pList, 1); */
    printList(pList);
    return 0;
}

void printList(ListElement* p)
{
    while (p != NULL) {
        std::cout << p->value;
        p = p->pNext;
    }
    cout << endl;
}

ListElement* addFront(ListElement* pList, int v)
{
    ListElement* p = new ListElement;
    p->pNext = pList;
    p->value = v;
    return p;
}
