#include "stack.h"


DynamicStack::~DynamicStack() {
    StackNode* nodePtr, * nextNode;

    // Position nodePtr at the top of the stack.
    nodePtr = top;

    // Traverse the list deleting each node.
    while (nodePtr != nullptr)
    {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

void DynamicStack::push(cardData card)
{
    StackNode* newNode = nullptr; // Pointer to a new node

    // Allocate a new node and store num there.
    newNode = new StackNode;
    newNode->data = card;

    // If there are no nodes in the list
    // make newNode the first node.
    if (isEmpty())
    {
        top = newNode;
        newNode->next = nullptr;
    }
    else  // Otherwise, insert NewNode before top.
    {
        newNode->next = top;
        top = newNode;
    }
}

void DynamicStack::pop(cardData& card)
{
    StackNode* temp = nullptr; // Temporary pointer

    // First make sure the stack isn't empty.
    if (isEmpty())
    {
        cout << "The stack is empty.\n";
    }
    else  // pop value off top of stack
    {
        card = top->data;
        temp = top->next;
        delete top;
        top = temp;
    }
}

bool DynamicStack::isEmpty()
{
    if (!top)
        return true;
    else
        return false;
}