#include <iostream>
using namespace std;

struct ListElement {
    int value;
    ListElement* pNext;
};

int insertToList(ListElement* pBefore, ListElement* pHead, int n)
{
    if (n > pHead->value) {
        if (pHead->pNext != NULL) {
            insertToList(pHead, pHead->pNext, n);
        } else {
            ListElement* f = new ListElement;
            pHead->pNext = f;
            f->value = n;
            f->pNext = NULL;
            return 0;
        }
    } else if (n < pHead->value) {
        ListElement* f = new ListElement;
        pBefore->pNext = f;
        f->value = n;
        f->pNext = pHead;
        return 0;
    }
}
void printList(ListElement* pHead)
{
    if (pHead != NULL) {
        cout << pHead->value;
        printList(pHead->pNext);
    }
}

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
        if (n < pHead->value) {
            ListElement* f = new ListElement;
            f->value = n;
            f->pNext = pHead;
            pHead = f;
        } else
            insertToList(NULL, pHead, n);
    }
    printList(pHead);
}
