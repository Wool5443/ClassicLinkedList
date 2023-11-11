#include "ClassicLinkedListSettings.ini"
#include "Utils.hpp"

struct Node
{
    ClassicListElement_t value;
    Node* prev;
    Node* next;
};

struct NodeResult
{
    Node* value;
    ErrorCode error;
};

struct ClassicList
{
    Node* head;
    Node* tail;
};

struct ClassicListResult
{
    ClassicList value;
    ErrorCode error;
};

struct ClassicListElementResult
{
    ClassicListElement_t value;
    ErrorCode error;
};

enum ClassicListDestructorStart { HEAD, TAIL };

ClassicListResult NewList();

NodeResult NewNode();

ErrorCode NodeDestructor(Node* node);

ErrorCode ClassicListDestructor(ClassicList* list);

ErrorCode PrintList(ClassicList* list);

NodeResult InsertAfter(ClassicListElement_t value, Node* after);

NodeResult InsertBefore(ClassicListElement_t value, Node* before);

ClassicListElementResult Pop(Node* node);

NodeResult FindElement(ClassicList* list, size_t index);
