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
long front(List L);

// length()
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
int listEquals(List A, List B);

List copyList(List L);

void deleteBack(List L);

void delete(List L);

void insertAfter(List L, long data);

void insertBefore(List L, long data);

void append(List L, long data);

void prepend(List L, long data);

void moveNext(List L);

void movePrev(List L);

void moveBack(List L);

void moveFront(List L);

void clear(List L);

long get(List L);

long back(List L);

int index(List L);

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, long x);


#endif