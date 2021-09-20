//  This is the file LL.h

#ifndef LL_h
#define LL_h

#include <cstdio>

template <class T>
class LL {
public:
	typedef size_t size_type;
	typedef T value_type;

private:
	struct node {
		value_type data;
		node* next;
	};
	node* list;


public:
	class iterator {
	public:
		iterator(node* initial = nullptr) {
			current = initial;
		}

		value_type& operator*() const {
			return current->data;
		}

		iterator& operator++() {
			current = current->next;
			return *this;
		}

		iterator operator++(int) {
			iterator original(current);
			current = current->next;
			return original;
		}

		bool operator==(iterator other) const {
			return current == other.current;
		}

		bool operator !=(iterator other) const {
			return current != other.current;
		}

		const node* link() const {
			return current;
		}

		node*& link() {
			return current;
		}

	private:
		node* current;
	};


	class const_iterator {
	public:
		const_iterator(const node* initial = nullptr) {
			current = initial;
		}

		const value_type& operator*() const {
			return current->data;
		}

		const_iterator& operator++() {
			current = current->next;
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator original(current);
			current = current->next;
			return original;
		}

		bool operator==(const const_iterator other) const {
			return current == other.current;
		}

		bool operator !=(const const_iterator other) const {
			return current != other.current;
		}

		const node* link() const {
			return current;
		}

		node*& link() {
			return current;
		}
	private:
		const node* current;
	};  // end of iterator class declarations.  LL class continues below.

	iterator begin() {
		return iterator(list);
	}

	iterator end() {
		return iterator();
	}

	const_iterator begin() const {
		return const_iterator(list);
	}

	const_iterator end() const {
		return const_iterator();
	}

	class Empty_List_Error {};
	LL();
	LL(const LL& copyMe);
	LL operator=(const LL& right);
	~LL();
	bool empty() const;
	size_type size() const;
	void clone(const LL& copyMe);
	void clear();
	void pop_front();
	void push_front(const value_type& item);
	value_type& front();
	const value_type& front() const;
	void insert_after(iterator& position, const value_type& insertMe);
	void delete_after(iterator& position);
};


template <class T>
LL<T>::LL() {
	list = nullptr;
}

template <class T>
void LL<T>::delete_after(iterator& position) {
	assert(position.link()->next != nullptr);
	node * tempptr = position.link()->next;
	position.link()->next = position.link()->next->next;
	delete tempptr;
}



template <class T>
void LL<T>::insert_after(iterator & position, const value_type & insertMe) {
	node* newnode = new node;
	newnode->data = insertMe;
	newnode->next = position.link()->next;
	position.link()->next = newnode;
	position.link() = newnode;
}



template <class T>
void LL<T>::pop_front() {
	if (empty()) {
		throw Empty_List_Error();
	}
	else {
		node* deleteMe = list;
		list = list->next;
		delete deleteMe;
	}

}





template <class T>
typename LL<T>::value_type& LL<T>::front() {
	if (empty()) {
		throw Empty_List_Error();
	}
	else {
		return list->data;
	}
}





template <class T>
const typename LL<T>::value_type& LL<T>::front()  const {
	if (empty()) {
		throw Empty_List_Error();
	}
	else {
		return list->data;
	}
}






template <class T>
void LL<T>::clear() {
	node* deleteMe;
	while (list != nullptr) {
		deleteMe = list;
		list = list->next;
		delete deleteMe;
	}
}





// Note this is an exact copy of the clone() function from SimpleList

template <class T>
void LL<T>::clone(const LL<T> & copyMe) {
	if (copyMe.list == nullptr) {
		list = nullptr;
	}
	else {
		list = new node;
		list->data = copyMe.list->data;

		node* newListPtr = list;
		node* sourcePtr = copyMe.list->next;
		while (sourcePtr != nullptr) {
			newListPtr->next = new node;
			newListPtr = newListPtr->next;
			newListPtr->data = sourcePtr->data;
			sourcePtr = sourcePtr->next;
		}

		newListPtr->next = nullptr;
	}
}





// returns the number of items in the LL object.
template <class T>
typename LL<T>::size_type LL<T>::size() const {
	LL<T>::size_type numberOfItems = 0;
	node* curPtr = list;
	while (curPtr != nullptr) {
		++numberOfItems;
		curPtr = curPtr->next;
	}
	return numberOfItems;
}





// returns true if the LL object is empty, false otherwise.
template <class T>
bool LL<T>::empty() const {
	return list == nullptr;
}





// insert x at the front of the LL object.
template <class T>
void LL<T>::push_front(const value_type & item) {
	node* oldList = list;
	list = new node;
	list->next = oldList;
	list->data = item;
}


// THE BIG-3

template <class T>
LL<T>  LL<T>::operator=(const LL<T> & right) {
	if (this != &right) {
		clear();
		clone(right);
	}
	return *this;
}





template <class T>
LL<T>::LL(const LL<T> & copyMe) {
	clone(copyMe);
}






template <class T>
LL<T>::~LL() {
	clear();
}
#endif