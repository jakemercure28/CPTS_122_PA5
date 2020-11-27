#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include "cardData.h"

#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;



class DynamicStack
{
    private:

        struct StackNode{
            cardData data;
            StackNode* next;  // Pointer to next node
        };
        StackNode* top;     // Pointer to the stack top

    public:
        //Constructor
        DynamicStack()
        {
            top = nullptr;
        }

        // Destructor
        ~DynamicStack();

        // Stack operations
        void push(cardData card);
        void pop(cardData &card);
        bool isEmpty();
    };
#endif