#include<iostream>
#include<cassert>
#include "Sequence.h"
using namespace std;
namespace cs_sequence {
	Sequence::Sequence() {
		headPtr = nullptr;
		tailPtr = nullptr;
		cursor = nullptr;
		precursor = nullptr;
		numItems = 0;


	}
	// postcondition: The Sequence has been initialized to an empty Sequence.
	void Sequence::start() {
		cursor = headPtr;

	}
	// postcondition: The first item in the Sequence becomes the current item (but if the 
	// Sequence is empty, then there is no current item).

	void Sequence::advance() {
		assert(is_item());
		if (cursor == tailPtr) {
			precursor = cursor;
			cursor = nullptr;
		}
		else {
			precursor = cursor;
			cursor=cursor->next;
		}
		

	}
	// precondition: is_item() returns true
	// Postcondition: If the current item was already the last item in the Sequence, then there 
	// is no longer any current item. Otherwise, the new current item is the item immediately after 
	// the original current item.

	void Sequence::insert(const value_type& entry) {
		node* new_node = new node;
		new_node->data = entry;
		numItems++;

		if (cursor == headPtr || cursor == nullptr) { // insert at front (or into empty list).
			new_node->next = headPtr;                 // precursor remains nullptr.
			headPtr = new_node;
			if (numItems == 1) {
				tailPtr = new_node;
			}
		}
		else {                                       // inserting anywhere else
			new_node->next = cursor;                   // tailPtr, headPtr and precursor don't change.
			precursor->next = new_node;
		}

		cursor = new_node;
	}
	// Postcondition: A new copy of entry has been inserted in the Sequence before the 
	// current item. If there was no current item, then the new entry has been inserted at the 
	// front. In either case, the new item is now the current item of the Sequence.

	void Sequence::attach(const value_type& entry) {
		node* new_node = new node;
		new_node->data = entry;
		
		if (cursor == nullptr && numItems==0) {
			insert(entry);
		}
		else if (cursor == nullptr && numItems>=1) {
			tailPtr->next = new_node;
			cursor = new_node;
			precursor = tailPtr;
			tailPtr = new_node;

		}
		else if (cursor == tailPtr && numItems>=1) {
			cursor->next = new_node;
			precursor = cursor;
			cursor = new_node;
			tailPtr = new_node;
			tailPtr->next = nullptr;
			numItems++;
		}
		
		else {
			new_node->next = cursor->next;
			cursor->next = new_node;
			precursor = cursor;
			cursor = new_node;
			numItems++;

		}
			
	}
	// Postcondition: A new copy of entry has been inserted in the Sequence after the current 
	// item. If there was no current item, then the new entry has been attached to the end of 
	// the Sequence. In either case, the new item is now the current item of the Sequence.

	void Sequence::remove_current() {
		assert(is_item());
		if (numItems == 1) {
			
			cursor = nullptr;
			headPtr = nullptr;
			precursor = nullptr;
			tailPtr = nullptr;
			numItems--;

		}
		else if (cursor == headPtr) {
			
			headPtr = headPtr->next;
			cursor = cursor->next;
			numItems--;
			
		}
		else if(cursor == tailPtr) {
			tailPtr = precursor;
			precursor->next = nullptr;
			cursor = nullptr;
			precursor = nullptr;
			numItems--;
			
		}
		else {
			precursor->next = cursor->next;
			cursor->next = nullptr;
			cursor = precursor->next;
			numItems--;


		}
			
	}
	// Precondition: is_item returns true. 
	// Postcondition: The current item has been removed from the Sequence.  If the item removed 
	// was the last item in the Sequence, then there is now no current item.  Otherwise, the item
	// that was after the removed item is now the current item.


	size_t Sequence::size() const {
		return numItems;
	}
	// Postcondition: Returns the number of items in the Sequence.

	bool Sequence::is_item() const {
		if (cursor!=nullptr)
			return true;
		else
			return false;
	}
	// Postcondition: A true return value indicates that there is a valid "current" item that
	// may be retrieved by the current member function (listed below). A false return value
	// indicates that there is no valid current item.

	double Sequence::current() const {
		assert(is_item());
		return cursor->data;

	}
	// Precondition: is_item() returns true
	// Postcondition: The current item in the Sequence is returned.
	

	void Sequence::clear() {
		cursor = nullptr;
		precursor = nullptr;
		tailPtr = nullptr;
		while (headPtr != nullptr) {
			node* nodeToDeletePtr = headPtr;
			nodeToDeletePtr = headPtr;
			headPtr = headPtr->next;
			nodeToDeletePtr->next = nullptr;
			delete nodeToDeletePtr;
		}
		numItems = 0;
	}
		
		




	void Sequence::copy(const Sequence& copyMe) {
		numItems = copyMe.numItems;
		node* ptr = copyMe.headPtr;
		
		if (ptr == nullptr) {
			headPtr = nullptr;
			tailPtr = nullptr;
			cursor = nullptr;
			precursor = nullptr;


		}
		else {
			
			headPtr = new node;
			headPtr->data = ptr->data;
			node* ptr2 = headPtr;

			if (copyMe.cursor == ptr) {
				cursor = ptr2;
			}

			if (copyMe.precursor == ptr) {
				precursor = ptr2;
			}

			while ( ptr->next != nullptr) {
				ptr = ptr->next;
				double nextItem = ptr->data;
				node* ptr3 = new node;
				ptr3->data = nextItem;
				ptr2->next = ptr3;
				ptr2 = ptr2->next;
				if (copyMe.cursor == ptr) {
					cursor = ptr2;
				}
				if (copyMe.precursor == ptr) {
					precursor = ptr2;
				}
				
			}
			ptr2->next = nullptr;
			tailPtr = ptr2;
		}
	
	}

	Sequence::Sequence(const Sequence& copyMe) {
		copy(copyMe);
	}


	Sequence::~Sequence() {
		clear();
	}

	Sequence Sequence::operator=(const Sequence& right) {
		if (this != &right) {
			clear();
			copy(right);
		}
		return *this;

	}
}