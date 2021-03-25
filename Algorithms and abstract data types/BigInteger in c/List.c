//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
	long data;
	int index;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(long data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->index = -1;
	N->prev = NULL;

	return(N);
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL.
//Private.
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}


// freeList()
// Frees all heap memory associated with Queue *pL, and sets *pL to NULL.S
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		while (!isEmpty(*pL)) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}


// Access functions -----------------------------------------------------------

// Returns cursor element of L. Pre: length()>0, index()>=0
long get(List L) {
	if (L != NULL)
		return (L->cursor->data);

}

long back(List L) {
	if (L->length > 0) {
		return(L->back->data);
	}
	else
		return(-1);

}
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
	if (L->cursor != NULL) {
		return (L->index);
	}
	else
		return (-1);

}
// front()
// Returns the value at the front of L.
// Pre: !isEmpty(Q)
long front(List L) {
	if (L == NULL) {
		printf("Queue Error: calling getFront() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(L)) {
		printf("Queue Error: calling getFront() on an empty Queue\n");
		exit(1);
	}
	return(L->front->data);
}

// Length()
// Returns the length of L.
int length(List L) {
	if (L == NULL) {
		printf("Queue Error: calling getLength() on NULL Queue reference\n");
		exit(1);
	}
	return(L->length);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L) {
	if (L == NULL) {
		printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
		exit(1);
	}
	return(L->length == 0);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int listEquals(List A, List B) {
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL Queue reference\n");
		exit(1);
	}
	if (A->length != B->length) {
		return 0;
	}

	eq = (A->length == B->length);
	N = A->front;
	M = B->front;
	if (A->length != B->length)
		return 0;
	while (eq && N != NULL) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;

}


// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
	Node temp = L->cursor;
	moveFront(L);
	while (L->cursor != NULL) {
		fprintf(out, "%d", L->cursor->data);
		fprintf(out, " ");
		moveNext(L);
	}
	L->cursor = temp;
}


// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {

	List N = newList();
	moveFront(L);
	while (index(L) != -1) {
		append(N, get(L));
		moveNext(L);
	}

	N->cursor = NULL;
	return N;
}
// Manipulation procedures ----------------------------------------------------

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling deleteBack() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(L)) {
		printf("List Error: calling deleteBack on an empty Queue\n");
		exit(1);
	}
	if(L->cursor == L->back){
        L->index = -1;
        L->cursor = NULL;
	}
	N = L->back;
	if (L->length > 1) {
		L->back = L->back->prev;
	}
	else {
		L->front = L->back = NULL;
	}
	L->length--;
	N = NULL;
	freeNode(&N);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
	if (L->cursor == L->front) {
		deleteFront(L);
		L->length++;

	}
	else if (L->cursor == L->back) {
		deleteBack(L);
		L->length++;
	}
	else {

		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->cursor->next = NULL;
		L->cursor->prev = NULL;
		freeNode(&L->cursor);

	}
	L->cursor = NULL;
	L->length--;
}
// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, long data) {

	if (L->length <= 0) {
		printf("Error: cannot insert after cursor on an empty list");
		exit(1);
	}
	if (L->cursor == NULL) {
		printf("Error: cursor was undefined. Cannot insert after undefined cursor");
		exit(1);
	}
	if (L->cursor != L->back) {
		Node N = newNode(data);
		N->prev = L->cursor;
		N->next = L->cursor->next;
		L->cursor->next->prev = N;
		L->cursor->next = N;
		L->length++;
	}
	else {
		append(L, data);
	}

}
// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, long data) {
	Node N = newNode(data);
	N->next = L->cursor;
	if (L->cursor->prev != NULL) {
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		N->index = L->cursor->index - 1;
	}
	N->prev = L->cursor->prev;
	L->cursor->prev = N;
	if (N->prev == NULL) {
		L->front = N;
		//N->index = 0;

	}
	//L->cursor->index++;
	L->length++;
	L->index++;

}

// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, long data) {
	Node N = newNode(data);

	if (L == NULL) {
		printf("List Error: calling Enqueue() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(L)) {
		L->front = L->back = L->cursor = N;
		L->front->index = 0;
	}
	else {
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->index++;
		L->front->prev = NULL;

	}

	L->length++;
}
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor != NULL && L->cursor != L->back) {
		L->cursor = L->cursor->next;
		L->cursor->index++;
		L->index++;
	}
	else if (L->cursor != NULL && L->cursor == L->back) {

		L->cursor = NULL;
		L->index = -1;


	}

}
// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L) {
	if (L->cursor != NULL && L->cursor != L->front) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if (L->cursor != NULL && L->cursor == L->front) {
		//	L->cursor->index = -1;
		L->cursor = NULL;
		L->index = -1;

	}
	else if (L->cursor == NULL) {
		return;
	}
}
// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L) {
	if (L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.

void moveFront(List L) {
	if (L->length > 0) {
		L->cursor = L->front;
		L->index = 0;
		L->cursor->index = 0;
	}
}
// Resets L to its original empty state.
void clear(List L) {
	moveFront(L);
	while (L->cursor != NULL) {
		delete(L);
		moveNext(L);
	}
	L->cursor = NULL;
	L->back = L->front = NULL;
	L->length = 0;
}

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, long data)
{
	Node N = newNode(data);

	if (L == NULL) {
		printf("Queue Error: calling append() on NULL Queue reference\n");
		exit(1);
	}
	if (L->front == NULL) {
		L->front = L->back = L->cursor = N;
		L->index = 0;

	}
	else {
		L->back->next = N;
		N->prev = L->back;
		L->back = N;



	}
	L->length++;

}
//
// Deletes element at front of L
// Pre: !isEmpty(L)
void deleteFront(List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("List Error: calling Dequeue() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(L)) {
		printf("List Error: calling Dequeue on an empty Queue\n");
		exit(1);
	}
	if (L->cursor == L->front) {
		L->index = -1;
		L->cursor = NULL;
	}
	N = L->front;
	if (length(L) > 1) {
		L->front = L->front->next;
		L->index--;
	}
	else {
		L->front = L->back = NULL;
		L->index = 0;
	}

	L->length--;
	freeNode(&N);
}

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, long x) {
	if (length(L) > 0 && L->index >= 0) {
		L->cursor->data = x;
	}
	else
		return;

}


