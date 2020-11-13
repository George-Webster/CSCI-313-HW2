//Header File: linkedStack.h 

#ifndef H_StackType
#define H_StackType

#include <iostream>
#include <cassert> 
#include "stackADT.h"
using namespace std;

//Define the node 
template <class Type>
struct nodeType
{
    //the information contained in the node
    Type info;

    //the pointer to the next node
    nodeType<Type>* link;
};

template <class Type>
class linkedStackType : public stackADT<Type>
{
public:
    //Assignment operator overload
    const linkedStackType<Type>& operator=
        (const linkedStackType<Type>&);
 
    //Function returns true when stack is empty
    bool isEmptyStack() const;

    //Function returns true when stack is full
    bool isFullStack() const;

    //Sets an empty stack, or deletes the node of a stack until it is empty
    void initializeStack();
    //Postcondition: stackTop = nullptr

    //Function to add a newItem to the stack
    void push(const Type& newItem);
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem is added to the top of the stack.

    //function to return the top of the stack
    Type top() const;
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program terminates; otherwise, the top element of the stack is returned.

    //function to remove the top of the stack
    void pop();
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top element is removed from the stack.

    //default constructor
    linkedStackType();
    //Postcondition: stackTop = nullptr;

    //copy constructor
    linkedStackType(const linkedStackType<Type>& otherStack);

    //destructor
    ~linkedStackType();
    //Postcondition: All the elements of the stack are removed from the stack.

private:
    //pointer to the stack
    nodeType<Type>* stackTop; //pointer to the stack

    //function to make a copy of the otherStack
    void copyStack(const linkedStackType<Type>& otherStack);
    
};


//Default constructor
template <class Type>
linkedStackType<Type>::linkedStackType()
{
    //Merely creates a pointer to nullptr
    stackTop = nullptr;
}

//Bool isEmpty function
template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    //returns true if stackTop is equal to nullptr, meaning the stack is empty
    return(stackTop == nullptr);
} //end isEmptyStack

//Bool isFull function
template <class Type>
bool linkedStackType<Type>::isFullStack() const
{
    //because it is a linked list, the stack can never be full
    return false;
} //end isFullStack

//initialize stack. i.e. return it to an empty stack
template <class Type>
void linkedStackType<Type>::initializeStack()
{
    //temporary pointer needed to delete the node after the stackTop has moved
    nodeType<Type>* temp; 

    //While the stack contains elements, stackTop will not equal nullptr
    while (stackTop != nullptr)
    {
        //set temp equal to the current node
        temp = stackTop;    

        //move stackTop to the next node
        stackTop = stackTop->link; 

        //delete temp to free the memory space
        delete temp;    
    }
} //end initializeStack

//push function
template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    //pointer to create new node
    nodeType<Type>* newNode; 

    //create the node
    newNode = new nodeType<Type>; 

    //store newElement in newNode->info
    newNode->info = newElement; 

    //place the newNode "on top" of the old stackTop
    newNode->link = stackTop; 

    //set stackTop equal to the newNode, so it becomes the new top
    stackTop = newNode;       
} //end push


template <class Type>
Type linkedStackType<Type>::top() const
{
    //if the stack is empty, exit
    assert(stackTop != nullptr); 

    //return the information contained in the top of the stack
    return stackTop->info;
}//end top

template <class Type>
void linkedStackType<Type>::pop()
{
    //temporary pointer needed to delete the node after the stackTop has moved
    nodeType<Type>* temp;  

    //check if stack is empty
    if (stackTop != nullptr)
    {
        //set the temporary node equal to the node to be deleted
        temp = stackTop;  

        //move the stackTop to the node "under" the current top
        stackTop = stackTop->link;  

        //delete the temp node
        delete temp; 
    }
    else
        //if the stack is empty, do nothing
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
void linkedStackType<Type>::copyStack
(const linkedStackType<Type>& otherStack)
{
    //create multiple pointers for the process
    nodeType<Type>* newNode, * current, * last;

    //if the target stack (i.e. the one to be copied into) is not empty, make it empty
    if (stackTop != nullptr) 
        initializeStack();

    //if the stack to be copied is empty, we're done
    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    //otherwise begin copying the stack
    else
    {
        //set current equal to the top of the otherStack
        current = otherStack.stackTop;  

        //copy the stackTop element of the stack 
        //create the new node
        stackTop = new nodeType<Type>;  

        //copy the info fromt the otherStack node into the new stackTop
        stackTop->info = current->info; 

        //set the new stackTop link to nullptr
        stackTop->link = nullptr;

        //set last to point to the node as we move on to other nodes
        last = stackTop;       

        //move current to the next node in otherStack
        current = current->link; 

        //copy the remaining nodes of otherStack, while current still points to a node
        while (current != nullptr)
        {
            //create a new node
            newNode = new nodeType<Type>;

            //set newNode's info to current's info
            newNode->info = current->info;

            //set newNode's link to nullptr
            newNode->link = nullptr;

            //set last's link to newNode, which effectively adds newNode to the bottom of the new stack
            last->link = newNode;

            //advance last, so another node can be added to the bottom of the stack
            last = newNode;

            //advance current in otherStack
            current = current->link;
        }
    }
} //end copyStack

//copy constructor
template <class Type>
linkedStackType<Type>::linkedStackType(
    const linkedStackType<Type>& otherStack)
{
    //create a new stack
    stackTop = nullptr;

    //use the private copyStack function to duplicate the otherStack
    copyStack(otherStack);
}//end copy constructor

//destructor
template <class Type>
linkedStackType<Type>::~linkedStackType()
{
    //use initalizeStack to delete all the nodes of the stack
    initializeStack();
}//end destructor

//overloading the assignment operator
template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=
(const linkedStackType<Type>& otherStack)
{
    //avoid self-copy
    if (this != &otherStack) 
        //use the private copy stack function to rewrite the stack as otherStack
        copyStack(otherStack);

    return *this;
}//end operator=

#endif