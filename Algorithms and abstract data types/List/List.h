//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include<stdio.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;
typedef struct FILE* out;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty Queue object. 
List newList(void);

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pQ);


// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
int front(List L);

// getLength()
// Returns the length of Q.
int length(List L);

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data element at the end of Q
//void Enqueue(List Q, int data);

// Dequeue()
// Deletes element at front of Q
// Pre: !isEmpty(Q)
void deleteFront(List Q);


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints data elements in Q on a single line to stdout.
void printList(FILE* out, List Q);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);

List copyList(List L);

void deleteBack(List L);

void delete(List L);

void insertAfter(List L, int data);

void insertBefore(List L, int data);

void append(List L, int data);

void prepend(List L, int data);

void moveNext(List L);

void movePrev(List L);

void moveBack(List L);

void moveFront(List L);

void clear(List L);

int get(List L);

int back(List L);

int index(List L);


#endif