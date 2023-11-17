#include <stdlib.h>
#include "ClassicLinkedList.hpp"

ErrorCode _classicListDestructorRec(Node* node);

NodeResult NewNode()
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (!node)
        return { NULL, ERROR_NO_MEMORY };
    return { node, EVERYTHING_FINE };
}

ErrorCode NodeDestructor(Node* node)
{
    MyAssertSoft(node, ERROR_NULLPTR);

    node->value = CLASSIC_LIST_POISON;
    node->prev = NULL;
    node->next = NULL;

    free(node);

    return EVERYTHING_FINE;
}

ClassicListResult NewList()
{
    NodeResult headRes = NewNode();
    RETURN_ERROR_RESULT(headRes, {});

    return
    {
        {
            .head = headRes.value,
            .tail = headRes.value,
        },
        EVERYTHING_FINE
    };
}

ErrorCode ClassicListDestructor(ClassicList* list)
{
    MyAssertSoft(list, ERROR_NULLPTR);

    RETURN_ERROR(_classicListDestructorRec(list->head));

    list->head = NULL;
    list->tail = NULL;

    MyAssertSoft(list, ERROR_NULLPTR);

    Node* curNode = list->tail;
    if (!curNode)
        return EVERYTHING_FINE;

    while (curNode)
    {
        curNode = curNode->prev;
        RETURN_ERROR(NodeDestructor(curNode->next));
    }
    return NodeDestructor(curNode->next);
}

// ErrorCode _classicListDestructorRec(Node* node)
// {
//     if (!node)
//         return EVERYTHING_FINE;

//     RETURN_ERROR(_classicListDestructorRec(node->next));

//     return NodeDestructor(node);
// }

ErrorCode PrintList(ClassicList* list)
{
    MyAssertSoft(list, ERROR_NULLPTR);

    printf("List\n{\n");

    Node* current = list->head;
    size_t i = 1;

    while (current)
    {
        printf("%3s list[%zu] = " CLASSIC_LIST_ELEM_SPECIFIER "\n", "", i, current->value);
        current = current->next;
        i++;
    }

    printf("}\n");

    return EVERYTHING_FINE;
}

NodeResult InsertAfter(ClassicListElement_t value, Node* after)
{
    MyAssertSoftResult(after, NULL, ERROR_NULLPTR);

    NodeResult nodeRes = NewNode();
    RETURN_ERROR_RESULT(nodeRes, NULL);

    Node* node = nodeRes.value;

    node->value = value;

    node->prev  = after;
    node->next  = after->next;

    if (after->next)
        after->next->prev = node;
    after->next = node;

    return nodeRes;
}

NodeResult InsertBefore(ClassicListElement_t value, Node* before)
{
    MyAssertSoftResult(before, NULL, ERROR_NULLPTR);

    if (!before->prev)
        return { NULL, ERROR_INDEX_OUT_OF_BOUNDS };

    return InsertAfter(value, before->prev);
}

ClassicListElementResult Pop(Node* node)
{
    MyAssertSoftResult(node, CLASSIC_LIST_POISON, ERROR_NULLPTR);

    ClassicListElement_t value = node->value;

    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    return { value, NodeDestructor(node) };
}

NodeResult FindElement(ClassicList* list, size_t index)
{
    size_t i = 1;
    Node* cur = list->head;

    while (cur && i < index)
    {
        cur = cur->next;
        i++;
    }

    if (cur)
        return { cur, EVERYTHING_FINE };
    return { NULL, ERROR_INDEX_OUT_OF_BOUNDS };
}
