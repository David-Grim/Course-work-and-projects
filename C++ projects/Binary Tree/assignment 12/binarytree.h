//David Grim
//Assignment 12
//CS10C
//Dave Harden
//4/29/19
//binarytree.h

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <cstdlib>	// for size_t
#include "LL.h"


class binarytree {

public:
	typedef std::size_t size_type;
	binarytree();
	void insert(int item);
	void print() const;
	size_type size();
	int find(int target, bool& found) const;
	void del(int target, bool& found);
	int numPrimes();
	LL<int> toLL();
	~binarytree();
	binarytree( binarytree& copyMe);
	binarytree operator=(binarytree& right);


private:
	struct treenode {
		int data;
		treenode* left;
		treenode* right;
	};

	treenode* root;
	size_type mSize;
	static void insert_aux(treenode*& root, int item);
	static void print_aux(const treenode* root);
	static size_type size_aux(const treenode* root);
	static int find_aux(const treenode* root, int target, bool& found);
	static void del_aux(treenode*& root, int target, bool& found);
	static void remove_max(treenode*& root, int& max);
	bool isPrime(const treenode* root);
	void prime_aux(const treenode* node, int& primes);
	void LL_aux(treenode*& root, LL<int>& lList);
	void clear();
	static void clear_aux(treenode*& node);
	void clone(binarytree& copyMe);
	void clone_aux(treenode*& root, treenode*& nRoot);


};
#endif