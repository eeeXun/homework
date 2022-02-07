#include <iostream>
using namespace std;

struct ListElement {
    int value; // value of an element
    ListElement* pNext; // Pointer to a list element
};

void addBack(ListElement* pHead, int v);

void printList(ListElement* p);

int main()
{
    ListElement* pHead = new ListElement;
    pHead->pNext = NULL;
    int n;
    cin >> n;
    if (n > 0) {
        pHead->value = n;
    } else {
        return 0;
    }
    while (cin >> n && n > 0) {
        addBack(pHead, n);
    }
    /*
pList = addFront(NULL, 5);
pList = addFront(pList, 4);
pList = addFront(pList, 3);
pList = addFront(pList, 2);
pList = addFront(pList, 1); */
    printList(pHead);
    return 0;
}

void printList(ListElement* pHead)
{
    do {
        std::cout << pHead->value;
        pHead = pHead->pNext;
    } while (pHead != NULL);
    cout << endl;
}

void addBack(ListElement* pHead, int v)
{
    ListElement** PNext = &pHead;
    ListElement* p = new ListElement;
    while ((*PNext)->pNext != NULL) {
        *PNext = (*PNext)->pNext;
    }
    (*PNext)->pNext = p;
    p->value = v;
    p->pNext = NULL;
}
