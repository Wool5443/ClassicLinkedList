#include "ClassicLinkedList.hpp"

int main()
{
    ClassicList list = NewList().value;
    list.head->value = 1;

    int n = 11;

    Node* current = list.head;
    for (int i = 2; i < n; i++)
        current = InsertAfter((double)i, current).value;

    InsertAfter(2.5, list.head->next);
    InsertBefore(1.5, list.head->next);

    Remove(FindElement(&list, 8).value);

    PrintList(&list);

    ClassicListDestructor(&list);

    return 0;
}
