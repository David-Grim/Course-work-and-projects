//David Grim
//Assignment 12
//CS10C
//Dave Harden
//4/29/19
//binarytree.cpp

#include <iostream>
#include "binarytree.h"
#include "LL.h"
using namespace std;



binarytree::binarytree() {
	mSize = 0;
	root = nullptr;
}


void binarytree::print() const {
	print_aux(root);
}


void binarytree::insert(int item) {
	insert_aux(root, item);
}


binarytree::size_type binarytree::size() {
	mSize = size_aux(root);
	return mSize;
}


int binarytree::find(int target, bool& found) const {
	return find_aux(root, target, found);
}


void binarytree::del(int target, bool& found) {
	del_aux(root, target, found);
}


void binarytree::del_aux(treenode*& root,
	int target,
	bool& found) {

	if (root == nullptr) {
		found = false;
	}
	else if (target < root->data) {
		del_aux(root->left, target, found);
	}
	else if (target > root->data) {
		del_aux(root->right, target, found);
	}
	else if (root->left == nullptr) {
		treenode* tempptr = root;
		root = root->right;
		delete tempptr;
		found = true;
	}
	else {
		int max;
		remove_max(root->left, max);
		root->data = max;
		found = true;
	}
}

// pre: root != nullptr

void binarytree::remove_max(treenode*& root, int& max) {
	if (root->right == nullptr) {
		max = root->data;
		treenode* tempptr = root;
		root = root->left;
		delete tempptr;
	}
	else {
		remove_max(root->right, max);
	}
}



int binarytree::find_aux(const treenode* root,
	int target,
	bool& found) {

	if (root == nullptr) {
		found = false;
		return 0;
	}
	else if (target == root->data) {
		found = true;
		return root->data;
	}
	else if (target < root->data) {
		return find_aux(root->left, target, found);
	}
	else {
		return find_aux(root->right, target, found);
	}
}


binarytree::size_type binarytree::size_aux(const treenode* root) {
	if (root == nullptr) {
		return 0;
	}
	else {
		return size_aux(root->left)
			+ size_aux(root->right)
			+ 1;
	}
}


void binarytree::insert_aux(treenode*& root, int item) {
	if (root == nullptr) {
		root = new treenode;
		root->data = item;
		root->left = nullptr;
		root->right = nullptr;
	}
	else if (item <= root->data) {
		insert_aux(root->left, item);
	}
	else {
		insert_aux(root->right, item);
	}
}


void binarytree::print_aux(const treenode* root) {
	if (root != nullptr) {
		print_aux(root->left);
		cout << root->data << " ";
		print_aux(root->right);
	}
}




bool binarytree::isPrime(const treenode* root) {
	for (int i = root->data - 1; i > 1; i--) {
		if (root->data % i == 0) {
			return false;
		}
	}
	return true;
}


int binarytree::numPrimes() {
	int primes = 0;
	prime_aux(root, primes);
	return primes;

}

void binarytree::prime_aux(const treenode* root, int& primes) {
	if (root != nullptr) {
		prime_aux(root->left, primes);
		if (isPrime(root)) {
			primes++;
		}
		prime_aux(root->right, primes);
	}

}



LL<int> binarytree::toLL() {
	LL<int> lList;
	LL_aux(root, lList);
	return lList;


}

void binarytree::LL_aux(treenode*& root, LL<int>& lList) {
	if (root != nullptr) {
		LL_aux(root->right, lList);
		lList.push_front(root->data);
		LL_aux(root->left, lList);
	}
}




void binarytree::clear() {
	clear_aux(root);
}



void binarytree::clear_aux(treenode*& root) {
	if (root) {
		clear_aux(root->left);
		clear_aux(root->right);
		delete root;
	}
}



binarytree::~binarytree() {
	clear();
}


binarytree binarytree::operator=(binarytree& right) {
	if (this != &right) {
		clear();
		clone(right);
	}
	return *this;
}

binarytree::binarytree(binarytree& copyMe) {
	clone(copyMe);
}


void binarytree::clone(binarytree& copy) {
	clone_aux(root, copy.root);

}


void binarytree::clone_aux(treenode*& root, treenode*& nRoot) {
	
	if (nRoot != nullptr) {
		root = new treenode;
		root->data = nRoot->data;
		clone_aux(root->left, nRoot->left);
		clone_aux(root->right, nRoot->right);
	}
	else
		root = nullptr;
}
